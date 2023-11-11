/*
 * File:   Estado_Seguridad.c
 * Author: evelin
 *
 * Created on 6 de octubre de 2023, 02:53 PM
 */


#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "Color_RGB.h"
#include "Estado_Bloqueado.h"
#include "Estado_Monitoreo.h"

// Contraseña predefinida
const char password[5] = {'1', '5', '9', '8', 0};

// Almacena la contraseña ingresada por el usuario
char pass_user[5];

// Índice para rastrear la posición actual al ingresar la contraseña
unsigned char idx = 0;

// Número de intentos permitidos
unsigned char intentos = 4;

// Función para verificar la seguridad ingresando una contraseña
unsigned char Funcion_Seguridad(void) {
    // Variable local para indicar el estado del sistema de seguridad
    unsigned char Seguro_Activo = 0;

    // Carácter ingresado por el usuario
    char key = '0';

    // Limpia la pantalla LCD
    LCD_Clear();        

    // Verifica si hay intentos restantes
    if (intentos > 0) {
        // Muestra un mensaje en el LCD para ingresar la clave
        LCD_String_xy(0, 0, "INGRESE CLAVE");
        LCD_Command(0xC0); 

        // Captura la clave ingresada por el usuario
        do {
            key = keypad_getkey();
            if (key != 0) {
                LCD_Char('*');  // Muestra asteriscos en lugar de la clave ingresada
                pass_user[idx++] = key;
            }
            __delay_ms(100);
        } while (idx < 4);

        // Compara la clave ingresada con la contraseña predefinida
        if (strncmp(pass_user, password, 4) == 0) {
            // La clave es correcta
            LCD_Clear();
            LCD_String_xy(0, 0, "Clave Correcta :D");
            Color(0, 1, 0);  // Cambia el color a verde
            __delay_ms(1000);
            Color(0, 0, 0);  // Restaura el color 
            Seguro_Activo = 1;  // Indica que el sistema de seguridad está activo
            idx = 0;
        } else {
            // La clave es incorrecta
            LCD_Clear();
            LCD_String_xy(0, 0, "Clave Incorrecta :C");
            Color(0, 0, 1);  // Cambia el color a azul
            __delay_ms(1000);
            Color(0, 0, 0);  // Restaura el color 
            LCD_Clear();
            idx = 0;
            __delay_ms(2000);
            intentos--;  // Decrementa el número de intentos restantes
        }

        // Verifica si se han agotado los intentos
        if (intentos == 0) {
            Seguro_Activo = 2;  // Indica que el sistema está bloqueado debido a demasiados intentos fallidos
            idx = 0;  // Reinicia el índice
        } // Retorna el estado del sistema de seguridad
    return Seguro_Activo;
    }
//si no funciona aqui iba return^  
}
