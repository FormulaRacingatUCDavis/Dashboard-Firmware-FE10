/*******************************************************************************
* File Name: HV_Request.h  
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

#if !defined(CY_PINS_HV_Request_H) /* Pins HV_Request_H */
#define CY_PINS_HV_Request_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HV_Request_aliases.h"


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
} HV_Request_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HV_Request_Read(void);
void    HV_Request_Write(uint8 value);
uint8   HV_Request_ReadDataReg(void);
#if defined(HV_Request__PC) || (CY_PSOC4_4200L) 
    void    HV_Request_SetDriveMode(uint8 mode);
#endif
void    HV_Request_SetInterruptMode(uint16 position, uint16 mode);
uint8   HV_Request_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HV_Request_Sleep(void); 
void HV_Request_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HV_Request__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HV_Request_DRIVE_MODE_BITS        (3)
    #define HV_Request_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HV_Request_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HV_Request_SetDriveMode() function.
         *  @{
         */
        #define HV_Request_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HV_Request_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HV_Request_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HV_Request_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HV_Request_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HV_Request_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HV_Request_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HV_Request_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HV_Request_MASK               HV_Request__MASK
#define HV_Request_SHIFT              HV_Request__SHIFT
#define HV_Request_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HV_Request_SetInterruptMode() function.
     *  @{
     */
        #define HV_Request_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HV_Request_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HV_Request_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HV_Request_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HV_Request__SIO)
    #define HV_Request_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HV_Request__PC) && (CY_PSOC4_4200L)
    #define HV_Request_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HV_Request_USBIO_DISABLE              ((uint32)(~HV_Request_USBIO_ENABLE))
    #define HV_Request_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HV_Request_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HV_Request_USBIO_ENTER_SLEEP          ((uint32)((1u << HV_Request_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HV_Request_USBIO_SUSPEND_DEL_SHIFT)))
    #define HV_Request_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HV_Request_USBIO_SUSPEND_SHIFT)))
    #define HV_Request_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HV_Request_USBIO_SUSPEND_DEL_SHIFT)))
    #define HV_Request_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HV_Request__PC)
    /* Port Configuration */
    #define HV_Request_PC                 (* (reg32 *) HV_Request__PC)
#endif
/* Pin State */
#define HV_Request_PS                     (* (reg32 *) HV_Request__PS)
/* Data Register */
#define HV_Request_DR                     (* (reg32 *) HV_Request__DR)
/* Input Buffer Disable Override */
#define HV_Request_INP_DIS                (* (reg32 *) HV_Request__PC2)

/* Interrupt configuration Registers */
#define HV_Request_INTCFG                 (* (reg32 *) HV_Request__INTCFG)
#define HV_Request_INTSTAT                (* (reg32 *) HV_Request__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HV_Request_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HV_Request__SIO)
    #define HV_Request_SIO_REG            (* (reg32 *) HV_Request__SIO)
#endif /* (HV_Request__SIO_CFG) */

/* USBIO registers */
#if !defined(HV_Request__PC) && (CY_PSOC4_4200L)
    #define HV_Request_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HV_Request_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HV_Request_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HV_Request_DRIVE_MODE_SHIFT       (0x00u)
#define HV_Request_DRIVE_MODE_MASK        (0x07u << HV_Request_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HV_Request_H */


/* [] END OF FILE */
