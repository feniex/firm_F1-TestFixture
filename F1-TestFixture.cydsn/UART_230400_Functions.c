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
#include "UART_230400_Functions.h"

#define HEADER_BYTE_COUNT       2
#define EOP_BYTE_COUNT          2

#define HEADER_START_INDEX      0
#define PAYLOAD_START_INDEX     HEADER_BYTE_COUNT

#define MAX_PAYLOAD_BYTE_COUNT  15
#define PACKET_TYPE_COUNT       4

/**************************************/
#define PACKET_VERIFICATION_COUNT   5

/**********DEFINED CONSTANTS**********/
enum DataType
{ 
    CTEST_RELAY, 
    RTEST_CONTROLLER,
    RTEST_SIREN,
    STEST_RELAY
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
    {'~', 'P', 8, '\r', '\n'},          // CTest - RelayPacket(from Controller)
    {'~', 'D', 15, '\r', '\n'},         // RTest - RelayPacket(to Controller)
    {'~', 'H', 5, '\r', '\n'},          // RTest - RelayPacket(from Siren)
    {'~', 'S', 3, '\r', '\n'},          // STest - SirenPacket(from Relay)
};

///**********GLOBAL VARIABLES**********/
//static uint16 singlepacketsuccess = 0;
static uint16 packetsuccess[4] = {0,0,0,0};
//static uint8 packetsuccess_log[100];
//static uint8 count = 0;

static uint8 packetsuccess_GPS = 0;

//static RxPacket_DL2 rxPacket_DL2;                    
//static RxPacket_DL2 * pRxPacket_DL2;      
//static RxPacket rxPacket;            
//static RxPacket * pRxPacket;       

static RxPacket_Controller rxPacket_Controller;            
static RxPacket_Controller * pRxPacket_Controller;  

static RxPacket_RelaySiren rxPacket_RelaySiren;              // 'D' packet from relay/sirem to controller
static RxPacket_RelaySiren * pRxPacket_RelaySiren;  

static Packet_H rxPacket_H; 
static Packet_H * pRxPacket_H;

static Packet_H txPacket_H; 
static Packet_H * pTxPacket_H;

