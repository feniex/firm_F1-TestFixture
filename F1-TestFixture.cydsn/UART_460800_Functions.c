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
#include "CommonVariables.h"
#include "UART_460800_Functions.h"

#define HEADER_BYTE_COUNT       2
#define EOP_BYTE_COUNT          2

#define HEADER_START_INDEX      0
#define PAYLOAD_START_INDEX     HEADER_BYTE_COUNT

#define MAX_PAYLOAD_BYTE_COUNT  111
#define PACKET_TYPE_COUNT       2

/**************************************/
#define PACKET_VERIFICATION_COUNT   5

/**********DEFINED CONSTANTS**********/
enum DEMUX_460800_CHANNEL
{ 
    CTEST_OBDII_TX,       
    RTEST_QUAD_TX,       
    STEST_AUDIO_TX,
};

enum DataType
{ 
    CTEST_AUDIO,        // This is for both cont and relay tests
    CTEST_RTEST_QUAD,   // CTest/RTest - quad normal - (controller to relay, relay to quad)
//    CTEST_A,            //*** needs to  (*** not used - only need to look for 'L' packet)
//    QTEST_QUAD          // (*** not used - Quad-Controller packets - type 'C')
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
    {'~', 'A', 10, '\r', '\n'},             // CTest - audio stream - (controller to siren)
    {'~', 'L', 111, '\r', '\n'},            // CTest/RTest - quad stream - (controller to relay, relay to quad)
//    {'~', 'Y', 9, '\r', '\n'},              // (*** not used - only need to look for 'L' packet)
//    {'~', 'C', 4, '\r', '\n'},              // (*** not used - Quad-Controller packets)
};

///**********GLOBAL VARIABLES**********/
//static uint16 singlepacketsuccess = 0;
static uint16 packetsuccess[4] = {0,0,0,0};

static RxPacket_Quad rxPacket_Quad;            
static RxPacket_Quad * pRxPacket_Quad;  

