/*
  DisplayTFT.h
  Permite utilizar un display TFT ILI9341
  y acomodar los objetos en pantalla.
  Específicamente para el proyecto PIG GUARD de Inventu.

  ----------------------------------------------------
  IMPORTANTE:
  No olvidarse de colocar esto en el .ini:

  build_flags =
    -DUSER_SETUP_LOADED                  <== DESDE ACA ES SOLO PARA EL DISPLAY
    -DDISABLE_ALL_LIBRARY_WARNINGS=1
    -DGC9A01_DRIVER=1
    -DTFT_CS=39
    -DTFT_DC=40
    -DTFT_MOSI=7
    -DTFT_SCLK=15
    -DTFT_MISO=6
    -DTFT_RST=-1
    -DLOAD_GFXFF=1
    -DSPI_FREQUENCY=16000000
    -DSPI_READ_FREQUENCY=20000000
    -DSPI_TOUCH_FREQUENCY=2500000
    -DTOUCH_CS=-1                        <== HASTA ACA
  ----------------------------------------------------

  JJTeam 2021
*/

#ifndef _display_tft_h
#define _display_tft_h
#include <TFT_eSPI.h>
#include "GimpImage.h"
#include <vector>

class Display
{
   private:
    bool tftInitialized = false;  // por si no se conecta el display
    uint16_t bgColor    = TFT_BLACK;
    uint16_t textColor  = TFT_WHITE;
    std::vector<String> logs;
    std::vector<uint16_t> colores;
    uint16_t bufferImg[320 * 80];  // buffer (de 1/3 de tamaño de la pantalla)

    void addLinesToLog(uint16_t color, String &txt);

    //  TFT_WIDTH  240 x  TFT_HEIGHT 240

   public:
    const int altoStatusBar       = 18;
    const int altoFont            = 8;
    const int cantidadLineasDeLog = 27;

    TFT_eSPI tft = TFT_eSPI();  // Use hardware SPI
    bool isOk    = false;

    void init();
    void clearScreen(uint16_t color);
    void print(uint16_t color, String txt);
    void showGIMPImage(int x, int y, const GimpImage_t *image);
    void showGIMPImageTransp(int x1, int y1, const GimpImage_t *image);  // el color transparente es el WHITE
    void copyImage(int x, int y, const GimpImage_t *image, const GimpImage_t *backImg);
};

//-- unica instancia para todo el proyecto...
extern Display display;

#endif  // _display_tft_h