/*
 * Este archivo es parte del proyecto display-circular.
 *
 * Este trabajo ha sido dedicado al dominio público bajo la licencia CC0 1.0 Universal.
 * Para ver una copia de esta licencia, visite:
 * https://creativecommons.org/publicdomain/zero/1.0/
 *
 * Renunciamos a todos los derechos de autor y derechos conexos en la mayor medida
 * permitida por la ley aplicable.
 *
 * Autor: Javier Rambaldo
 * Fecha: 1 de julio de 2024
 */

#include <Arduino.h>
#include "utiles/debug.h"
#include "display/DisplayTFT.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);
    display.init();

    // muestro una sola vez el ojo entero:
    display.showGIMPImage(0, 0, &ojo_img);
}

int y = 0;
void loop()
{
    if (++y % 2 == 0)
    {
        // Muestra la imagen en pantalla, pero primero restaura la pantalla con el rectangulo de la imagen del background.
        int x = 43 + esp_random() % 69;
        int y = 43 + esp_random() % 69;
        display.copyImage(x, y, &pupila_img, &ojo_img);
        delay(1600);
    }
}
