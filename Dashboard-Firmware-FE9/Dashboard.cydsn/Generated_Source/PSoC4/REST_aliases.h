/*******************************************************************************
* File Name: REST.h  
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

#if !defined(CY_PINS_REST_ALIASES_H) /* Pins REST_ALIASES_H */
#define CY_PINS_REST_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define REST_0			(REST__0__PC)
#define REST_0_PS		(REST__0__PS)
#define REST_0_PC		(REST__0__PC)
#define REST_0_DR		(REST__0__DR)
#define REST_0_SHIFT	(REST__0__SHIFT)
#define REST_0_INTR	((uint16)((uint16)0x0003u << (REST__0__SHIFT*2u)))

#define REST_INTR_ALL	 ((uint16)(REST_0_INTR))


#endif /* End Pins REST_ALIASES_H */


/* [] END OF FILE */
