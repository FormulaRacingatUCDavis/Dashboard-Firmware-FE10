/*******************************************************************************
* File Name: Analog_2.h  
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

#if !defined(CY_PINS_Analog_2_ALIASES_H) /* Pins Analog_2_ALIASES_H */
#define CY_PINS_Analog_2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Analog_2_0			(Analog_2__0__PC)
#define Analog_2_0_PS		(Analog_2__0__PS)
#define Analog_2_0_PC		(Analog_2__0__PC)
#define Analog_2_0_DR		(Analog_2__0__DR)
#define Analog_2_0_SHIFT	(Analog_2__0__SHIFT)
#define Analog_2_0_INTR	((uint16)((uint16)0x0003u << (Analog_2__0__SHIFT*2u)))

#define Analog_2_INTR_ALL	 ((uint16)(Analog_2_0_INTR))


#endif /* End Pins Analog_2_ALIASES_H */


/* [] END OF FILE */
