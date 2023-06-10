/*******************************************************************************
* File Name: TCAN.h
* Version 3.0
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the CAN Component.
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

#if !defined(CY_CAN_TCAN_H)
#define CY_CAN_TCAN_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
#include "cyapicallbacks.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component CAN_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 TCAN_initVar;

#define TCAN_INT_ISR_DISABLE                (0u)


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define TCAN_ARB_LOST                       (0u)
#define TCAN_OVERLOAD                       (0u)
#define TCAN_BIT_ERR                        (0u)
#define TCAN_STUFF_ERR                      (0u)
#define TCAN_ACK_ERR                        (0u)
#define TCAN_FORM_ERR                       (0u)
#define TCAN_CRC_ERR                        (0u)
#define TCAN_BUS_OFF                        (1u)
#define TCAN_RX_MSG_LOST                    (0u)
#define TCAN_TX_MESSAGE                     (0u)
#define TCAN_RX_MESSAGE                     (1u)
#define TCAN_ARB_LOST_USE_HELPER            (1u)
#define TCAN_OVERLOAD_USE_HELPER            (1u)
#define TCAN_BIT_ERR_USE_HELPER             (1u)
#define TCAN_STUFF_ERR_USE_HELPER           (1u)
#define TCAN_ACK_ERR_USE_HELPER             (1u)
#define TCAN_FORM_ERR_USE_HELPER            (1u)
#define TCAN_CRC_ERR_USE_HELPER             (1u)
#define TCAN_BUS_OFF_USE_HELPER             (1u)
#define TCAN_RX_MSG_LOST_USE_HELPER         (1u)
#define TCAN_TX_MESSAGE_USE_HELPER          (1u)
#define TCAN_RX_MESSAGE_USE_HELPER          (1u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define TCAN_RTR_AUTO_MSG_SENT          (0u)
    #define TCAN_STUCK_AT_ZERO              (0u)
    #define TCAN_SST_FAILURE                (0u)

    #define TCAN_RTR_MESSAGE_USE_HELPER     (1u)
    #define TCAN_STUCK_AT_ZERO_USE_HELPER   (1u)
    #define TCAN_SST_FAILURE_USE_HELPER     (1u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define TCAN_ADVANCED_INTERRUPT_CFG         (0u)

/* TX/RX Function Enable */
#define TCAN_TX0_FUNC_ENABLE           (0u)
#define TCAN_TX1_FUNC_ENABLE           (0u)
#define TCAN_TX2_FUNC_ENABLE           (0u)
#define TCAN_TX3_FUNC_ENABLE           (0u)
#define TCAN_TX4_FUNC_ENABLE           (0u)
#define TCAN_TX5_FUNC_ENABLE           (0u)
#define TCAN_TX6_FUNC_ENABLE           (0u)
#define TCAN_TX7_FUNC_ENABLE           (0u)
#define TCAN_RX0_FUNC_ENABLE           (0u)
#define TCAN_RX1_FUNC_ENABLE           (0u)
#define TCAN_RX2_FUNC_ENABLE           (0u)
#define TCAN_RX3_FUNC_ENABLE           (0u)
#define TCAN_RX4_FUNC_ENABLE           (0u)
#define TCAN_RX5_FUNC_ENABLE           (0u)
#define TCAN_RX6_FUNC_ENABLE           (0u)
#define TCAN_RX7_FUNC_ENABLE           (0u)
#define TCAN_RX8_FUNC_ENABLE           (0u)
#define TCAN_RX9_FUNC_ENABLE           (0u)
#define TCAN_RX10_FUNC_ENABLE          (0u)
#define TCAN_RX11_FUNC_ENABLE          (0u)
#define TCAN_RX12_FUNC_ENABLE          (0u)
#define TCAN_RX13_FUNC_ENABLE          (0u)
#define TCAN_RX14_FUNC_ENABLE          (0u)
#define TCAN_RX15_FUNC_ENABLE          (0u)
#define TCAN_RX_MAILBOX_TYPE           (0x0u)
#define TCAN_TX_MAILBOX_TYPE           (0x0u)


/***************************************
*        Data Struct Definition
***************************************/

/* Struct for DATA of BASIC CAN mailbox */
typedef struct
{
    uint8 byte[8u];
} TCAN_DATA_BYTES_MSG;

/* Struct for DATA of CAN RX register */
typedef struct
{
    reg8 byte[8u];
} TCAN_DATA_BYTES;

/* Struct for 32-bit CAN register */
typedef struct
{
    reg8 byte[4u];
} TCAN_REG_32;

/* Struct for BASIC CAN mailbox to send messages */
typedef struct
{
    uint32 id;
    uint8 rtr;
    uint8 ide;
    uint8 dlc;
    uint8 irq;
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 sst;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */
    TCAN_DATA_BYTES_MSG *msg;
} TCAN_TX_MSG;

/* Constant configuration of CAN RX */
typedef struct
{
    uint8 rxmailbox;
    uint32 rxcmd;
    uint32 rxamr;
    uint32 rxacr;
} TCAN_RX_CFG;

/* Constant configuration of CAN TX */
typedef struct
{
    uint8 txmailbox;
    uint32 txcmd;
    uint32 txid;
} TCAN_TX_CFG;

/* CAN RX registers */
typedef struct
{
    TCAN_REG_32 rxcmd;
    TCAN_REG_32 rxid;
    TCAN_DATA_BYTES rxdata;
    TCAN_REG_32 rxamr;
    TCAN_REG_32 rxacr;
    TCAN_REG_32 rxamrd;
    TCAN_REG_32 rxacrd;
} TCAN_RX_STRUCT;

/* CAN TX registers */
typedef struct
{
    TCAN_REG_32 txcmd;
    TCAN_REG_32 txid;
    TCAN_DATA_BYTES txdata;
} TCAN_TX_STRUCT;

/* Sleep Mode API Support */
typedef struct
{
    uint8  enableState;
    #if (CY_PSOC3 || CY_PSOC5)
        uint32 intSr;
        uint32 intEn;
        uint32 cmd;
        uint32 cfg;
    #endif /* CY_PSOC3 || CY_PSOC5 */
} TCAN_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8  TCAN_Init(void) ;
uint8  TCAN_Start(void) ;
uint8  TCAN_Stop(void) ;
uint8  TCAN_Enable(void) ;
uint8  TCAN_GlobalIntEnable(void) ;
uint8  TCAN_GlobalIntDisable(void) ;
uint8  TCAN_SetPreScaler(uint16 bitrate) ;
uint8  TCAN_SetArbiter(uint8 arbiter) ;
uint8  TCAN_SetTsegSample(uint8 cfgTseg1, uint8 cfgTseg2, uint8 sjw, uint8 sm)
                                                ;
uint8  TCAN_SetRestartType(uint8 reset) ;
uint8  TCAN_SetEdgeMode(uint8 edge) ;
uint8  TCAN_SetOpMode(uint8 opMode) ;
uint8  TCAN_RXRegisterInit(reg32 *regAddr, uint32 config)
                                            ;
uint8  TCAN_SetIrqMask(uint16 mask) ;
uint8  TCAN_GetTXErrorFlag(void) ;
uint8  TCAN_GetRXErrorFlag(void) ;
uint8  TCAN_GetTXErrorCount(void) ;
uint8  TCAN_GetRXErrorCount(void) ;
uint8  TCAN_GetErrorState(void) ;
void   TCAN_Sleep(void) ;
void   TCAN_Wakeup(void) ;
void   TCAN_SaveConfig(void) ;
void   TCAN_RestoreConfig(void) ;

#if (!(CY_PSOC3 || CY_PSOC5))
    uint8  TCAN_SetSwapDataEndianness(uint8 swap);
    uint8  TCAN_SetErrorCaptureRegisterMode(uint8 ecrMode);
    uint32 TCAN_ReadErrorCaptureRegister(void);
    uint8  TCAN_ArmErrorCaptureRegister(void);
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#if (TCAN_ARB_LOST)
    void TCAN_ArbLostIsr(void) ;
#endif /* TCAN_ARB_LOST */
#if (TCAN_OVERLOAD)
    void TCAN_OvrLdErrorIsr(void) ;
#endif /* TCAN_OVERLOAD */
#if (TCAN_BIT_ERR)
    void TCAN_BitErrorIsr(void) ;
#endif /* TCAN_BIT_ERR */
#if (TCAN_STUFF_ERR)
    void TCAN_BitStuffErrorIsr(void) ;
#endif /* TCAN_STUFF_ERR */
#if (TCAN_ACK_ERR)
    void TCAN_AckErrorIsr(void) ;
#endif /* TCAN_ACK_ERR */
#if (TCAN_FORM_ERR)
    void TCAN_MsgErrorIsr(void) ;
#endif /* TCAN_FORM_ERR */
#if (TCAN_CRC_ERR)
    void TCAN_CrcErrorIsr(void) ;
#endif /* TCAN_CRC_ERR */
#if (TCAN_BUS_OFF)
    void TCAN_BusOffIsr(void) ;
#endif /* TCAN_BUS_OFF */
#if (TCAN_RX_MSG_LOST)
    void TCAN_MsgLostIsr(void) ;
#endif /* TCAN_RX_MSG_LOST */
#if (TCAN_TX_MESSAGE)
   void TCAN_MsgTXIsr(void) ;
#endif /* TCAN_TX_MESSAGE */
#if (TCAN_RX_MESSAGE)
    void TCAN_MsgRXIsr(void) ;
#endif /* TCAN_RX_MESSAGE */

#if (!(CY_PSOC3 || CY_PSOC5))
    #if (TCAN_RTR_AUTO_MSG_SENT)
        void TCAN_RtrAutoMsgSentIsr(void);
    #endif /* TCAN_RTR_MESSAGE */
    #if (TCAN_STUCK_AT_ZERO)
        void TCAN_StuckAtZeroIsr(void);
    #endif /* TCAN_STUCK_AT_ZERO */
    #if (TCAN_SST_FAILURE)
        void TCAN_SSTErrorIsr(void);
    #endif /* TCAN_SST_ERROR */
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

uint8 TCAN_RxBufConfig(const TCAN_RX_CFG *rxConfig) \
                                   ;
uint8 TCAN_TxBufConfig(const TCAN_TX_CFG *txConfig) \
                                   ;
uint8 TCAN_RxTxBuffersConfig(void) ;                                
uint8 TCAN_SendMsg(const TCAN_TX_MSG *message) ;
void  TCAN_TxCancel(uint8 bufferId) ;
void  TCAN_ReceiveMsg(uint8 rxMailbox) ;

