/*******************************************************************************
* File Name: CAN_0_PM.c
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

#include "CAN_0.h"

static CAN_0_BACKUP_STRUCT CAN_0_backup =
{
    0u,
    #if (CY_PSOC3 || CY_PSOC5)
        0u,
        CAN_0_INIT_INTERRUPT_MASK,
        CAN_0_MODE_MASK,
        (((uint32) ((uint32) CAN_0_SYNC_EDGE    << CAN_0_EDGE_MODE_SHIFT))     |
        ((uint32) ((uint32) CAN_0_SAMPLING_MODE << CAN_0_SAMPLE_MODE_SHIFT))   |
        ((uint32) ((uint32) CAN_0_CFG_REG_SJW   << CAN_0_CFG_REG_SJW_SHIFT))   |
        ((uint32) ((uint32) CAN_0_RESET_TYPE    << CAN_0_RESET_SHIFT))         |
        ((uint32) ((uint32) CAN_0_CFG_REG_TSEG2 << CAN_0_CFG_REG_TSEG2_SHIFT)) |
        ((uint32) ((uint32) CAN_0_CFG_REG_TSEG1 << CAN_0_CFG_REG_TSEG1_SHIFT)) |
        ((uint32) ((uint32) CAN_0_ARBITER       << CAN_0_ARBITER_SHIFT))       |
        ((uint32) ((uint32) CAN_0_BITRATE       << CAN_0_BITRATE_SHIFT)))
    #endif /* CY_PSOC3 || CY_PSOC5 */
};


/*******************************************************************************
* Function Name: CAN_0_SaveConfig
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
*  CAN_0_backup - Modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CAN_0_SaveConfig(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        CAN_0_backup.intSr = (CY_GET_REG32(CAN_0_INT_SR_PTR));
        CAN_0_backup.intEn = (CY_GET_REG32(CAN_0_INT_EN_PTR));
        CAN_0_backup.cmd = (CY_GET_REG32(CAN_0_CMD_PTR));
        CAN_0_backup.cfg = (CY_GET_REG32(CAN_0_CFG_PTR));
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: CAN_0_RestoreConfig
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
*  CAN_0_backup - Used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then default values
*  from Customizer will be in the following registers: CAN_0_INT_SR,
*  CAN_0_INT_EN, CAN_0_CMD, CAN_0_CFG.
*
*******************************************************************************/
void CAN_0_RestoreConfig(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        CY_SET_REG32(CAN_0_INT_SR_PTR, CAN_0_backup.intSr);
        CY_SET_REG32(CAN_0_INT_EN_PTR, CAN_0_backup.intEn);
        CY_SET_REG32(CAN_0_CMD_PTR, CAN_0_backup.cmd);
        CY_SET_REG32(CAN_0_CFG_PTR, CAN_0_backup.cfg);
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: CAN_0_Sleep
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
*  CAN_0_backup - Modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CAN_0_Sleep(void) 
{
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 i;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */

    if (0u != (CY_GET_REG32(CAN_0_CMD_PTR) & CAN_0_MODE_MASK))
    {
        CAN_0_backup.enableState = 1u;
    }
    else /* CAN block is disabled */
    {
        CAN_0_backup.enableState = 0u;
    }

    #if (CY_PSOC3 || CY_PSOC5)
        CAN_0_SaveConfig();
        (void) CAN_0_Stop();
    #else /* CY_PSOC4 */
        /* Abort respective pending TX message requests */
        for (i = 0u; i < CAN_0_NUMBER_OF_TX_MAILBOXES; i++)
        {
            CAN_0_TX_ABORT_MESSAGE(i);
        }

        /* Sets CAN controller to Stop mode */
        (void) CAN_0_Stop();

        /* Clear Global Interrupt enable Flag */
        (void) CAN_0_GlobalIntDisable();
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* Function Name: CAN_0_Wakeup
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
*  CAN_0_backup - Used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CAN_0_Wakeup(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Enable CAN block in Active mode */
        CAN_0_PM_ACT_CFG_REG |= CAN_0_ACT_PWR_EN;
        /* Enable CAN block in Alternate Active (Standby) mode */
        CAN_0_PM_STBY_CFG_REG |= CAN_0_STBY_PWR_EN;

        CAN_0_RestoreConfig();

        /* Reconfigure Rx and Tx Buffers control registers */
        (void) CAN_0_RxTxBuffersConfig();

        if (CAN_0_backup.enableState != 0u)
        {
            /* Enable component's operation */
            (void) CAN_0_Enable();
        } /* Do nothing if component's block was disabled before */
    #else /* CY_PSOC4 */
        /* Clear all INT_STATUS bits */
        CAN_0_INT_SR_REG = CAN_0_INT_STATUS_MASK;

        /* Set Global Interrupt enable Flag */
        (void) CAN_0_GlobalIntEnable();

        if (CAN_0_backup.enableState != 0u)
        {
            (void) CAN_0_Enable();
        } /* Do nothing if component's block was disabled before */
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/* [] END OF FILE */
