#include <stdio.h>

#include "m_argv.h"
#include "z_zone.h"
#include "doomgeneric.h"

// pixel_t* DG_ScreenBuffer = NULL;
uint8_t  DG_ScreenBuffer_Valid = 0;

void M_FindResponseFile(void);
void D_DoomMain (void);

void doomgeneric_Create(int argc, char **argv)
{
  // save arguments
  myargc = argc;
  myargv = argv;

  M_FindResponseFile();

  DG_ScreenBuffer_Valid = 0;

  DG_Init();

  D_DoomMain ();
}

