/*
 * File:   Estado_Monitoreo.c
 * Author: Evelin Ortiz-Oscar Matabajoy
 *
 * Created on 6 de octubre de 2023, 03:34 PM
 */

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "Sensor.h"
#include "LCD.h"

// Variables globales para los estados de los sensores
unsigned char var_sensor_ir = 0;
unsigned char var_sensor_hall = 0;
unsigned char var_sensor_metal = 0;

// Buffer para almacenar texto
char buffer[17];

unsigned char Funcion_Monitoreo(void) {
    // Variable local para el estado general del sensor
    unsigned char var_Sensor = 0;

    // Lee los estados de los sensores
    var_sensor_ir = SENSOR_IR;
    var_sensor_hall = SENSOR_HALL;
    var_sensor_metal = SENSOR_METAL;

    // Verifica el estado general utilizando la función monitoring_sensor()
    if (monitoring_sensor() == 0) {
        // Muestra un mensaje en el LCD indicando que el monitoreo es normal
        LCD_String_xy(0, 0, "MONITOREO NOR");
        __delay_ms(2000);
        LCD_Clear();

        // Crea una cadena de texto con los estados individuales de los sensores
        sprintf(buffer, "ir=%d,hl=%d,mt=%d", var_sensor_ir, var_sensor_hall, var_sensor_metal);

        // Muestra la cadena en el LCD
        LCD_String_xy(0, 0, buffer);
        __delay_ms(1000);
        LCD_Clear();

        // Actualiza la variable local para indicar un estado de sensor normal
        var_Sensor = 1;
    }

    // Retorna el estado del sensor
    return var_Sensor;
}
