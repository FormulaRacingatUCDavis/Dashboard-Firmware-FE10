/*******************************************************************************
* File Name: RX_CAN0.h  
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

#if !defined(CY_PINS_RX_CAN0_ALIASES_H) /* Pins RX_CAN0_ALIASES_H */
#define CY_PINS_RX_CAN0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define RX_CAN0_0			(RX_CAN0__0__PC)
#define RX_CAN0_0_PS		(RX_CAN0__0__PS)
#define RX_CAN0_0_PC		(RX_CAN0__0__PC)
#define RX_CAN0_0_DR		(RX_CAN0__0__DR)
#define RX_CAN0_0_SHIFT	(RX_CAN0__0__SHIFT)
#define RX_CAN0_0_INTR	((uint16)((uint16)0x0003u << (RX_CAN0__0__SHIFT*2u)))

#define RX_CAN0_INTR_ALL	 ((uint16)(RX_CAN0_0_INTR))


#endif /* End Pins RX_CAN0_ALIASES_H */


/* [] END OF FILE */
