/*******************************************************************************
* File Name: TCAN_INT.c
* Version 3.0
*
* Description:
*  This file contains Interrupt Service Routine (ISR) for CAN Component.
*  The Interrupt handlers functions are generated accordingly to the PSoC
*  Creator Customizer inputs.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TCAN.h"
#include "cyapicallbacks.h"

/* `#START CAN_INT_C_CODE_DEFINITION` */

/* `#END` */

#if (TCAN_ARB_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ArbLostIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Arbitration Lost Interrupt. Clears
    *  Arbitration Lost interrupt flag. Only generated if Arbitration Lost
    *  Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_ArbLostIsr(void) 
    {
        /* Clear Arbitration Lost flag */
        TCAN_INT_SR_REG = TCAN_ARBITRATION_LOST_MASK;

        /* `#START ARBITRATION_LOST_ISR` */

        /* `#END` */

        #ifdef TCAN_ARB_LOST_ISR_CALLBACK
            TCAN_ArbLostIsr_Callback();
        #endif /* TCAN_ARB_LOST_ISR_CALLBACK */
    }
#endif /* TCAN_ARB_LOST */


#if (TCAN_OVERLOAD)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_OvrLdErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Overload Error Interrupt. Clears Overload
    *  Error interrupt flag. Only generated if Overload Error Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_OvrLdErrorIsr(void) 
    {
        /* Clear Overload Error flag */
        TCAN_INT_SR_REG = TCAN_OVERLOAD_ERROR_MASK;

        /* `#START OVER_LOAD_ERROR_ISR` */

        /* `#END` */

        #ifdef TCAN_OVR_LD_ERROR_ISR_CALLBACK
            TCAN_OvrLdErrorIsr_Callback();
        #endif /* TCAN_OVR_LD_ERROR_ISR_CALLBACK */
    }
#endif /* TCAN_OVERLOAD */


#if (TCAN_BIT_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_BitErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bit Error Interrupt. Clears Bit Error
    *  interrupt flag. Only generated if Bit Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_BitErrorIsr(void) 
    {
        /* Clear Bit Error flag */
        TCAN_INT_SR_REG = TCAN_BIT_ERROR_MASK;

        /* `#START BIT_ERROR_ISR` */

        /* `#END` */

        #ifdef TCAN_BIT_ERROR_ISR_CALLBACK
            TCAN_BitErrorIsr_Callback();
        #endif /* TCAN_BIT_ERROR_ISR_CALLBACK */
    }
#endif /* TCAN_BIT_ERR */


#if (TCAN_STUFF_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_BitStuffErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bit Stuff Error Interrupt. Clears Bit Stuff
    *  Error interrupt flag. Only generated if Bit Stuff Error Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_BitStuffErrorIsr(void) 
    {
        /* Clear Stuff Error flag */
        TCAN_INT_SR_REG = TCAN_STUFF_ERROR_MASK;

        /* `#START BIT_STUFF_ERROR_ISR` */

        /* `#END` */

        #ifdef TCAN_BIT_STUFF_ERROR_ISR_CALLBACK
            TCAN_BitStuffErrorIsr_Callback();
        #endif /* TCAN_BIT_STUFF_ERROR_ISR_CALLBACK */
    }
#endif /* TCAN_STUFF_ERR */


#if (TCAN_ACK_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_AckErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Acknowledge Error Interrupt. Clears
    *  Acknowledge Error interrupt flag. Only generated if Acknowledge Error
    *  Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_AckErrorIsr(void) 
    {
        /* Clear Acknoledge Error flag */
        TCAN_INT_SR_REG = TCAN_ACK_ERROR_MASK;

        /* `#START ACKNOWLEDGE_ERROR_ISR` */

        /* `#END` */

        #ifdef TCAN_ACK_ERROR_ISR_CALLBACK
            TCAN_AckErrorIsr_Callback();
        #endif /* TCAN_ACK_ERROR_ISR_CALLBACK */
    }
#endif /* TCAN_ACK_ERR */


#if (TCAN_FORM_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_MsgErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Form Error Interrupt. Clears Form Error
    *  interrupt flag. Only generated if Form Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_MsgErrorIsr(void) 
    {
        /* Clear Form Error flag */
        TCAN_INT_SR_REG = TCAN_FORM_ERROR_MASK;

        /* `#START MESSAGE_ERROR_ISR` */

        /* `#END` */

        #ifdef TCAN_MSG_ERROR_ISR_CALLBACK
            TCAN_MsgErrorIsr_Callback();
        #endif /* TCAN_MSG_ERROR_ISR_CALLBACK */
    }
#endif /* TCAN_FORM_ERR */


