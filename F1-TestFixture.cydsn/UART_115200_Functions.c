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
#include "UART_115200_Functions.h"

#define HEADER_BYTE_COUNT       2
#define EOP_BYTE_COUNT          2

#define HEADER_START_INDEX      0
#define PAYLOAD_START_INDEX     HEADER_BYTE_COUNT

#define MAX_PAYLOAD_BYTE_COUNT  3
#define PACKET_TYPE_COUNT       1

/**************************************/
#define PACKET_VERIFICATION_COUNT   5

/**********DEFINED CONSTANTS**********/
enum DataType           // MUX_115200 channel lineup
{ 
    RTEST_DLINK,             //
//    RTEST_DLINK2,        // 
//    CTEST_USB_DEBUG,
    //DIAG_UART_RX         //
};

enum PacketState
{
    HEADER_STATE,
    PAYLOAD_STATE,
    EOP_STATE
};

/**********DATA STRUCTURES**********/
typedef struct
{
    const uint8 HEADER_BYTE;
    const uint8 PACKET_TYPE;
    const uint8 PAYLOAD_SIZE;
    const uint8 EOP_CARRIAGE_RETURN;
    const uint8 EOP_LINE_FEED;
}Packet;

static Packet PacketList[PACKET_TYPE_COUNT] = 
{
    //{'~', 'S', 3, '\r', '\n'},              // RTest - DataLink - (controller to siren)
    {'~', '3', 3, '\r', '\n'},
//    {'~', 'L', 111, '\r', '\n'},            // CTest - quad normal - (controller to relay)
//    {'~', 'Y', 9, '\r', '\n'},              // RTest - quad serial - (relay to modules)
//    {'~', 'C', 4, '\r', '\n'},              // (Quad-Controller packets)
};

///**********GLOBAL VARIABLES**********/
//static uint16 singlepacketsuccess = 0;
static uint16 packetsuccess[1] = {0};

static RxPacket_DLink_S rxPacket_DLink_S;            

/**********LOCAL FUNCTION PROTOTYPES**********/
static void detectPacket(uint8 dataByte);

/**********DEFINED GLOBAL FUNCTIONS**********/

//RxPacket_DL2 * getRxPacket_DL2(void)
//{
//    pRxPacket_DL2 = &rxPacket_DL2;
//    
//    return pRxPacket_DL2;
//}

//RxPacket * getRxPacket(void)
//{
//    pRxPacket = &rxPacket;
//    
//    return pRxPacket;
//}

/*******************************************************************************
* Function Name: processByteReceivedHandler
********************************************************************************
*
* Summary:
*  Triggers when a byte is received in UART, called in UART_ISR(). If in voice
*  stream mode, the byte is sent directly to the DAC.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void processByteReceivedHandler_115200(void)
{
    uint8 dataByte = 0;
    
    static uint8 testbuffer[100];
    static uint8 testbuffer_count = 0;
    
    do
    {
        dataByte = UART_115200_GetChar();
        
        testbuffer[testbuffer_count] = dataByte;
        testbuffer_count++;
        if(testbuffer_count >= 100)
            testbuffer_count = 0;
        
        detectPacket(dataByte);
        
    }while(UART_115200_ReadRxStatus() & UART_115200_RX_STS_FIFO_NOTEMPTY);
    
    //UART_Timer_Start();
}


/**********DEFINED LOCAL FUNCTIONS**********/
/*******************************************************************************
* Function Name: detectPacket
********************************************************************************
*
* Summary:
*  Determines if the incoming byte belongs to a valid packet. If the packet is for
*  for starting voice stream, voice stream mode will be activated.
*
* Parameters:
*  dataByte: The byte to check
*
* Return:
*  None.
*
*******************************************************************************/
static void detectPacket(uint8 dataByte)
{
    static uint8 packet[MAX_PAYLOAD_BYTE_COUNT+HEADER_BYTE_COUNT+EOP_BYTE_COUNT];   
    static enum PacketState currentState = HEADER_STATE;
    static enum DataType currentType = RTEST_DLINK;
    static uint8 currentPacketIndex = HEADER_START_INDEX;
    
    switch(currentState)
    {
        case HEADER_STATE:
            if( (currentPacketIndex == HEADER_START_INDEX) && ( (dataByte == PacketList[RTEST_DLINK].HEADER_BYTE) ) )// ||
//                                                                (dataByte == PacketList[CTEST_QUADSERIAL].HEADER_BYTE) ||
//                                                                (dataByte == PacketList[CTEST_AUDIO].HEADER_BYTE) ||
//                                                                (dataByte == PacketList[QTEST_QUAD].HEADER_BYTE) ) )
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
            }
            else if( (currentPacketIndex == (HEADER_START_INDEX+1)) && ( (dataByte == PacketList[RTEST_DLINK].PACKET_TYPE) ) )// ||
//                                                                            (dataByte == PacketList[CTEST_QUADSERIAL].PACKET_TYPE) ||
//                                                                            (dataByte == PacketList[CTEST_AUDIO].PACKET_TYPE) ||
//                                                                            (dataByte == PacketList[QTEST_QUAD].PACKET_TYPE) ) )
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
                currentState = PAYLOAD_STATE;
                
                if(dataByte == PacketList[RTEST_DLINK].PACKET_TYPE)
                    currentType = RTEST_DLINK;
//                else if(dataByte == PacketList[CTEST_QUADSERIAL].PACKET_TYPE)
//                    currentType = CTEST_QUADSERIAL;
//                else if(dataByte == PacketList[CTEST_AUDIO].PACKET_TYPE)
//                    currentType = CTEST_AUDIO;
//                else if(dataByte == PacketList[QTEST_QUAD].PACKET_TYPE)
//                    currentType = QTEST_QUAD;
//                else
//                    currentType = CTEST_QUAD;
            }
            else
            {
                currentPacketIndex = HEADER_START_INDEX;
                currentType = RTEST_DLINK;
            }
            break;
            
        case PAYLOAD_STATE:
            packet[currentPacketIndex] = dataByte;
            currentPacketIndex++;
            
            if(currentPacketIndex >= (PAYLOAD_START_INDEX + PacketList[currentType].PAYLOAD_SIZE))
                currentState = EOP_STATE;
            break;   
            
        case EOP_STATE:
            if((currentPacketIndex == (PAYLOAD_START_INDEX + PacketList[currentType].PAYLOAD_SIZE)) &&
                (dataByte == PacketList[currentType].EOP_CARRIAGE_RETURN))
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
            }
            else if((currentPacketIndex == (PAYLOAD_START_INDEX + PacketList[currentType].PAYLOAD_SIZE + 1)) &&
                (dataByte == PacketList[currentType].EOP_LINE_FEED))
            {
                packet[currentPacketIndex] = dataByte;
                              
                if(currentType == RTEST_DLINK)
                {
//                   pRxPacket_Controller = getRxPacket_Controller();
//                   memcpy(&pRxPacket_Controller->bytes[0], &packet[2], PacketList[CTEST_RELAY].PAYLOAD_SIZE);
                    packetsuccess[RTEST_DLINK]++;   
                }
//                else if(currentType == CTEST_QUADSERIAL)
//                {
////                   pRxPacket_Relay = getRxPacket_Relay();
////                   memcpy(&pRxPacket_Relay->bytes[0], &packet[2], PacketList[RTEST_CONTROLLER].PAYLOAD_SIZE);
//                   packetsuccess[CTEST_QUADSERIAL]++;   
//                }
//                else if(currentType == CTEST_AUDIO)
//                   packetsuccess[CTEST_AUDIO]++;
//
//                else if(currentType == QTEST_QUAD)
//                   packetsuccess[QTEST_QUAD]++;
//
////                if(packetsuccess[0] > 1000)
////                    packetsuccess[0] = 0;
////                if(packetsuccess[2] > 1000)
////                    packetsuccess[2] = 0;
//
////                if(count >= 50)
////                    packetsuccess[2] = 0;
////                if(count == 0)
////                    packetsuccess[2] = 0;
                
                currentPacketIndex = HEADER_START_INDEX;
                currentState = HEADER_STATE;
                currentType = RTEST_DLINK;
            }
            else
            {
                currentPacketIndex = HEADER_START_INDEX;
                currentState = HEADER_STATE;
                currentType = RTEST_DLINK;
            }
            break;
    }
}

