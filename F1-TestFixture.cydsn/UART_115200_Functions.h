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
    
// R-Test - Rx - Siren DataLink from Relay (to DataLink device)
typedef union rxPacket_DLink_S
{
    uint8 bytes[3];

    struct rxData_DLink_S
    {
        uint8 Siren1Tone;
        uint8 Siren2Tone;
        uint8 DualDelay; 
    }Payload;
}RxPacket_DLink_S;
    
/**********GLOBAL VARIABLES**********/

    
/**********GLOBAL FUNCTION PROTOTYPES**********/
void processByteReceivedHandler_115200(void); 

//void sendPacketToController(void);

void ResetPacketSuccess_115200(void);
uint8 VerifyPacket_115200(uint8 PacketType);

RxPacket_DLink_S * getRxPacket_DLink_S(void);


/* [] END OF FILE */