#if (TCAN_TX0_FUNC_ENABLE)
    uint8 TCAN_SendMsg0(void) ;
#endif /* TCAN_TX0_FUNC_ENABLE */
#if (TCAN_TX1_FUNC_ENABLE)
    uint8 TCAN_SendMsg1(void) ;
#endif /* TCAN_TX1_FUNC_ENABLE */
#if (TCAN_TX2_FUNC_ENABLE)
    uint8 TCAN_SendMsg2(void) ;
#endif /* TCAN_TX2_FUNC_ENABLE */
#if (TCAN_TX3_FUNC_ENABLE)
    uint8 TCAN_SendMsg3(void) ;
#endif /* TCAN_TX3_FUNC_ENABLE */
#if (TCAN_TX4_FUNC_ENABLE)
    uint8 TCAN_SendMsg4(void) ;
#endif /* TCAN_TX4_FUNC_ENABLE */
#if (TCAN_TX5_FUNC_ENABLE)
    uint8 TCAN_SendMsg5(void) ;
#endif /* TCAN_TX5_FUNC_ENABLE */
#if (TCAN_TX6_FUNC_ENABLE)
    uint8 TCAN_SendMsg6(void) ;
#endif /* TCAN_TX6_FUNC_ENABLE */
#if (TCAN_TX7_FUNC_ENABLE)
    uint8 TCAN_SendMsg7(void) ;
#endif /* TCAN_TX7_FUNC_ENABLE */
#if (TCAN_RX0_FUNC_ENABLE)
    void TCAN_ReceiveMsg0(void) ;
#endif /* TCAN_RX0_FUNC_ENABLE */
#if (TCAN_RX1_FUNC_ENABLE)
    void TCAN_ReceiveMsg1(void) ;
#endif /* TCAN_RX1_FUNC_ENABLE */
#if (TCAN_RX2_FUNC_ENABLE)
    void TCAN_ReceiveMsg2(void) ;
#endif /* TCAN_RX2_FUNC_ENABLE */
#if (TCAN_RX3_FUNC_ENABLE)
    void TCAN_ReceiveMsg3(void) ;
#endif /* TCAN_RX3_FUNC_ENABLE */
#if (TCAN_RX4_FUNC_ENABLE)
    void TCAN_ReceiveMsg4(void) ;
#endif /* TCAN_RX4_FUNC_ENABLE */
#if (TCAN_RX5_FUNC_ENABLE)
    void TCAN_ReceiveMsg5(void) ;
#endif /* TCAN_RX5_FUNC_ENABLE */
#if (TCAN_RX6_FUNC_ENABLE)
    void TCAN_ReceiveMsg6(void) ;
#endif /* TCAN_RX6_FUNC_ENABLE */
#if (TCAN_RX7_FUNC_ENABLE)
    void TCAN_ReceiveMsg7(void) ;
#endif /* TCAN_RX7_FUNC_ENABLE */
#if (TCAN_RX8_FUNC_ENABLE)
    void TCAN_ReceiveMsg8(void) ;
#endif /* TCAN_RX8_FUNC_ENABLE */
#if (TCAN_RX9_FUNC_ENABLE)
    void TCAN_ReceiveMsg9(void) ;
#endif /* TCAN_RX9_FUNC_ENABLE */
#if (TCAN_RX10_FUNC_ENABLE)
    void TCAN_ReceiveMsg10(void) ;
#endif /* TCAN_RX10_FUNC_ENABLE */
#if (TCAN_RX11_FUNC_ENABLE)
    void TCAN_ReceiveMsg11(void) ;
#endif /* TCAN_RX11_FUNC_ENABLE */
#if (TCAN_RX12_FUNC_ENABLE)
    void TCAN_ReceiveMsg12(void) ;
#endif /* TCAN_RX12_FUNC_ENABLE */
#if (TCAN_RX13_FUNC_ENABLE)
    void TCAN_ReceiveMsg13(void) ;
#endif /* TCAN_RX13_FUNC_ENABLE */
#if (TCAN_RX14_FUNC_ENABLE)
    void TCAN_ReceiveMsg14(void) ;
#endif /* TCAN_RX14_FUNC_ENABLE */
#if (TCAN_RX15_FUNC_ENABLE)
    void TCAN_ReceiveMsg15(void) ;
#endif /* TCAN_RX15_FUNC_ENABLE */

#if(!TCAN_INT_ISR_DISABLE)
    /* Interrupt handler */
    CY_ISR_PROTO(TCAN_ISR);
#endif /* !TCAN_INT_ISR_DISABLE */


/***************************************
*           API Constants
***************************************/

#if (!TCAN_INT_ISR_DISABLE)
    /* Number of TCAN_isr interrupt */
    #define TCAN_ISR_NUMBER            ((uint8) TCAN_isr__INTC_NUMBER)
    /* Priority of TCAN_isr interrupt */
    #define TCAN_ISR_PRIORITY          ((uint8) TCAN_isr__INTC_PRIOR_NUM)
#endif /* !TCAN_INT_ISR_DISABLE */

/* One bit time in CAN clock cycles */
#define TCAN_ONE_BIT_TIME              ((TCAN_BITRATE + 1u) * \
        ((TCAN_CFG_REG_TSEG1 + 1u) + (TCAN_CFG_REG_TSEG2 + 1u) + 1u))

/* Timeout for CAN state machine to switch operation mode to Run */
#define TCAN_MODE_STATE_RUN_TIMEOUT    (12u * TCAN_ONE_BIT_TIME)
/* Timeout for CAN state machine to switch operation mode to Stop */
#define TCAN_MODE_STATE_STOP_TIMEOUT   (160u * TCAN_ONE_BIT_TIME)

/* One or more parameters to function were invalid. */
#define TCAN_FAIL                      (0x01u)
#define TCAN_OUT_OF_RANGE              (0x02u)

#if (CY_PSOC3 || CY_PSOC5)
    /* PM_ACT_CFG (Active Power Mode CFG Register) */
    #define TCAN_ACT_PWR_EN            (TCAN_CanIP__PM_ACT_MSK)    /* Power enable mask */
    /* PM_STBY_CFG (Alternate Active (Standby) Power Mode CFG Register) */
    #define TCAN_STBY_PWR_EN           (TCAN_CanIP__PM_STBY_MSK)   /* Power enable mask */
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Number of TX and RX mailboxes */
#define TCAN_NUMBER_OF_TX_MAILBOXES    (8u)
#define TCAN_NUMBER_OF_RX_MAILBOXES    (16u)

/* Error status of CAN */
#define TCAN_ERROR_ACTIVE              (0x00u)
#define TCAN_ERROR_PASIVE              (0x01u)
#define TCAN_ERROR_BUS_OFF             (0x10u)

/* Operation mode */
#define TCAN_INITIAL_MODE              (0x00u)
#define TCAN_STOP_MODE                 (0x00u)
#define TCAN_ACTIVE_RUN_MODE           (0x01u)
#define TCAN_LISTEN_ONLY_MODE          (0x02u)
#if (!(CY_PSOC3 || CY_PSOC5))
    #define TCAN_INTERNAL_LOOP_BACK    (0x06u)
    #define TCAN_EXTERNAL_LOOP_BACK    (0x04u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* TX Defines to link mailbox names with mailbox numbers */
#define TCAN_TX_MAILBOX_0              (0u)
#define TCAN_TX_MAILBOX_1              (1u)
#define TCAN_TX_MAILBOX_2              (2u)
#define TCAN_TX_MAILBOX_3              (3u)
#define TCAN_TX_MAILBOX_4              (4u)
#define TCAN_TX_MAILBOX_5              (5u)
#define TCAN_TX_MAILBOX_6              (6u)
#define TCAN_TX_MAILBOX_7              (7u)

/* RX Defines to link mailbox names with mailbox numbers */
#define TCAN_RX_MAILBOX_0              (0u)
#define TCAN_RX_MAILBOX_1              (1u)
#define TCAN_RX_MAILBOX_2              (2u)
#define TCAN_RX_MAILBOX_3              (3u)
#define TCAN_RX_MAILBOX_4              (4u)
#define TCAN_RX_MAILBOX_5              (5u)
#define TCAN_RX_MAILBOX_6              (6u)
#define TCAN_RX_MAILBOX_7              (7u)
#define TCAN_RX_MAILBOX_8              (8u)
#define TCAN_RX_MAILBOX_9              (9u)
#define TCAN_RX_MAILBOX_10             (10u)
#define TCAN_RX_MAILBOX_11             (11u)
#define TCAN_RX_MAILBOX_12             (12u)
#define TCAN_RX_MAILBOX_13             (13u)
#define TCAN_RX_MAILBOX_14             (14u)
#define TCAN_RX_MAILBOX_15             (15u)


/***************************************
*    Initial Parameter Constants
***************************************/

/* General */
#define TCAN_BITRATE                   (2u)
#define TCAN_CFG_REG_TSEG1             (13u - 1u)
#define TCAN_CFG_REG_TSEG2             (2u - 1u)
#define TCAN_CFG_REG_SJW               (2u - 1u)
#define TCAN_SAMPLING_MODE             (0u)
#define TCAN_ARBITER                   (0u)
#define TCAN_RESET_TYPE                (0u)
#define TCAN_SYNC_EDGE                 (0u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define TCAN_SWAP_DATA_END         (0u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* Interrupts */
#define TCAN_INT_ENABLE                (1u)

#if (CY_PSOC3 || CY_PSOC5)
    #define TCAN_INIT_INTERRUPT_MASK (((uint16) TCAN_INT_ENABLE) | \
                ((uint16) ((uint16) TCAN_ARB_LOST    <<  TCAN_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) TCAN_OVERLOAD    <<  TCAN_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) TCAN_BIT_ERR     <<  TCAN_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) TCAN_STUFF_ERR   <<  TCAN_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) TCAN_ACK_ERR     <<  TCAN_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) TCAN_FORM_ERR    <<  TCAN_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) TCAN_CRC_ERR     << (TCAN_ONE_BYTE_OFFSET          + \
                                                                     TCAN_CRC_ERROR_SHIFT)))       | \
                ((uint16) ((uint16) TCAN_BUS_OFF     << (TCAN_ONE_BYTE_OFFSET          + \
                                                                     TCAN_BUS_OFF_SHIFT)))         | \
                ((uint16) ((uint16) TCAN_RX_MSG_LOST << (TCAN_ONE_BYTE_OFFSET          + \
                                                                     TCAN_RX_MSG_LOST_SHIFT)))     | \
                ((uint16) ((uint16) TCAN_TX_MESSAGE  << (TCAN_ONE_BYTE_OFFSET          + \
                                                                     TCAN_TX_MESSAGE_SHIFT)))      | \
                ((uint16) ((uint16) TCAN_RX_MESSAGE  << (TCAN_ONE_BYTE_OFFSET          + \
                                                                     TCAN_RX_MESSAGE_SHIFT))))
