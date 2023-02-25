/*******************************************************************************
* File Name: Drive_Request.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Drive_Request.h"

static Drive_Request_BACKUP_STRUCT  Drive_Request_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Drive_Request_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Drive_Request_SUT.c usage_Drive_Request_Sleep_Wakeup
*******************************************************************************/
void Drive_Request_Sleep(void)
{
    #if defined(Drive_Request__PC)
        Drive_Request_backup.pcState = Drive_Request_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Drive_Request_backup.usbState = Drive_Request_CR1_REG;
            Drive_Request_USB_POWER_REG |= Drive_Request_USBIO_ENTER_SLEEP;
            Drive_Request_CR1_REG &= Drive_Request_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Drive_Request__SIO)
        Drive_Request_backup.sioState = Drive_Request_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Drive_Request_SIO_REG &= (uint32)(~Drive_Request_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Drive_Request_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Drive_Request_Sleep() for an example usage.
*******************************************************************************/
void Drive_Request_Wakeup(void)
{
    #if defined(Drive_Request__PC)
        Drive_Request_PC = Drive_Request_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Drive_Request_USB_POWER_REG &= Drive_Request_USBIO_EXIT_SLEEP_PH1;
            Drive_Request_CR1_REG = Drive_Request_backup.usbState;
            Drive_Request_USB_POWER_REG &= Drive_Request_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Drive_Request__SIO)
        Drive_Request_SIO_REG = Drive_Request_backup.sioState;
    #endif
}


/* [] END OF FILE */