static RxPacket_QuadSerial rxPacket_QuadSerial;            
static RxPacket_QuadSerial * pRxPacket_QuadSerial; 


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
void processByteReceivedHandler_460800(void)
{
    uint8 dataByte = 0;
    
    static uint8 testbuffer[100];
    static uint8 testbuffer_count = 0;
    
    do
    {
        dataByte = UART_460800_GetChar();
        
        testbuffer[testbuffer_count] = dataByte;
        testbuffer_count++;
        if(testbuffer_count >= 100)
            testbuffer_count = 0;
        
        detectPacket(dataByte);
        
    }while(UART_460800_ReadRxStatus() & UART_460800_RX_STS_FIFO_NOTEMPTY);
    
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
    static enum DataType currentType = CTEST_AUDIO;
    static uint8 currentPacketIndex = HEADER_START_INDEX;
    
    switch(currentState)
    {
        case HEADER_STATE:
            if( (currentPacketIndex == HEADER_START_INDEX) && ( (dataByte == PacketList[CTEST_AUDIO].HEADER_BYTE) ||
                                                                (dataByte == PacketList[CTEST_RTEST_QUAD].HEADER_BYTE) ) )    // ||
//                                                                (dataByte == PacketList[CTEST_A].HEADER_BYTE) ||
//                                                                (dataByte == PacketList[QTEST_QUAD].HEADER_BYTE) ) )                                                      
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
            }
            else if( (currentPacketIndex == (HEADER_START_INDEX+1)) && ( (dataByte == PacketList[CTEST_AUDIO].PACKET_TYPE) ||
                                                                            (dataByte == PacketList[CTEST_RTEST_QUAD].PACKET_TYPE) ) )  //||
//                                                                            (dataByte == PacketList[CTEST_A].PACKET_TYPE) ||
//                                                                            (dataByte == PacketList[QTEST_QUAD].PACKET_TYPE) ) )
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
                currentState = PAYLOAD_STATE;
                
                if(dataByte == PacketList[CTEST_AUDIO].PACKET_TYPE)
                    currentType = CTEST_AUDIO;
                else if(dataByte == PacketList[CTEST_RTEST_QUAD].PACKET_TYPE)
                    currentType = CTEST_RTEST_QUAD;
//                else if(dataByte == PacketList[CTEST_A].PACKET_TYPE)
//                    currentType = CTEST_A;
//                else if(dataByte == PacketList[QTEST_QUAD].PACKET_TYPE)
//                    currentType = QTEST_QUAD;
                else
                    currentType = CTEST_AUDIO;
            }
            else
            {
                currentPacketIndex = HEADER_START_INDEX;
                currentType = CTEST_AUDIO;
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
                              
                if(currentType == CTEST_AUDIO)
                {
//                   pRxPacket_Controller = getRxPacket_Controller();
//                   memcpy(&pRxPacket_Controller->bytes[0], &packet[2], PacketList[CTEST_RELAY].PAYLOAD_SIZE);
                    packetsuccess[CTEST_AUDIO]++;   
                }
                else if(currentType == CTEST_RTEST_QUAD)
                {
//                   pRxPacket_Relay = getRxPacket_Relay();
//                   memcpy(&pRxPacket_Relay->bytes[0], &packet[2], PacketList[RTEST_CONTROLLER].PAYLOAD_SIZE);
                   packetsuccess[CTEST_RTEST_QUAD]++;   
                }
//                else if(currentType == CTEST_A)
//                   packetsuccess[CTEST_A]++;
//
//                else if(currentType == QTEST_QUAD)
//                   packetsuccess[QTEST_QUAD]++;
                
                currentPacketIndex = HEADER_START_INDEX;
                currentState = HEADER_STATE;
                currentType = CTEST_AUDIO;
            }
            else
            {
                currentPacketIndex = HEADER_START_INDEX;
                currentState = HEADER_STATE;
                currentType = CTEST_AUDIO;
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

void ResetPacketSuccess_460800(void)           //*** This can be improved
{
//    packetsuccess[0] = 0;
//    packetsuccess[1] = 0;
//    packetsuccess[2] = 0;
//    packetsuccess[3] = 0;
    
    return;
}

uint8 VerifyPacket_460800(uint8 PacketType)
{
    
    //MUX_CTRL_460800_Write(PacketType);
       
    if(packetsuccess[PacketType] >= PACKET_VERIFICATION_COUNT)                //maybe we wait until pass here
    {
        packetsuccess[PacketType] = 0;
        
        //CurrentTest.Failures
        
        return(1);
    }
    else
        return(0);
       
}

//  ---------RTest----------------------------
void sendPacketToRelay_Quad(void)              
{
    //static uint16 iterator = 0;

        UART_460800_WriteTxData('~');                          // Send 'L' packet 
        UART_460800_WriteTxData('L');
        for(uint8 iterator = 0; iterator<111; iterator++)             
        {
            UART_460800_WriteTxData(iterator);
        }
        
//        for(uint8 iterator = 0; iterator<111; iterator++)             
//        {
//            UART_460800_WriteTxData(iterator);
//        }

        UART_460800_WriteTxData(0x0D);
        UART_460800_WriteTxData(0x0A);
        
        return;
}

//  ----------------STest---------------
void sendPacketToSiren_Audio(void)
{
    
    static uint16 iterator = 0;
    static uint16 ADCReading[100];

//    UART_460800_WriteTxData(0x7E);                          // Send 'L' packet 
//    UART_460800_WriteTxData('L');
//    for(iterator = 0; iterator<100; iterator++)             
//    {
//        UART_460800_WriteTxData(iterator);
//    }
//    UART_460800_WriteTxData(0x0D);
//    UART_460800_WriteTxData(0x0A);
    
    //UART_460800_WriteTxData(iterator);
    
//    ADCReading[iterator] = ADC_AudioStream_GetResult16();
//    UART_460800_WriteTxData( ADCReading[iterator] );
    
    iterator++;
    if(iterator > 100)
        iterator = 0;
    
    return;
}

void sendPacketToController_OBDII(void)
{
    
    DEMUX_CTRL_460800_Write(CTEST_OBDII_TX);
    
    UART_460800_WriteTxData('~');                          // Send 'L' packet 
    UART_460800_WriteTxData(2);
    for(uint8 iterator = 0; iterator<7; iterator++)             
    {
        UART_460800_WriteTxData(0);
    }
    UART_460800_WriteTxData(0x40);      // Send 'drivers side door open' command
    UART_460800_WriteTxData(0x42);      // Checksum
    UART_460800_WriteTxData(0x0D);
    UART_460800_WriteTxData(0x0A);  
    
    return;
}

//void sendIgnition_OBDII(uint8 key_position)     // On or off
//{
//    
//    DEMUX_CTRL_460800_Write(CTEST_OBDII_TX);
//    
//    uint8 bytetosend = 0;
//    //bytetosend = key_position;
//    //bytetosend = (key_position | 0x08);
//    
//    if(key_position == 1)
//        bytetosend = 0x02;
//    else
//        bytetosend = 0x00;
//    
//    UART_460800_WriteTxData('~');                          // Send 'L' packet 
//    UART_460800_WriteTxData(1);
//    for(uint8 iterator = 0; iterator<5; iterator++)             
//    {
//        UART_460800_WriteTxData(0);
//    }
//    UART_460800_WriteTxData(bytetosend);            // Send 'drivers side door open' command
//    for(uint8 iterator = 6; iterator<8; iterator++)             
//    {
//        UART_460800_WriteTxData(0);
//    }
//    UART_460800_WriteTxData(bytetosend ^ 0x01);      // Checksum
//    UART_460800_WriteTxData(0x0D);
//    UART_460800_WriteTxData(0x0A);  
//    
//    return;
//}

void sendPacket_OBDII(void)     // On or off
{
    
    static TxPacket_Intermotive txPacket_Intermotive;       // Intermotive Packet - for ignition and OBDII test
    static TxPacket_Intermotive * pTxPacket_Intermotive;    // 
    
    DEMUX_CTRL_460800_Write(CTEST_OBDII_TX);
    
    pTxPacket_Intermotive = getTxPacket_Intermotive();        // Tx - Send relay ignition 'off';
    
    uint8 Checksum_Calc = 0x01;    // Header ID       
    for(uint8 i = 0; i<8; i++)
        Checksum_Calc ^= pTxPacket_Intermotive->bytes[i];
        
    pTxPacket_Intermotive->Payload.Checksum = Checksum_Calc;

    UART_460800_WriteTxData('~');                         
    UART_460800_WriteTxData(1);
    for(uint8 iterator = 0; iterator<9; iterator++)             
    {
        UART_460800_WriteTxData(pTxPacket_Intermotive->bytes[iterator]);
    }
    UART_460800_WriteTxData(0x0D);
    UART_460800_WriteTxData(0x0A);  // 13th byte 
    
    return;
}


/* [] END OF FILE */