#else /* CY_PSOC4 */
    #define TCAN_INIT_INTERRUPT_MASK    (((uint16) TCAN_INT_ENABLE) | \
                ((uint16) ((uint16) TCAN_ARB_LOST    <<  TCAN_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) TCAN_OVERLOAD    <<  TCAN_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) TCAN_BIT_ERR     <<  TCAN_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) TCAN_STUFF_ERR   <<  TCAN_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) TCAN_ACK_ERR     <<  TCAN_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) TCAN_FORM_ERR    <<  TCAN_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) TCAN_CRC_ERR     <<  TCAN_CRC_ERROR_SHIFT))        | \
                ((uint16) ((uint16) TCAN_BUS_OFF     <<  TCAN_BUS_OFF_SHIFT))          | \
                ((uint16) ((uint16) TCAN_RX_MSG_LOST <<  TCAN_RX_MSG_LOST_SHIFT))      | \
                ((uint16) ((uint16) TCAN_TX_MESSAGE  <<  TCAN_TX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) TCAN_RX_MESSAGE  <<  TCAN_RX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) TCAN_RTR_AUTO_MSG_SENT  << TCAN_RTR_MSG_SHIFT))    | \
                ((uint16) ((uint16) TCAN_STUCK_AT_ZERO << TCAN_STUCK_AT_ZERO_SHIFT))   | \
                ((uint16) ((uint16) TCAN_SST_FAILURE   << TCAN_SST_FAILURE_SHIFT)))
#endif /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*             Registers
***************************************/

#if (CY_PSOC3 || CY_PSOC5)
#define TCAN_TX          ( (volatile TCAN_TX_STRUCT XDATA *) TCAN_CanIP__TX0_CMD)
#define TCAN_RX          ( (volatile TCAN_RX_STRUCT XDATA *) TCAN_CanIP__RX0_CMD)
#define TCAN_INT_SR_REG  (*(volatile TCAN_REG_32 XDATA *) TCAN_CanIP__CSR_INT_SR)
#define TCAN_INT_SR_PTR  ( (reg32 *) TCAN_CanIP__CSR_INT_SR)
#define TCAN_INT_EN_REG  (*(volatile TCAN_REG_32 XDATA *) TCAN_CanIP__CSR_INT_EN)
#define TCAN_INT_EN_PTR  ( (reg32 *) TCAN_CanIP__CSR_INT_EN)
#define TCAN_BUF_SR_REG  (*(volatile TCAN_REG_32 XDATA *) TCAN_CanIP__CSR_BUF_SR)
#define TCAN_BUF_SR_PTR  ( (reg32 *) TCAN_CanIP__CSR_BUF_SR)
#define TCAN_ERR_SR_REG  (*(volatile TCAN_REG_32 XDATA *) TCAN_CanIP__CSR_ERR_SR)
#define TCAN_ERR_SR_PTR  ( (reg32 *) TCAN_CanIP__CSR_ERR_SR)
#define TCAN_CMD_REG     (*(volatile TCAN_REG_32 XDATA *) TCAN_CanIP__CSR_CMD)
#define TCAN_CMD_PTR     ( (reg32 *) TCAN_CanIP__CSR_CMD)
#define TCAN_CFG_REG     (*(volatile TCAN_REG_32 XDATA *) TCAN_CanIP__CSR_CFG)
#define TCAN_CFG_PTR     ( (reg32 *) TCAN_CanIP__CSR_CFG)

/* Power manager */
#define TCAN_PM_ACT_CFG_REG           (*(reg8 *) TCAN_CanIP__PM_ACT_CFG)
#define TCAN_PM_ACT_CFG_PTR           ( (reg8 *) TCAN_CanIP__PM_ACT_CFG)
#define TCAN_PM_STBY_CFG_REG          (*(reg8 *) TCAN_CanIP__PM_STBY_CFG)
#define TCAN_PM_STBY_CFG_PTR          ( (reg8 *) TCAN_CanIP__PM_STBY_CFG)

#define TCAN_RX_FIRST_REGISTER_PTR    ((reg32 *) TCAN_CanIP__RX0_CMD)
#define TCAN_RX_LAST_REGISTER_PTR     ((reg32 *) TCAN_CanIP__RX15_ACRD)

#else /* CY_PSOC4 */
#define TCAN_TX    ((volatile TCAN_TX_STRUCT XDATA *) TCAN_CanIP__CAN_TX0_CONTROL)
#define TCAN_RX    ((volatile TCAN_RX_STRUCT XDATA *) TCAN_CanIP__CAN_RX0_CONTROL)
#define TCAN_TX_REG                   (*(reg32 *) TCAN_CanIP__CAN_TX0_CONTROL)
#define TCAN_TX_PTR                   ( (reg32 *) TCAN_CanIP__CAN_TX0_CONTROL)
#define TCAN_RX_REG                   (*(reg32 *) TCAN_CanIP__CAN_RX0_CONTROL)
#define TCAN_RX_PTR                   ( (reg32 *) TCAN_CanIP__CAN_RX0_CONTROL)
#define TCAN_INT_SR_REG               (*(reg32 *) TCAN_CanIP__INT_STATUS)
#define TCAN_INT_SR_PTR               ( (reg32 *) TCAN_CanIP__INT_STATUS)
#define TCAN_INT_EN_REG               (*(reg32 *) TCAN_CanIP__INT_EBL)
#define TCAN_INT_EN_PTR               ( (reg32 *) TCAN_CanIP__INT_EBL)
#define TCAN_BUF_SR_REG               (*(reg32 *) TCAN_CanIP__BUFFER_STATUS)
#define TCAN_BUF_SR_PTR               ( (reg32 *) TCAN_CanIP__BUFFER_STATUS)
#define TCAN_ERR_SR_REG               (*(reg32 *) TCAN_CanIP__ERROR_STATUS)
#define TCAN_ERR_SR_PTR               ( (reg32 *) TCAN_CanIP__ERROR_STATUS)
#define TCAN_CNTL_REG                 (*(reg32 *) TCAN_CanIP__CNTL)
#define TCAN_CNTL_PTR                 ( (reg32 *) TCAN_CanIP__CNTL)
#define TCAN_CMD_REG                  (*(reg32 *) TCAN_CanIP__COMMAND)
#define TCAN_CMD_PTR                  ( (reg32 *) TCAN_CanIP__COMMAND)
#define TCAN_CFG_REG                  (*(reg32 *) TCAN_CanIP__CONFIG)
#define TCAN_CFG_PTR                  ( (reg32 *) TCAN_CanIP__CONFIG)
#define TCAN_ECR_REG                  (*(reg32 *) TCAN_CanIP__ECR)
#define TCAN_ECR_PTR                  ( (reg32 *) TCAN_CanIP__ECR)
#define TCAN_RX_FIRST_REGISTER_PTR    ( (reg32 *) TCAN_CanIP__CAN_RX0_CONTROL)
#define TCAN_RX_LAST_REGISTER_PTR     ( (reg32 *) TCAN_CanIP__CAN_RX15_ACR_DATA)

#define TCAN_TX_DATA_LO_REG(i)        (*(reg32 *) (&TCAN_TX[i].txdata))
#define TCAN_TX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&TCAN_TX[i].txdata) + \
                                                  TCAN_DATA_HIGH_ADDR))
#define TCAN_RX_DATA_LO_REG(i)        (*(reg32 *) (&TCAN_RX[i].rxdata))
#define TCAN_RX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&TCAN_RX[i].rxdata) + \
                                                  TCAN_DATA_HIGH_ADDR))
#endif /* (CY_PSOC3 || CY_PSOC5) */

#define TCAN_TX_CMD_PTR(i)            ( (reg32 *) (&TCAN_TX[i].txcmd))
#define TCAN_TX_CMD_REG(i)            (*(reg32 *) (&TCAN_TX[i].txcmd))
#define TCAN_RX_CMD_PTR(i)            ( (reg32 *) (&TCAN_RX[i].rxcmd))
#define TCAN_RX_CMD_REG(i)            (*(reg32 *) (&TCAN_RX[i].rxcmd))
#define TCAN_RX_ID_PTR(i)             ( (reg32 *) (&TCAN_RX[i].rxid))
#define TCAN_RX_ID_REG(i)             (*(reg32 *) (&TCAN_RX[i].rxid))
#define TCAN_TX_ID_PTR(i)             ( (reg32 *) (&TCAN_TX[i].txid))
#define TCAN_TX_ID_REG(i)             (*(reg32 *) (&TCAN_TX[i].txid))


/***************************************
*        Register Constants
***************************************/

/* Run/Stop mode */
#define TCAN_MODE_STOP                (0x00u)
#define TCAN_MODE_START               (0x01u)

/* Transmit buffer arbiter */
#define TCAN_ROUND_ROBIN              (0x00u)
#define TCAN_FIXED_PRIORITY           (0x01u)

/* Restart type */
#define TCAN_MANUAL_RESTART           (0x00u)
#define TCAN_AUTO_RESTART             (0x01u)

/* Sampling mode */
#define TCAN_ONE_SAMPLE_POINT         (0x00u)
#define TCAN_THREE_SAMPLE_POINTS      (0x01u)

/* Edge mode */
#define TCAN_EDGE_R_TO_D              (0x00u)
#define TCAN_BOTH_EDGES               (0x01u)

/* Extended identifier */
#define TCAN_STANDARD_MESSAGE         (0x00u)
#define TCAN_EXTENDED_MESSAGE         (0x01u)

/* Write Protect Mask for Basic and Full mailboxes */
#define TCAN_TX_WPN_CLEAR           ((uint32) (~TCAN_TX_WPN_SET))
#define TCAN_RX_WPN_CLEAR           ((uint32) (~TCAN_RX_WPN_SET))
#define TCAN_TX_RSVD_MASK           ((uint32) 0x00FF00FFu)
#define TCAN_TX_READ_BACK_MASK      (TCAN_TX_WPN_CLEAR & TCAN_TX_RSVD_MASK)
#define TCAN_RX_READ_BACK_MASK      (TCAN_RX_WPN_CLEAR & TCAN_TX_RSVD_MASK)
#define TCAN_RX_CMD_REG_WIDTH       (0x20u)

