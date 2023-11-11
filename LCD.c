/*!
\file   LCD.c
\date   2023-09-22
\author Evelin Ortiz-Oscar Matabajoy <evelinortiz@unicauca.edu.co><omatabajoy@unicauca.edu.co>
\brief  LCD 16x2 mode 4 bits.

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
#include "LCD.h"
#include "CONFIG.h"

/*F**************************************************************************
* NAME: LCD_Init
*----------------------------------------------------------------------------
* PARAMS:   none
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Initialize LCD 16x2
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
// Funci�n para inicializar un LCD
void LCD_Init(void){
    // Configura el puerto del LCD como un puerto de salida
    LCD_Port = 0;   /* Puerto como Puerto de Salida */

    // Espera 15 ms, tiempo de encendido
    __delay_ms(15);   /* 15 ms, retardo de encendido */

    // Envia comandos de inicializaci�n al LCD usando el m�todo de nibble
    LCD_Command(0x02);   /* env�a para inicializaci�n del LCD con m�todo de nibble */
    LCD_Command(0x28);   /* usa 2 l�neas e inicializa matriz 5x7 en modo de 4 bits */
    LCD_Command(0x01);   /* limpia la pantalla del display */
    LCD_Command(0x0C);   /* enciende la pantalla, apaga el cursor */
    LCD_Command(0x06);   /* incrementa el cursor (mueve el cursor a la derecha) */
}


/*F**************************************************************************
* NAME: LCD_Command
*----------------------------------------------------------------------------
* PARAMS:   
* cmd: Command to execute in LCD (example: 0x01 clear display screen, 0x0C display On, Cursor Off)
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Send Command to LCD 16x2
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
void LCD_Command(unsigned char cmd )
{
	ldata = (ldata & 0x0f) |(0xF0 & cmd);  /*Send higher nibble of command first to PORT*/ 
	RS = 0;  /*Command Register is selected i.e.RS=0*/ 
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	__delay_ms(1);
    ldata = (unsigned char)((ldata & 0x0f) | (cmd<<4));  /*Send lower nibble of command to PORT */
	EN = 1;
	NOP();
	EN = 0;
	__delay_ms(3);
}

/*F**************************************************************************
* NAME: LCD_Char
*----------------------------------------------------------------------------
* PARAMS:   
* dat: character to display in LCD
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Display Character to LCD 16x2
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/

void LCD_Char(unsigned char dat)
{
	ldata = (ldata & 0x0f) | (0xF0 & dat);  /*Send higher nibble of data first to PORT*/
	RS = 1;  /*Data Register is selected*/
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	__delay_ms(1);
    ldata = (unsigned char)((ldata & 0x0f) | (dat<<4));  /*Send lower nibble of data to PORT*/
	EN = 1;  /*High-to-low pulse on Enable pin to latch data*/
	NOP();
	EN = 0;
	__delay_ms(3);
}

// Funci�n para imprimir una cadena de texto en un LCD
void LCD_String(const char *msg)
{
    // Bucle que recorre la cadena de texto hasta encontrar el car�cter nulo (fin de la cadena)
    while ((*msg) != 0)
    {		
        // Llama a la funci�n LCD_Char para imprimir el car�cter actual en el LCD
        LCD_Char(*msg);

        // Incrementa el puntero para apuntar al siguiente car�cter en la cadena
        msg++;	
    }
}

// Funci�n para imprimir una cadena de texto en una posici�n espec�fica en un LCD de dos filas
void LCD_String_xy(char row, char pos, const char *msg)
{
    char location = 0;

    // Verifica si la fila especificada es menor o igual a 1
    if (row <= 1)
    {
        // Calcula la ubicaci�n para la 1ra fila y la posici�n deseada
        location = (0x80) | ((pos) & 0x0F);  /* Imprimir mensaje en la 1ra fila y la posici�n deseada */
        LCD_Command(location);  // Env�a el comando de posici�n al LCD
    }
    else
    {
        // Calcula la ubicaci�n para la 2da fila y la posici�n deseada
        location = (0xC0) | ((pos) & 0x0F);  /* Imprimir mensaje en la 2da fila y la posici�n deseada */
        LCD_Command(location);  // Env�a el comando de posici�n al LCD
    }

    // Llama a la funci�n LCD_String para imprimir la cadena de texto en la ubicaci�n calculada
    LCD_String(msg);
}

/*F**************************************************************************
* NAME: LCD_Clear
*----------------------------------------------------------------------------
* PARAMS:   none
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Clear the Display Screen
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
// Funci�n para limpiar la pantalla de un LCD
void LCD_Clear(void)
{
    // Env�a el comando de limpiar la pantalla (0x01) al LCD
    LCD_Command(0x01);

    // Espera un tiempo (3 milisegundos) para asegurar que el LCD haya completado la operaci�n
    __delay_ms(3);
}
