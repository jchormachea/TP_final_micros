/***************************************************************************//**
  @file     calefactor.h
  @brief    calefactor for .h file
  @author   Conradeus
 ******************************************************************************/

#ifndef _CALEFACTOR_H_
#define _CALEFACTOR_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "common.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE 
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void calefactor_setPotencia(uint8_t);
void calefactor_turnOn(void);
void calefactor_turnOff(void);
char calefactor_status(void);
/*******************************************************************************
 ******************************************************************************/

#endif // _HARDWARE_H_
