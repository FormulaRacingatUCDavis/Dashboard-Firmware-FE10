/* ========================================
 * Can API for FRUCD
 * Schuyler Alschuler 2016 - 2017
 * ========================================
*/

#ifndef CAN_MANGA_H
#define CAN_MANGA_H

#include "project.h"
#include "CAN.h"
//#include "T6963C.h"
//#include "graphic.h"
    
#include "data.h"

//volatile uint32 CURRENT = 0; 
    
typedef enum {
    DRIVER_SWITCHES = 0x050,
    VEHICLE_STATE = 0x766,
    BSPD_FLAGS = 0x0c1,
    MC_COMMAND = 0x0C0, 
    PEI_ESTOP = 0x366,
    PEI_CURRENT_SHUTDOWN = 0x387,
    BMS_STATUS_MSG = 0x380,
    BMS_VOLTAGES = 0x388,
    BMS_TEMPERATURES = 0x389,
    MC_VOLTAGE_INFO = 0x0A7,
    MC_INTERNAL_STATES = 0xAA,
    MC_TEMPERATURE_3 = 0xA2
} CAN_ID;
    
// Basic CAN functionality
void can_receive(uint8_t *msg, int ID);
void can_test_send();
void can_send(uint8_t data[8], uint32_t ID);

// Advanced CAN functionality
void can_send_cmd(uint8_t SetInterlock, uint16_t VCL_Throttle_High, uint16_t VCL_Throttle_Low, uint8_t E_Stop_Check);
void can_send_switches(uint8_t sw_status);
void can_send_charge(uint8_t charge, uint8_t save_soc);

uint8_t getCapacitorVoltage();
uint8_t getPedalLow();
uint8_t getPedalHigh();

#endif

