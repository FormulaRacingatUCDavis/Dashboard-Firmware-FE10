/*******************************************************************************
* File Name: ADC_GLV_V_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_GLV_V.h"


/***************************************
* Local data allocation
***************************************/

static ADC_GLV_V_BACKUP_STRUCT  ADC_GLV_V_backup =
{
    ADC_GLV_V_DISABLED,
    0u    
};


/*******************************************************************************
* Function Name: ADC_GLV_V_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_GLV_V_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_GLV_V_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_GLV_V_RestoreConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_GLV_V_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_GLV_V_backup - modified.
*
*******************************************************************************/
void ADC_GLV_V_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    ADC_GLV_V_backup.dftRegVal = ADC_GLV_V_SAR_DFT_CTRL_REG & (uint32)~ADC_GLV_V_ADFT_OVERRIDE;
    ADC_GLV_V_SAR_DFT_CTRL_REG |= ADC_GLV_V_ADFT_OVERRIDE;
    if((ADC_GLV_V_SAR_CTRL_REG  & ADC_GLV_V_ENABLE) != 0u)
    {
        if((ADC_GLV_V_SAR_SAMPLE_CTRL_REG & ADC_GLV_V_CONTINUOUS_EN) != 0u)
        {
            ADC_GLV_V_backup.enableState = ADC_GLV_V_ENABLED | ADC_GLV_V_STARTED;
        }
        else
        {
            ADC_GLV_V_backup.enableState = ADC_GLV_V_ENABLED;
        }
        ADC_GLV_V_StopConvert();
        ADC_GLV_V_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((ADC_GLV_V_SAR_CTRL_REG & ADC_GLV_V_BOOSTPUMP_EN) != 0u)
        {
            ADC_GLV_V_SAR_CTRL_REG &= (uint32)~ADC_GLV_V_BOOSTPUMP_EN;
            ADC_GLV_V_backup.enableState |= ADC_GLV_V_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        ADC_GLV_V_backup.enableState = ADC_GLV_V_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_GLV_V_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_GLV_V_backup - used.
*
*******************************************************************************/
void ADC_GLV_V_Wakeup(void)
{
    ADC_GLV_V_SAR_DFT_CTRL_REG = ADC_GLV_V_backup.dftRegVal;
    if(ADC_GLV_V_backup.enableState != ADC_GLV_V_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((ADC_GLV_V_backup.enableState & ADC_GLV_V_BOOSTPUMP_ENABLED) != 0u)
        {
            ADC_GLV_V_SAR_CTRL_REG |= ADC_GLV_V_BOOSTPUMP_EN;
        }
        ADC_GLV_V_Enable();
        if((ADC_GLV_V_backup.enableState & ADC_GLV_V_STARTED) != 0u)
        {
            ADC_GLV_V_StartConvert();
        }
    }
}
/* [] END OF FILE */
