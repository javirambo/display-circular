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

void setup()
{
    Serial.begin(115200);
    pinMode(0, INPUT_PULLUP);
    delay(1000);
    Serial.println("Listo");
}

void loop() {}
