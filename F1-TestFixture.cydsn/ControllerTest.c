/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include "ControllerTest.h"
#include "UART_230400_Functions.h"

static RxPacket_Controller rxPacket_Controller;            
static RxPacket_Controller * pRxPacket_Controller; 
static TxPacket_Controller txPacket_Controller;            
static TxPacket_Controller * pTxPacket_Controller;


static uint8 TestState = 0;

static uint8 testvalue = 0;
static uint16 testvaluearray[200];
static uint8 testindex = 0;

enum DataType
{ 
    CONFIRM_BOOTUP, 
    TEST_POWERMODES,
    FAIL
};


// Should have SOM installed (maybe with test software embedded)
// Controller should already be programmed with a test config file



void ControllerTest(void)
{
    
    switch(TestState)
    {   
        
        //----------------Set Default States----------------------------
        // Controller should be powered only by Vbatt at this time, with ignition ON
        //  - Enable Vbatt
        //  - Disable USB_5V
        //  - Send packet simulating ignition ON event
        //--------------------------------------------------------------
        
        case CONFIRM_BOOTUP:
        
        //***CTest_SendIgnitionState(IGNITION_ON);                 // Simulate ignition ON
            
        //*** need to setup a transmit to controller every 20msec - (this part will need some work still)
        // (this is causing priority issues and messes up the Rx)
            
        // Verify the SOM has booted by verifying a valid packet is being sent (could be any packet coming from the SOM)
            ResetPacketSuccess();                       // Reset the packetsuccess count
            while( !VerifyPacket_230400(0) )                   // Wait for 5 successful packets - (this looks for the Relay 'P' packet, it might be better to look for the entire 'I' packet with the checksum)
            {
//                LED_EN_Write(0);
            }
            
        // Indicate this step has been passed and move to next step
//            LED_EN_Write(1);                            
            CyDelay(1000);
//            LED_EN_Write(0);
            
            TestState = TEST_POWERMODES;                // Move to the next test step
            
        //*** need to add a timeout here - if 5 packets aren't received in a certain time, then move to TestState = FAIL            
        //  TestState = FAIL;
        
        break;
        
        case TEST_POWERMODES:           // Vbatt Detect, USB Detect - 230400bps 
  

//        // Send_IgnitionState(IGNITION_OFF);      
//        if(CTest_ReadPowerMode() == 0x00)       // Verify Low Power Mode  
//            LED_EN_Write(1);
//        else
//            TestState = FAIL;
                      
//        // Send_IgnitionState(IGNITION_ON);  
//        if(CTest_ReadPowerMode() == 0x01)       // Verify Normal Power Mode
//            LED_EN_Write(1);
//        else
//            TestState = FAIL;
                
        // Send_IgnitionState(IGNITION_ON);
                
//        if(CTest_ReadPowerMode() == 0x02)       // Verify Live Power Mode
//            LED_EN_Write(1);
//        else
//            TestState = FAIL;
        
            //----------------------test code----------------------
            testvalue = CTest_ReadPowerMode();
            
            testvaluearray[testindex] = testvalue;
            testindex++;
            
            if(testindex >= 200)
                testindex = 0;
                
 //           if(testvalue == 0x00)
//                LED_EN_Write(1);
//            else if(testvalue == 0x01)
//                LED_EN_Write(1);
//            else if(testvalue == 0x02)
//                LED_EN_Write(1);
//            else
//                LED_EN_Write(1);
            //-----------------------------------------------------

        break;
                
//            case TEST_QUAD:
                
        //-------------------------------------------
        // Quad Stream - 460800
        // - Check that valid quad packets are being sent
        //      - If pass, move to next step
        //      - If fail, set LED to solid red, and wait for the user to reset the test
                while( CTest_VerifyPacket_QUAD() )      // Wait until the packet has been verified
                {}   
        //-------------------------------------------
              
                
                
                
        //-------------------------------------------
        // Debug Port (will need hardware to test)    
        //-------------------------------------------
        // Audio Stream (not a priority)
        //-------------------------------------------   
                
                
        // (Manual and requires a config file)
        //-------------------------------------------
        // Pushbuttons - 230400 - 'packet type'
        //  - Check that the packet is turning all Relay Outputs on - (requires config file)
                CTest_ReadPushbuttons();
        //-------------------------------------------
                
                
        //-------------------------------------------
        // OBDII - (requires a config file)
        // Send a known vehicle event
        // Verify expected response - (corresponding output will be enabled)
        //-------------------------------------------
//                break;
                
        case FAIL:
                
            // Unit has failed the overall test
            // Indicate to the user to press and hold the 'Next Action' button for 3 seconds to reset the test
            
        break;
                

    }
    
    return;
}


uint8 CTest_VerifyPacket_QUAD()
{
    
    //  Setup to read Quad packets
    //  - Switch the mux
    //  - Setup UART_460800
    
    return(0);
}

uint8 CTest_ReadPushbuttons()
{

    // Switch MUX_230400 to read CTest_RS485_Relay_Rx
//        MUX_CTRL_230400_Write(0x00);
    
    // Read the Outputs1_8 and Outputs9_16 bytes, return TRUE if all are active
    
        pRxPacket_Controller = getRxPacket_Controller();
        
        if ( (pRxPacket_Controller->Payload.Outputs1_8 == 0xFF) && (pRxPacket_Controller->Payload.Outputs9_16 == 0xFF) )
            return(1);
        else
            return(0);
       
}

uint8 CTest_ReadPowerMode()
{  
    
    //*** We need to inlude Relay ignition signal, and OBD as triggers
    //*** (Controller config file should have all input logic set to Hi???)
    
    // Switch MUX_230400 to read CTest_RS485_Relay_Rx
//        MUX_CTRL_230400_Write(0x00);
     
    // Read the PowerState byte, Return the Powerstate byte
        pRxPacket_Controller = getRxPacket_Controller();
        return(pRxPacket_Controller->Payload.PowerState);
   
}

void CTest_SendIgnitionState(uint8 ignition_state)           //*** This function needs work
{
    
    pTxPacket_Controller = getTxPacket_Controller();
    pTxPacket_Controller->Payload.RelayInputs = (pTxPacket_Controller->Payload.RelayInputs | 0x01);
    
    MUX_CTRL_230400_Write(0x00);                        // Set the Mux channel
    
    
    return;
}




RxPacket_Controller * getRxPacket_Controller(void)
{
    pRxPacket_Controller = &rxPacket_Controller;
    
    return pRxPacket_Controller;
}

TxPacket_Controller * getTxPacket_Controller(void)
{
    pTxPacket_Controller = &txPacket_Controller;
    
    return pTxPacket_Controller;
}




/* [] END OF FILE */