#if (CY_PSOC3 || CY_PSOC5)
    #define TCAN_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << TCAN_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (TCAN_TWO_BYTE_OFFSET + TCAN_TX_WPNH_SHIFT))))
    #define TCAN_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << TCAN_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (TCAN_TWO_BYTE_OFFSET + TCAN_RX_WPNH_SHIFT))))
#else  /* CY_PSOC4 */
    #define TCAN_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << TCAN_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << TCAN_TX_WPNH_SHIFT)))
    #define TCAN_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << TCAN_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << TCAN_RX_WPNH_SHIFT)))

    /* CAN IP Block Enable */
    #define TCAN_IP_ENABLE_SHIFT    (31u)
    #define TCAN_IP_ENABLE          ((uint32) ((uint32) 0x00000001u << TCAN_IP_ENABLE_SHIFT))

    /* Error Capture register mode setting */
    #define TCAN_ECR_FREE_RUNNING   (0x00u)
    #define TCAN_ECR_ERROR_CAPTURE  (0x01u)

    /* Swap Endian */
    #define TCAN_SWAP_ENDIANNESS_DISABLE  (0x00u)
    #define TCAN_SWAP_ENDIANNESS_ENABLE   (0x01u)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* TX send message */
#define TCAN_TX_REQUEST_PENDING     (0x01u)
#define TCAN_RETRY_NUMBER           (0x03u)
#define TCAN_SEND_MESSAGE_SHIFT     (0u)
#define TCAN_SEND_MESSAGE           ((uint32) ((uint32) 0x00000001u << TCAN_SEND_MESSAGE_SHIFT))

/* Offsets to maintain bytes within uint32 */
#define TCAN_ONE_BYTE_OFFSET        (8u)
#define TCAN_TWO_BYTE_OFFSET        (16u)
#define TCAN_THREE_BYTE_OFFSET      (24u)

