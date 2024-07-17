//                            USER DEFINED SETTINGS
// Este esta copiado del original, para que no se reemplace con las actualizaciones de la libreria.
// Javier.

// User defined information reported by "Read_User_Setup" test & diagnostics example
#define USER_SETUP_INFO "Javier_Setup"

// Define to disable all #warnings in library (can be put in User_Setup_Select.h)
#define DISABLE_ALL_LIBRARY_WARNINGS

#define GC9A01_DRIVER

#define TFT_CS   39  // Chip select control pin
#define TFT_DC   40  // Data Command control pin
#define TFT_MOSI 41  // SDA
#define TFT_SCLK 42  // SCL
#define TFT_MISO -1  // no se usa
#define TFT_RST  -1  // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts
#define SMOOTH_FONT

#define SPI_FREQUENCY       40000000

#define SPI_READ_FREQUENCY  20000000

#define SPI_TOUCH_FREQUENCY 2500000

// #define SUPPORT_TRANSACTIONS
