/*
  DisplayTFT.cpp
  Permite utilizar un display TFT ILI9341
  y acomodar los objetos en pantalla.
  Específicamente para el proyecto PIG GUARD de Inventu.

  ----------------------------------------------------
  IMPORTANTE:
  Quitar de User_Setup.h todos los define y colocarlos en playformio.ini

  Estos son los pines a usar:
    -DTFT_MOSI=23
    -DTFT_MISO=19
    -DTFT_CS=26
    -DTFT_SCLK=18
    -DTFT_DC=4
    -DTFT_RST=-1
    -DSPI_FREQUENCY=40000000
    -DSPI_READ_FREQUENCY=20000000
  ----------------------------------------------------

  JJTeam 2021
*/

#include "DisplayTFT.h"
#include "utiles/debug.h"
#include "utiles/SplitString.h"
#include <vector>

// construct only with the background color
void Display::init()
{
    tftInitialized = true;
    tft.begin();
    tft.setRotation(1);
    tft.setSwapBytes(true);
    isOk = true;  // isWorking();
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(TL_DATUM);  // Set text datum to Top Left
    clearScreen(TFT_BLACK);
}

// de alguna forma tengo que determinar si existe el display...
// bool Display::isWorking()
// {
//     for (int z = 0; z < 5; z++)
//     {
//         for (int x = 0; x < 20; x++)
//             for (int y = 0; y < 15; y++) tft.fillRect(x * 16, y * 16, 16, 16, tft.color565(random(0xff), random(0xff), random(0xff)));
//         delay(100);
//     }
//     tft.drawPixel(1, 1, TFT_RED);
//     uint16_t pix = tft.readPixel(1, 1);
//     return tftInitialized && pix == TFT_RED;
// }

// borra toda la pantalla (incluida la status bar).
void Display::clearScreen(uint16_t color)
{
    if (!tftInitialized) return;

    // status bar:
    tft.fillRect(0, 0, tft.width(), altoStatusBar, TFT_BLACK);
    // texto:
    bgColor = color;
    tft.fillRect(0, altoStatusBar, tft.width(), tft.height() - altoStatusBar, bgColor);

    logs.clear();
    colores.clear();
}

void Display::addLinesToLog(uint16_t color, String &txt)
{
    // si la linea tiene mas de 52 caracteres la divido en varias lineas.
    // (porque no entran mas de 52 en el display)
    char buf[55];
    char *s = buf;
    char *p = (char *)txt.c_str();
    int l   = 0;
    while ((*s = *p))
    {
        if (*s == '\t') *s = ' ';
        s++;
        p++;
        l++;
        if (l >= 52)  // corto la linea y la agrego al log.
        {
            *s = 0;
            logs.push_back(buf);
            colores.push_back(color);
            l = 0;
            s = buf;
        }
    }
    logs.push_back(buf);  // agrego la ultima (o unica) linea de log.
    colores.push_back(color);
}

void Display::print(uint16_t color, String txt)
{
    if (!tftInitialized) return;

    addLinesToLog(color, txt);

    // y dejo solo las ultimas lineas que puedo mostrar.
    if (logs.size() > cantidadLineasDeLog)
    {
        logs.erase(logs.begin(), logs.begin() + logs.size() - cantidadLineasDeLog);
        colores.erase(colores.begin(), colores.begin() + colores.size() - cantidadLineasDeLog);
    }

    // borro toda el area a escribir.
    tft.fillRect(0, altoStatusBar, tft.width(), tft.height() - altoStatusBar, bgColor);

    // muestro todas las lineas posibles:
    int y = altoStatusBar + 1;
    for (int i = 0; i < logs.size(); i++, y += altoFont)
    {
        tft.setTextColor(colores[i]);
        tft.drawString(logs[i], 0, y, 1);
    }
}

void Display::showGIMPImage(int x1, int y1, const GimpImage_t *image)
{
    if (!tftInitialized) return;
    tft.setAddrWindow(x1, y1, image->width, image->height);
    tft.pushColors(image->pixel_data, image->size, true);
}

void Display::showGIMPImageTransp(int x1, int y1, const GimpImage_t *image)
{
    if (!tftInitialized) return;
    tft.pushImage(x1, y1, image->width, image->height, image->pixel_data, TFT_WHITE);  // el color transparente es el WHITE
}

void Display::copyImage(int x, int y, const GimpImage_t *image, const GimpImage_t *backImg)
{
    static int xAnt = -1, yAnt = -1;

    if (xAnt >= 0)  // la primera vez no se copia.
    {
        // copio un rect de una imagen a un rect de la pantalla:
        for (int yy = 0; yy < image->height; yy++)
        {
            display.tft.setAddrWindow(xAnt, yy + yAnt, image->width, 1);
            display.tft.pushColors(backImg->pixel_data + xAnt + ((yy + yAnt) * backImg->width), image->width, true);
        }
    }
    xAnt = x;
    yAnt = y;
    display.showGIMPImageTransp(x, y, image);
}

//-- unica instancia para todo el proyecto...
Display display;