//void sendPacketToController(void)                   //*** This part needs some work
//{
//    static uint16 iterator = 0;
//    static uint8 checkSumRelay = 0;
//    static uint8 checkSumRelayIterator = 0;
//    static uint8 toggleSend = 0;
//    
//    static TxPacket_Controller txPacket_Controller;            
//    static TxPacket_Controller * pTxPacket_Controller;
//    
//    pRxPacket_Controller = getRxPacket_Controller();
//
//    checkSumRelay = 0;
//    for(checkSumRelayIterator = 0; checkSumRelayIterator<PacketList[CTEST_RELAY].PAYLOAD_SIZE; checkSumRelayIterator++)     // Calculate and load checksum
//    {
//        checkSumRelay ^= pTxPacket_Controller->bytes[checkSumRelayIterator];
//    }
//    
//    toggleSend^=0x01;
//    if(toggleSend == 1)
//    {
//
//        UART_230400_WriteTxData(0x7E);
//        UART_230400_WriteTxData('D');
//        for(iterator = 0; iterator<PacketList[CTEST_RELAY].PAYLOAD_SIZE; iterator++)              // Send entire payload every other send
//        {
//            UART_230400_WriteTxData(pTxPacket_Controller->bytes[iterator]);
//        }
//       
//        UART_230400_WriteTxData(checkSumRelay);
//        UART_230400_WriteTxData(0x0D);
//        UART_230400_WriteTxData(0x0A);
//    }
////    else                                                                                    // Send GPS data every other send
////    {
////        for(iterator = 0; iterator<72; iterator++)
////        {
////            CONTROLLER_WriteTxData(gpsValuesToSend->byte[iterator]);
////        }
////    }
//}

void ResetPacketSuccess_115200(void)           //*** This can be improved
{
//    packetsuccess[0] = 0;
//    packetsuccess[1] = 0;
//    packetsuccess[2] = 0;
//    packetsuccess[3] = 0;
    
    return;
}

uint8 VerifyPacket_115200(uint8 PacketType)
{
    
    if(packetsuccess[PacketType] == PACKET_VERIFICATION_COUNT)                //maybe we wait until pass here
    {
        packetsuccess[PacketType] = 0;
        return(1);
    }
    else if(packetsuccess[PacketType] > PACKET_VERIFICATION_COUNT)
        packetsuccess[PacketType] = 0;
    
        
    return(0);
        
        
//    if(packetsuccess[PacketType] >= PACKET_VERIFICATION_COUNT)                //maybe we wait until pass here
//        return(1);
//    else
//        return(0);
       
}



/* [] END OF FILE */
