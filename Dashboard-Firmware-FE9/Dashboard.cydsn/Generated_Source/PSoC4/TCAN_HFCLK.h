/*******************************************************************************
* File Name: TCAN_HFCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_TCAN_HFCLK_H)
#define CY_CLOCK_TCAN_HFCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void TCAN_HFCLK_StartEx(uint32 alignClkDiv);
#define TCAN_HFCLK_Start() \
    TCAN_HFCLK_StartEx(TCAN_HFCLK__PA_DIV_ID)

#else

void TCAN_HFCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void TCAN_HFCLK_Stop(void);

void TCAN_HFCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 TCAN_HFCLK_GetDividerRegister(void);
uint8  TCAN_HFCLK_GetFractionalDividerRegister(void);

#define TCAN_HFCLK_Enable()                         TCAN_HFCLK_Start()
#define TCAN_HFCLK_Disable()                        TCAN_HFCLK_Stop()
#define TCAN_HFCLK_SetDividerRegister(clkDivider, reset)  \
    TCAN_HFCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define TCAN_HFCLK_SetDivider(clkDivider)           TCAN_HFCLK_SetDividerRegister((clkDivider), 1u)
#define TCAN_HFCLK_SetDividerValue(clkDivider)      TCAN_HFCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define TCAN_HFCLK_DIV_ID     TCAN_HFCLK__DIV_ID

#define TCAN_HFCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define TCAN_HFCLK_CTRL_REG   (*(reg32 *)TCAN_HFCLK__CTRL_REGISTER)
#define TCAN_HFCLK_DIV_REG    (*(reg32 *)TCAN_HFCLK__DIV_REGISTER)

#define TCAN_HFCLK_CMD_DIV_SHIFT          (0u)
#define TCAN_HFCLK_CMD_PA_DIV_SHIFT       (8u)
#define TCAN_HFCLK_CMD_DISABLE_SHIFT      (30u)
#define TCAN_HFCLK_CMD_ENABLE_SHIFT       (31u)

#define TCAN_HFCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << TCAN_HFCLK_CMD_DISABLE_SHIFT))
#define TCAN_HFCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << TCAN_HFCLK_CMD_ENABLE_SHIFT))

#define TCAN_HFCLK_DIV_FRAC_MASK  (0x000000F8u)
#define TCAN_HFCLK_DIV_FRAC_SHIFT (3u)
#define TCAN_HFCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define TCAN_HFCLK_DIV_INT_SHIFT  (8u)

#else 

#define TCAN_HFCLK_DIV_REG        (*(reg32 *)TCAN_HFCLK__REGISTER)
#define TCAN_HFCLK_ENABLE_REG     TCAN_HFCLK_DIV_REG
#define TCAN_HFCLK_DIV_FRAC_MASK  TCAN_HFCLK__FRAC_MASK
#define TCAN_HFCLK_DIV_FRAC_SHIFT (16u)
#define TCAN_HFCLK_DIV_INT_MASK   TCAN_HFCLK__DIVIDER_MASK
#define TCAN_HFCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_TCAN_HFCLK_H) */

/* [] END OF FILE */
