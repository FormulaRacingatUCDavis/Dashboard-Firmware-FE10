/*******************************************************************************
* File Name: RX_CAN.h  
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

#if !defined(CY_PINS_RX_CAN_H) /* Pins RX_CAN_H */
#define CY_PINS_RX_CAN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RX_CAN_aliases.h"


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
} RX_CAN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   RX_CAN_Read(void);
void    RX_CAN_Write(uint8 value);
uint8   RX_CAN_ReadDataReg(void);
#if defined(RX_CAN__PC) || (CY_PSOC4_4200L) 
    void    RX_CAN_SetDriveMode(uint8 mode);
#endif
void    RX_CAN_SetInterruptMode(uint16 position, uint16 mode);
uint8   RX_CAN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void RX_CAN_Sleep(void); 
void RX_CAN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(RX_CAN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define RX_CAN_DRIVE_MODE_BITS        (3)
    #define RX_CAN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RX_CAN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the RX_CAN_SetDriveMode() function.
         *  @{
         */
        #define RX_CAN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define RX_CAN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define RX_CAN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define RX_CAN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define RX_CAN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define RX_CAN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define RX_CAN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define RX_CAN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define RX_CAN_MASK               RX_CAN__MASK
#define RX_CAN_SHIFT              RX_CAN__SHIFT
#define RX_CAN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RX_CAN_SetInterruptMode() function.
     *  @{
     */
        #define RX_CAN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define RX_CAN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define RX_CAN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define RX_CAN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(RX_CAN__SIO)
    #define RX_CAN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(RX_CAN__PC) && (CY_PSOC4_4200L)
    #define RX_CAN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define RX_CAN_USBIO_DISABLE              ((uint32)(~RX_CAN_USBIO_ENABLE))
    #define RX_CAN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define RX_CAN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define RX_CAN_USBIO_ENTER_SLEEP          ((uint32)((1u << RX_CAN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << RX_CAN_USBIO_SUSPEND_DEL_SHIFT)))
    #define RX_CAN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << RX_CAN_USBIO_SUSPEND_SHIFT)))
    #define RX_CAN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << RX_CAN_USBIO_SUSPEND_DEL_SHIFT)))
    #define RX_CAN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(RX_CAN__PC)
    /* Port Configuration */
    #define RX_CAN_PC                 (* (reg32 *) RX_CAN__PC)
#endif
/* Pin State */
#define RX_CAN_PS                     (* (reg32 *) RX_CAN__PS)
/* Data Register */
#define RX_CAN_DR                     (* (reg32 *) RX_CAN__DR)
/* Input Buffer Disable Override */
#define RX_CAN_INP_DIS                (* (reg32 *) RX_CAN__PC2)

/* Interrupt configuration Registers */
#define RX_CAN_INTCFG                 (* (reg32 *) RX_CAN__INTCFG)
#define RX_CAN_INTSTAT                (* (reg32 *) RX_CAN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define RX_CAN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(RX_CAN__SIO)
    #define RX_CAN_SIO_REG            (* (reg32 *) RX_CAN__SIO)
#endif /* (RX_CAN__SIO_CFG) */

/* USBIO registers */
#if !defined(RX_CAN__PC) && (CY_PSOC4_4200L)
    #define RX_CAN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define RX_CAN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define RX_CAN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define RX_CAN_DRIVE_MODE_SHIFT       (0x00u)
#define RX_CAN_DRIVE_MODE_MASK        (0x07u << RX_CAN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins RX_CAN_H */


/* [] END OF FILE */
