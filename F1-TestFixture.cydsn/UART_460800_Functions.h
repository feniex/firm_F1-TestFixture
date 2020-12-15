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
    
    
// C-Test/R-Test - Rx - Quad from Controller (to Relay)
typedef union rxPacket_Quad
{
    uint8 bytes[111];

    struct rxData_Quad
    {
           uint8 SizeOfPayload;
           uint8 FLB_Module1;
           uint8 FLB_Module2;
           uint8 FLB_Module3;
           uint8 FLB_Module4;
           uint8 FLB_Module5;
           uint8 FLB_Module6;
           uint8 FLB_Module7;
           uint8 FLB_Module8;  
           uint8 FLB_Module9;
           uint8 FLB_Module10;
           uint8 FLB_Module11;
           uint8 FLB_Module12;
           uint8 FLB_Module13;
           uint8 FLB_Module14;
           uint8 FLB_Module15;
           uint8 FLB_Module16;
           uint8 FLB_Module17;
           uint8 FLB_Module18;  
           uint8 FLB_Module19;
           uint8 FLB_Module20;
           uint8 FLB_Module21;
           uint8 FLB_Module22;
           uint8 FLB_Module23;
           uint8 FLB_Module24;
           uint8 FLB_Module25;
           uint8 FLB_Module26;
           uint8 FLB_Module27;
           uint8 FLB_Module28;  
           uint8 FLB_Module29;
            uint8 FLB_Module30;
            
            uint8 SM_Zone1;
            uint8 SM_Zone2;
            uint8 SM_Zone3;
            
            uint8 LS400_Module4;
            uint8 LS400_Module5;
            uint8 LS400_Module6;
            uint8 LS400_Module7;
            
            uint8 SM_Zone4;
            uint8 SM_Zone5;
            uint8 SM_Zone6;
            uint8 SM_Zone7;
            
            uint8 FrontILB_Module2;
            uint8 FrontILB_Module3;
            uint8 FrontILB_Module4;
            uint8 FrontILB_Module5;
            uint8 FrontILB_Module6;
            uint8 FrontILB_Module7;
            uint8 FrontILB_Module8;
            uint8 FrontILB_Module9;
            
            uint8 SM_Zone8;
            uint8 SM_ZoneAddress;
            
            uint8 LS600_Module2;
            uint8 LS600_Module3;
            uint8 LS600_Module4;
            uint8 LS600_Module5;
            uint8 LS600_Module6;
            uint8 LS600_Module7;
            uint8 LS600_Module8;
            uint8 LS600_Module9;
            uint8 LS600_Module10;
            
            uint8 LS800_Module1;
            uint8 LS800_Module2;
            uint8 LS800_Module3;
            uint8 LS800_Module4;
            uint8 LS800_Module5;
            uint8 LS800_Module6;
            uint8 LS800_Module7;
            uint8 LS800_Module8;
            uint8 LS800_Module9;
            uint8 LS800_Module10;
            
            uint8 RearILB_Module1;
            uint8 RearILB_Module2;
            uint8 RearILB_Module3;
            uint8 RearILB_Module4;
            uint8 RearILB_Module5;
            uint8 RearILB_Module6;
            uint8 RearILB_Module7;
            uint8 RearILB_Module8;
            uint8 RearILB_Module9;
            uint8 RearILB_Module10;
            
            uint8 RockLeft_Module1;
            uint8 RockLeft_Module2;
            uint8 RockLeft_Module3;
            uint8 RockLeft_Module4;
            uint8 RockLeft_Module5;
            uint8 RockLeft_Module6;
            uint8 RockLeft_Module7;
            uint8 RockLeft_Module8;
            uint8 RockLeft_Module9;
            uint8 RockLeft_Module10;
            
            uint8 RockRight_Module1;
            uint8 RockRight_Module2;
            uint8 RockRight_Module3;
            uint8 RockRight_Module4;
            uint8 RockRight_Module5;
            uint8 RockRight_Module6;
            uint8 RockRight_Module7;
            uint8 RockRight_Module8;
            uint8 RockRight_Module9;
            uint8 RockRight_Module10;
            
            uint8 Arrow_Module1;
            uint8 Arrow_Module2;
            uint8 Arrow_Module3;
            uint8 Arrow_Module4;
            uint8 Arrow_Module5;
            uint8 Arrow_Module6;
            uint8 Arrow_Module7;
            uint8 Arrow_Module8;
            uint8 Arrow_Module9;
            uint8 Arrow_Module10;
    }Payload;
}RxPacket_Quad;

// C-Test/R-Test - Rx - Quad-Serial from Controller (to Relay)
typedef union rxPacket_QuadSerial
{
    uint8 bytes[9];

    struct rxData_QuadSerial
    {
            uint8 SM_Zone1;
            uint8 SM_Zone2;
            uint8 SM_Zone3;
            uint8 SM_Zone4;
            uint8 SM_Zone5;
            uint8 SM_Zone6;
            uint8 SM_Zone7;
            uint8 SM_Zone8;
            uint8 SM_ZoneAddress;  
    }Payload;
}RxPacket_QuadSerial;
    
/**********GLOBAL VARIABLES**********/

    
/**********GLOBAL FUNCTION PROTOTYPES**********/
void processByteReceivedHandler_460800(void); 

//void sendPacketToController(void);

void ResetPacketSuccess_460800(void);
uint8 VerifyPacket_460800(uint8 PacketType);
void sendPacketToRelay_Quad(void);

//void CTest_SendIgnitionState(uint8 ignition_state);

RxPacket_Quad * getRxPacket_Quad(void);
//RxPacket_QuadSerial * getRxPacket_QuadSerial(void);


/* [] END OF FILE */
