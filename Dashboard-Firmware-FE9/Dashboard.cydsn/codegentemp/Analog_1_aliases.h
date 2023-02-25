/*******************************************************************************
* File Name: Analog_1.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Analog_1_ALIASES_H) /* Pins Analog_1_ALIASES_H */
#define CY_PINS_Analog_1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Analog_1_0			(Analog_1__0__PC)
#define Analog_1_0_PS		(Analog_1__0__PS)
#define Analog_1_0_PC		(Analog_1__0__PC)
#define Analog_1_0_DR		(Analog_1__0__DR)
#define Analog_1_0_SHIFT	(Analog_1__0__SHIFT)
#define Analog_1_0_INTR	((uint16)((uint16)0x0003u << (Analog_1__0__SHIFT*2u)))

#define Analog_1_INTR_ALL	 ((uint16)(Analog_1_0_INTR))


#endif /* End Pins Analog_1_ALIASES_H */


/* [] END OF FILE */
