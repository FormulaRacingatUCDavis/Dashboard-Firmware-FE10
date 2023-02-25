/*******************************************************************************
* File Name: HV_Request.h  
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

#if !defined(CY_PINS_HV_Request_ALIASES_H) /* Pins HV_Request_ALIASES_H */
#define CY_PINS_HV_Request_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HV_Request_0			(HV_Request__0__PC)
#define HV_Request_0_PS		(HV_Request__0__PS)
#define HV_Request_0_PC		(HV_Request__0__PC)
#define HV_Request_0_DR		(HV_Request__0__DR)
#define HV_Request_0_SHIFT	(HV_Request__0__SHIFT)
#define HV_Request_0_INTR	((uint16)((uint16)0x0003u << (HV_Request__0__SHIFT*2u)))

#define HV_Request_INTR_ALL	 ((uint16)(HV_Request_0_INTR))


#endif /* End Pins HV_Request_ALIASES_H */


/* [] END OF FILE */
