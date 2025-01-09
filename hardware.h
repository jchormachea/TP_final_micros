/***************************************************************************//**
  @file     hardware.h
  @brief    Hardware, system and MCU registers management
  @author   Conradeus
 ******************************************************************************/

#ifndef _HARDWARE_H_
#define _HARDWARE_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "common.h"

#include <msp430.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/***** SYSTEM defines *********************************************************/

#define DCOCLK_FREQ_HZ          8000000UL // 8MHz
#define MCLK_PRESCALER_2POW     0
#define SMCLK_PRESCALER_2POW    0
#define MCLK_FREQ_HZ            (DCOCLK_FREQ_HZ/(1UL<<MCLK_PRESCALER_2POW)) // 8MHz
#define SMCLK_FREQ_HZ           (DCOCLK_FREQ_HZ/(1UL<<SMCLK_PRESCALER_2POW)) // 8MHz


#define enable_interrupts()     _BIS_SR(GIE)
#define disable_interrupts()    _BIC_SR(GIE)


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/



/*******************************************************************************
 ******************************************************************************/

#endif // _HARDWARE_H_
