/*******************************************************************************
* File Name: GraphicLCDIntf_1.h
* Version 1.80
*
* Description:
*  This file provides the constants and parameter values and API definition for the 
*  GraphicLCDIntf Component
*
********************************************************************************
* Copyright 2008-2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_GraphicLCDIntf_GraphicLCDIntf_1_H)
#define CY_GraphicLCDIntf_GraphicLCDIntf_1_H

#include "cyfitter.h"

#if (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC6)
    #include "syslib/cy_syslib.h"
#elif (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 || \
       CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4 || \
       CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5)
    #include "cytypes.h"
#endif

/*************************************** 
*   Conditional Compilation Parameters
***************************************/

#define GraphicLCDIntf_1_BUS_WIDTH (16u)

/***************************************
*        Function Prototypes            
***************************************/

void GraphicLCDIntf_1_Start(void) ;
void GraphicLCDIntf_1_Stop(void) ;
void GraphicLCDIntf_1_Write16(uint8 d_c, uint16 wrData) ;
void GraphicLCDIntf_1_WriteM16(uint8 d_c, uint16 wrData[], uint16 num) ;
uint16 GraphicLCDIntf_1_Read16(uint8 d_c) ;
void GraphicLCDIntf_1_ReadM16(uint8 d_c, uint16 rdData[], uint16 num) ;  
                                                
void GraphicLCDIntf_1_Write16_A0(uint16 wrData) ;
void GraphicLCDIntf_1_Write16_A1(uint16 wrData) ;
void GraphicLCDIntf_1_WriteM16_A0(uint16 wrData[], int num) ;
void GraphicLCDIntf_1_WriteM16_A1(uint16 wrData[], int num) ;
uint16 GraphicLCDIntf_1_Read16_A1(void) ;
void GraphicLCDIntf_1_ReadM16_A1(uint16 rdData[], int num) ;

void GraphicLCDIntf_1_Sleep(void) ;
void GraphicLCDIntf_1_Wakeup(void) ;
void GraphicLCDIntf_1_SaveConfig(void) ;   
void GraphicLCDIntf_1_RestoreConfig(void) ;
void GraphicLCDIntf_1_Init(void) ;
void GraphicLCDIntf_1_Enable(void) ;

#define CYGRAPHICS_START()                  GraphicLCDIntf_1_Start()
#define CYGRAPHICS_STOP()                   GraphicLCDIntf_1_Stop()
#define CYGRAPHICS_WRITE(addr, data)        GraphicLCDIntf_1_Write16(addr, data)
#define CYGRAPHICS_READ(addr)               GraphicLCDIntf_1_Read16(addr)
#define CYGRAPHICS_WRITEM(addr, data, num)  GraphicLCDIntf_1_WriteM16(addr, data, num)
#define CYGRAPHICS_READM(addr, data, num)   GraphicLCDIntf_1_ReadM16(addr, data, num)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8 GraphicLCDIntf_1_initVar;


/***************************************
*           API Constants               
***************************************/

#define GraphicLCDIntf_1_CMD_QUEUE_FULL           (0x01u)
#define GraphicLCDIntf_1_DATA_VALID               (0x02u)

#define GraphicLCDIntf_1_READ_COMMAND             (0x02u)

#define GraphicLCDIntf_1_DATA_ADDRESS             (0x01u)
#define GraphicLCDIntf_1_COMMAND_ADDRESS          (0x00u)


/***************************************
*    Enumerated Types and Parameters    
***************************************/


/***************************************
*    Initial Parameter Constants        
***************************************/

/* Set 2 smaller than a period because di must be sampled one cycle before
*  the end of the read Low intervals.
*/ 
#define GraphicLCDIntf_1_READ_LOW_PULSE           (10u - 2u)   

/* Set 1 smaller than a period */ 
#define GraphicLCDIntf_1_READ_HIGH_PULSE          (10u - 1u)


/***************************************
*             Registers                 
***************************************/

#define GraphicLCDIntf_1_STATUS_REG                     (* (reg8 *)  GraphicLCDIntf_1_StsReg__STATUS_REG)
#define GraphicLCDIntf_1_STATUS_PTR                     (  (reg8 *)  GraphicLCDIntf_1_StsReg__STATUS_REG)

