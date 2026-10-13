// w_file_mem_load
// Load doom wad file to memory in bulk.

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pff3a/diskio.h>

#include "w_file.h"
#include "deh_str.h"
#include "z_zone.h"

extern const unsigned char _binary_doom1_wad_start[];
extern const unsigned char _binary_doom1_wad_end[];

typedef struct
{
    wad_file_t wad;
} mem_load_wad_file_t;

extern wad_file_class_t mem_load_wad_file;

FATFS *p_wad_file_sys = NULL;
byte *p_wad_buffer = NULL;

int wad_bulk_read(byte *p_buf);

// new version that will mount, open and read the SDCARD.
static wad_file_t *W_mem_load_OpenFile(char *path)
{
    int error;
    unsigned int len = 0;
    mem_load_wad_file_t *result;

    if(path == NULL) return NULL;
    
    if(p_wad_file_sys == NULL)
    {
      DEH_printf(" Opening WAD file\n");

      p_wad_file_sys = malloc(sizeof(FATFS));
      
      if(p_wad_file_sys == NULL) return NULL;
      
      error = pf_mount(p_wad_file_sys);
  
      if(error) 
      {
        free(p_wad_file_sys);
        p_wad_file_sys = NULL;
        return NULL;
      }
    
      error = pf_open(path);
      
      if(error)
      {
        free(p_wad_file_sys);
        p_wad_file_sys = NULL;
        return NULL;
      }

      DEH_printf(" Creating WAD file buffer\n");

      p_wad_buffer = Z_Malloc(p_wad_file_sys->fsize, PU_STATIC, 0); //malloc(sizeof(p_wad_file_sys->fsize));

      if(p_wad_buffer == NULL)
      {
        free(p_wad_file_sys);
        p_wad_file_sys = NULL;
        return NULL;
      }

      DEH_printf(" Load WAD file buffer - ");
      fflush(stdout);

      error = wad_bulk_read(p_wad_buffer);

      if(error)
      {
        DEH_printf(" Failed WAD file load\n");
        free(p_wad_file_sys);
        Z_Free(p_wad_buffer);
        p_wad_file_sys = NULL;
        p_wad_buffer = NULL;
        return NULL;
      }
    }

    DEH_printf("\n");

    DEH_printf(" Map WAD file result\n");

    result = Z_Malloc(sizeof(mem_load_wad_file_t), PU_STATIC, 0);

    result->wad.file_class = &mem_load_wad_file;
    result->wad.mapped = p_wad_buffer;
    result->wad.length = p_wad_file_sys->fsize;

    return &result->wad;
}

//alter for memory load only once... this should only be called on exit.
static void W_mem_load_CloseFile(wad_file_t *wad)
{
    mem_load_wad_file_t *e = (mem_load_wad_file_t *)wad;
    Z_Free(e);
}

// copy pasta from embedded read.
static size_t W_mem_load_Read(wad_file_t *wad, unsigned int offset,
                             void *buffer, size_t buffer_len)
{
    void *p_base = NULL;
    size_t avail_data;

    if (offset >= wad->length) return 0;

    p_base = wad->mapped + offset;

    if(p_base == NULL) return 0;

    avail_data = wad->length - offset;

    buffer_len = (buffer_len > avail_data ? avail_data : buffer_len);

    memcpy(buffer, p_base, buffer_len);

    // for(int index = 0; index < buffer_len; index++)
    // {
    //   ((byte *)buffer)[index] = ((byte *)p_base)[index];
    // }

    return buffer_len;
}

int wad_bulk_read(byte *p_buf)
{
  int error = 0;
  unsigned int len = 0;
  unsigned int total_len = 0;

  do
  {
    error = pf_read(p_buf, 512, &len);

    total_len += len;

    if((total_len%524288) == 0)
    {
      DEH_printf(".");
      fflush(stdout);
    }
    
    if(error) break;
    
    p_buf += len;
  }
  while(len >= 512);
  
  return error;
}

wad_file_class_t mem_load_wad_file =
{
    W_mem_load_OpenFile,
    W_mem_load_CloseFile,
    W_mem_load_Read,
};
