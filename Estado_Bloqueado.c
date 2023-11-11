/*
 * File:   Estado_Bloqueado.c
 * Author: evelin
 *
 * Created on 6 de octubre de 2023, 03:28 PM
 */


#include <xc.h>
#include "CONFIG.h"
#include "LCD.h"
#include "Color_RGB.h"

// Función para indicar que el sistema está bloqueado
void Funcion_Bloqueado(void) {
    // Limpia la pantalla LCD
    LCD_Clear();

    // Muestra un mensaje en el LCD indicando que el sistema está bloqueado
    LCD_String_xy(0, 0, "SISTEMA BLOQUEADO ^-^");

    // Cambia el color a rojo
    Color(1, 0, 0);

    // Espera 500 milisegundos (0.5 segundos)
    __delay_ms(500);

    // Restaura el color (apagado)
    Color(0, 0, 0);

    // Espera 1000 milisegundos (1 segundo)
    __delay_ms(1000);
}
