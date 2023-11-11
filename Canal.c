#include    <xc.h>
#include    <pic16f887.h>
#include    "CONFIG.h"

// Configura el módulo ADC para su uso
void adc_begin(void) {
    ADCON1bits.ADFM = 0;    // Justificación izquierda (modo de 8 bits).
    ADCON1bits.VCFG0 = 0;   // Selecciona voltajes de referencia (5V a 0V).
    ADCON1bits.VCFG1 = 0;   // Selecciona voltajes de referencia (5V a 0V).
    ADCON0bits.ADCS = 0b01; // Tiempo de conversión Fosc/8.
}

// Realiza una conversión ADC en el canal especificado
int adc_conversion(int canal) {
    ADCON0bits.CHS = (0x0F & canal); // Selecciona el canal de entrada
    ADCON0bits.ADON = 1;             // Habilita el módulo ADC.
    __delay_us(30);
    ADCON0bits.GO = 1;               // Inicia la conversión ADC.
    
    while (ADCON0bits.GO);           // Espera a que termine la conversión ADC.
    
    ADCON0bits.ADON = 0;             // Deshabilita el módulo ADC.
    return ADRESH;                   // Retorna el resultado de la conversión ADC de 8 bits.
}
