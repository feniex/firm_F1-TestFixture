/* ========================================
 *
 * Copyright FENIEX INDUSTRIES, 2016
 * 200W SIREN
 *
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/**********CHANGE LOG**********/


/**********PREPROCESSOR DIRECTIVES**********/
#include "project.h"
    
/**********DEFINED CONSTANTS**********/

    
/**********DATA STRUCTURES**********/

   
// C-Test - Rx from Controller (to Relay)
typedef union rxPacket_Controller
{
    uint8 bytes[8];

    struct rxData_Controller
    {
        uint8 Outputs1_8;
        uint8 Outputs9_16;
        uint8 Outputs17_24;
        uint8 Outputs25_32;
        uint8 Input_Logic;
        uint8 PowerState;
        uint8 Siren_RRB_EN;          
        uint8 Siren_EN;
    }Payload;
}RxPacket_Controller;

// C-Test - Tx to the Controller (from relay)
typedef union txPacket_Controller                                
{
    uint8 bytes[15];    

    struct txData_Controller
    {
        uint8 BlockCurrent_1;
        uint8 BlockCurrent_2;
        uint8 BlockCurrent_3;
        uint8 BlockCurrent_4;
        uint8 Voltage_BATT;
        uint8 Speaker1_Overcurrent;
        uint8 Speaker2_Overcurrent;
        uint8 RelayInputs;
        uint8 SirenFirm_0;
        uint8 SirenFirm_1;
        uint8 SirenFirm_2;
        uint8 RelayFirm_0;
        uint8 RelayFirm_1;
        uint8 RelayFirm_2;
        uint8 checkSum;
    }Payload;
}TxPacket_Controller;

// C-Test - Tx to Controller (from the relay)
//    typedef union rxPacket_OBDII_Union                               
//    {
//        uint8 bytes[10];  
//        
//        struct rxData_OBDII                                                                       
//        {
//           uint8 Header_ID;
//           uint8 Data_0;
//           uint8 Data_1;
//           uint8 Data_2;
//           uint8 Data_3;
//           uint8 Data_4;
//           uint8 Data_5;
//           uint8 Data_6;
//           uint8 Data_7;  
//           uint8 Checksum;
//        }Payload;
//    }RxPacket_OBDII;


//---------------------------------------------------------------------
   
// R-Test - Rx from the Relay (to the controller) - 'D'
typedef union rxPacket_RelaySiren                                     
{
    uint8 bytes[15];    

    struct rxData_RelaySiren 
    {
        uint8 BlockCurrent_1;
        uint8 BlockCurrent_2;
        uint8 BlockCurrent_3;
        uint8 BlockCurrent_4;
        uint8 Voltage_BATT;
        uint8 Speaker1_Overcurrent;
        uint8 Speaker2_Overcurrent;
        uint8 RelayInputs;
        uint8 SirenFirm_0;
        uint8 SirenFirm_1;
        uint8 SirenFirm_2;
        uint8 RelayFirm_0;
        uint8 RelayFirm_1;
        uint8 RelayFirm_2;
        uint8 checkSum;
    }Payload;
}RxPacket_RelaySiren;

//// R-Test - Tx to the Relay (from controller)
//typedef union txPacket_RelaySiren                                        
//{
//    uint8 bytes[8];    
//
//    struct txData
//    {             
//        uint8 Outputs_1to8;
//        uint8 Outputs_9to16;
//        uint8 Outputs_17to24;
//        uint8 Outputs_25to32;
//        uint8 HiLoInputLogic;
//        uint8 PowerState;
//        uint8 RRB;
//        uint8 SirenEnable;
//               
//    }Payload;
//}TxPacket_RelaySiren;


