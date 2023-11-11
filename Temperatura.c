#include    <xc.h>
#include    <pic16f887.h>
#include    "CONFIG.h"
#include    <math.h>
#define     beta  4090 

// Función para convertir el valor del sensor de temperatura a grados Celsius
int conversor_Temperatura(int temperatura) {
    // Constante beta para el cálculo de temperatura
    long beta = 3975;

    // Ajusta el valor de temperatura para el cálculo
    long a = temperatura - 250;

    // Calcula la temperatura en grados Celsius utilizando la fórmula de Steinhart-Hart
    // y la convierte a un entero antes de devolverla
    float TempC = (float)(beta / (log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0);
    
    // Retorna la temperatura en grados Celsius como un entero
    return (int) TempC;
}
