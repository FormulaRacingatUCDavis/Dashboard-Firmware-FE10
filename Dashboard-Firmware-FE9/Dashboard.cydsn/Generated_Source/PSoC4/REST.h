/*******************************************************************************
* File Name: REST.h  
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

#if !defined(CY_PINS_REST_H) /* Pins REST_H */
#define CY_PINS_REST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "REST_aliases.h"


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
} REST_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   REST_Read(void);
void    REST_Write(uint8 value);
uint8   REST_ReadDataReg(void);
#if defined(REST__PC) || (CY_PSOC4_4200L) 
    void    REST_SetDriveMode(uint8 mode);
#endif
void    REST_SetInterruptMode(uint16 position, uint16 mode);
uint8   REST_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void REST_Sleep(void); 
void REST_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(REST__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define REST_DRIVE_MODE_BITS        (3)
    #define REST_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - REST_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the REST_SetDriveMode() function.
         *  @{
         */
        #define REST_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define REST_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define REST_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define REST_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define REST_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define REST_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define REST_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define REST_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define REST_MASK               REST__MASK
#define REST_SHIFT              REST__SHIFT
#define REST_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in REST_SetInterruptMode() function.
     *  @{
     */
        #define REST_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define REST_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define REST_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define REST_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(REST__SIO)
    #define REST_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(REST__PC) && (CY_PSOC4_4200L)
    #define REST_USBIO_ENABLE               ((uint32)0x80000000u)
    #define REST_USBIO_DISABLE              ((uint32)(~REST_USBIO_ENABLE))
    #define REST_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define REST_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define REST_USBIO_ENTER_SLEEP          ((uint32)((1u << REST_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << REST_USBIO_SUSPEND_DEL_SHIFT)))
    #define REST_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << REST_USBIO_SUSPEND_SHIFT)))
    #define REST_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << REST_USBIO_SUSPEND_DEL_SHIFT)))
    #define REST_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(REST__PC)
    /* Port Configuration */
    #define REST_PC                 (* (reg32 *) REST__PC)
#endif
/* Pin State */
#define REST_PS                     (* (reg32 *) REST__PS)
/* Data Register */
#define REST_DR                     (* (reg32 *) REST__DR)
/* Input Buffer Disable Override */
#define REST_INP_DIS                (* (reg32 *) REST__PC2)

/* Interrupt configuration Registers */
#define REST_INTCFG                 (* (reg32 *) REST__INTCFG)
#define REST_INTSTAT                (* (reg32 *) REST__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define REST_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(REST__SIO)
    #define REST_SIO_REG            (* (reg32 *) REST__SIO)
#endif /* (REST__SIO_CFG) */

/* USBIO registers */
#if !defined(REST__PC) && (CY_PSOC4_4200L)
    #define REST_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define REST_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define REST_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define REST_DRIVE_MODE_SHIFT       (0x00u)
#define REST_DRIVE_MODE_MASK        (0x07u << REST_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins REST_H */


/* [] END OF FILE */
