
#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"
#include "i_video.h"

#include <base.h>
#include <riscv-csr.h>
#include <axi_tft.h>
#include <gpio.h>
#include <plic.h>
#include <clint.h>
#include <irq/vector-table.h>

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define TFT_XRES      640
#define TFT_XRES_VIR  1024

struct s_axi_tft *gp_axi_tft = NULL;
struct s_gpio   *gp_gpio = NULL;
struct s_plic   *gp_plic = NULL;
struct s_clint  *gp_clint = NULL;

// Global to hold current timestamp, written in MTI handler.
static volatile uint64_t timestamp = 0;
static volatile uint64_t milliseconds = 0;

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned char convertToDoomKey(uint32_t key)
{
  if(key & (1 << 0)) return KEY_ENTER;
  
  if(key & (1 << 1)) return KEY_UPARROW;
  
  if(key & (1 << 2)) return KEY_LEFTARROW;
  
  if(key & (1 << 3)) return KEY_RIGHTARROW;
  
  if(key & (1 << 4)) return KEY_DOWNARROW;
  
  if(key & (1 << 5)) return KEY_FIRE;
  
  if(key & (1 << 6)) return KEY_USE;
  
  if(key & (1 << 7)) return KEY_RSHIFT;
  
  return 0;
}

static void addKeyToQueue(int pressed, uint32_t keypress)
{
  unsigned char key = convertToDoomKey(keypress);

  s_KeyQueue[s_KeyQueueWriteIndex] = (pressed << 8) | key;
  s_KeyQueueWriteIndex++;
  s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

static void handleKeyInput(uint32_t keypress)
{
  int index = 0;
  static uint32_t prev_keypress = 0;
  
  if(prev_keypress != keypress)
  {
    for(index = 0; index < 8; index++)
    {
      if(((prev_keypress >> index) & 1) != ((keypress >> index) & 1))
      {
        addKeyToQueue(((keypress >> index) & 1), (((keypress >> index) & 1) ? keypress : prev_keypress));
      }
    }
  }
  
  prev_keypress = keypress;
}

void writeVRAM(struct s_axi_tft *p_axi_tft, void *p_buffer)
{
  uint16_t x_cor = 0;
  uint16_t y_cor = DOOMGENERIC_RESY;
  struct color c;

  //Get start address
  uint32_t *p_vram = (uint32_t *)p_axi_tft->addr;
  uint8_t *p_temp = (uint8_t *)p_buffer;

  while(y_cor--)
  {
    for(x_cor = 0; x_cor < DOOMGENERIC_RESX; x_cor++)
    {
      c = colors[p_temp[x_cor]];
      
      p_vram[x_cor] = (c.r << 16) |
                      (c.g <<  8) |
                      (c.b <<  0);
    }

    p_temp += DOOMGENERIC_RESX;
    
    //update pointer to new x plus offset unused virtual pixes.
    p_vram += XRES_VIR;
  }
}

void DG_Init()
{
  gp_axi_tft = initAxiTft(TFT_ADDR);

  writeAxiTftVRAMconst(gp_axi_tft, 0, 0, 640*480);

  gp_gpio = initGpio(GPIO_ADDR);

  gp_gpio->tri1 = 0x000000FF;

  gp_clint = initClint(CLINT_ADDR);

  // Setup timer for 1 second interval
  timestamp = getClintMTime(gp_clint);

  setClintMTimeCmpOffset(gp_clint, calcMtimecmpMilliseconds(BUS_FREQ_HZ, 1));
  
  gp_plic  = initPlic(PLIC_ADDR);

  // setup plic to enable interrupt 2, axi tft.
  gp_plic->priority2 = 7;

  gp_plic->threshold = 0;

  gp_plic->enable1.bits.i2 = 1;
  
  setAxiTftIntrEna(gp_axi_tft);
}

void DG_SleepMs(uint32_t ms)
{
  uint64_t prev_milliseconds = milliseconds;

  while((milliseconds-prev_milliseconds) > ms)
  {
    __asm__ volatile ("wfi");
  }
}

uint32_t DG_GetTicksMs()
{
  return milliseconds;
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
  if (s_KeyQueueReadIndex != s_KeyQueueWriteIndex)
  {
    unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
    s_KeyQueueReadIndex++;
    s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

    *pressed = keyData >> 8;
    *doomKey = keyData & 0xFF;

    return 1;
  }

  return 0;
}

void DG_SetWindowTitle(const char * title)
{
  (void) title;
  return;
}

int main(int argc, char **argv)
{
    (void) argv;
    (void) argc;

    char *emb_argv[] = {"DOOM","-iwad","DOOM1.WAD","-nosound",};
    int emb_argc = 3;
    
    doomgeneric_Create(emb_argc, emb_argv);

    for (int i = 0; ; i++)
    {
        doomgeneric_Tick();
    }
    
    return 0;
}

#pragma GCC push_options
// Force the alignment for mtvec.BASE. A 'C' extension program could be aligned to to bytes.
#pragma GCC optimize ("align-functions=4")
// The 'riscv_mtvec_mei' function is added to the vector table by the vector_table.c
void riscv_mtvec_mei(void)
{
  uint32_t claim_num = 0;

  claim_num = gp_plic->claim;

  if(gp_axi_tft->iesr.bits.ie && gp_axi_tft->iesr.bits.status && DG_ScreenBuffer_Valid)
  {
    writeVRAM(gp_axi_tft, DG_ScreenBuffer);
    
    DG_ScreenBuffer_Valid = 0;
    
    handleKeyInput(gp_gpio->data1 & 0x000000FF);
  }

  gp_plic->claim = claim_num;
}

// The 'riscv_mtvec_mti' function is added to the vector table by the vector_table.c
void riscv_mtvec_mti(void)
{
  milliseconds++;

  // Timer exception, re-program the timer for a one second tick.
  timestamp = getClintMTime(gp_clint);

  setClintMTimeCmpOffset(gp_clint, calcMtimecmpMilliseconds(BUS_FREQ_HZ, 1));
}
