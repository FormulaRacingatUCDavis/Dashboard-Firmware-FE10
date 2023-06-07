/*******************************************************************************
* File Name: CAN_TX_RX_func.c
* Version 3.0
*
* Description:
*  There are functions process "Full" Receive and Transmit mailboxes:
*     - CAN_SendMsg0-7();
*     - CAN_ReceiveMsg0-15();
*  Transmission of message, and receive routine for "Basic" mailboxes:
*     - CAN_SendMsg();
*     - CAN_TxCancel();
*     - CAN_ReceiveMsg();
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

#include "CAN.h"
#include "cyapicallbacks.h"

/* `#START TX_RX_FUNCTION` */

/* `#END` */


/*******************************************************************************
* FUNCTION NAME:   CAN_SendMsg
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
*    CAN_FAIL              The function failed
*
*******************************************************************************/
uint8 CAN_SendMsg(const CAN_TX_MSG *message) 
{
    uint8 i, j, shift;
    uint8 retry = 0u;
    uint8 result = CAN_FAIL;
    uint32 regTemp;

    while (retry < CAN_RETRY_NUMBER)
    {
        shift = 1u;    /* Start from first mailbox */
        for (i = 0u; i < CAN_NUMBER_OF_TX_MAILBOXES; i++)
        {
            /* Find Basic TX mailboxes */
            if ((CAN_TX_MAILBOX_TYPE & shift) == 0u)
            {
                /* Find free mailbox */
                #if (CY_PSOC3 || CY_PSOC5)
                    if ((CAN_BUF_SR_REG.byte[2] & shift) == 0u)
                #else  /* CY_PSOC4 */
                    if ((CAN_BUF_SR_REG &
                        (uint32) ((uint32) shift << CAN_TWO_BYTE_OFFSET)) == 0u)
                #endif /* CY_PSOC3 || CY_PSOC5 */
                    {
                        regTemp = 0u;

                        /* Set message parameters */
                        if (message->rtr != CAN_STANDARD_MESSAGE)
                        {
                            regTemp = CAN_TX_RTR_MASK;    /* RTR message Enable */
                        }

                        if (message->ide == CAN_STANDARD_MESSAGE)
                        {
                            CAN_SET_TX_ID_STANDARD_MSG(i, message->id);
                        }
                        else
                        {
                            regTemp |= CAN_TX_IDE_MASK;
                            CAN_SET_TX_ID_EXTENDED_MSG(i, message->id);
                        }

                        if (message->dlc < CAN_TX_DLC_MAX_VALUE)
                        {
                            regTemp |= ((uint32) message->dlc) << CAN_TWO_BYTE_OFFSET;
                        }
                        else
                        {
                            regTemp |= CAN_TX_DLC_UPPER_VALUE;
                        }

                        if (message->irq != CAN_TRANSMIT_INT_DISABLE)
                        {
                            regTemp |= CAN_TX_INT_ENABLE_MASK;    /* Transmit Interrupt Enable */
                        }

                        for (j = 0u; (j < message->dlc) && (j < CAN_TX_DLC_MAX_VALUE); j++)
                        {
                            #if (CY_PSOC3 || CY_PSOC5)
                                CAN_TX_DATA_BYTE(i, j) = message->msg->byte[j];
                            #else /* CY_PSOC4 */
                                CAN_TX_DATA_BYTE(i, j, message->msg->byte[j]);
                            #endif /* CY_PSOC3 || CY_PSOC5 */
                        }

                        /* Disable isr */
    CyIntDisable(CAN_ISR_NUMBER);

                        /* WPN[23] and WPN[3] set to 1 for write to CAN Control reg */
                        CY_SET_REG32(CAN_TX_CMD_PTR(i), (regTemp | CAN_TX_WPN_SET));

                        #if (CY_PSOC3 || CY_PSOC5)
                            CY_SET_REG32(CAN_TX_CMD_PTR(i), CAN_SEND_MESSAGE);
                        #else /* CY_PSOC4 */
                            if (message->sst != CAN_STANDARD_MESSAGE)
                            {
                                /* Single Shot Transmission */
                                CAN_TX_CMD_REG(i) |= CAN_SEND_MESSAGE |
                                CAN_TX_ABORT_MASK;
                            }
                            else
                            {
                                CAN_TX_CMD_REG(i) |= CAN_SEND_MESSAGE;
                            }
                        #endif /* CY_PSOC3 || CY_PSOC5 */

                        /* Enable isr */
    CyIntEnable(CAN_ISR_NUMBER);

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
* FUNCTION NAME:   CAN_TxCancel
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
void CAN_TxCancel(uint8 bufferId) 
{
    if (bufferId < CAN_NUMBER_OF_TX_MAILBOXES)
    {
        CAN_TX_ABORT_MESSAGE(bufferId);
    }
}


#if (CAN_TX0_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_SendMsgDRIVER_SWITCHES
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
    *    CAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 CAN_SendMsgDRIVER_SWITCHES(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((CAN_TX[0u].txcmd.byte[0u] & CAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((CAN_TX_CMD_REG(0u) & CAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = CAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_DRIVER_SWITCHES_TRASMITTED` */

                /* `#END` */

                #ifdef CAN_SEND_MSG_DRIVER_SWITCHES_CALLBACK
                    CAN_SendMsg_DRIVER_SWITCHES_Callback();
                #endif /* CAN_SEND_MSG_DRIVER_SWITCHES_CALLBACK */

                CY_SET_REG32(CAN_TX_CMD_PTR(0u),
                CY_GET_REG32(CAN_TX_CMD_PTR(0u)) | CAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* CAN_TX0_FUNC_ENABLE */


#if (CAN_TX1_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_SendMsg1
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
    *    CAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 CAN_SendMsg1(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((CAN_TX[1u].txcmd.byte[0u] & CAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((CAN_TX_CMD_REG(1u) & CAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = CAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_1_TRASMITTED` */

                /* `#END` */

                #ifdef CAN_SEND_MSG_1_CALLBACK
                    CAN_SendMsg_1_Callback();
                #endif /* CAN_SEND_MSG_1_CALLBACK */

                CY_SET_REG32(CAN_TX_CMD_PTR(1u),
                CY_GET_REG32(CAN_TX_CMD_PTR(1u)) | CAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* CAN_TX1_FUNC_ENABLE */


#if (CAN_TX2_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_SendMsg2
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
    *    CAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 CAN_SendMsg2(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((CAN_TX[2u].txcmd.byte[0u] & CAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((CAN_TX_CMD_REG(2u) & CAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = CAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_2_TRASMITTED` */

                /* `#END` */

                #ifdef CAN_SEND_MSG_2_CALLBACK
                    CAN_SendMsg_2_Callback();
                #endif /* CAN_SEND_MSG_2_CALLBACK */

                CY_SET_REG32(CAN_TX_CMD_PTR(2u),
                CY_GET_REG32(CAN_TX_CMD_PTR(2u)) | CAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* CAN_TX2_FUNC_ENABLE */


#if (CAN_TX3_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_SendMsg3
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
    *    CAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 CAN_SendMsg3(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((CAN_TX[3u].txcmd.byte[0u] & CAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((CAN_TX_CMD_REG(3u) & CAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = CAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_3_TRASMITTED` */

                /* `#END` */

                #ifdef CAN_SEND_MSG_3_CALLBACK
                    CAN_SendMsg_3_Callback();
                #endif /* CAN_SEND_MSG_3_CALLBACK */

                CY_SET_REG32(CAN_TX_CMD_PTR(3u),
                CY_GET_REG32(CAN_TX_CMD_PTR(3u)) | CAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* CAN_TX3_FUNC_ENABLE */


#if (CAN_TX4_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_SendMsg4
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
    *    CAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 CAN_SendMsg4(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((CAN_TX[4u].txcmd.byte[0u] & CAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((CAN_TX_CMD_REG(4u) & CAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = CAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_4_TRASMITTED` */

                /* `#END` */

                #ifdef CAN_SEND_MSG_4_CALLBACK
                    CAN_SendMsg_4_Callback();
                #endif /* CAN_SEND_MSG_4_CALLBACK */

                CY_SET_REG32(CAN_TX_CMD_PTR(4u),
                CY_GET_REG32(CAN_TX_CMD_PTR(4u)) | CAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* CAN_TX4_FUNC_ENABLE */


#if (CAN_TX5_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_SendMsg5
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
    *    CAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 CAN_SendMsg5(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((CAN_TX[5u].txcmd.byte[0u] & CAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((CAN_TX_CMD_REG(5u) & CAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = CAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_5_TRASMITTED` */

                /* `#END` */

                #ifdef CAN_SEND_MSG_5_CALLBACK
                    CAN_SendMsg_5_Callback();
                #endif /* CAN_SEND_MSG_5_CALLBACK */

                CY_SET_REG32(CAN_TX_CMD_PTR(5u),
                CY_GET_REG32(CAN_TX_CMD_PTR(5u)) | CAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* CAN_TX5_FUNC_ENABLE */


#if (CAN_TX6_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_SendMsg6
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
    *    CAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 CAN_SendMsg6(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((CAN_TX[6u].txcmd.byte[0u] & CAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((CAN_TX_CMD_REG(6u) & CAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = CAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_6_TRASMITTED` */

                /* `#END` */

                #ifdef CAN_SEND_MSG_6_CALLBACK
                    CAN_SendMsg_6_Callback();
                #endif /* CAN_SEND_MSG_6_CALLBACK */

                CY_SET_REG32(CAN_TX_CMD_PTR(6u),
                CY_GET_REG32(CAN_TX_CMD_PTR(6u)) | CAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* CAN_TX6_FUNC_ENABLE */


#if (CAN_TX7_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_SendMsg7)
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
    *    CAN_FAIL              The function failed
    *
    *******************************************************************************/
    uint8 CAN_SendMsg7(void) 
    {
        uint8 result = CYRET_SUCCESS;

        #if (CY_PSOC3 || CY_PSOC5)
            if ((CAN_TX[7u].txcmd.byte[0u] & CAN_TX_REQUEST_PENDING) != 0u)
        #else  /* CY_PSOC4 */
            if ((CAN_TX_CMD_REG(7u) & CAN_TX_REQUEST_PENDING) != 0u)
        #endif /* CY_PSOC3 || CY_PSOC5 */
            {
                result = CAN_FAIL;
            }
            else
            {
                /* `#START MESSAGE_7_TRASMITTED` */

                /* `#END` */

                #ifdef CAN_SEND_MSG_7_CALLBACK
                    CAN_SendMsg_7_Callback();
                #endif /* CAN_SEND_MSG_7_CALLBACK */

                CY_SET_REG32(CAN_TX_CMD_PTR(7u),
                CY_GET_REG32(CAN_TX_CMD_PTR(7u)) | CAN_SEND_MESSAGE);
            }

        return (result);
    }
#endif /* CAN_TX7_FUNC_ENABLE */


/*******************************************************************************
* FUNCTION NAME:   CAN_ReceiveMsg
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
void CAN_ReceiveMsg(uint8 rxMailbox) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        if ((CAN_RX[rxMailbox].rxcmd.byte[0u] & CAN_RX_ACK_MSG) != 0u)
    #else  /* CY_PSOC4 */
        if ((CAN_RX_CMD_REG(rxMailbox) & CAN_RX_ACK_MSG) != 0u)
    #endif /* CY_PSOC3 || CY_PSOC5 */
        {
            /* `#START MESSAGE_BASIC_RECEIVED` */

            /* `#END` */

            #ifdef CAN_RECEIVE_MSG_CALLBACK
                CAN_ReceiveMsg_Callback();
            #endif /* CAN_RECEIVE_MSG_CALLBACK */

            #if (CY_PSOC3 || CY_PSOC5)
                CAN_RX[rxMailbox].rxcmd.byte[0u] |= CAN_RX_ACK_MSG;
            #else  /* CY_PSOC4 */
                CAN_RX_CMD_REG(rxMailbox) |= CAN_RX_ACK_MSG;
            #endif /* CY_PSOC3 || CY_PSOC5 */
        }
}


#if (CAN_RX0_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsgVEHICLE_STATE
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
    void CAN_ReceiveMsgVEHICLE_STATE(void) 
    {
        /* `#START MESSAGE_VEHICLE_STATE_RECEIVED` */
        state = CAN_RX_DATA_BYTE5(CAN_RX_MAILBOX_VEHICLE_STATE);
        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_VEHICLE_STATE_CALLBACK
            CAN_ReceiveMsg_VEHICLE_STATE_Callback();
        #endif /* CAN_RECEIVE_MSG_VEHICLE_STATE_CALLBACK */

        CAN_RX_ACK_MESSAGE(0u);
    }
#endif /* CAN_RX0_FUNC_ENABLE */


#if (CAN_RX1_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:    CAN_ReceiveMsgBSPD_FLAGS
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
    void CAN_ReceiveMsgBSPD_FLAGS(void) 
    {
        /* `#START MESSAGE_BSPD_FLAGS_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_BSPD_FLAGS_CALLBACK
            CAN_ReceiveMsg_BSPD_FLAGS_Callback();
        #endif /* CAN_RECEIVE_MSG_BSPD_FLAGS_CALLBACK */

        CAN_RX_ACK_MESSAGE(1u);
    }
#endif /* CAN_RX1_FUNC_ENABLE */


#if (CAN_RX2_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsgBMS_STATUS_MSG
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
    void CAN_ReceiveMsgBMS_STATUS_MSG(void) 
    {
        /* `#START MESSAGE_BMS_STATUS_MSG_RECEIVED` */
        PACK_TEMP = CAN_RX_DATA_BYTE1(CAN_RX_MAILBOX_BMS_STATUS_MSG);
        soc = CAN_RX_DATA_BYTE2(CAN_RX_MAILBOX_BMS_STATUS_MSG);
        bms_status = CAN_RX_DATA_BYTE3(CAN_RX_MAILBOX_BMS_STATUS_MSG) << 8;    // bms error flags
        bms_status |= CAN_RX_DATA_BYTE4(CAN_RX_MAILBOX_BMS_STATUS_MSG);        // bms error flags
        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_BMS_STATUS_MSG_CALLBACK
            CAN_ReceiveMsg_BMS_STATUS_MSG_Callback();
        #endif /* CAN_RECEIVE_MSG_BMS_STATUS_MSG_CALLBACK */

        CAN_RX_ACK_MESSAGE(2u);
    }
#endif /* CAN_RX2_FUNC_ENABLE */


#if (CAN_RX3_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsgBMS_VOLTAGES
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
    void CAN_ReceiveMsgBMS_VOLTAGES(void) 
    {
        /* `#START MESSAGE_BMS_VOLTAGES_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_BMS_VOLTAGES_CALLBACK
            CAN_ReceiveMsg_BMS_VOLTAGES_Callback();
        #endif /* CAN_RECEIVE_MSG_BMS_VOLTAGES_CALLBACK */

        CAN_RX_ACK_MESSAGE(3u);
    }
#endif /* CAN_RX3_FUNC_ENABLE */


#if (CAN_RX4_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsgBMS_TEMPERATURES
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
    void CAN_ReceiveMsgBMS_TEMPERATURES(void) 
    {
        /* `#START MESSAGE_BMS_TEMPERATURES_RECEIVED` */
        
        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_BMS_TEMPERATURES_CALLBACK
            CAN_ReceiveMsg_BMS_TEMPERATURES_Callback();
        #endif /* CAN_RECEIVE_MSG_BMS_TEMPERATURES_CALLBACK */

        CAN_RX_ACK_MESSAGE(4u);
    }
#endif /* CAN_RX4_FUNC_ENABLE */


#if (CAN_RX5_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsgPEI_ESTOP
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
    void CAN_ReceiveMsgPEI_ESTOP(void) 
    {
        /* `#START MESSAGE_PEI_ESTOP_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_PEI_ESTOP_CALLBACK
            CAN_ReceiveMsg_PEI_ESTOP_Callback();
        #endif /* CAN_RECEIVE_MSG_PEI_ESTOP_CALLBACK */

        CAN_RX_ACK_MESSAGE(5u);
    }
#endif /* CAN_RX5_FUNC_ENABLE */


#if (CAN_RX6_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsgPEI_CURRENT_SHUTDOWN
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
    void CAN_ReceiveMsgPEI_CURRENT_SHUTDOWN(void) 
    {
        /* `#START MESSAGE_PEI_CURRENT_SHUTDOWN_RECEIVED` */
        CURRENT = CAN_RX_DATA_BYTE1(CAN_RX_MAILBOX_PEI_CURRENT_SHUTDOWN) << 8; // BYTE #s start at 1 bruh cringe
        CURRENT |= CAN_RX_DATA_BYTE2(CAN_RX_MAILBOX_PEI_CURRENT_SHUTDOWN);
        shutdown_flags = CAN_RX_DATA_BYTE3(CAN_RX_MAILBOX_PEI_CURRENT_SHUTDOWN);
        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_PEI_CURRENT_SHUTDOWN_CALLBACK
            CAN_ReceiveMsg_PEI_CURRENT_SHUTDOWN_Callback();
        #endif /* CAN_RECEIVE_MSG_PEI_CURRENT_SHUTDOWN_CALLBACK */

        CAN_RX_ACK_MESSAGE(6u);
    }
#endif /* CAN_RX6_FUNC_ENABLE */


#if (CAN_RX7_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsgMC_VOLTAGE_INFO
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
    void CAN_ReceiveMsgMC_VOLTAGE_INFO(void) 
    {
        /* `#START MESSAGE_MC_VOLTAGE_INFO_RECEIVED` */
        CAPACITOR_VOLT = CAN_RX_DATA_BYTE1(CAN_RX_MAILBOX_MC_VOLTAGE_INFO) << 8; // upper bits
        CAPACITOR_VOLT |= CAN_RX_DATA_BYTE2(CAN_RX_MAILBOX_MC_VOLTAGE_INFO); // lower bits
        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_MC_VOLTAGE_INFO_CALLBACK
            CAN_ReceiveMsg_MC_VOLTAGE_INFO_Callback();
        #endif /* CAN_RECEIVE_MSG_MC_VOLTAGE_INFO_CALLBACK */

        CAN_RX_ACK_MESSAGE(7u);
    }
#endif /* CAN_RX7_FUNC_ENABLE */


#if (CAN_RX8_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsgMC_INTERNAL_STATES
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
    void CAN_ReceiveMsgMC_INTERNAL_STATES(void) 
    {
        /* `#START MESSAGE_MC_INTERNAL_STATES_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_MC_INTERNAL_STATES_CALLBACK
            CAN_ReceiveMsg_MC_INTERNAL_STATES_Callback();
        #endif /* CAN_RECEIVE_MSG_MC_INTERNAL_STATES_CALLBACK */

        CAN_RX_ACK_MESSAGE(8u);
    }
#endif /* CAN_RX8_FUNC_ENABLE */


#if (CAN_RX9_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsg9
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
    void CAN_ReceiveMsg9(void) 
    {
        /* `#START MESSAGE_9_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_9_CALLBACK
            CAN_ReceiveMsg_9_Callback();
        #endif /* CAN_RECEIVE_MSG_9_CALLBACK */

        CAN_RX_ACK_MESSAGE(9u);
    }
#endif /* CAN_RX9_FUNC_ENABLE */


#if (CAN_RX10_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsg10
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
    void CAN_ReceiveMsg10(void) 
    {
        /* `#START MESSAGE_10_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_10_CALLBACK
            CAN_ReceiveMsg_10_Callback();
        #endif /* CAN_RECEIVE_MSG_10_CALLBACK */

        CAN_RX_ACK_MESSAGE(10u);
    }
#endif /* CAN_RX10_FUNC_ENABLE */


#if (CAN_RX11_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsg11
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
    void CAN_ReceiveMsg11(void) 
    {
        /* `#START MESSAGE_11_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_11_CALLBACK
            CAN_ReceiveMsg_11_Callback();
        #endif /* CAN_RECEIVE_MSG_11_CALLBACK */

        CAN_RX_ACK_MESSAGE(11u);
    }
#endif /* CAN_RX11_FUNC_ENABLE */


#if (CAN_RX12_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsg12
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
    void CAN_ReceiveMsg12(void) 
    {
        /* `#START MESSAGE_12_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_12_CALLBACK
            CAN_ReceiveMsg_12_Callback();
        #endif /* CAN_RECEIVE_MSG_12_CALLBACK */

        CAN_RX_ACK_MESSAGE(12u);
    }
#endif /* CAN_RX12_FUNC_ENABLE */


#if (CAN_RX13_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsg13
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
    void CAN_ReceiveMsg13(void) 
    {
        /* `#START MESSAGE_13_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_13_CALLBACK
            CAN_ReceiveMsg_13_Callback();
        #endif /* CAN_RECEIVE_MSG_13_CALLBACK */

        CAN_RX_ACK_MESSAGE(13u);
    }
#endif /* CAN_RX13_FUNC_ENABLE */


#if (CAN_RX14_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsg14
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
    void CAN_ReceiveMsg14(void) 
    {
        /* `#START MESSAGE_14_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_14_CALLBACK
            CAN_ReceiveMsg_14_Callback();
        #endif /* CAN_RECEIVE_MSG_14_CALLBACK */

        CAN_RX_ACK_MESSAGE(14u);
    }
#endif /* CAN_RX14_FUNC_ENABLE */


#if (CAN_RX15_FUNC_ENABLE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ReceiveMsg15
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
    void CAN_ReceiveMsg15(void) 
    {
        /* `#START MESSAGE_15_RECEIVED` */

        /* `#END` */

        #ifdef CAN_RECEIVE_MSG_15_CALLBACK
            CAN_ReceiveMsg_15_Callback();
        #endif /* CAN_RECEIVE_MSG_15_CALLBACK */

        CAN_RX_ACK_MESSAGE(15u);
    }
#endif /* CAN_RX15_FUNC_ENABLE */


/* [] END OF FILE */
