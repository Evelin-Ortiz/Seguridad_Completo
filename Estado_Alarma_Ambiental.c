/*
 * File:   Estado_Alarma.c
 * Author: evelin
 *
 * Created on 6 de octubre de 2023, 04:45 PM
 */


#include <xc.h>
#include "CONFIG.h"
#include "Color_RGB.h"
#include "LCD.h"

// Función para activar una alarma ambiental (presumiblemente visual y sonora)
void Funcion_Alarma_Ambiental(void) {
    int o;

    // Repite el siguiente bloque de código 5 veces
    for (o = 0; o < 5; o++) {
        // Muestra un mensaje en el LCD indicando que la alarma ambiental está activada
        LCD_String_xy(0, 0, "Alarm Amb Activ");

        // Cambia el color a rojo
        Color(1, 0, 0);

        // Espera 500 milisegundos (0.5 segundos)
        __delay_ms(500);

        // Restaura el color (apagado)
        Color(0, 0, 0);

        // Espera 500 milisegundos (0.5 segundos)
        __delay_ms(500);

        // Limpia la pantalla LCD
        LCD_Clear();
    }
}


