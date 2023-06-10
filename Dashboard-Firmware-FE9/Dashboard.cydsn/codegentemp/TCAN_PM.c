/*******************************************************************************
* File Name: TCAN_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in the low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TCAN.h"

static TCAN_BACKUP_STRUCT TCAN_backup =
{
    0u,
    #if (CY_PSOC3 || CY_PSOC5)
        0u,
        TCAN_INIT_INTERRUPT_MASK,
        TCAN_MODE_MASK,
        (((uint32) ((uint32) TCAN_SYNC_EDGE    << TCAN_EDGE_MODE_SHIFT))     |
        ((uint32) ((uint32) TCAN_SAMPLING_MODE << TCAN_SAMPLE_MODE_SHIFT))   |
        ((uint32) ((uint32) TCAN_CFG_REG_SJW   << TCAN_CFG_REG_SJW_SHIFT))   |
        ((uint32) ((uint32) TCAN_RESET_TYPE    << TCAN_RESET_SHIFT))         |
        ((uint32) ((uint32) TCAN_CFG_REG_TSEG2 << TCAN_CFG_REG_TSEG2_SHIFT)) |
        ((uint32) ((uint32) TCAN_CFG_REG_TSEG1 << TCAN_CFG_REG_TSEG1_SHIFT)) |
        ((uint32) ((uint32) TCAN_ARBITER       << TCAN_ARBITER_SHIFT))       |
        ((uint32) ((uint32) TCAN_BITRATE       << TCAN_BITRATE_SHIFT)))
    #endif /* CY_PSOC3 || CY_PSOC5 */
};


/*******************************************************************************
* Function Name: TCAN_SaveConfig
********************************************************************************
*
* Summary:
*  Save the CAN configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TCAN_backup - Modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TCAN_SaveConfig(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        TCAN_backup.intSr = (CY_GET_REG32(TCAN_INT_SR_PTR));
        TCAN_backup.intEn = (CY_GET_REG32(TCAN_INT_EN_PTR));
        TCAN_backup.cmd = (CY_GET_REG32(TCAN_CMD_PTR));
        TCAN_backup.cfg = (CY_GET_REG32(TCAN_CFG_PTR));
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: TCAN_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the CAN configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TCAN_backup - Used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then default values
*  from Customizer will be in the following registers: TCAN_INT_SR,
*  TCAN_INT_EN, TCAN_CMD, TCAN_CFG.
*
*******************************************************************************/
void TCAN_RestoreConfig(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        CY_SET_REG32(TCAN_INT_SR_PTR, TCAN_backup.intSr);
        CY_SET_REG32(TCAN_INT_EN_PTR, TCAN_backup.intEn);
        CY_SET_REG32(TCAN_CMD_PTR, TCAN_backup.cmd);
        CY_SET_REG32(TCAN_CFG_PTR, TCAN_backup.cfg);
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: TCAN_Sleep
********************************************************************************
*
* Summary:
*  Prepares CAN Component to go to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TCAN_backup - Modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TCAN_Sleep(void) 
{
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 i;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */

    if (0u != (CY_GET_REG32(TCAN_CMD_PTR) & TCAN_MODE_MASK))
    {
        TCAN_backup.enableState = 1u;
    }
    else /* CAN block is disabled */
    {
        TCAN_backup.enableState = 0u;
    }

    #if (CY_PSOC3 || CY_PSOC5)
        TCAN_SaveConfig();
        (void) TCAN_Stop();
    #else /* CY_PSOC4 */
        /* Abort respective pending TX message requests */
        for (i = 0u; i < TCAN_NUMBER_OF_TX_MAILBOXES; i++)
        {
            TCAN_TX_ABORT_MESSAGE(i);
        }

        /* Sets CAN controller to Stop mode */
        (void) TCAN_Stop();

        /* Clear Global Interrupt enable Flag */
        (void) TCAN_GlobalIntDisable();
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: TCAN_Wakeup
********************************************************************************
*
* Summary:
*  Prepares CAN Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  TCAN_backup - Used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void TCAN_Wakeup(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Enable CAN block in Active mode */
        TCAN_PM_ACT_CFG_REG |= TCAN_ACT_PWR_EN;
        /* Enable CAN block in Alternate Active (Standby) mode */
        TCAN_PM_STBY_CFG_REG |= TCAN_STBY_PWR_EN;

        TCAN_RestoreConfig();

        /* Reconfigure Rx and Tx Buffers control registers */
        (void) TCAN_RxTxBuffersConfig();

        if (TCAN_backup.enableState != 0u)
        {
            /* Enable component's operation */
            (void) TCAN_Enable();
        } /* Do nothing if component's block was disabled before */
    #else /* CY_PSOC4 */
        /* Clear all INT_STATUS bits */
        TCAN_INT_SR_REG = TCAN_INT_STATUS_MASK;

        /* Set Global Interrupt enable Flag */
        (void) TCAN_GlobalIntEnable();

        if (TCAN_backup.enableState != 0u)
        {
            (void) TCAN_Enable();
        } /* Do nothing if component's block was disabled before */
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/* [] END OF FILE */