#if (CY_PSOC3 || CY_PSOC5)
    /* Set/Clear bits macro for TCAN_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define TCAN_RX_ACK_MSG_SHIFT       (0u)
    #define TCAN_RX_ACK_MSG             ((uint8) ((uint8) 0x01u << TCAN_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define TCAN_RX_RTR_ABORT_SHIFT     (2u)
    #define TCAN_RX_RTR_ABORT_MASK      ((uint8) ((uint8) 0x01u << TCAN_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define TCAN_RX_BUF_ENABLE_SHIFT    (3u)
    #define TCAN_RX_BUF_ENABLE_MASK     ((uint8) ((uint8) 0x01u << TCAN_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define TCAN_RX_RTRREPLY_SHIFT      (4u)
    #define TCAN_RX_RTRREPLY_MASK       ((uint8) ((uint8) 0x01u << TCAN_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define TCAN_RX_INT_ENABLE_SHIFT    (5u)
    #define TCAN_RX_INT_ENABLE_MASK     ((uint8) ((uint8) 0x01u << TCAN_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define TCAN_RX_LINKING_SHIFT       (6u)
    #define TCAN_RX_LINKING_MASK        ((uint8) ((uint8) 0x01u << TCAN_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define TCAN_RX_WPNL_SHIFT          (7u)
    #define TCAN_RX_WPNL_MASK           ((uint8) ((uint8) 0x01u << TCAN_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define TCAN_RX_DLC_VALUE_SHIFT     (0u)
    #define TCAN_RX_DLC_VALUE_MASK      ((uint8) ((uint8) 0x0Fu << TCAN_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define TCAN_RX_IDE_SHIFT           (4u)
    #define TCAN_RX_IDE_MASK            ((uint8) ((uint8) 0x01u << TCAN_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define TCAN_RX_WPNH_SHIFT          (7u)
    #define TCAN_RX_WPNH_MASK           ((uint8) ((uint8) 0x01u << TCAN_RX_WPNH_SHIFT))

    #define TCAN_RX_ACK_MESSAGE(i)    (TCAN_RX[i].rxcmd.byte[0u] |= TCAN_RX_ACK_MSG)
    #define TCAN_RX_RTR_ABORT_MESSAGE(i) \
            (TCAN_RX[i].rxcmd.byte[0u] |= TCAN_RX_RTR_ABORT_MASK)
    #define TCAN_RX_BUF_ENABLE(i)      \
            (TCAN_RX[i].rxcmd.byte[0u] |= TCAN_RX_BUF_ENABLE_MASK)
    #define TCAN_RX_BUF_DISABLE(i)     \
            (TCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~TCAN_RX_BUF_ENABLE_MASK))
    #define TCAN_SET_RX_RTRREPLY(i)    \
            (TCAN_RX[i].rxcmd.byte[0u] |= TCAN_RX_RTRREPLY_MASK)
    #define TCAN_CLEAR_RX_RTRREPLY(i)  \
            (TCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~TCAN_RX_RTRREPLY_MASK))
    #define TCAN_RX_INT_ENABLE(i)      \
            (TCAN_RX[i].rxcmd.byte[0u] |= TCAN_RX_INT_ENABLE_MASK)
    #define TCAN_RX_INT_DISABLE(i)     \
            (TCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~TCAN_RX_INT_ENABLE_MASK))
    #define TCAN_SET_RX_LINKING(i)     \
            (TCAN_RX[i].rxcmd.byte[0u] |= TCAN_RX_LINKING_MASK)
    #define TCAN_CLEAR_RX_LINKING(i)   \
            (TCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~TCAN_RX_LINKING_MASK))
    #define TCAN_SET_RX_WNPL(i)     (TCAN_RX[i].rxcmd.byte[0u] |= TCAN_RX_WPNL_MASK)
    #define TCAN_CLEAR_RX_WNPL(i)      \
            (TCAN_RX[i].rxcmd.byte[0u] &= (uint8) (~TCAN_RX_WPNL_MASK))
    #define TCAN_SET_RX_WNPH(i)     (TCAN_RX[i].rxcmd.byte[2u] |= TCAN_RX_WPNH_MASK)
    #define TCAN_CLEAR_RX_WNPH(i)      \
            (TCAN_RX[i].rxcmd.byte[2u] &= (uint8) (~TCAN_RX_WPNH_MASK))
    #define TCAN_GET_DLC(i)            \
            (TCAN_RX[i].rxcmd.byte[2u] & TCAN_RX_DLC_VALUE_MASK)
    #define TCAN_GET_RX_IDE(i)         ((uint8) \
            (TCAN_RX[i].rxcmd.byte[2u] & TCAN_RX_IDE_MASK) >> TCAN_RX_IDE_SHIFT)
    #define TCAN_GET_RX_ID(i)          ((TCAN_GET_RX_IDE(i)) ? \
            (CY_GET_REG32(TCAN_RX_ID_PTR(i)) >> TCAN_SET_TX_ID_EXTENDED_MSG_SHIFT) : \
            (CY_GET_REG32(TCAN_RX_ID_PTR(i)) >> TCAN_SET_TX_ID_STANDARD_MSG_SHIFT))

    /* Set/Clear bits macro for TCAN_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define TCAN_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define TCAN_TX_TRANSMIT_REQUEST ((uint8) ((uint8) 0x01u << TCAN_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define TCAN_TX_ABORT_SHIFT        (1u)
    #define TCAN_TX_ABORT_MASK         ((uint8) ((uint8) 0x01u << TCAN_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define TCAN_TRANSMIT_INT_ENABLE   (0x01u)
    #define TCAN_TRANSMIT_INT_DISABLE  (0x00u)
    #define TCAN_TX_INT_ENABLE_SHIFT   (2u)
    #define TCAN_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << TCAN_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define TCAN_TX_WPNL_SHIFT         (3u)
    #define TCAN_TX_WPNL_MASK          ((uint8) ((uint8) 0x01u << TCAN_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define TCAN_TX_DLC_VALUE_SHIFT    (0u)
    #define TCAN_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define TCAN_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << TCAN_TX_DLC_UPPER_VALUE_SHIFT))
    #define TCAN_TX_DLC_VALUE_MASK     ((uint8) ((uint8) 0x0Fu << TCAN_TX_DLC_VALUE_SHIFT))
    #define TCAN_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define TCAN_TX_IDE_SHIFT          (20u)
    #define TCAN_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << TCAN_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define TCAN_TX_RTR_SHIFT          (21u)
    #define TCAN_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  TCAN_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define TCAN_TX_WPNH_SHIFT         (7u)
    #define TCAN_TX_WPNH_MASK          ((uint8) ((uint8) 0x01u << TCAN_TX_WPNH_SHIFT))

    #define TCAN_TX_TRANSMIT_MESSAGE(i) \
            (TCAN_TX[i].txcmd.byte[0u] |= TCAN_TX_TRANSMIT_REQUEST)
    #define TCAN_TX_ABORT_MESSAGE(i)   \
            (TCAN_TX[i].txcmd.byte[0u] = (TCAN_TX[i].txcmd.byte[0u] & \
            (uint8) (~TCAN_TX_TRANSMIT_REQUEST)) | TCAN_TX_ABORT_MASK)
    #define TCAN_TX_INT_ENABLE(i)      \
            (TCAN_TX[i].txcmd.byte[0u] |= (uint8) TCAN_TX_INT_ENABLE_MASK)
    #define TCAN_TX_INT_DISABLE(i)     \
            (TCAN_TX[i].txcmd.byte[0u] &= (uint8) (~TCAN_TX_INT_ENABLE_MASK))
    #define TCAN_SET_TX_WNPL(i)        \
            (TCAN_TX[i].txcmd.byte[0u] |= TCAN_TX_WPNL_MASK)
    #define TCAN_CLEAR_TX_WNPL(i)      \
            (TCAN_TX[i].txcmd.byte[0u] &= (uint8) (~TCAN_TX_WPNL_MASK))
    #define TCAN_SET_TX_IDE(i)         (TCAN_TX[i].txcmd.byte[2u] |= \
            (uint8) (TCAN_TX_IDE_MASK >> TCAN_TWO_BYTE_OFFSET))
    #define TCAN_CLEAR_TX_IDE(i)       (TCAN_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~TCAN_TX_IDE_MASK)) >> TCAN_TWO_BYTE_OFFSET))
    #define TCAN_SET_TX_RTR(i)         (TCAN_TX[i].txcmd.byte[2u] |= \
            (uint8) (TCAN_TX_RTR_MASK >> TCAN_TWO_BYTE_OFFSET))
    #define TCAN_CLEAR_TX_RTR(i)       (TCAN_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~TCAN_TX_RTR_MASK)) >> TCAN_TWO_BYTE_OFFSET))
    #define TCAN_SET_TX_WNPH(i)        \
            (TCAN_TX[i].txcmd.byte[2u] |= TCAN_TX_WPNH_MASK)
    #define TCAN_CLEAR_TX_WNPH(i)      \
            (TCAN_TX[i].txcmd.byte[2u] &= (uint8) (~TCAN_TX_WPNH_MASK))

    #define TCAN_RX_DATA_BYTE(mailbox, i) (TCAN_RX[mailbox].rxdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
    #define TCAN_TX_DATA_BYTE(mailbox, i) (TCAN_TX[mailbox].txdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
#else  /* CY_PSOC4 */
    /* Set/Clear bits macro for TCAN_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define TCAN_RX_ACK_MSG_SHIFT       (0u)
    #define TCAN_RX_ACK_MSG             ((uint32) ((uint32) 0x01u << TCAN_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define TCAN_RX_RTR_ABORT_SHIFT     (2u)
    #define TCAN_RX_RTR_ABORT_MASK      ((uint32) ((uint32) 0x01u << TCAN_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define TCAN_RX_BUF_ENABLE_SHIFT    (3u)
    #define TCAN_RX_BUF_ENABLE_MASK     ((uint32) ((uint32) 0x01u << TCAN_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define TCAN_RX_RTRREPLY_SHIFT      (4u)
    #define TCAN_RX_RTRREPLY_MASK       ((uint32) ((uint32) 0x01u << TCAN_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define TCAN_RX_INT_ENABLE_SHIFT    (5u)
    #define TCAN_RX_INT_ENABLE_MASK     ((uint32) ((uint32) 0x01u << TCAN_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define TCAN_RX_LINKING_SHIFT       (6u)
    #define TCAN_RX_LINKING_MASK        ((uint32) ((uint32) 0x01u << TCAN_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define TCAN_RX_WPNL_SHIFT          (7u)
    #define TCAN_RX_WPNL_MASK           ((uint32) ((uint32) 0x01u << TCAN_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define TCAN_RX_DLC_VALUE_SHIFT     (16u)
    #define TCAN_RX_DLC_VALUE_MASK      ((uint32) ((uint32) 0x0Fu << TCAN_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define TCAN_RX_IDE_SHIFT           (20u)
    #define TCAN_RX_IDE_MASK            ((uint32) ((uint32) 0x01u << TCAN_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define TCAN_RX_WPNH_SHIFT          (23u)
    #define TCAN_RX_WPNH_MASK           ((uint32) ((uint32) 0x01u << TCAN_RX_WPNH_SHIFT))

    #define TCAN_RX_ACK_MESSAGE(i)       (TCAN_RX_CMD_REG(i) |= TCAN_RX_ACK_MSG)
    #define TCAN_RX_RTR_ABORT_MESSAGE(i) (TCAN_RX_CMD_REG(i) |= \
                                                     TCAN_RX_RTR_ABORT_MASK)
    #define TCAN_RX_BUF_ENABLE(i)      (TCAN_RX_CMD_REG(i) |= \
                                                   TCAN_RX_BUF_ENABLE_MASK)
    #define TCAN_RX_BUF_DISABLE(i)     (TCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~TCAN_RX_BUF_ENABLE_MASK))
    #define TCAN_SET_RX_RTRREPLY(i)    (TCAN_RX_CMD_REG(i) |= \
                                                   TCAN_RX_RTRREPLY_MASK)
    #define TCAN_CLEAR_RX_RTRREPLY(i)  (TCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~TCAN_RX_RTRREPLY_MASK))
    #define TCAN_RX_INT_ENABLE(i)      (TCAN_RX_CMD_REG(i) |= \
                                                   TCAN_RX_INT_ENABLE_MASK)
    #define TCAN_RX_INT_DISABLE(i)     (TCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~TCAN_RX_INT_ENABLE_MASK))
    #define TCAN_SET_RX_LINKING(i)     (TCAN_RX_CMD_REG(i) |= TCAN_RX_LINKING_MASK)
    #define TCAN_CLEAR_RX_LINKING(i)   (TCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~TCAN_RX_LINKING_MASK))
    #define TCAN_SET_RX_WNPL(i)        (TCAN_RX_CMD_REG(i) |= TCAN_RX_WPNL_MASK)
    #define TCAN_CLEAR_RX_WNPL(i)      (TCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~TCAN_RX_WPNL_MASK))
    #define TCAN_SET_RX_WNPH(i)        (TCAN_RX_CMD_REG(i) |= TCAN_RX_WPNH_MASK)
    #define TCAN_CLEAR_RX_WNPH(i)      (TCAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~TCAN_RX_WPNH_MASK))
    #define TCAN_GET_DLC(i)            ((uint32) ((TCAN_RX_CMD_REG(i) & \
            TCAN_RX_DLC_VALUE_MASK) >> TCAN_RX_DLC_VALUE_SHIFT))
    #define TCAN_GET_RX_IDE(i)         ((uint32) ((TCAN_RX_CMD_REG(i) & \
            TCAN_RX_IDE_MASK) >> TCAN_RX_IDE_SHIFT))
    #define TCAN_GET_RX_ID(i)          ((TCAN_GET_RX_IDE(i) == 0u) ? \
            (TCAN_RX_ID_REG(i) >> TCAN_SET_TX_ID_STANDARD_MSG_SHIFT) : \
            (TCAN_RX_ID_REG(i) >> TCAN_SET_TX_ID_EXTENDED_MSG_SHIFT))

    /* Set/Clear bits macro for TCAN_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define TCAN_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define TCAN_TX_TRANSMIT_REQUEST   \
            ((uint32) ((uint32) 0x01u << TCAN_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define TCAN_TX_ABORT_SHIFT        (1u)
    #define TCAN_TX_ABORT_MASK         ((uint32) ((uint32) 0x01u << TCAN_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define TCAN_TRANSMIT_INT_ENABLE   (0x01u)
    #define TCAN_TRANSMIT_INT_DISABLE  (0x00u)
    #define TCAN_TX_INT_ENABLE_SHIFT   (2u)
    #define TCAN_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << TCAN_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define TCAN_TX_WPNL_SHIFT         (3u)
    #define TCAN_TX_WPNL_MASK          ((uint32) ((uint32) 0x01u << TCAN_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define TCAN_TX_DLC_VALUE_SHIFT    (0u)
    #define TCAN_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define TCAN_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << TCAN_TX_DLC_UPPER_VALUE_SHIFT))
    #define TCAN_TX_DLC_VALUE_MASK     ((uint32) ((uint32) 0x0Fu << TCAN_TX_DLC_VALUE_SHIFT))
    #define TCAN_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define TCAN_TX_IDE_SHIFT          (20u)
    #define TCAN_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << TCAN_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define TCAN_TX_RTR_SHIFT          (21u)
    #define TCAN_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  TCAN_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define TCAN_TX_WPNH_SHIFT         (23u)
    #define TCAN_TX_WPNH_MASK          ((uint32) ((uint32) 0x01u << TCAN_TX_WPNH_SHIFT))

    #define TCAN_TX_TRANSMIT_MESSAGE(i) \
            (TCAN_TX_CMD_REG(i) |= TCAN_TX_TRANSMIT_REQUEST)
    #define TCAN_TX_ABORT_MESSAGE(i) (TCAN_TX_CMD_REG(i) = (TCAN_TX_CMD_REG(i) & \
            (uint32) (~TCAN_TX_TRANSMIT_REQUEST)) | TCAN_TX_ABORT_MASK)
    #define TCAN_TX_INT_ENABLE(i)    (TCAN_TX_CMD_REG(i) |= TCAN_TX_INT_ENABLE_MASK)
    #define TCAN_TX_INT_DISABLE(i)   (TCAN_TX_CMD_REG(i) &= \
                                                 (uint32) (~TCAN_TX_INT_ENABLE_MASK))
    #define TCAN_SET_TX_WNPL(i)     (TCAN_TX_CMD_REG(i) |= TCAN_TX_WPNL_MASK)
    #define TCAN_CLEAR_TX_WNPL(i)   \
            (TCAN_TX_CMD_REG(i) &= (uint32)(~TCAN_TX_WPNL_MASK))
    #define TCAN_SET_TX_IDE(i)      (TCAN_TX_CMD_REG(i) |= TCAN_TX_IDE_MASK)
    #define TCAN_CLEAR_TX_IDE(i)    \
            (TCAN_TX_CMD_REG(i) &= (uint32) (~TCAN_TX_IDE_MASK))
    #define TCAN_SET_TX_RTR(i)      (TCAN_TX_CMD_REG(i) |= TCAN_TX_RTR_MASK)
    #define TCAN_CLEAR_TX_RTR(i)    \
            (TCAN_TX_CMD_REG(i) &= (uint32) (~TCAN_TX_RTR_MASK))
    #define TCAN_SET_TX_WNPH(i)     (TCAN_TX_CMD_REG(i) |= TCAN_TX_WPNH_MASK)
    #define TCAN_CLEAR_TX_WNPH(i)   \
            (TCAN_TX_CMD_REG(i) &= (uint32)(~TCAN_TX_WPNH_MASK))

    #define TCAN_DATA_HIGH_ADDR     (4u)
    #define TCAN_DATA_BYTE_MASK     ((uint32) 0xFFu)

    #define TCAN_RX_DATA_BYTE(mailbox, i) (((i) > 3u) ? \
            (uint8) (TCAN_RX_DATA_HI_REG(mailbox) >> ((7u - (i)) * TCAN_ONE_BYTE_OFFSET)) : \
            (uint8) (TCAN_RX_DATA_LO_REG(mailbox) >> ((3u - (i)) * TCAN_ONE_BYTE_OFFSET)))

    #define TCAN_TX_DATA_BYTE(mailbox, i, byte) (((i) > 3u) ? \
        (TCAN_TX_DATA_HI_REG(mailbox) = (TCAN_TX_DATA_HI_REG(mailbox) & \
        (uint32) (~((uint32) (TCAN_DATA_BYTE_MASK << ((7u - (i)) * TCAN_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((7u - (i)) * TCAN_ONE_BYTE_OFFSET))) : \
        (TCAN_TX_DATA_LO_REG(mailbox) = (TCAN_TX_DATA_LO_REG(mailbox) & \
        (uint32) (~((uint32) (TCAN_DATA_BYTE_MASK << ((3u - (i)) * TCAN_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((3u - (i)) * TCAN_ONE_BYTE_OFFSET))))
#endif /* CY_PSOC3 || CY_PSOC5 */

