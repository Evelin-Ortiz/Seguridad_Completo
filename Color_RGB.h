/* 
 * File:   Color_RGB.h
 * Author: Asus
 *
 * Created on 29 de septiembre de 2023, 02:32 PM
 */

#ifndef COLOR_RGB_H
#define	COLOR_RGB_H

#ifdef	__cplusplus
extern "C" {
#endif

#define RGB     PORTE
#define ldatae  TRISE
#define ROJO    PORTEbits.RE0
#define VERDE   PORTEbits.RE1
#define AZUL    PORTEbits.RE2
void Color(unsigned char red,unsigned char green,unsigned char blue);



#ifdef	__cplusplus
}
#endif

#endif	/* COLOR_RGB_H */

