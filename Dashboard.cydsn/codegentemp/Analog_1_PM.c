/*******************************************************************************
* File Name: Analog_1.c  
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
#include "Analog_1.h"

static Analog_1_BACKUP_STRUCT  Analog_1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Analog_1_Sleep
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
*  \snippet Analog_1_SUT.c usage_Analog_1_Sleep_Wakeup
*******************************************************************************/
void Analog_1_Sleep(void)
{
    #if defined(Analog_1__PC)
        Analog_1_backup.pcState = Analog_1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Analog_1_backup.usbState = Analog_1_CR1_REG;
            Analog_1_USB_POWER_REG |= Analog_1_USBIO_ENTER_SLEEP;
            Analog_1_CR1_REG &= Analog_1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Analog_1__SIO)
        Analog_1_backup.sioState = Analog_1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Analog_1_SIO_REG &= (uint32)(~Analog_1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Analog_1_Wakeup
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
*  Refer to Analog_1_Sleep() for an example usage.
*******************************************************************************/
void Analog_1_Wakeup(void)
{
    #if defined(Analog_1__PC)
        Analog_1_PC = Analog_1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Analog_1_USB_POWER_REG &= Analog_1_USBIO_EXIT_SLEEP_PH1;
            Analog_1_CR1_REG = Analog_1_backup.usbState;
            Analog_1_USB_POWER_REG &= Analog_1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Analog_1__SIO)
        Analog_1_SIO_REG = Analog_1_backup.sioState;
    #endif
}


/* [] END OF FILE */
