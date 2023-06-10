/*******************************************************************************
* File Name: TCAN_TX_RX_func.c
* Version 3.0
*
* Description:
*  There are functions process "Full" Receive and Transmit mailboxes:
*     - TCAN_SendMsg0-7();
*     - TCAN_ReceiveMsg0-15();
*  Transmission of message, and receive routine for "Basic" mailboxes:
*     - TCAN_SendMsg();
*     - TCAN_TxCancel();
*     - TCAN_ReceiveMsg();
*
*  Note:
*   None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TCAN.h"
#include "cyapicallbacks.h"

/* `#START TX_RX_FUNCTION` */

/* `#END` */


/*******************************************************************************
* FUNCTION NAME:   TCAN_SendMsg
********************************************************************************
*
* Summary:
*  This function is Send Message from one of Basic mailboxes. The function loops
*  through the transmit message buffer designed as Basic CAN mailboxes for the
*  first free available and sends from it. The number of retries is limited.
*
* Parameters:
*  message: The pointer to a structure that contains all required data to send
*           messages.
*
* Return:
*  Indication if message has been sent.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    TCAN_FAIL              The function failed
*
*******************************************************************************/
uint8 TCAN_SendMsg(const TCAN_TX_MSG *message) 
{
    uint8 i, j, shift;
    uint8 retry = 0u;
    uint8 result = TCAN_FAIL;
    uint32 regTemp;

    while (retry < TCAN_RETRY_NUMBER)
    {
        shift = 1u;    /* Start from first mailbox */
        for (i = 0u; i < TCAN_NUMBER_OF_TX_MAILBOXES; i++)
        {
            /* Find Basic TX mailboxes */
            if ((TCAN_TX_MAILBOX_TYPE & shift) == 0u)
            {
                /* Find free mailbox */
                #if (CY_PSOC3 || CY_PSOC5)
                    if ((TCAN_BUF_SR_REG.byte[2] & shift) == 0u)
                #else  /* CY_PSOC4 */
                    if ((TCAN_BUF_SR_REG &
                        (uint32) ((uint32) shift << TCAN_TWO_BYTE_OFFSET)) == 0u)
                #endif /* CY_PSOC3 || CY_PSOC5 */
                    {
                        regTemp = 0u;

                        /* Set message parameters */
                        if (message->rtr != TCAN_STANDARD_MESSAGE)
                        {
                            regTemp = TCAN_TX_RTR_MASK;    /* RTR message Enable */
                        }

                        if (message->ide == TCAN_STANDARD_MESSAGE)
                        {
                            TCAN_SET_TX_ID_STANDARD_MSG(i, message->id);
                        }
                        else
                        {
                            regTemp |= TCAN_TX_IDE_MASK;
                            TCAN_SET_TX_ID_EXTENDED_MSG(i, message->id);
                        }

                        if (message->dlc < TCAN_TX_DLC_MAX_VALUE)
                        {
                            regTemp |= ((uint32) message->dlc) << TCAN_TWO_BYTE_OFFSET;
                        }
                        else
                        {
                            regTemp |= TCAN_TX_DLC_UPPER_VALUE;
                        }

                        if (message->irq != TCAN_TRANSMIT_INT_DISABLE)
                        {
                            regTemp |= TCAN_TX_INT_ENABLE_MASK;    /* Transmit Interrupt Enable */
                        }

                        for (j = 0u; (j < message->dlc) && (j < TCAN_TX_DLC_MAX_VALUE); j++)
                        {
                            #if (CY_PSOC3 || CY_PSOC5)
                                TCAN_TX_DATA_BYTE(i, j) = message->msg->byte[j];
                            #else /* CY_PSOC4 */
                                TCAN_TX_DATA_BYTE(i, j, message->msg->byte[j]);
                            #endif /* CY_PSOC3 || CY_PSOC5 */
                        }

                        /* Disable isr */
    CyIntDisable(TCAN_ISR_NUMBER);

                        /* WPN[23] and WPN[3] set to 1 for write to CAN Control reg */
                        CY_SET_REG32(TCAN_TX_CMD_PTR(i), (regTemp | TCAN_TX_WPN_SET));

                        #if (CY_PSOC3 || CY_PSOC5)
                            CY_SET_REG32(TCAN_TX_CMD_PTR(i), TCAN_SEND_MESSAGE);
                        #else /* CY_PSOC4 */
                            if (message->sst != TCAN_STANDARD_MESSAGE)
                            {
                                /* Single Shot Transmission */
                                TCAN_TX_CMD_REG(i) |= TCAN_SEND_MESSAGE |
                                TCAN_TX_ABORT_MASK;
                            }
                            else
                            {
                                TCAN_TX_CMD_REG(i) |= TCAN_SEND_MESSAGE;
                            }
                        #endif /* CY_PSOC3 || CY_PSOC5 */

                        /* Enable isr */
    CyIntEnable(TCAN_ISR_NUMBER);

                        result = CYRET_SUCCESS;
                    }
            }
            shift <<= 1u;
            if (result == CYRET_SUCCESS)
            {
                break;
            }
        }
        if (result == CYRET_SUCCESS)
        {
            break;
        }
        else
        {
            retry++;
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   TCAN_TxCancel
********************************************************************************
*
* Summary:
*  This function cancels transmission of a message that has been queued to be
*  transmitted. Values between 0 and 7 are valid.
*
* Parameters:
*  bufferId: The mailbox number.
*
* Return:
*  None.
*
*******************************************************************************/
void TCAN_TxCancel(uint8 bufferId) 
{
    if (bufferId < TCAN_NUMBER_OF_TX_MAILBOXES)
    {
        TCAN_TX_ABORT_MESSAGE(bufferId);
    }
}


#if (TCAN_TX0_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SendMsg0
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 0. The function checks
    *  if mailbox 0 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    TCAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 TCAN_SendMsg0(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((TCAN_TX[0u].txcmd.byte[0u] & TCAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((TCAN_TX_CMD_REG(0u) & TCAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = TCAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_0_TRASMITTED` */

                /* `#END` */

                #ifdef TCAN_SEND_MSG_0_CALLBACK
                    TCAN_SendMsg_0_Callback();
                #endif /* TCAN_SEND_MSG_0_CALLBACK */

                CY_SET_REG32(TCAN_TX_CMD_PTR(0u),
                CY_GET_REG32(TCAN_TX_CMD_PTR(0u)) | TCAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* TCAN_TX0_FUNC_ENABLE */


#if (TCAN_TX1_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SendMsg1
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 1. The function checks
    *  if mailbox 1 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    TCAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 TCAN_SendMsg1(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((TCAN_TX[1u].txcmd.byte[0u] & TCAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((TCAN_TX_CMD_REG(1u) & TCAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = TCAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_1_TRASMITTED` */

                /* `#END` */

                #ifdef TCAN_SEND_MSG_1_CALLBACK
                    TCAN_SendMsg_1_Callback();
                #endif /* TCAN_SEND_MSG_1_CALLBACK */

                CY_SET_REG32(TCAN_TX_CMD_PTR(1u),
                CY_GET_REG32(TCAN_TX_CMD_PTR(1u)) | TCAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* TCAN_TX1_FUNC_ENABLE */


#if (TCAN_TX2_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SendMsg2
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 2. The function checks
    *  if mailbox 2 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    TCAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 TCAN_SendMsg2(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((TCAN_TX[2u].txcmd.byte[0u] & TCAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((TCAN_TX_CMD_REG(2u) & TCAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = TCAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_2_TRASMITTED` */

                /* `#END` */

                #ifdef TCAN_SEND_MSG_2_CALLBACK
                    TCAN_SendMsg_2_Callback();
                #endif /* TCAN_SEND_MSG_2_CALLBACK */

                CY_SET_REG32(TCAN_TX_CMD_PTR(2u),
                CY_GET_REG32(TCAN_TX_CMD_PTR(2u)) | TCAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* TCAN_TX2_FUNC_ENABLE */


#if (TCAN_TX3_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SendMsg3
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 3. The function checks
    *  if mailbox 3 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    TCAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 TCAN_SendMsg3(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((TCAN_TX[3u].txcmd.byte[0u] & TCAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((TCAN_TX_CMD_REG(3u) & TCAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = TCAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_3_TRASMITTED` */

                /* `#END` */

                #ifdef TCAN_SEND_MSG_3_CALLBACK
                    TCAN_SendMsg_3_Callback();
                #endif /* TCAN_SEND_MSG_3_CALLBACK */

                CY_SET_REG32(TCAN_TX_CMD_PTR(3u),
                CY_GET_REG32(TCAN_TX_CMD_PTR(3u)) | TCAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* TCAN_TX3_FUNC_ENABLE */


#if (TCAN_TX4_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SendMsg4
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 4. The function checks
    *  if mailbox 4 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    TCAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 TCAN_SendMsg4(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((TCAN_TX[4u].txcmd.byte[0u] & TCAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((TCAN_TX_CMD_REG(4u) & TCAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = TCAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_4_TRASMITTED` */

                /* `#END` */

                #ifdef TCAN_SEND_MSG_4_CALLBACK
                    TCAN_SendMsg_4_Callback();
                #endif /* TCAN_SEND_MSG_4_CALLBACK */

                CY_SET_REG32(TCAN_TX_CMD_PTR(4u),
                CY_GET_REG32(TCAN_TX_CMD_PTR(4u)) | TCAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* TCAN_TX4_FUNC_ENABLE */


#if (TCAN_TX5_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SendMsg5
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 5. The function checks
    *  if mailbox 5 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    TCAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 TCAN_SendMsg5(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((TCAN_TX[5u].txcmd.byte[0u] & TCAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((TCAN_TX_CMD_REG(5u) & TCAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = TCAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_5_TRASMITTED` */

                /* `#END` */

                #ifdef TCAN_SEND_MSG_5_CALLBACK
                    TCAN_SendMsg_5_Callback();
                #endif /* TCAN_SEND_MSG_5_CALLBACK */

                CY_SET_REG32(TCAN_TX_CMD_PTR(5u),
                CY_GET_REG32(TCAN_TX_CMD_PTR(5u)) | TCAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* TCAN_TX5_FUNC_ENABLE */


#if (TCAN_TX6_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SendMsg6
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 6. The function checks
    *  if mailbox 6 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    TCAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 TCAN_SendMsg6(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((TCAN_TX[6u].txcmd.byte[0u] & TCAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((TCAN_TX_CMD_REG(6u) & TCAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = TCAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_6_TRASMITTED` */

                /* `#END` */

                #ifdef TCAN_SEND_MSG_6_CALLBACK
                    TCAN_SendMsg_6_Callback();
                #endif /* TCAN_SEND_MSG_6_CALLBACK */

                CY_SET_REG32(TCAN_TX_CMD_PTR(6u),
                CY_GET_REG32(TCAN_TX_CMD_PTR(6u)) | TCAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* TCAN_TX6_FUNC_ENABLE */


#if (TCAN_TX7_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_SendMsg7)
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Transmit Message 7. The function checks
    *  if mailbox 7 doesn't already have un-transmitted messages waiting for
    *  arbitration. If not initiate transmission of the message.
    *  Generated only for the Transmit mailbox designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Indication if Message has been sent.
    *   Define                             Description
    *    CYRET_SUCCESS                      The function passed successfully
    *    TCAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 TCAN_SendMsg7(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((TCAN_TX[7u].txcmd.byte[0u] & TCAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((TCAN_TX_CMD_REG(7u) & TCAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = TCAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_7_TRASMITTED` */

                /* `#END` */

                #ifdef TCAN_SEND_MSG_7_CALLBACK
                    TCAN_SendMsg_7_Callback();
                #endif /* TCAN_SEND_MSG_7_CALLBACK */

                CY_SET_REG32(TCAN_TX_CMD_PTR(7u),
                CY_GET_REG32(TCAN_TX_CMD_PTR(7u)) | TCAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* TCAN_TX7_FUNC_ENABLE */


/*******************************************************************************
* FUNCTION NAME:   TCAN_ReceiveMsg
********************************************************************************
*
* Summary:
*  This function is the entry point to Receive Message Interrupt for Basic
*  mailboxes. Clears the Receive particular Message interrupt flag. Generated
*  only if one of the Receive mailboxes is designed as Basic.
*
* Parameters:
*  rxMailbox: The mailbox number that trig Receive Message Interrupt.
*
* Return:
*  None.
*
* Reentrant:
*  Depends on the Customer code.
*
*******************************************************************************/
void TCAN_ReceiveMsg(uint8 rxMailbox) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        if ((TCAN_RX[rxMailbox].rxcmd.byte[0u] & TCAN_RX_ACK_MSG) != 0u)
    #else  /* CY_PSOC4 */
        if ((TCAN_RX_CMD_REG(rxMailbox) & TCAN_RX_ACK_MSG) != 0u)
    #endif /* CY_PSOC3 || CY_PSOC5 */
        {
            /* `#START MESSAGE_BASIC_RECEIVED` */

            /* `#END` */

            #ifdef TCAN_RECEIVE_MSG_CALLBACK
                TCAN_ReceiveMsg_Callback();
            #endif /* TCAN_RECEIVE_MSG_CALLBACK */

            #if (CY_PSOC3 || CY_PSOC5)
                TCAN_RX[rxMailbox].rxcmd.byte[0u] |= TCAN_RX_ACK_MSG;
            #else  /* CY_PSOC4 */
                TCAN_RX_CMD_REG(rxMailbox) |= TCAN_RX_ACK_MSG;
            #endif /* CY_PSOC3 || CY_PSOC5 */
        }
}


#if (TCAN_RX0_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg0
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 0 Interrupt. Clears the
    *  Receive Message 0 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg0(void) 
    {
        /* `#START MESSAGE_0_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_0_CALLBACK
            TCAN_ReceiveMsg_0_Callback();
        #endif /* TCAN_RECEIVE_MSG_0_CALLBACK */

        TCAN_RX_ACK_MESSAGE(0u);
    }
#endif /* TCAN_RX0_FUNC_ENABLE */


#if (TCAN_RX1_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:    TCAN_ReceiveMsg1
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 1 Interrupt. Clears the
    *  Receive Message 1 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg1(void) 
    {
        /* `#START MESSAGE_1_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_1_CALLBACK
            TCAN_ReceiveMsg_1_Callback();
        #endif /* TCAN_RECEIVE_MSG_1_CALLBACK */

        TCAN_RX_ACK_MESSAGE(1u);
    }
#endif /* TCAN_RX1_FUNC_ENABLE */


#if (TCAN_RX2_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg2
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 2 Interrupt. Clears the
    *  Receive Message 2 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg2(void) 
    {
        /* `#START MESSAGE_2_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_2_CALLBACK
            TCAN_ReceiveMsg_2_Callback();
        #endif /* TCAN_RECEIVE_MSG_2_CALLBACK */

        TCAN_RX_ACK_MESSAGE(2u);
    }
#endif /* TCAN_RX2_FUNC_ENABLE */


#if (TCAN_RX3_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg3
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 3 Interrupt. Clears the
    *  Receive Message 3 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg3(void) 
    {
        /* `#START MESSAGE_3_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_3_CALLBACK
            TCAN_ReceiveMsg_3_Callback();
        #endif /* TCAN_RECEIVE_MSG_3_CALLBACK */

        TCAN_RX_ACK_MESSAGE(3u);
    }
#endif /* TCAN_RX3_FUNC_ENABLE */


#if (TCAN_RX4_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg4
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 4 Interrupt. Clears the
    *  Receive Message 4 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg4(void) 
    {
        /* `#START MESSAGE_4_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_4_CALLBACK
            TCAN_ReceiveMsg_4_Callback();
        #endif /* TCAN_RECEIVE_MSG_4_CALLBACK */

        TCAN_RX_ACK_MESSAGE(4u);
    }
#endif /* TCAN_RX4_FUNC_ENABLE */


#if (TCAN_RX5_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg5
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 5 Interrupt. Clears the
    *  Receive Message 5 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg5(void) 
    {
        /* `#START MESSAGE_5_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_5_CALLBACK
            TCAN_ReceiveMsg_5_Callback();
        #endif /* TCAN_RECEIVE_MSG_5_CALLBACK */

        TCAN_RX_ACK_MESSAGE(5u);
    }
#endif /* TCAN_RX5_FUNC_ENABLE */


#if (TCAN_RX6_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg6
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 6 Interrupt. Clears the
    *  Receive Message 6 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg6(void) 
    {
        /* `#START MESSAGE_6_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_6_CALLBACK
            TCAN_ReceiveMsg_6_Callback();
        #endif /* TCAN_RECEIVE_MSG_6_CALLBACK */

        TCAN_RX_ACK_MESSAGE(6u);
    }
#endif /* TCAN_RX6_FUNC_ENABLE */


#if (TCAN_RX7_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg7
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 7 Interrupt. Clears the
    *  Receive Message 7 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg7(void) 
    {
        /* `#START MESSAGE_7_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_7_CALLBACK
            TCAN_ReceiveMsg_7_Callback();
        #endif /* TCAN_RECEIVE_MSG_7_CALLBACK */

        TCAN_RX_ACK_MESSAGE(7u);
    }
#endif /* TCAN_RX7_FUNC_ENABLE */


#if (TCAN_RX8_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg8
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 8 Interrupt. Clears the
    *  Receive Message 8 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg8(void) 
    {
        /* `#START MESSAGE_8_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_8_CALLBACK
            TCAN_ReceiveMsg_8_Callback();
        #endif /* TCAN_RECEIVE_MSG_8_CALLBACK */

        TCAN_RX_ACK_MESSAGE(8u);
    }
#endif /* TCAN_RX8_FUNC_ENABLE */


#if (TCAN_RX9_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg9
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 9 Interrupt. Clears the
    *  Receive Message 9 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg9(void) 
    {
        /* `#START MESSAGE_9_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_9_CALLBACK
            TCAN_ReceiveMsg_9_Callback();
        #endif /* TCAN_RECEIVE_MSG_9_CALLBACK */

        TCAN_RX_ACK_MESSAGE(9u);
    }
#endif /* TCAN_RX9_FUNC_ENABLE */


#if (TCAN_RX10_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg10
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 10 Interrupt. Clears the
    *  Receive Message 10 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg10(void) 
    {
        /* `#START MESSAGE_10_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_10_CALLBACK
            TCAN_ReceiveMsg_10_Callback();
        #endif /* TCAN_RECEIVE_MSG_10_CALLBACK */

        TCAN_RX_ACK_MESSAGE(10u);
    }
#endif /* TCAN_RX10_FUNC_ENABLE */


#if (TCAN_RX11_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg11
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 11 Interrupt. Clears the
    *  Receive Message 11 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg11(void) 
    {
        /* `#START MESSAGE_11_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_11_CALLBACK
            TCAN_ReceiveMsg_11_Callback();
        #endif /* TCAN_RECEIVE_MSG_11_CALLBACK */

        TCAN_RX_ACK_MESSAGE(11u);
    }
#endif /* TCAN_RX11_FUNC_ENABLE */


#if (TCAN_RX12_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg12
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 12 Interrupt. Clears the
    *  Receive Message 12 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg12(void) 
    {
        /* `#START MESSAGE_12_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_12_CALLBACK
            TCAN_ReceiveMsg_12_Callback();
        #endif /* TCAN_RECEIVE_MSG_12_CALLBACK */

        TCAN_RX_ACK_MESSAGE(12u);
    }
#endif /* TCAN_RX12_FUNC_ENABLE */


#if (TCAN_RX13_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg13
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 13 Interrupt. Clears the
    *  Receive Message 13 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg13(void) 
    {
        /* `#START MESSAGE_13_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_13_CALLBACK
            TCAN_ReceiveMsg_13_Callback();
        #endif /* TCAN_RECEIVE_MSG_13_CALLBACK */

        TCAN_RX_ACK_MESSAGE(13u);
    }
#endif /* TCAN_RX13_FUNC_ENABLE */


#if (TCAN_RX14_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg14
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 14 Interrupt. Clears the
    *  Receive Message 14 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg14(void) 
    {
        /* `#START MESSAGE_14_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_14_CALLBACK
            TCAN_ReceiveMsg_14_Callback();
        #endif /* TCAN_RECEIVE_MSG_14_CALLBACK */

        TCAN_RX_ACK_MESSAGE(14u);
    }
#endif /* TCAN_RX14_FUNC_ENABLE */


#if (TCAN_RX15_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   TCAN_ReceiveMsg15
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to Receive Message 15 Interrupt. Clears the
    *  Receive Message 15 interrupt flag. Generated only for the Receive mailbox
    *  designed as Full.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on the Customer code.
    *
    *******************************************************************************/
    void TCAN_ReceiveMsg15(void) 
    {
        /* `#START MESSAGE_15_RECEIVED` */

        /* `#END` */

        #ifdef TCAN_RECEIVE_MSG_15_CALLBACK
            TCAN_ReceiveMsg_15_Callback();
        #endif /* TCAN_RECEIVE_MSG_15_CALLBACK */

        TCAN_RX_ACK_MESSAGE(15u);
    }
#endif /* TCAN_RX15_FUNC_ENABLE */


/* [] END OF FILE */