#if (CY_PSOC3 || CY_PSOC5)
    #define TCAN_DATA_BYTE_1            (3u)
    #define TCAN_DATA_BYTE_2            (2u)
    #define TCAN_DATA_BYTE_3            (1u)
    #define TCAN_DATA_BYTE_4            (0u)
    #define TCAN_DATA_BYTE_5            (7u)
    #define TCAN_DATA_BYTE_6            (6u)
    #define TCAN_DATA_BYTE_7            (5u)
    #define TCAN_DATA_BYTE_8            (4u)

    /* Macros for access to RX DATA for mailbox(i) */
    #define TCAN_RX_DATA_BYTE1(i)       TCAN_RX[i].rxdata.byte[TCAN_DATA_BYTE_1]
    #define TCAN_RX_DATA_BYTE2(i)       TCAN_RX[i].rxdata.byte[TCAN_DATA_BYTE_2]
    #define TCAN_RX_DATA_BYTE3(i)       TCAN_RX[i].rxdata.byte[TCAN_DATA_BYTE_3]
    #define TCAN_RX_DATA_BYTE4(i)       TCAN_RX[i].rxdata.byte[TCAN_DATA_BYTE_4]
    #define TCAN_RX_DATA_BYTE5(i)       TCAN_RX[i].rxdata.byte[TCAN_DATA_BYTE_5]
    #define TCAN_RX_DATA_BYTE6(i)       TCAN_RX[i].rxdata.byte[TCAN_DATA_BYTE_6]
    #define TCAN_RX_DATA_BYTE7(i)       TCAN_RX[i].rxdata.byte[TCAN_DATA_BYTE_7]
    #define TCAN_RX_DATA_BYTE8(i)       TCAN_RX[i].rxdata.byte[TCAN_DATA_BYTE_8]

    /* Macros for access to TX DATA for mailbox(i) */
    #define TCAN_TX_DATA_BYTE1(i)       TCAN_TX[i].txdata.byte[TCAN_DATA_BYTE_1]
    #define TCAN_TX_DATA_BYTE2(i)       TCAN_TX[i].txdata.byte[TCAN_DATA_BYTE_2]
    #define TCAN_TX_DATA_BYTE3(i)       TCAN_TX[i].txdata.byte[TCAN_DATA_BYTE_3]
    #define TCAN_TX_DATA_BYTE4(i)       TCAN_TX[i].txdata.byte[TCAN_DATA_BYTE_4]
    #define TCAN_TX_DATA_BYTE5(i)       TCAN_TX[i].txdata.byte[TCAN_DATA_BYTE_5]
    #define TCAN_TX_DATA_BYTE6(i)       TCAN_TX[i].txdata.byte[TCAN_DATA_BYTE_6]
    #define TCAN_TX_DATA_BYTE7(i)       TCAN_TX[i].txdata.byte[TCAN_DATA_BYTE_7]
    #define TCAN_TX_DATA_BYTE8(i)       TCAN_TX[i].txdata.byte[TCAN_DATA_BYTE_8]
