#include <SPI.h> // ini untuk memori external 
#include <SPIMemory.h>

SPIFlash memory;
#define eraseSec(x) memory.eraseSector(x)

