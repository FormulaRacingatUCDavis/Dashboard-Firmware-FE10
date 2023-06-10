/*******************************************************************************
* File Name: timer_clock_3.h
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

#if !defined(CY_CLOCK_timer_clock_3_H)
#define CY_CLOCK_timer_clock_3_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void timer_clock_3_StartEx(uint32 alignClkDiv);
#define timer_clock_3_Start() \
    timer_clock_3_StartEx(timer_clock_3__PA_DIV_ID)

#else

void timer_clock_3_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void timer_clock_3_Stop(void);

void timer_clock_3_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 timer_clock_3_GetDividerRegister(void);
uint8  timer_clock_3_GetFractionalDividerRegister(void);

#define timer_clock_3_Enable()                         timer_clock_3_Start()
#define timer_clock_3_Disable()                        timer_clock_3_Stop()
#define timer_clock_3_SetDividerRegister(clkDivider, reset)  \
    timer_clock_3_SetFractionalDividerRegister((clkDivider), 0u)
#define timer_clock_3_SetDivider(clkDivider)           timer_clock_3_SetDividerRegister((clkDivider), 1u)
#define timer_clock_3_SetDividerValue(clkDivider)      timer_clock_3_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define timer_clock_3_DIV_ID     timer_clock_3__DIV_ID

#define timer_clock_3_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define timer_clock_3_CTRL_REG   (*(reg32 *)timer_clock_3__CTRL_REGISTER)
#define timer_clock_3_DIV_REG    (*(reg32 *)timer_clock_3__DIV_REGISTER)

#define timer_clock_3_CMD_DIV_SHIFT          (0u)
#define timer_clock_3_CMD_PA_DIV_SHIFT       (8u)
#define timer_clock_3_CMD_DISABLE_SHIFT      (30u)
#define timer_clock_3_CMD_ENABLE_SHIFT       (31u)

#define timer_clock_3_CMD_DISABLE_MASK       ((uint32)((uint32)1u << timer_clock_3_CMD_DISABLE_SHIFT))
#define timer_clock_3_CMD_ENABLE_MASK        ((uint32)((uint32)1u << timer_clock_3_CMD_ENABLE_SHIFT))

#define timer_clock_3_DIV_FRAC_MASK  (0x000000F8u)
#define timer_clock_3_DIV_FRAC_SHIFT (3u)
#define timer_clock_3_DIV_INT_MASK   (0xFFFFFF00u)
#define timer_clock_3_DIV_INT_SHIFT  (8u)

#else 

#define timer_clock_3_DIV_REG        (*(reg32 *)timer_clock_3__REGISTER)
#define timer_clock_3_ENABLE_REG     timer_clock_3_DIV_REG
#define timer_clock_3_DIV_FRAC_MASK  timer_clock_3__FRAC_MASK
#define timer_clock_3_DIV_FRAC_SHIFT (16u)
#define timer_clock_3_DIV_INT_MASK   timer_clock_3__DIVIDER_MASK
#define timer_clock_3_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_timer_clock_3_H) */

/* [] END OF FILE */
