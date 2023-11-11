/* 
 * File:   Canal.h
 * Author: eveli
 *
 * Created on 20 de octubre de 2023, 02:20 PM
 */

#ifndef CANAL_H
#define	CANAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    void adc_begin(void);
    int adc_conversion(int canal);

#ifdef	__cplusplus
}
#endif

#endif	/* CANAL_H */
