#include    <xc.h>
#include    <pic16f887.h>
#include    <string.h>
#include    <stdio.h>
#include    "CONFIG.h"
#include    "Canal.h"
#include    "Temperatura.h"
#include    "LCD.h"

// Variables globales para almacenar valores de sensores y un buffer de texto
int Temperatura;
int Fotocelda;
int Fuego;
char buffer[17];

// Función para monitorear el entorno ambiental
unsigned char Funcion_Monitoreo_Ambiental(void) {
    // Convierte la temperatura a grados Celsius utilizando la función conversor_Temperatura()
    int TempC = conversor_Temperatura(Temperatura);

    // Variable local para el estado del sensor ambiental
    unsigned char var_Sensor_Ambiental = 0;

    // Verifica si la temperatura es mayor o igual a 30 grados Celsius
    if (TempC >= 30) {
        // Muestra un mensaje en el LCD indicando que se está monitoreando el entorno ambiental
        LCD_String_xy(0, 0, "MONIT AMBIENTAL");
        __delay_ms(2000);

        // Realiza conversiones ADC para obtener los valores de los sensores
        Temperatura = adc_conversion(0);
        Fotocelda = adc_conversion(1);
        Fuego = adc_conversion(4);

        // Crea una cadena de texto con los valores de temperatura, fuego y fotocelda
        int n = sprintf(buffer, "T=%d,Fg=%d,F=%d", TempC, Fuego, Fotocelda);

        // Muestra la cadena en el LCD
        LCD_String_xy(1, 0, buffer);
        __delay_ms(2000);
        LCD_Clear();

        // Actualiza la variable local para indicar un estado de sensor ambiental normal
        var_Sensor_Ambiental = 1;
    }

    // Retorna el estado del sensor ambiental
    return var_Sensor_Ambiental;
}