// RTest/STest Tx to Relay (from Controller)              Packet 'I' - 
    typedef union txPacket_RelaySiren                                         
    {
        uint8 bytes[79];    // 79 originally
    
        struct txData
        {
            uint8 LED_16_R;
            uint8 LED_16_G;
            uint8 LED_16_B;            
            uint8 LED_15_R;
            uint8 LED_15_G;
            uint8 LED_15_B;            
            uint8 LED_14_R;
            uint8 LED_14_G;
            uint8 LED_14_B;           
            uint8 LED_13_R;
            uint8 LED_13_G;
            uint8 LED_13_B;                      
            uint8 LED_12_R;
            uint8 LED_12_G;
            uint8 LED_12_B;
            uint8 LED_11_R;
            uint8 LED_11_G;
            uint8 LED_11_B;            
            uint8 LED_10_R;
            uint8 LED_10_G;
            uint8 LED_10_B;            
            uint8 LED_09_R;
            uint8 LED_09_G;
            uint8 LED_09_B;          
            uint8 LED_08_R;
            uint8 LED_08_G;
            uint8 LED_08_B;            
            uint8 LED_07_R;
            uint8 LED_07_G;
            uint8 LED_07_B;            
            uint8 LED_06_R;
            uint8 LED_06_G;
            uint8 LED_06_B;           
            uint8 LED_05_R;
            uint8 LED_05_G;
            uint8 LED_05_B;           
            uint8 LED_04_R;
            uint8 LED_04_G;
            uint8 LED_04_B;  
            uint8 LED_03_R;
            uint8 LED_03_G;
            uint8 LED_03_B;       
            uint8 LED_02_R;
            uint8 LED_02_G;
            uint8 LED_02_B;           
            uint8 LED_01_R;
            uint8 LED_01_G;
            uint8 LED_01_B;           
            uint8 Buzzer_H;
            uint8 Buzzer_L;
            uint8 ScreenBrightness;
            uint8 controllerSpeakerEnable;
            uint8 controllerPowerState;
            uint8 StartByte_FLB;
            uint8 FLB_PacketType;                   // 3 - Payload byte number 55
                uint8 WireActivation1;
                uint8 WireActivation2;
                uint8 WireActivation3; 
            uint8 StopByte1_FLB;
            uint8 StopByte2_FLB;
            uint8 StartByte1_Siren;
            uint8 Siren_PacketType;                 // S - Payload byte number 62
                uint8 Siren1Tone;
                uint8 Siren2Tone;
                uint8 DualDelay; 
            uint8 StopByte1_Siren;
            uint8 StopByte2_Siren;
            uint8 StartByte1_Relay;
            uint8 Relay_PacketType;                 // P - Payload byte number 69
                uint8 Outputs_1to8;
                uint8 Outputs_9to16;
                uint8 Outputs_17to24;
                uint8 Outputs_25to32;
                uint8 HiLoInputLogic;
                uint8 PowerState;
                uint8 RRB;
                uint8 SirenEnable;
            uint8 StopByte1_Relay;
            uint8 StopByte2_Relay;                    // Payload byte number 79
        }Payload;
    }TxPacket_RelaySiren;
    
//    //RTest/STest Tx to Relay (from Siren) - 'H' packet
//    typedef union txPacket_Relay                                       
//    {
//        uint8 bytes[5];    
//    
//        struct txData_Siren
//        {
//            
//            uint8 SirenFirm_0;
//            uint8 SirenFirm_1;
//            uint8 SirenFirm_2;
//            uint8 Speaker1_Overcurrent;
//            uint8 Speaker2_Overcurrent;
//
//        }Payload;
//    }TxPacket_Relay;
    
    //RTest/STest Tx to Relay (from Siren) - 'H' packet
    typedef union packet_H                                      
    {
        uint8 bytes[5];    
    
        struct Data_H
        {
            
            uint8 SirenFirm_0;
            uint8 SirenFirm_1;
            uint8 SirenFirm_2;
            uint8 Speaker1_Overcurrent;
            uint8 Speaker2_Overcurrent;

        }Payload;
    }Packet_H;
    
    //RTest Rx packet from Relay(to Siren) - 'S' packet
    typedef union rxPacket_Siren                                     
    {
        uint8 bytes[3];    
    
        struct rxData_Siren
        {
            uint8 Siren1Tone;
            uint8 Siren2Tone;
            uint8 DualDelay;

        }Payload;
    }RxPacket_Siren;
    
//    //STest Tx to Siren - (functionality not yet added on the SOM side)
//    typedef union rxPacket_Controller                                         
//    {
//        uint8 bytes[79];    
//    
//        struct rxData
//        {
//            uint8 LED_16_R;
//
//        }Payload;
//    }RxPacket_Controller;
    
/**********GLOBAL VARIABLES**********/

    
/**********GLOBAL FUNCTION PROTOTYPES**********/
void processByteReceivedHandler(void); 

void sendPacketToRelaySiren(void);

void ResetPacketSuccess(void);
uint8 VerifyPacket_230400(uint8 PacketType);

uint8 findpacket(uint8 dataByte);

void sendPacket_SirenToRelay(void);
void sendPacket_RelayToSiren(void);

//void CTest_SendIgnitionState(uint8 ignition_state);

RxPacket_Controller * getRxPacket_Controller(void);
TxPacket_Controller * getTxPacket_Controller(void);

Packet_H * getTxPacket_H(void);
Packet_H * getRxPacket_H(void);

TxPacket_RelaySiren * getTxPacket_RelaySiren(void); // STest - 'I' packet to Siren - enable RRB
RxPacket_RelaySiren * getRxPacket_Relay(void);

//TxPacket_RelaySiren * getTxPacket_Siren(void);          // STest - 'I' packet to Siren - enable RRB

//TxPacket_Relay * getTxPacket_Relay(void);

//RxPacket_Siren * getRxPacket_Siren(void);

// -----------------------------
//enum MUX_230400_CHANNEL              
//{ 
//    CTest_Relay, 
//    RTest_Cont,              
//    RTest_Siren,           
//    STest_Relay            
//};

/* [] END OF FILE */
