/*******************************************************************************
* File Name: HV.h  
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

#if !defined(CY_PINS_HV_ALIASES_H) /* Pins HV_ALIASES_H */
#define CY_PINS_HV_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HV_0			(HV__0__PC)
#define HV_0_PS		(HV__0__PS)
#define HV_0_PC		(HV__0__PC)
#define HV_0_DR		(HV__0__DR)
#define HV_0_SHIFT	(HV__0__SHIFT)
#define HV_0_INTR	((uint16)((uint16)0x0003u << (HV__0__SHIFT*2u)))

#define HV_INTR_ALL	 ((uint16)(HV_0_INTR))


#endif /* End Pins HV_ALIASES_H */


/* [] END OF FILE */