#if (TCAN_CRC_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_CrcErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to CRC Error Interrupt. Clears CRC Error
    *  interrupt flag. Only generated if CRC Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_CrcErrorIsr(void) 
    {
        /* Clear CRC Error flag */
        TCAN_INT_SR_REG = TCAN_CRC_ERROR_MASK;

        /* `#START CRC_ERROR_ISR` */

        /* `#END` */

        #ifdef TCAN_CRC_ERROR_ISR_CALLBACK
            TCAN_CrcErrorIsr_Callback();
        #endif /* TCAN_CRC_ERROR_ISR_CALLBACK */
    }
#endif /* TCAN_CRC_ERR */


#if (TCAN_BUS_OFF)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_BusOffIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bus Off Interrupt. Places CAN Component
    *  to Stop mode. Only generated if Bus Off Interrupt enable in Customizer.
    *  Recommended setting to enable this interrupt.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Stops CAN component operation.
    *
    *******************************************************************************/
    void TCAN_BusOffIsr(void) 
    {
        /* Clear Bus Off flag */
        TCAN_INT_SR_REG = TCAN_BUS_OFF_MASK;

        /* `#START BUS_OFF_ISR` */

        /* `#END` */

        #ifdef TCAN_BUS_OFF_ISR_CALLBACK
            TCAN_BusOffIsr_Callback();
        #endif /* TCAN_BUS_OFF_ISR_CALLBACK */

        (void) TCAN_Stop();
    }
#endif /* TCAN_BUS_OFF */


#if (TCAN_RX_MSG_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_MsgLostIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Message Lost Interrupt. Clears Message Lost
    *  interrupt flag. Only generated if Message Lost Interrupt enable in Customizer
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_MsgLostIsr(void) 
    {
        /* Clear Receive Message Lost flag */
        TCAN_INT_SR_REG = TCAN_RX_MSG_LOST_MASK;

        /* `#START MESSAGE_LOST_ISR` */

        /* `#END` */

        #ifdef TCAN_MSG_LOST_ISR_CALLBACK
            TCAN_MsgLostIsr_Callback();
        #endif /* TCAN_MSG_LOST_ISR_CALLBACK */
    }
#endif /* TCAN_RX_MSG_LOST */


#if (TCAN_TX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_MsgTXIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Transmit Message Interrupt. Clears Transmit
    *  Message interrupt flag. Only generated if Transmit Message Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void TCAN_MsgTXIsr(void) 
    {
        /* Clear Transmit Message flag */
        TCAN_INT_SR_REG = TCAN_TX_MESSAGE_MASK;

        /* `#START MESSAGE_TRANSMITTED_ISR` */

        /* `#END` */

        #ifdef TCAN_MSG_TX_ISR_CALLBACK
            TCAN_MsgTXIsr_Callback();
        #endif /* TCAN_MSG_TX_ISR_CALLBACK */
    }
#endif /* TCAN_TX_MESSAGE */


#if (TCAN_RX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_MsgRXIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Receive Message Interrupt. Clears Receive
    *  Message interrupt flag and call appropriate handlers for Basic and Full
    *  interrupt based mailboxes. Only generated if Receive Message Interrupt
    *  enable in Customizer. Recommended setting to enable this interrupt.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void TCAN_MsgRXIsr(void) 
    {
        uint8 mailboxNumber;
        uint16 shift = 0x01u;

        /* Clear Receive Message flag */
        TCAN_INT_SR_REG = TCAN_RX_MESSAGE_MASK;

        /* `#START MESSAGE_RECEIVE_ISR` */

        /* `#END` */

        #ifdef TCAN_MSG_RX_ISR_CALLBACK
            TCAN_MsgRXIsr_Callback();
        #endif /* TCAN_MSG_RX_ISR_CALLBACK */

        for (mailboxNumber = 0u; mailboxNumber < TCAN_NUMBER_OF_RX_MAILBOXES; mailboxNumber++)
        {

            if ((TCAN_BUF_SR_REG & shift) != 0u)
            {
                if ((TCAN_RX_CMD_REG(mailboxNumber) & TCAN_RX_INT_ENABLE_MASK) != 0u)
                {
                    if ((TCAN_RX_MAILBOX_TYPE & shift) != 0u)
                    {
                        /* RX Full mailboxes handler */
                    }
                    else
                    {
                        /* RX Basic mailbox handler */
                        TCAN_ReceiveMsg(mailboxNumber);
                    }
                }
            }
            shift <<= 1u;
        }
    }
#endif /* TCAN_RX_MESSAGE */