#define GraphicLCDIntf_1_DIN_LSB_DATA_REG               (* (reg8 *)  GraphicLCDIntf_1_LsbReg__STATUS_REG)
#define GraphicLCDIntf_1_DIN_LSB_DATA_PTR               (  (reg8 *)  GraphicLCDIntf_1_LsbReg__STATUS_REG)

#if (GraphicLCDIntf_1_BUS_WIDTH == 8u)   /* 8-bit interface */
    #define GraphicLCDIntf_1_CMD_FIFO_REG               (* (reg8 *)  GraphicLCDIntf_1_GraphLcd8_Lsb__F0_REG)
    #define GraphicLCDIntf_1_CMD_FIFO_PTR               (  (reg8 *)  GraphicLCDIntf_1_GraphLcd8_Lsb__F0_REG)
    #define GraphicLCDIntf_1_DATA_FIFO_REG              (* (reg8 *)  GraphicLCDIntf_1_GraphLcd8_Lsb__F1_REG)
    #define GraphicLCDIntf_1_DATA_FIFO_PTR              (  (reg8 *)  GraphicLCDIntf_1_GraphLcd8_Lsb__F1_REG)    
    #define GraphicLCDIntf_1_READ_LO_PULSE_REG          (* (reg8 *)  GraphicLCDIntf_1_GraphLcd8_Lsb__D0_REG)
    #define GraphicLCDIntf_1_READ_LO_PULSE_PTR          (  (reg8 *)  GraphicLCDIntf_1_GraphLcd8_Lsb__D0_REG)
    #define GraphicLCDIntf_1_READ_HI_PULSE_REG          (* (reg8 *)  GraphicLCDIntf_1_GraphLcd8_Lsb__D1_REG)
    #define GraphicLCDIntf_1_READ_HI_PULSE_PTR          (  (reg8 *)  GraphicLCDIntf_1_GraphLcd8_Lsb__D1_REG)
#else   /* 16-bit interface */   
    #define GraphicLCDIntf_1_CMD_FIFO_REG               (* (reg8 *)  GraphicLCDIntf_1_GraphLcd16_Lsb__F0_REG)
    #define GraphicLCDIntf_1_CMD_FIFO_PTR               (  (reg8 *)  GraphicLCDIntf_1_GraphLcd16_Lsb__F0_REG)
	
    #if (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4)
        #define GraphicLCDIntf_1_DATA_FIFO_PTR              (  (reg16 *) GraphicLCDIntf_1_GraphLcd16_Lsb__16BIT_F1_REG)
    #else
        #define GraphicLCDIntf_1_DATA_FIFO_PTR              (  (reg16 *) GraphicLCDIntf_1_GraphLcd16_Lsb__F1_REG)
    #endif
    #define GraphicLCDIntf_1_DIN_MSB_DATA_REG           (* (reg8 *)  GraphicLCDIntf_1_GraphLcd16_MsbReg__STATUS_REG)
    #define GraphicLCDIntf_1_DIN_MSB_DATA_PTR           (  (reg8 *)  GraphicLCDIntf_1_GraphLcd16_MsbReg__STATUS_REG)
    #define GraphicLCDIntf_1_READ_LO_PULSE_REG          (* (reg8 *)  GraphicLCDIntf_1_GraphLcd16_Lsb__D0_REG)
    #define GraphicLCDIntf_1_READ_LO_PULSE_PTR          (  (reg8 *)  GraphicLCDIntf_1_GraphLcd16_Lsb__D0_REG)
    #define GraphicLCDIntf_1_READ_HI_PULSE_REG          (* (reg8 *)  GraphicLCDIntf_1_GraphLcd16_Lsb__D1_REG)
    #define GraphicLCDIntf_1_READ_HI_PULSE_PTR          (  (reg8 *)  GraphicLCDIntf_1_GraphLcd16_Lsb__D1_REG)        
#endif /* GraphicLCDIntf_1_BUS_WIDTH == 8u */

#endif /* CY_GraphicLCDIntf_GraphicLCDIntf_1_H */


/* [] END OF FILE */
