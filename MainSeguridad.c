/*!
\file   seguridad.c
\date   2023-10-04
\author Evelin Ortiz-Oscar Matabajoy 
\brief  Security House.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2022. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/
#include <xc.h>
#include <pic16f887.h>  // Archivo de definiciones para PIC16f887
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "Color_RGB.h"
#include "Sensor.h"
#include "Estado_Seguridad.h"
#include "Estado_Bloqueado.h"
#include "Estado_Monitoreo.h"
#include "Estado_Alarma.h"
#include "Canal.h"
#include "Temperatura.h"
#include "Estado_Monitoreo_Ambiental.h"
#include "Estado_Alarma_Ambiental.h"

enum State{
    Seguridad,
    Monitoreo,
    Monitoreo_Ambiental,
    Bloqueado,
    Alarma,
    Alarma_Ambiental
};

enum State Estado;

void main() {
    // Configuración del microcontrolador
    OSCCON = 0x71;  // Configura oscilador interno (FOSC = 8Mhz)
    TRISD  = 0x00;  // Configura puerto D como salida
    TRISA0 = 1;     // Configura RA0 como entrada
    TRISA1 = 1;     // Configura RA1 como entrada
    TRISA5 = 1;     // Configura RA5 como entrada
    TRISC = 0x07;   // Configura primeros tres bits de RC como entrada
    ANSEL  = 0x01;  // Configura el puerto como entrada analógica
    
    // Inicialización de periféricos
    adc_begin();    // Inicia el convertidor analógico a digital
    LCD_Init();     // Inicializa el LCD
    keypad_init();  // Inicializa el teclado
    
    Estado = Seguridad;  // Establece el estado inicial del sistema como "Seguridad"
           
    while (1) {
         // Máquina de estados
        if(Estado == Seguridad){
            unsigned char n = Funcion_Seguridad();       // Llama a la función de seguridad
            if(n == 1){
                Estado = Monitoreo;                     // Cambia al estado de monitoreo si la función devuelve 1
            } else if(n == 2){
                Estado = Bloqueado;                    // Cambia al estado bloqueado si la función devuelve 2
            }   
        } else if(Estado == Bloqueado){
            Funcion_Bloqueado();                      // Llama a la función de bloqueo
            Estado = Seguridad;                      // Vuelve al estado de seguridad
        } else if(Estado == Monitoreo){
            unsigned char m = Funcion_Monitoreo();  // Llama a la función de monitoreo
            if(m == 1){
                Estado = Alarma;  // Cambia al estado de alarma si la función devuelve 1
            } else {
                Estado = Monitoreo_Ambiental;  // Cambia al estado de monitoreo ambiental
            }
        } else if(Estado == Monitoreo_Ambiental){ 
            unsigned char p = Funcion_Monitoreo_Ambiental();  // Llama a la función de monitoreo ambiental
            if(p == 1){
                Estado = Alarma_Ambiental;  // Cambia al estado de alarma ambiental si la función devuelve 1
            } else {
                Estado = Monitoreo;  // Vuelve al estado de monitoreo
            } 
        } else if (Estado == Alarma_Ambiental){
            Funcion_Alarma_Ambiental();  // Llama a la función de alarma ambiental
            __delay_ms(1000);  // Espera 1 segundo
            Estado = Monitoreo_Ambiental;  // Vuelve al estado de monitoreo ambiental
        } else if(Estado == Alarma){
            Funcion_Alarma();  // Llama a la función de alarma
            __delay_ms(1000);  // Espera 1 segundo
            Estado = Monitoreo;  // Vuelve al estado de monitoreo
        }
    }
}