#else  /* CY_PSOC4 */
    /* Macros for access to RX DATA for mailbox(i) */
    #define TCAN_RX_DATA_BYTE1(i)       \
            ((uint8) (TCAN_RX_DATA_LO_REG(i) >> TCAN_THREE_BYTE_OFFSET))
    #define TCAN_RX_DATA_BYTE2(i)       \
            ((uint8) (TCAN_RX_DATA_LO_REG(i) >> TCAN_TWO_BYTE_OFFSET))
    #define TCAN_RX_DATA_BYTE3(i)       \
            ((uint8) (TCAN_RX_DATA_LO_REG(i) >> TCAN_ONE_BYTE_OFFSET))
    #define TCAN_RX_DATA_BYTE4(i)       ((uint8) TCAN_RX_DATA_LO_REG(i))
    #define TCAN_RX_DATA_BYTE5(i)       \
            ((uint8) (TCAN_RX_DATA_HI_REG(i) >> TCAN_THREE_BYTE_OFFSET))
    #define TCAN_RX_DATA_BYTE6(i)       \
            ((uint8) (TCAN_RX_DATA_HI_REG(i) >> TCAN_TWO_BYTE_OFFSET))
    #define TCAN_RX_DATA_BYTE7(i)       \
            ((uint8) (TCAN_RX_DATA_HI_REG(i) >> TCAN_ONE_BYTE_OFFSET))
    #define TCAN_RX_DATA_BYTE8(i)       ((uint8) TCAN_RX_DATA_HI_REG(i))

    /* Macros for access to TX DATA for mailbox(i) */
    #define TCAN_TX_DATA_BYTE1(i, byte) \
            (TCAN_TX_DATA_LO_REG(i) = (TCAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (TCAN_DATA_BYTE_MASK << TCAN_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << TCAN_THREE_BYTE_OFFSET))
    #define TCAN_TX_DATA_BYTE2(i, byte) \
            (TCAN_TX_DATA_LO_REG(i) = (TCAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (TCAN_DATA_BYTE_MASK << TCAN_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << TCAN_TWO_BYTE_OFFSET))
    #define TCAN_TX_DATA_BYTE3(i, byte) \
            (TCAN_TX_DATA_LO_REG(i) = (TCAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (TCAN_DATA_BYTE_MASK << TCAN_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << TCAN_ONE_BYTE_OFFSET))
    #define TCAN_TX_DATA_BYTE4(i, byte) \
            (TCAN_TX_DATA_LO_REG(i) = (TCAN_TX_DATA_LO_REG(i) & \
            (uint32) (~TCAN_DATA_BYTE_MASK)) | (uint32) (byte))
    #define TCAN_TX_DATA_BYTE5(i, byte) \
            (TCAN_TX_DATA_HI_REG(i) = (TCAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (TCAN_DATA_BYTE_MASK << TCAN_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << TCAN_THREE_BYTE_OFFSET))
    #define TCAN_TX_DATA_BYTE6(i, byte) \
            (TCAN_TX_DATA_HI_REG(i) = (TCAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (TCAN_DATA_BYTE_MASK << TCAN_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << TCAN_TWO_BYTE_OFFSET))
    #define TCAN_TX_DATA_BYTE7(i, byte) \
            (TCAN_TX_DATA_HI_REG(i) = (TCAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (TCAN_DATA_BYTE_MASK << TCAN_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << TCAN_ONE_BYTE_OFFSET))
    #define TCAN_TX_DATA_BYTE8(i, byte) \
            (TCAN_TX_DATA_HI_REG(i) = (TCAN_TX_DATA_HI_REG(i) & \
            (uint32) (~TCAN_DATA_BYTE_MASK)) | (uint32) (byte))
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Macros for setting Tx Msg Identifier in TCAN_TX_ID register */
#define TCAN_SET_TX_ID_STANDARD_MSG_SHIFT  (21u)
#define TCAN_SET_TX_ID_EXTENDED_MSG_SHIFT  (3u)
#define TCAN_SET_TX_ID_STANDARD_MSG(i, id) (CY_SET_REG32(TCAN_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << TCAN_SET_TX_ID_STANDARD_MSG_SHIFT)))
#define TCAN_SET_TX_ID_EXTENDED_MSG(i, id) (CY_SET_REG32(TCAN_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << TCAN_SET_TX_ID_EXTENDED_MSG_SHIFT)))

/* Mask for bits within TCAN_CSR_CFG */
#define TCAN_EDGE_MODE_SHIFT           (0u)
/* Bit 0 within CSR_CFG */
#define TCAN_EDGE_MODE_MASK            ((uint8) ((uint8) 0x01u << TCAN_EDGE_MODE_SHIFT))
#define TCAN_SAMPLE_MODE_SHIFT         (1u)
/* Bit 1 within CSR_CFG */
#define TCAN_SAMPLE_MODE_MASK          ((uint8) ((uint8) 0x01u << TCAN_SAMPLE_MODE_SHIFT))
#define TCAN_CFG_REG_SJW_SHIFT         (2u)
/* Bits 3-2 within CSR_CFG */
#define TCAN_CFG_REG_SJW_MASK          ((uint8) ((uint8) 0x03u << TCAN_CFG_REG_SJW_SHIFT))
#define TCAN_CFG_REG_SJW_LOWER_LIMIT   (0x03u)  /* the lowest allowed value of cfg_sjw */
#define TCAN_RESET_SHIFT               (4u)
/* Bit 4 within CSR_CFG    */
#define TCAN_RESET_MASK                ((uint8) ((uint8) 0x01u << TCAN_RESET_SHIFT))
#define TCAN_CFG_REG_TSEG2_SHIFT       (5u)
/* Bits 7-5 within CSR_CFG */
#define TCAN_CFG_REG_TSEG2_MASK        ((uint8) ((uint8) 0x07u << TCAN_CFG_REG_TSEG2_SHIFT))
/* Highest allowed value of cfg_tseg2 */
#define TCAN_CFG_REG_TSEG2_UPPER_LIMIT (0x07u)
/* Lowest allowed value of cfg_tseg2 */
#define TCAN_CFG_REG_TSEG2_LOWER_LIMIT (0x02u)
/* Lowest allowed value of cfg_tseg2 if sample point is one point */
#define TCAN_CFG_REG_TSEG2_EXCEPTION   (0x01u)
/* Bits 11-8 within CSR_CFG */
#define TCAN_CFG_REG_TSEG1_SHIFT       (8u)
#define TCAN_CFG_REG_TSEG1_MASK        (0x0Fu)
/* Highest allowed value of cfg_tseg1 */
#define TCAN_CFG_REG_TSEG1_UPPER_LIMIT (0x0Fu)
/* Lowest allowed value of cfg_tseg1 */
#define TCAN_CFG_REG_TSEG1_LOWER_LIMIT (0x02u)
#define TCAN_ARBITER_SHIFT             (12u)

#if (CY_PSOC3 || CY_PSOC5)
    #define TCAN_ARBITRATION_SHIFT     (4u)
    /* Bit 12 within CSR_CFG */
    #define TCAN_ARBITRATION_MASK      ((uint8) ((uint8) 0x01u << TCAN_ARBITRATION_SHIFT))
#else  /* CY_PSOC4 */
    #define TCAN_ARBITRATION_SHIFT     (12u)
    /* Bit 12 within CSR_CFG */
    #define TCAN_ARBITRATION_MASK      ((uint32) ((uint32) 0x01u << TCAN_ARBITRATION_SHIFT))
    /* Bit 13 within CSR_CFG */
    #define TCAN_ENDIANNESS_SHIFT      (13u)
    #define TCAN_ENDIANNESS_MASK       ((uint32) ((uint32) 0x01u << TCAN_ENDIANNESS_SHIFT))
    /* Bit 14 within CSR_CFG */
    #define TCAN_ECR_MODE_SHIFT        (14u)
    #define TCAN_ECR_MODE_MASK         ((uint32) ((uint32) 0x01u << TCAN_ECR_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Bits 23-16 within CSR_CFG */
#define TCAN_BITRATE_SHIFT             (16u)
#define TCAN_BITRATE_MASK              (0x7FFFu)
#define TCAN_BITRATE_MASK_SHIFTED      \
        ((uint32) ((uint32) TCAN_BITRATE_MASK << TCAN_BITRATE_SHIFT))

/* Mask for bits within TCAN_CSR_CMD */
#define TCAN_MODE_SHIFT                (0u)
/* Bit 0 within CSR_CMD */
#define TCAN_MODE_MASK                 ((uint8) ((uint8) 0x01u << TCAN_MODE_SHIFT))
#define TCAN_OPMODE_MASK_SHIFT         (1u)
/* Bit 1 within CSR_CMD */
#define TCAN_OPMODE_MASK               ((uint8) ((uint8) 0x01u << TCAN_OPMODE_MASK_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define TCAN_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x03u << TCAN_MODE_SHIFT))
#else  /* CY_PSOC4 */
    #define TCAN_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x07u << TCAN_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask for bits within TCAN_CSR_CMD */
#define TCAN_ERROR_STATE_SHIFT         (0u)
/* Bit 17-16 within ERR_SR */
#define TCAN_ERROR_STATE_MASK          ((uint8) ((uint8) 0x03u << TCAN_ERROR_STATE_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define TCAN_TX_ERROR_FLAG_SHIFT   (2u)
    /* Bit 18 within ERR_SR */
    #define TCAN_TX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << TCAN_TX_ERROR_FLAG_SHIFT))
    #define TCAN_RX_ERROR_FLAG_SHIFT   (3u)
    /* Bit 19 within ERR_SR */
    #define TCAN_RX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << TCAN_RX_ERROR_FLAG_SHIFT))
#else  /* CY_PSOC4 */
    #define TCAN_TX_ERROR_FLAG_SHIFT   (18u)
    /* Bit 18 within ERR_SR */
    #define TCAN_TX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << TCAN_TX_ERROR_FLAG_SHIFT))
    #define TCAN_RX_ERROR_FLAG_SHIFT   (19u)
    /* Bit 19 within ERR_SR */
    #define TCAN_RX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << TCAN_RX_ERROR_FLAG_SHIFT))

    /* Mask and Macros for bits within TCAN_ECR_REG */
    #define TCAN_ECR_STATUS_ARM        (0x01u)
    /* Mask for clearing TCANINT_STATUS */
    #define TCAN_INT_STATUS_MASK       (0x00001FFCu)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask and Macros for bits within TCAN_INT_EN_REG */
#define TCAN_GLOBAL_INT_SHIFT          (0u)
#define TCAN_ARBITRATION_LOST_SHIFT    (2u)
#define TCAN_OVERLOAD_ERROR_SHIFT      (3u)
#define TCAN_BIT_ERROR_SHIFT           (4u)
#define TCAN_STUFF_ERROR_SHIFT         (5u)
#define TCAN_ACK_ERROR_SHIFT           (6u)
#define TCAN_FORM_ERROR_SHIFT          (7u)

#if (CY_PSOC3 || CY_PSOC5)
    #define TCAN_CRC_ERROR_SHIFT       (0u)
    #define TCAN_BUS_OFF_SHIFT         (1u)
    #define TCAN_RX_MSG_LOST_SHIFT     (2u)
    #define TCAN_TX_MESSAGE_SHIFT      (3u)
    #define TCAN_RX_MESSAGE_SHIFT      (4u)

    /* Bit 0 within INT_EN */
    #define TCAN_GLOBAL_INT_MASK       ((uint8) ((uint8) 0x01u << TCAN_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define TCAN_ARBITRATION_LOST_MASK ((uint8) ((uint8) 0x01u << TCAN_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define TCAN_OVERLOAD_ERROR_MASK   ((uint8) ((uint8) 0x01u << TCAN_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define TCAN_BIT_ERROR_MASK        ((uint8) ((uint8) 0x01u << TCAN_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define TCAN_STUFF_ERROR_MASK      ((uint8) ((uint8) 0x01u << TCAN_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define TCAN_ACK_ERROR_MASK        ((uint8) ((uint8) 0x01u << TCAN_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define TCAN_FORM_ERROR_MASK       ((uint8) ((uint8) 0x01u << TCAN_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define TCAN_CRC_ERROR_MASK        ((uint8) ((uint8) 0x01u << TCAN_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define TCAN_BUS_OFF_MASK          ((uint8) ((uint8) 0x01u << TCAN_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define TCAN_RX_MSG_LOST_MASK      ((uint8) ((uint8) 0x01u << TCAN_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define TCAN_TX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << TCAN_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define TCAN_RX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << TCAN_RX_MESSAGE_SHIFT))

    #define TCAN_ARBITRATION_LOST_INT_ENABLE   \
            (TCAN_INT_EN_REG.byte[0u] |= TCAN_ARBITRATION_LOST_MASK)
    #define TCAN_ARBITRATION_LOST_INT_DISABLE  \
            (TCAN_INT_EN_REG.byte[0u] &= (uint8) (~TCAN_ARBITRATION_LOST_MASK))
    #define TCAN_OVERLOAD_ERROR_INT_ENABLE     \
            (TCAN_INT_EN_REG.byte[0u] |= TCAN_OVERLOAD_ERROR_MASK)
    #define TCAN_OVERLOAD_ERROR_INT_DISABLE    \
            (TCAN_INT_EN_REG.byte[0u] &= (uint8) (~TCAN_OVERLOAD_ERROR_MASK))
    #define TCAN_BIT_ERROR_LOST_INT_ENABLE     \
            (TCAN_INT_EN_REG.byte[0u] |= TCAN_BIT_ERROR_MASK)
    #define TCAN_BIT_ERROR_LOST_INT_DISABLE    \
            (TCAN_INT_EN_REG.byte[0u] &= (uint8) (~TCAN_BIT_ERROR_MASK))
    #define TCAN_STUFF_ERROR_INT_ENABLE        \
            (TCAN_INT_EN_REG.byte[0u] |= TCAN_STUFF_ERROR_MASK)
    #define TCAN_STUFF_ERROR_INT_DISABLE       \
            (TCAN_INT_EN_REG.byte[0u] &= (uint8) (~TCAN_STUFF_ERROR_MASK))
    #define TCAN_ACK_ERROR_INT_ENABLE          \
            (TCAN_INT_EN_REG.byte[0u] |= TCAN_ACK_ERROR_MASK)
    #define TCAN_ACK_ERROR_INT_DISABLE         \
            (TCAN_INT_EN_REG.byte[0u] &= (uint8) (~TCAN_ACK_ERROR_MASK))
    #define TCAN_FORM_ERROR_INT_ENABLE         \
            (TCAN_INT_EN_REG.byte[0u] |= TCAN_FORM_ERROR_MASK)
    #define TCAN_FORM_ERROR_INT_DISABLE        \
            (TCAN_INT_EN_REG.byte[0u] &= (uint8) (~TCAN_FORM_ERROR_MASK))
    #define TCAN_CRC_ERROR_INT_ENABLE          \
            (TCAN_INT_EN_REG.byte[1u] |= TCAN_CRC_ERROR_MASK)
    #define TCAN_CRC_ERROR_INT_DISABLE         \
            (TCAN_INT_EN_REG.byte[1u] &= (uint8) (~TCAN_CRC_ERROR_MASK))
    #define TCAN_BUS_OFF_INT_ENABLE            \
            (TCAN_INT_EN_REG.byte[1u] |= TCAN_BUS_OFF_MASK)
    #define TCAN_BUS_OFF_INT_DISABLE           \
            (TCAN_INT_EN_REG.byte[1u] &= (uint8) (~TCAN_BUS_OFF_MASK))
    #define TCAN_RX_MSG_LOST_INT_ENABLE        \
            (TCAN_INT_EN_REG.byte[1u] |= TCAN_RX_MSG_LOST_MASK)
    #define TCAN_RX_MSG_LOST_INT_DISABLE       \
            (TCAN_INT_EN_REG.byte[1u] &= (uint8) (~TCAN_RX_MSG_LOST_MASK))
    #define TCAN_TX_MSG_INT_ENABLE             \
            (TCAN_INT_EN_REG.byte[1u] |= TCAN_TX_MESSAGE_MASK)
    #define TCAN_TX_MSG_INT_DISABLE            \
            (TCAN_INT_EN_REG.byte[1u] &= (uint8) (~TCAN_TX_MESSAGE_MASK))
    #define TCAN_RX_MSG_INT_ENABLE             \
            (TCAN_INT_EN_REG.byte[1u] |= TCAN_RX_MESSAGE_MASK)
    #define TCAN_RX_MSG_INT_DISABLE            \
            (TCAN_INT_EN_REG.byte[1u] &= (uint8) (~TCAN_RX_MESSAGE_MASK))
#else  /* CY_PSOC4 */
    #define TCAN_CRC_ERROR_SHIFT       (8u)
    #define TCAN_BUS_OFF_SHIFT         (9u)
    #define TCAN_RX_MSG_LOST_SHIFT     (10u)
    #define TCAN_TX_MESSAGE_SHIFT      (11u)
    #define TCAN_RX_MESSAGE_SHIFT      (12u)

    /* Mask and Macros for bits within TCAN_INT_EN_REG */
    /* Bit 0 within INT_EN */
    #define TCAN_GLOBAL_INT_MASK       ((uint32) ((uint32) 0x01u << TCAN_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define TCAN_ARBITRATION_LOST_MASK ((uint32) ((uint32) 0x01u << TCAN_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define TCAN_OVERLOAD_ERROR_MASK   ((uint32) ((uint32) 0x01u << TCAN_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define TCAN_BIT_ERROR_MASK        ((uint32) ((uint32) 0x01u << TCAN_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define TCAN_STUFF_ERROR_MASK      ((uint32) ((uint32) 0x01u << TCAN_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define TCAN_ACK_ERROR_MASK        ((uint32) ((uint32) 0x01u << TCAN_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define TCAN_FORM_ERROR_MASK       ((uint32) ((uint32) 0x01u << TCAN_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define TCAN_CRC_ERROR_MASK        ((uint32) ((uint32) 0x01u << TCAN_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define TCAN_BUS_OFF_MASK          ((uint32) ((uint32) 0x01u << TCAN_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define TCAN_RX_MSG_LOST_MASK      ((uint32) ((uint32) 0x01u << TCAN_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define TCAN_TX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << TCAN_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define TCAN_RX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << TCAN_RX_MESSAGE_SHIFT))

    #define TCAN_ARBITRATION_LOST_INT_ENABLE   \
            (TCAN_INT_EN_REG |= TCAN_ARBITRATION_LOST_MASK)
    #define TCAN_ARBITRATION_LOST_INT_DISABLE  \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_ARBITRATION_LOST_MASK))
    #define TCAN_OVERLOAD_ERROR_INT_ENABLE     \
            (TCAN_INT_EN_REG |= TCAN_OVERLOAD_ERROR_MASK)
    #define TCAN_OVERLOAD_ERROR_INT_DISABLE    \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_OVERLOAD_ERROR_MASK))
    #define TCAN_BIT_ERROR_LOST_INT_ENABLE     \
            (TCAN_INT_EN_REG |= TCAN_BIT_ERROR_MASK)
    #define TCAN_BIT_ERROR_LOST_INT_DISABLE    \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_BIT_ERROR_MASK))
    #define TCAN_STUFF_ERROR_INT_ENABLE        \
            (TCAN_INT_EN_REG |= TCAN_STUFF_ERROR_MASK)
    #define TCAN_STUFF_ERROR_INT_DISABLE       \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_STUFF_ERROR_MASK))
    #define TCAN_ACK_ERROR_INT_ENABLE          \
            (TCAN_INT_EN_REG |= TCAN_ACK_ERROR_MASK)
    #define TCAN_ACK_ERROR_INT_DISABLE         \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_ACK_ERROR_MASK))
    #define TCAN_FORM_ERROR_INT_ENABLE         \
            (TCAN_INT_EN_REG |= TCAN_FORM_ERROR_MASK)
    #define TCAN_FORM_ERROR_INT_DISABLE        \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_FORM_ERROR_MASK))
    #define TCAN_CRC_ERROR_INT_ENABLE          \
            (TCAN_INT_EN_REG |= TCAN_CRC_ERROR_MASK)
    #define TCAN_CRC_ERROR_INT_DISABLE         \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_CRC_ERROR_MASK))
    #define TCAN_BUS_OFF_INT_ENABLE            \
            (TCAN_INT_EN_REG |= TCAN_BUS_OFF_MASK)
    #define TCAN_BUS_OFF_INT_DISABLE           \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_BUS_OFF_MASK))
    #define TCAN_RX_MSG_LOST_INT_ENABLE        \
            (TCAN_INT_EN_REG |= TCAN_RX_MSG_LOST_MASK)
    #define TCAN_RX_MSG_LOST_INT_DISABLE       \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_RX_MSG_LOST_MASK))
    #define TCAN_TX_MSG_INT_ENABLE             \
            (TCAN_INT_EN_REG |= TCAN_TX_MESSAGE_MASK)
    #define TCAN_TX_MSG_INT_DISABLE            \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_TX_MESSAGE_MASK))
    #define TCAN_RX_MSG_INT_ENABLE             \
            (TCAN_INT_EN_REG |= TCAN_RX_MESSAGE_MASK)
    #define TCAN_RX_MSG_INT_DISABLE            \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_RX_MESSAGE_MASK))

    /* Bit 13 within INT_EN and INT_SR */
    #define TCAN_RTR_MSG_SHIFT              (13u)
    #define TCAN_RTR_MSG_MASK               ((uint32) ((uint32) 0x01u << TCAN_RTR_MSG_SHIFT))
    #define TCAN_RTR_MSG_INT_ENABLE         (TCAN_INT_EN_REG |= TCAN_RTR_MSG_MASK)
    #define TCAN_RTR_MSG_INT_DISABLE        \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_RTR_MSG_MASK))
    /* Bit 14 within INT_EN and INT_SR */
    #define TCAN_STUCK_AT_ZERO_SHIFT        (14u)
    #define TCAN_STUCK_AT_ZERO_MASK         \
            ((uint32) ((uint32) 0x01u << TCAN_STUCK_AT_ZERO_SHIFT))
    #define TCAN_STUCK_AT_ZERO_INT_ENABLE   \
            (TCAN_INT_EN_REG |= TCAN_STUCK_AT_ZERO_MASK)
    #define TCAN_STUCK_AT_ZERO_INT_DISABLE  \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_STUCK_AT_ZERO_MASK))
    /* Bit 15 within INT_EN and INT_SR */
    #define TCAN_SST_FAILURE_SHIFT          (15u)
    #define TCAN_SST_FAILURE_MASK           \
            ((uint32) ((uint32) 0x01u << TCAN_SST_FAILURE_SHIFT))
    #define TCAN_SST_FAILURE_INT_ENABLE     \
            (TCAN_INT_EN_REG |= TCAN_SST_FAILURE_MASK)
    #define TCAN_SST_FAILURE_INT_DISABLE    \
            (TCAN_INT_EN_REG &= (uint32) (~TCAN_SST_FAILURE_MASK))
#endif /* CY_PSOC3 || CY_PSOC5 */

#define TCAN_GLOBAL_INT_ENABLE_SHIFT        (0u)
#define TCAN_ARBITRATION_LOST_ENABLE_SHIFT  (2u)
#define TCAN_OVERLOAD_ERROR_ENABLE_SHIFT    (3u)
#define TCAN_BIT_ERROR_ENABLE_SHIFT         (4u)
#define TCAN_STUFF_ERROR_ENABLE_SHIFT       (5u)
#define TCAN_ACK_ERROR_ENABLE_SHIFT         (6u)
#define TCAN_FORM_ERROR_ENABLE_SHIFT        (7u)
#define TCAN_CRC_ERROR_ENABLE_SHIFT         (8u)
#define TCAN_BUS_OFF_ENABLE_SHIFT           (9u)
#define TCAN_RX_MSG_LOST_ENABLE_SHIFT       (10u)
#define TCAN_TX_MESSAGE_ENABLE_SHIFT        (11u)
#define TCAN_RX_MESSAGE_ENABLE_SHIFT        (12u)

#define TCAN_GLOBAL_INT_ENABLE    ((uint16) ((uint16) 0x01u << TCAN_GLOBAL_INT_ENABLE_SHIFT))
#define TCAN_ARBITRATION_LOST_ENABLE \
        ((uint16) ((uint16) 0x01u << TCAN_ARBITRATION_LOST_ENABLE_SHIFT))
#define TCAN_OVERLOAD_ERROR_ENABLE   \
        ((uint16) ((uint16) 0x01u << TCAN_OVERLOAD_ERROR_ENABLE_SHIFT))
#define TCAN_BIT_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << TCAN_BIT_ERROR_ENABLE_SHIFT))
#define TCAN_STUFF_ERROR_ENABLE   ((uint16) ((uint16) 0x01u << TCAN_STUFF_ERROR_ENABLE_SHIFT))
#define TCAN_ACK_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << TCAN_ACK_ERROR_ENABLE_SHIFT))
#define TCAN_FORM_ERROR_ENABLE    ((uint16) ((uint16) 0x01u << TCAN_FORM_ERROR_ENABLE_SHIFT))
#define TCAN_CRC_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << TCAN_CRC_ERROR_ENABLE_SHIFT))
#define TCAN_BUS_OFF_ENABLE       ((uint16) ((uint16) 0x01u << TCAN_BUS_OFF_ENABLE_SHIFT))
#define TCAN_RX_MSG_LOST_ENABLE   ((uint16) ((uint16) 0x01u << TCAN_RX_MSG_LOST_ENABLE_SHIFT))
#define TCAN_TX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << TCAN_TX_MESSAGE_ENABLE_SHIFT))
#define TCAN_RX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << TCAN_RX_MESSAGE_ENABLE_SHIFT))

#if (!(CY_PSOC3 || CY_PSOC5))
    #define TCAN_RTR_MESSAGE_ENABLE_SHIFT   (13u)
    #define TCAN_STUCK_AT_ZERO_ENABLE_SHIFT (14u)
    #define TCAN_SST_FAILURE_ENABLE_SHIFT   (15u)

    #define TCAN_RTR_MESSAGE_ENABLE   \
            ((uint16) ((uint16) 0x01u << TCAN_RTR_MESSAGE_ENABLE_SHIFT))
    #define TCAN_STUCK_AT_ZERO_ENABLE \
            ((uint16) ((uint16) 0x01u << TCAN_STUCK_AT_ZERO_ENABLE_SHIFT))
    #define TCAN_SST_FAILURE_ENABLE   \
            ((uint16) ((uint16) 0x01u << TCAN_SST_FAILURE_ENABLE_SHIFT))
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define TCAN_REG_ADDR_MASK        ((uint32) 0x0000FFFFu)


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define TCAN_TREE_BYTE_OFFSET     (TCAN_THREE_BYTE_OFFSET)

/* TCAN_SetRestartType() parameters */
#define TCAN_RESTART_BY_HAND      (TCAN_MANUAL_RESTART)

/* TCAN_SetOpMode() parameters */
#define TCAN_LISTEN_ONLY          (TCAN_LISTEN_ONLY_MODE)
#define TCAN_ACTIVE_MODE          (TCAN_INITIAL_MODE)

#ifdef TCAN_ISR_CALLBACK
    #define TCAN_ISR_INTERRUPT_CALLBACK
    #define TCAN_ISR_InterruptCallback  TCAN_Isr_Callback
#endif

#endif /* CY_CAN_TCAN_H */


/* [] END OF FILE */
