/* ========================================
 * Can API for FRUCD
 * Schuyler Alschuler 2016 - 2017
 * ========================================
*/

/*******************************************
 * Used to interface dashboard with CAN bus
 * some functinality can be found in CAN_TX_RX_func.c
 * which is a generated source file
 * see the can component of the top design for specific mailboxes
 ******************************************/

#include "CAN.h"
#include "can_manga.h"
#include "cytypes.h"
//#include "data.h"
#include "frucd_display.h"
// indicator LEDs
#include "BMS_LED.h"
#include "IMD_LED.h"

extern volatile vcu_state state;
extern volatile uint32_t pedalOK;
extern volatile uint8_t PACK_TEMP;
extern volatile uint8_t BSPD_CATCH;
extern volatile uint16_t CURRENT;
extern volatile uint8_t soc;
extern volatile uint32_t voltage;
extern volatile BMS_STATUS bms_status;
extern volatile uint8_t shutdown_flags;

// info from MC and motor
extern volatile uint16_t mc_temp;
extern volatile uint16_t motor_temp;

volatile uint8_t CAPACITOR_VOLT = 0;
volatile uint8_t ACK_RX = 0;


uint8 current_bytes[4] = {0};

// returns voltage of capacitor from motor controller
uint8_t getCapacitorVoltage()
{
    return CAPACITOR_VOLT;
}


// called from CAN_TX_RX_func.c in the generic RX func
// tldr: part of an interrupt service routine
/*void can_receive(uint8_t *msg, int ID)
{
    uint8 InterruptState = CyEnterCriticalSection();
    
    switch (ID) 
    {
        case VEHICLE_STATE:
            state = msg[1];
            break;
        case MC_PDO_SEND:
            CAPACITOR_VOLT = msg[1];
            ABS_MOTOR_RPM = msg[3];
            mc_temp = msg[7] << 8;
            mc_temp += msg[8];
            break;
        case MC_PDO_ACK:
            ACK_RX = msg[1];
            motor_temp = msg[5] << 8;
            motor_temp |= msg[6];
            break;
        case 0xA6:  // errors sent from MC node
            CURTIS_FAULT_CHECK = 0x1;
            break;
        case 0x726:     // from motor controller to confirm that node is still active
            CURTIS_HEART_BEAT_CHECK = 0x1;
            break;
        case BMS_VOLTAGES:
            voltage = msg[5] << 24;
            voltage |= msg[6] << 16;
            voltage |= msg[7] << 8;
            voltage |= msg[8];
            break;
        case BMS_STATUS_MSG:
            soc = msg[2];
            bms_status = msg[3] << 8;    // bms error flags
            bms_status |= msg[4];        // bms error flags
            break;
        case BMS_TEMPERATURES:
            PACK_TEMP = msg[8];
            break;
        case PEI_CURRENT:
            CURRENT = msg[1] << 8;
            CURRENT |= msg[2];
            shutdown_flags = msg[3];
            break;
        case 0x366: //Tehya test
            //ESTOP = msg[CAN_DATA_BYTE_1];
            break;
    }
    
    CyExitCriticalSection(InterruptState);
}*/

void can_test_send()
{
    //CAN_1_DATA_BYTES_MSG msg;
    CAN_TX_MSG HeartB;
    
    HeartB.id = 0x300;
    HeartB.rtr = 0;
    HeartB.ide = 0;
    HeartB.dlc = 1;
    
    HeartB.irq = 0;
    
    HeartB.msg->byte[0] = (uint8) 1;
    HeartB.msg->byte[1] = (uint8) 1;
    HeartB.msg->byte[2] = (uint8) 1;
    HeartB.msg->byte[3] = (uint8) 1;
    HeartB.msg->byte[4] = (uint8) 1;
    HeartB.msg->byte[5] = (uint8) 1;
    HeartB.msg->byte[6] = (uint8) 1;
    HeartB.msg->byte[7] = (uint8) 1;
    
    CAN_SendMsg(&HeartB);
}

void can_send(uint8_t data[8], uint32_t ID)
{
    uint8_t i;
	CAN_TX_MSG message;
	CAN_DATA_BYTES_MSG payload;
	message.id = ID; 
	message.rtr = 0;
	message.ide = 0;
	message.dlc = 0x08;
	message.irq = 0;
	message.msg = &payload;
	for(i=0;i<8;i++)
		payload.byte[i] = data[i];
	CAN_SendMsg(&message); 
}

void can_send_switches(uint8_t sw_status){
      
        CAN_DATA_BYTES_MSG data_switches;
        CAN_TX_MSG message_switches;
    
        /* BASIC CAN mailbox configuration */
        message_switches.dlc = 1;
        message_switches.id  = DRIVER_SWITCHES;
        message_switches.ide = 0;
        message_switches.irq = 0;
        message_switches.msg = &data_switches;
        message_switches.rtr = 0;
    
        data_switches.byte[0u] = sw_status;
        CAN_SendMsg(&message_switches);
    
        /*
        uint8_t data[8];
        
        data[0] = sw_status;
        data[1] = 0;
        
        data[2] = 0;
        data[3] = 0;
        
        data[4] = 0;
        data[5] = 0;
        data[6] = 0;
        data[7] = 0;

        can_send(data, DRIVER_SWITCHES);
*/
        
} // can_send_status()

void can_send_cmd(
    uint8_t SetInterlock,
    uint16_t VCL_Throttle_High,
    uint16_t VCL_Throttle_Low,
    uint8_t E_Stop_Check
)
{
    //max and min voltage means the voltage of single cell
        
        uint8_t data[8];
        
        data[0] = SetInterlock;
        
        data[1] = VCL_Throttle_High;
        data[2] = VCL_Throttle_Low;
        
        data[3] = 0;
        data[4] = E_Stop_Check;
        
        data[5] = 0;
        data[6] = 0;
        data[7] = 0;

        can_send(data, 0x766);
        CyDelay(1); // Wtf is this shit?

} // can_send_cmd()

void can_send_charge(uint8_t charge, uint8_t save_soc) {
    uint8_t data[8] = {0};
    data[0] = charge;
    data[1] = save_soc;
    
    can_send(data, 0x389);
}