static TxPacket_Controller * pTxPacket_Controller; 


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
void processByteReceivedHandler(void)
{
    uint8 dataByte = 0;
    
    static uint8 testbuffer[100];
    static uint8 testbuffer_count = 0;
    
    do
    {
        dataByte = UART_230400_GetChar();
        
        testbuffer[testbuffer_count] = dataByte;
        testbuffer_count++;
        if(testbuffer_count >= 100)
            testbuffer_count = 0;
        
        detectPacket(dataByte);
        findpacket(dataByte);
        
        
        //if(findpacket(dataByte))
            //packetsuccess_GPS = 1;
//            LED_EN_Write(0);
        
    }while(UART_230400_ReadRxStatus() & UART_230400_RX_STS_FIFO_NOTEMPTY);
    
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
    static enum DataType currentType = CTEST_RELAY;
    static uint8 currentPacketIndex = HEADER_START_INDEX;
    
    switch(currentState)
    {
        case HEADER_STATE:
            if((currentPacketIndex == HEADER_START_INDEX) && ( (dataByte == PacketList[CTEST_RELAY].HEADER_BYTE) ||
                                                               (dataByte == PacketList[RTEST_CONTROLLER].HEADER_BYTE) ||
                                                               (dataByte == PacketList[RTEST_SIREN].HEADER_BYTE) ||
                                                               (dataByte == PacketList[STEST_RELAY].HEADER_BYTE) ) )
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
            }
            else if((currentPacketIndex == (HEADER_START_INDEX+1)) && ( (dataByte == PacketList[CTEST_RELAY].PACKET_TYPE) ||
                                                                        (dataByte == PacketList[RTEST_CONTROLLER].PACKET_TYPE) ||
                                                                        (dataByte == PacketList[RTEST_SIREN].PACKET_TYPE) ||
                                                                        (dataByte == PacketList[STEST_RELAY].PACKET_TYPE) ) )
            {
                packet[currentPacketIndex] = dataByte;
                currentPacketIndex++;
                currentState = PAYLOAD_STATE;
                
                if(dataByte == PacketList[RTEST_CONTROLLER].PACKET_TYPE)
                    currentType = RTEST_CONTROLLER;
                else if(dataByte == PacketList[RTEST_SIREN].PACKET_TYPE)
                    currentType = RTEST_SIREN;
                else if(dataByte == PacketList[STEST_RELAY].PACKET_TYPE)
                    currentType = STEST_RELAY;
                else
                    currentType = CTEST_RELAY;
            }
            else
            {
                currentPacketIndex = HEADER_START_INDEX;
                currentType = CTEST_RELAY;
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
                              
                if(currentType == CTEST_RELAY)
                {
                   pRxPacket_Controller = getRxPacket_Controller();
                   memcpy(&pRxPacket_Controller->bytes[69], &packet[2], PacketList[CTEST_RELAY].PAYLOAD_SIZE);
                    packetsuccess[CTEST_RELAY]++;   
                }
                else if(currentType == RTEST_CONTROLLER)
                {
                   pRxPacket_RelaySiren = getRxPacket_RelaySiren();
                   memcpy(&pRxPacket_RelaySiren->bytes[0], &packet[2], PacketList[RTEST_CONTROLLER].PAYLOAD_SIZE);
                   //memcpy(&pRxPacket_Relay->bytes[0], &packet[2], PacketList[RTEST_CONTROLLER].PAYLOAD_SIZE);
                   packetsuccess[RTEST_CONTROLLER]++;   
                }
                else if(currentType == RTEST_SIREN)
                {
                    pRxPacket_H = getRxPacket_H();
                    memcpy(&pRxPacket_H->bytes[0], &packet[2], PacketList[RTEST_SIREN].PAYLOAD_SIZE);
                    packetsuccess[RTEST_SIREN]++;
                }
                else if(currentType == STEST_RELAY)        
                {  
                    pRxPacket_H = getRxPacket_H();
                    memcpy(&pRxPacket_H->bytes[0], &packet[2], PacketList[STEST_RELAY].PAYLOAD_SIZE);
                    packetsuccess[STEST_RELAY]++;
                }


//                if(packetsuccess[0] > 1000)
//                    packetsuccess[0] = 0;
//                if(packetsuccess[2] > 1000)
//                    packetsuccess[2] = 0;

//                if(count >= 50)
//                    packetsuccess[2] = 0;
//                if(count == 0)
//                    packetsuccess[2] = 0;
                
                currentPacketIndex = HEADER_START_INDEX;
                currentState = HEADER_STATE;
                currentType = CTEST_RELAY;
            }
            else
            {
                currentPacketIndex = HEADER_START_INDEX;
                currentState = HEADER_STATE;
                currentType = CTEST_RELAY;
            }
            break;
    }
}




void ResetPacketSuccess(void)           //*** This can be improved
{
    packetsuccess[0] = 0;
    packetsuccess[1] = 0;
    packetsuccess[2] = 0;
    packetsuccess[3] = 0;
    
    return;
}

uint8 VerifyPacket_230400(uint8 PacketType)
{
    
    //MUX_CTRL_230400_Write();

    if(packetsuccess[PacketType] >= PACKET_VERIFICATION_COUNT)                //maybe we wait until pass here
    {
        packetsuccess[PacketType] = 0;
        
        return(1);
    }
    else
        return(0);
       
}

uint8 findpacket(uint8 dataByte)
{
    static uint8 targetstring[7] = {'$','G','P','R','M','C',','};
    static uint8 index = 0;
    
    static uint8 gpsHeader_true = 0;
    static uint8 dataByte_prev = 0;
    

    if(gpsHeader_true != 1)
    {
        if(dataByte == targetstring[0])         // Detect the first byte of the string and reset index
        {
            index = 0;
        }

        if(dataByte != targetstring[index])     // If any sequential byte in the string is missed, then return fail       
            index = 0;

        index++;

        if(index > 6)                           // If header was read without missing a byte, then look for validation bit
        {
            
            index = 0;
            dataByte = 0;
            dataByte_prev = 0;
            //packetsuccess_GPS = 1;
            gpsHeader_true = 1;
    ////      return(1);
            
        }
    }
        

    
    if(gpsHeader_true == 1)
    {
        
        //if( (dataByte != '2') && (dataByte_prev == ',') )
        if(dataByte_prev == ',')
        {
            if(dataByte == 'A')                 // Valid gps reading
            {
                //gpsHeader_true = 0;
                packetsuccess_GPS = 1;
                gpsHeader_true = 0;
                return(1);
            }
            else if(dataByte == 'V')            // Invalid gps reading
            {
                //gpsHeader_true = 0;
                packetsuccess_GPS = 0;
                gpsHeader_true = 0;
                return(0);
            }
//            else
                gpsHeader_true = 0;
                //LED_EN_Write(0);
             
            packetsuccess_GPS = 0;
            
        }   
        
        dataByte_prev = dataByte;
        
    }

    return(0);
        
}