#if (TCAN_RTR_AUTO_MSG_SENT)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_RtrAutoMsgSentIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to the RTR automatic message sent Interrupt.
    *  It is only generated if RTR message sent Interrupt is enabled in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void TCAN_RtrAutoMsgSentIsr(void)
    {
        /* Clear RTR auto-reply message sent flag */
        TCAN_INT_SR_REG = TCAN_RTR_MSG_MASK;

        /* `#START RTR_AUTO_MSG_SENT_ISR` */

        /* `#END` */

        #ifdef TCAN_RTR_AUTO_MSG_SENT_ISR_CALLBACK
            TCAN_RtrAutoMsgSentIsr_Callback();
        #endif /* TCAN_RTR_AUTO_MSG_SENT_ISR_CALLBACK */
    }
#endif /* TCAN_RTR_AUTO_MSG_SENT */


#if (TCAN_STUCK_AT_ZERO)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_StuckAtZeroIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to the stuck at dominant bit Interrupt.
    *  It is only generated if stuck at zero Interrupt is enabled in Customizer.
    *  Enabling this interrupt is recommended.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Stops CAN component operation.
    *
    *******************************************************************************/
    void TCAN_StuckAtZeroIsr(void)
    {
        /* Clear Stuck at dominant error flag */
        TCAN_INT_SR_REG = TCAN_STUCK_AT_ZERO_MASK;

        /* `#START STUCK_AT_ZERO_ISR` */

        /* `#END` */

        #ifdef TCAN_STUCK_AT_ZERO_ISR_CALLBACK
            TCAN_StuckAtZeroIsr_Callback();
        #endif /* TCAN_STUCK_AT_ZERO_ISR_CALLBACK */

        (void) TCAN_Stop();
    }
#endif /* TCAN_STUCK_AT_ZERO */


#if (TCAN_SST_FAILURE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SSTErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to the single shot transmission error
    *  Interrupt. It is only generated if the single shot transmission Interrupt
    *  is enabled in Customizer. Generated when the mailbox set for single shot
    *  transmission experienced an arbitration loss or a bus error during
    *  transmission.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Removes message that failed SST transmission from the Tx mailbox.
    *
    *******************************************************************************/
    void TCAN_SSTErrorIsr(void)
    {
        uint8 i;

        /* Clear Single shot transmission failure flag */
        TCAN_INT_SR_REG = TCAN_SST_FAILURE_MASK;

        /* `#START SST_FAILURE_ISR_PRE` */

        /* `#END` */

        #ifdef TCAN_SST_ERROR_ISR_PRE_CALLBACK
            TCAN_SSTErrorIsr_Pre_Callback();
        #endif /* TCAN_SST_ERROR_ISR_PRE_CALLBACK */

        /* Removes message that failed SST transmission from the Tx mailbox */
        for (i = 0u; i < TCAN_NUMBER_OF_TX_MAILBOXES; i++)
        {
            if ((TCAN_TX_CMD_REG(i) & TCAN_TX_ABORT_MASK) != 0u)
            {
                TCAN_TX_CMD_REG(i) = (TCAN_TX_CMD_REG(i) & (uint32) (~(uint32) TCAN_TX_TRANSMIT_REQUEST)) |
                                    TCAN_TX_ABORT_MASK;
            }
        }

        /* `#START SST_FAILURE_ISR_POST` */

        /* `#END` */

        #ifdef TCAN_SST_ERROR_ISR_POST_CALLBACK
            TCAN_SSTErrorIsr_Post_Callback();
        #endif /* TCAN_SST_ERROR_ISR_POST_CALLBACK */
    }
#endif /* TCAN_SST_FAILURE */


