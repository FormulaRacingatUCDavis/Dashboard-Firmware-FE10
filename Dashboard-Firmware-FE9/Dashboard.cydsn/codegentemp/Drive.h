/*******************************************************************************
* File Name: Drive.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Drive_H) /* Pins Drive_H */
#define CY_PINS_Drive_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Drive_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Drive_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Drive_Read(void);
void    Drive_Write(uint8 value);
uint8   Drive_ReadDataReg(void);
#if defined(Drive__PC) || (CY_PSOC4_4200L) 
    void    Drive_SetDriveMode(uint8 mode);
#endif
void    Drive_SetInterruptMode(uint16 position, uint16 mode);
uint8   Drive_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Drive_Sleep(void); 
void Drive_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Drive__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Drive_DRIVE_MODE_BITS        (3)
    #define Drive_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Drive_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Drive_SetDriveMode() function.
         *  @{
         */
        #define Drive_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Drive_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Drive_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Drive_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Drive_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Drive_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Drive_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Drive_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Drive_MASK               Drive__MASK
#define Drive_SHIFT              Drive__SHIFT
#define Drive_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Drive_SetInterruptMode() function.
     *  @{
     */
        #define Drive_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Drive_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Drive_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Drive_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Drive__SIO)
    #define Drive_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Drive__PC) && (CY_PSOC4_4200L)
    #define Drive_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Drive_USBIO_DISABLE              ((uint32)(~Drive_USBIO_ENABLE))
    #define Drive_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Drive_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Drive_USBIO_ENTER_SLEEP          ((uint32)((1u << Drive_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Drive_USBIO_SUSPEND_DEL_SHIFT)))
    #define Drive_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Drive_USBIO_SUSPEND_SHIFT)))
    #define Drive_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Drive_USBIO_SUSPEND_DEL_SHIFT)))
    #define Drive_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Drive__PC)
    /* Port Configuration */
    #define Drive_PC                 (* (reg32 *) Drive__PC)
#endif
/* Pin State */
#define Drive_PS                     (* (reg32 *) Drive__PS)
/* Data Register */
#define Drive_DR                     (* (reg32 *) Drive__DR)
/* Input Buffer Disable Override */
#define Drive_INP_DIS                (* (reg32 *) Drive__PC2)

/* Interrupt configuration Registers */
#define Drive_INTCFG                 (* (reg32 *) Drive__INTCFG)
#define Drive_INTSTAT                (* (reg32 *) Drive__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Drive_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Drive__SIO)
    #define Drive_SIO_REG            (* (reg32 *) Drive__SIO)
#endif /* (Drive__SIO_CFG) */

/* USBIO registers */
#if !defined(Drive__PC) && (CY_PSOC4_4200L)
    #define Drive_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Drive_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Drive_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Drive_DRIVE_MODE_SHIFT       (0x00u)
#define Drive_DRIVE_MODE_MASK        (0x07u << Drive_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Drive_H */


/* [] END OF FILE */