//-----------------------------------TX FUNCTIONS----------------------------------------------

void sendPacket_RelayToController(void)
{
    
    static TxPacket_Controller txPacket_Controller;            
    static TxPacket_Controller * pTxPacket_Controller;
    
    pTxPacket_Controller = getTxPacket_Controller();              // Tx - Get pointers to packet 
    
    DEMUX_CTRL_230400_Write(CTEST_RELAY);
    
    UART_230400_WriteTxData('~');
    UART_230400_WriteTxData('D');
    for(uint8 iterator = 0; iterator<15; iterator++)              // Send entire payload every other send
    {
        UART_230400_WriteTxData(pTxPacket_Controller->bytes[iterator]);
    }
    UART_230400_WriteTxData('\r');
    UART_230400_WriteTxData('\n');
    
    return;
    
}

void sendPacket_RelayToController_Test(void)
{
    
    static TxPacket_RelaySiren txPacket_Relay;            
    static TxPacket_RelaySiren * pTxPacket_Relay;
    
    static uint8 iteratorChecksum = 0;
    static uint8 checksum = 0;
           
    pTxPacket_Relay = getTxPacket_Relay();                      // Tx - Get pointers to packet 
    
    DEMUX_CTRL_230400_Write(CTEST_RELAY);
    
    for(iteratorChecksum = 0; iteratorChecksum<80; iteratorChecksum++)          // Calculate checksum
    {
        checksum ^= pTxPacket_Relay->bytes[iteratorChecksum];
    }
    
    UART_230400_WriteTxData('~');
    UART_230400_WriteTxData('I');
    for(uint8 iterator = 0; iterator<79; iterator++)            
    {
        UART_230400_WriteTxData(pTxPacket_Relay->bytes[iterator]);
    }
    UART_230400_WriteTxData(checksum);
    UART_230400_WriteTxData('\r');
    UART_230400_WriteTxData('\n');
    
    return;
    
}