/*******************************************************************************
* Function Name: TCAN_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when CAN Core generates and interrupt on one of events:
*  Arb_lost, Overload, Bit_err, Stuff_err, Ack_err, Form_err, Crc_err,
*  Buss_off, Rx_msg_lost, Tx_msg or Rx_msg. The interrupt sources depends
*  on the Customizer inputs.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(TCAN_ISR)
{
    #ifdef TCAN_ISR_INTERRUPT_CALLBACK
        TCAN_ISR_InterruptCallback();
    #endif /* TCAN_ISR_INTERRUPT_CALLBACK */
    
    /* Place your Interrupt code here. */
    /* `#START CAN_ISR` */

    /* `#END` */
    
    /* Arbitration */
    #if (TCAN_ARB_LOST && (TCAN_ARB_LOST_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_ARBITRATION_LOST_MASK) != 0u)
        {
            TCAN_ArbLostIsr();
        }
    #endif /* TCAN_ARB_LOST && TCAN_ARB_LOST_USE_HELPER */

    /* Overload Error */
    #if (TCAN_OVERLOAD && (TCAN_OVERLOAD_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_OVERLOAD_ERROR_MASK) != 0u)
        {
            TCAN_OvrLdErrorIsr();
        }
    #endif /* TCAN_OVERLOAD && TCAN_OVERLOAD_USE_HELPER */

    /* Bit Error */
    #if (TCAN_BIT_ERR && (TCAN_BIT_ERR_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_BIT_ERROR_MASK) != 0u)
        {
            TCAN_BitErrorIsr();
        }
    #endif /* TCAN_BIT_ERR && TCAN_BIT_ERR_USE_HELPER */

    /* Bit Staff Error */
    #if (TCAN_STUFF_ERR && (TCAN_STUFF_ERR_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_STUFF_ERROR_MASK) != 0u)
        {
            TCAN_BitStuffErrorIsr();
        }
    #endif /* TCAN_STUFF_ERR && TCAN_STUFF_ERR_USE_HELPER */

    /* ACK Error */
    #if (TCAN_ACK_ERR && (TCAN_ACK_ERR_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_ACK_ERROR_MASK) != 0u)
        {
            TCAN_AckErrorIsr();
        }
    #endif /* TCAN_ACK_ERR && TCAN_ACK_ERR_USE_HELPER */

    /* Form(msg) Error */
    #if (TCAN_FORM_ERR && (TCAN_FORM_ERR_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_FORM_ERROR_MASK) != 0u)
        {
            TCAN_MsgErrorIsr();
        }
    #endif /* TCAN_FORM_ERR && TCAN_FORM_ERR_USE_HELPER */

    /* CRC Error */
    #if (TCAN_CRC_ERR && (TCAN_CRC_ERR_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_CRC_ERROR_MASK) != 0u)
        {
            TCAN_CrcErrorIsr();
        }
    #endif /* TCAN_CRC_ERR && TCAN_CRC_ERR_USE_HELPER */

    /* Bus Off state */
    #if (TCAN_BUS_OFF && (TCAN_BUS_OFF_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_BUS_OFF_MASK) != 0u)
        {
            TCAN_BusOffIsr();
        }
    #endif /* TCAN_BUS_OFF && TCAN_BUS_OFF_USE_HELPER */

    /* Message Lost */
    #if (TCAN_RX_MSG_LOST && (TCAN_RX_MSG_LOST_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_RX_MSG_LOST_MASK) != 0u)
        {
            TCAN_MsgLostIsr();
        }
    #endif /* TCAN_RX_MSG_LOST && TCAN_RX_MSG_LOST_USE_HELPER */

    /* TX Message Send */
    #if (TCAN_TX_MESSAGE && (TCAN_TX_MESSAGE_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_TX_MESSAGE_MASK) != 0u)
        {
            TCAN_MsgTXIsr();
        }
    #endif /* TCAN_TX_MESSAGE && TCAN_TX_MESSAGE_USE_HELPER */

    /* RX Message Available */
    #if (TCAN_RX_MESSAGE && (TCAN_RX_MESSAGE_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_RX_MESSAGE_MASK) != 0u)
        {
            TCAN_MsgRXIsr();
        }
    #endif /* TCAN_RX_MESSAGE && TCAN_RX_MESSAGE_USE_HELPER */

    /* RTR Auto-reply Message Sent */
    #if (TCAN_RTR_AUTO_MSG_SENT && (TCAN_RTR_MESSAGE_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_RTR_MSG_MASK) != 0u)
        {
            TCAN_RtrAutoMsgSentIsr();
        }
    #endif /* TCAN_RTR_AUTO_MSG_SENT && TCAN_RTR_MESSAGE_USE_HELPER */

    /* Stuck at dominant error */
    #if (TCAN_STUCK_AT_ZERO && (TCAN_STUCK_AT_ZERO_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_STUCK_AT_ZERO_MASK) != 0u)
        {
            TCAN_StuckAtZeroIsr();
        }
    #endif /* TCAN_STUCK_AT_ZERO && TCAN_STUCK_AT_ZERO_USE_HELPER */

    /* Single shot transmission failure */
    #if (TCAN_SST_FAILURE && (TCAN_SST_FAILURE_USE_HELPER || \
        (!TCAN_ADVANCED_INTERRUPT_CFG)))
        if ((TCAN_INT_SR_REG & TCAN_SST_FAILURE_MASK) != 0u)
        {
            TCAN_SSTErrorIsr();
        }
    #endif /* TCAN_SST_FAILURE && TCAN_SST_FAILURE_USE_HELPER */
}


/* [] END OF FILE */
