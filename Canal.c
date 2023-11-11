#include    <xc.h>
#include    <pic16f887.h>
#include    "CONFIG.h"

// Configura el m�dulo ADC para su uso
void adc_begin(void) {
    ADCON1bits.ADFM = 0;    // Justificaci�n izquierda (modo de 8 bits).
    ADCON1bits.VCFG0 = 0;   // Selecciona voltajes de referencia (5V a 0V).
    ADCON1bits.VCFG1 = 0;   // Selecciona voltajes de referencia (5V a 0V).
    ADCON0bits.ADCS = 0b01; // Tiempo de conversi�n Fosc/8.
}

// Realiza una conversi�n ADC en el canal especificado
int adc_conversion(int canal) {
    ADCON0bits.CHS = (0x0F & canal); // Selecciona el canal de entrada
    ADCON0bits.ADON = 1;             // Habilita el m�dulo ADC.
    __delay_us(30);
    ADCON0bits.GO = 1;               // Inicia la conversi�n ADC.
    
    while (ADCON0bits.GO);           // Espera a que termine la conversi�n ADC.
    
    ADCON0bits.ADON = 0;             // Deshabilita el m�dulo ADC.
    return ADRESH;                   // Retorna el resultado de la conversi�n ADC de 8 bits.
}