void sendPacketToRelaySiren(void)                   //*** This part needs some work
{
    static uint16 iterator = 0;
//    static uint8 checkSumRelay = 0;
//    static uint8 checkSumRelayIterator = 0;
//    static uint8 toggleSend = 0;
    
//    static TxPacket_Controller txPacket_Controller;            
//    static TxPacket_Controller * pTxPacket_Controller;
//    
//    pRxPacket_Controller = getRxPacket_Controller();
    
    static TxPacket_RelaySiren txPacket_RelaySiren;            
    static TxPacket_RelaySiren * pTxPacket_RelaySiren;
    
    pTxPacket_RelaySiren = getTxPacket_RelaySiren();              // Tx - Get pointers to packet 
    
    //DEMUX_CTRL_230400_Write(STEST_RELAY);
    
//        pTxPacket_RelaySiren->Payload.StartByte_FLB = '~';
//        pTxPacket_RelaySiren->Payload.FLB_PacketType = '3';
//        pTxPacket_RelaySiren->Payload.StopByte1_FLB = 0x0D;
//        pTxPacket_RelaySiren->Payload.StopByte2_FLB = 0x0A; 
//    
//        pTxPacket_RelaySiren->Payload.StartByte1_Siren = '~';    
//        pTxPacket_RelaySiren->Payload.Siren_PacketType = 'S';
//        pTxPacket_RelaySiren->Payload.StopByte1_Siren = 0x0D;
//        pTxPacket_RelaySiren->Payload.StopByte2_Siren = 0x0A;
//    
//        pTxPacket_RelaySiren->Payload.StartByte1_Relay = '~';
//        pTxPacket_RelaySiren->Payload.Relay_PacketType = 'P';
//        pTxPacket_RelaySiren->Payload.StopByte1_Relay = 0x0D;
//        pTxPacket_RelaySiren->Payload.StopByte2_Relay = 0x0A; 
    
        uint8 checksum = 0;
        for(uint8 iteratorChecksum = 0; iteratorChecksum<78; iteratorChecksum++)          // Calculate checksum
        {
        checksum ^= pTxPacket_RelaySiren->bytes[iteratorChecksum];
        }
        
        uint8 checksum_P = 0;
        for(uint8 iteratorChecksum = 69; iteratorChecksum<79; iteratorChecksum++)          // Calculate checksum
        {
        checksum_P ^= pTxPacket_RelaySiren->bytes[iteratorChecksum];
        }
        //pTxPacket_RelaySiren->Payload.Checksum_Relay = checksum_P;
        
//        pTxPacket_RelaySiren->bytes[80] = '0x0D';
//        pTxPacket_RelaySiren->bytes[81] = '0x0A';
    
        UART_230400_WriteTxData(0x7E);
        UART_230400_WriteTxData('I');
        for(iterator = 0; iterator<79; iterator++)              // Send entire payload every other send
        {
            UART_230400_WriteTxData(pTxPacket_RelaySiren->bytes[iterator]);
        }
        UART_230400_WriteTxData(checksum);                          // [79]
        UART_230400_WriteTxData(0x0D);                              // [80]
        UART_230400_WriteTxData(0x0A);                              // [81]
        UART_230400_WriteTxData(checksum_P);                        // [82]
        UART_230400_WriteTxData(0x0D);                              // [83]
        UART_230400_WriteTxData(0x0A);                              // [84]
        
  
        
                // Specific code for Controller to Relay/Siren packet 
//        UART_1_WriteTxData(0x7E);
//        UART_1_WriteTxData('I');
//        for(iterator = 0; iterator<79; iterator++)              // Send entire payload every other send
//        {
//            UART_1_WriteTxData(pTxPacket_RelaySiren->bytes[iterator]);
//        }
//        UART_1_WriteTxData(0x0D);
//        UART_1_WriteTxData(0x0A);
        
        return;

}

void sendPacket_SirenToRelay(void)               
{
    static uint16 iterator = 0;
    
    static TxPacket_RelaySiren txPacket_RelaySiren;            
    static TxPacket_RelaySiren * pTxPacket_RelaySiren;
    
    DEMUX_CTRL_230400_Write(RTEST_SIREN); 
    
    pTxPacket_H = getTxPacket_H();

    UART_230400_WriteTxData(0x7E);
    UART_230400_WriteTxData('H');
    for(iterator = 0; iterator<5; iterator++)             
    {
        UART_230400_WriteTxData(pTxPacket_H->bytes[iterator]);
    }
    UART_230400_WriteTxData(0x0D);
    UART_230400_WriteTxData(0x0A);
        
      return;  

}

void sendPacket_RelayToSiren(void)               
{
    static uint16 iterator = 0;
    
//    static TxPacket_RelaySiren txPacket_RelaySiren;            
//    static TxPacket_RelaySiren * pTxPacket_RelaySiren;
//    
//    pTxPacket_H = getTxPacket_H();
//    
//    pTxPacket_H->Payload.SirenFirm_0 = 1;
//    pTxPacket_H->Payload.SirenFirm_1 = 1;
//    pTxPacket_H->Payload.SirenFirm_2 = 1;
//    pTxPacket_H->Payload.Speaker1_Overcurrent = 1;
//    pTxPacket_H->Payload.Speaker2_Overcurrent = 1;
//
////    // Specific code for Controller to Relay/Siren packet 
//    UART_230400_WriteTxData(0x7E);
//    UART_230400_WriteTxData('H');
//    for(iterator = 0; iterator<5; iterator++)             
//    {
//        UART_230400_WriteTxData(pTxPacket_H->bytes[iterator]);
//    }
//    UART_230400_WriteTxData(0x0D);
//    UART_230400_WriteTxData(0x0A);
        
      return;  

}

uint8 VerifyPacket_GPS(void)
{
    if(packetsuccess_GPS == 1)
    {
        packetsuccess_GPS = 0;
        return(1);
    }
    else   
        return(0);

}



/* [] END OF FILE */
