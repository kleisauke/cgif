#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "cgif.h"

#define WIDTH  99
#define HEIGHT 99

int main(void) {
  GIF*          pGIF;
  GIFConfig     gConfig;
  FrameConfig   fConfig;
  uint8_t*      pImageData;
  uint8_t       aPalette[] = {
    0x00, 0x00, 0x00, // black (transparent)
    0xFF, 0xFF, 0xFF, // white
  };

  memset(&gConfig, 0, sizeof(GIFConfig));
  memset(&fConfig, 0, sizeof(FrameConfig));
  gConfig.attrFlags               = GIF_ATTR_IS_ANIMATED | GIF_ATTR_HAS_TRANSPARENCY;  // first entry in color table is transparency
  gConfig.width                   = WIDTH;
  gConfig.height                  = HEIGHT;
  gConfig.pGlobalPalette          = aPalette;
  gConfig.numGlobalPaletteEntries = 2;
  gConfig.path                    = "has_transparency.gif";
  //
  // create new GIF
  pGIF = cgif_newgif(&gConfig);
  //
  // add frames to GIF
  pImageData = malloc(WIDTH * HEIGHT);
  memset(pImageData, 0, WIDTH * HEIGHT);
  fConfig.pImageData = pImageData;
  fConfig.delay      = 100;
  // create an off/on pattern
  for (int i = 0; i < (WIDTH * HEIGHT); ++i) {
    pImageData[i] = i % 2;
  }
  cgif_addframe(pGIF, &fConfig);
  // create opposite pattern
  for (int i = 0; i < (WIDTH * HEIGHT); ++i) {
    pImageData[i] = 1 - (i % 2);
  }
  cgif_addframe(pGIF, &fConfig);
  free(pImageData);
  //
  // write GIF to file
  cgif_close(pGIF);
  return 0;
}
