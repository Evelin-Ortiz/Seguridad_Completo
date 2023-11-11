#include <xc.h>
#include "CONFIG.h"
#include "Color_RGB.h"

// Funci�n para configurar el color en un led RGB
void Color(unsigned char red, unsigned char green, unsigned char blue) {
    ldatae = 0;   // Desactiva la transmisi�n de datos al LCD (presumiblemente).
    ROJO = red;    // Configura la intensidad del color rojo.
    VERDE = green; // Configura la intensidad del color verde.
    AZUL = blue;   // Configura la intensidad del color azul.
}
