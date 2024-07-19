#include "GimpImage.h"

GimpImage_t ojo_img   = {.width = OJO_WIDTH, .height = OJO_HEIGHT, .size = OJO_WIDTH * OJO_HEIGHT, .pixel_data = (uint16_t*)OJO_PIXEL_DATA};
GimpImage_t pupila_img = {.width = PUPILA_WIDTH, .height = PUPILA_HEIGHT, .size = PUPILA_WIDTH * PUPILA_HEIGHT, .pixel_data = (uint16_t*)PUPILA_PIXEL_DATA};
