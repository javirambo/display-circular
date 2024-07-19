#pragma once
#include <stdint.h>
#include "iconos/ojo.h"
#include "iconos/pupila.h"

typedef struct
{
    uint16_t width;
    uint16_t height;
    uint32_t size;         // ya esta calculado (cantidad de pixels)
    uint16_t* pixel_data;  // ojo!! cada pixel es de 16 bits!!
} GimpImage_t;

/*
    Estas imagenes fueron tomadas con GIMP con la opcion:
    - Exportar imagen -> Codigo fuente en C -> y marcar:
        - guardar como RGB565,
        - usar macros en vez de struct.
    - Solo uso el array de datos.
    - (sacar el static)
*/

extern GimpImage_t ojo_img;
extern GimpImage_t pupila_img;
