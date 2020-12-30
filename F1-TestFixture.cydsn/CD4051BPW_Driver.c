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

#include <CD4051BPW_Driver.h>

//#define OTHER_CHIP_EN 33

// *** Pins need to be remapped if they are going to be read individually
// *** Right now it is set up to read all channels only

//  Out_7   -   Mux_1 Channel_0         - 0
//  Out_6   -   Mux_1 Channel_1         - 1
//  Out_5   -   Mux_1 Channel_2         - 2
//  Out_8   -   Mux_1 Channel_3         - 3
//  Out_24   -   Mux_1 Channel_4        - 4
//  Out_21   -   Mux_1 Channel_5        - 5
//  Out_23   -   Mux_1 Channel_6        - 6
//  Out_22   -   Mux_1 Channel_7        - 7
//
//  Out_14   -   Mux_2 Channel_0        - 8
//  Out_15   -   Mux_2 Channel_1        - 9
//  Out_16   -   Mux_2 Channel_2        - 10
//  Out_13   -   Mux_2 Channel_3        - 11
//  Out_4   -   Mux_2 Channel_4         - 12
//  Out_1   -   Mux_2 Channel_5         - 13
//  Out_3   -   Mux_2 Channel_6         - 14
//  Out_2   -   Mux_2 Channel_7         - 15
//
//  Out_26   -   Mux_3 Channel_0        - 16
//  Out_27   -   Mux_3 Channel_1        - 17
//  Out_28   -   Mux_3 Channel_2        - 18
//  Out_25   -   Mux_3 Channel_3        - 19
//  Out_29   -   Mux_3 Channel_4        - 20
//  Out_32   -   Mux_3 Channel_5        - 21
//  Out_30   -   Mux_3 Channel_6        - 22
//  Out_31   -   Mux_3 Channel_7        - 23
//
//  Out_18   -   Mux_4 Channel_0        - 24
//  Out_19   -   Mux_4 Channel_1        - 25
//  Out_20   -   Mux_4 Channel_2        - 26
//  Out_17   -   Mux_4 Channel_3        - 27
//  Out_12   -   Mux_4 Channel_4        - 28
//  Out_9   -   Mux_4 Channel_5         - 29
//  Out_11   -   Mux_4 Channel_6        - 30
//  Out_10   -   Mux_4 Channel_7        - 31





void initDiagnostics(void)
{
    //DIAG_INH_1_Write(0);
    //DIAG_INH_2_Write(0);
    //DIAG_INH_3_Write(0);
}

static unsigned char getMuxValue(uint8 channelToRead)
{

    static unsigned char lookUpChipMuxValues[32] = {13, 15, 14, 12, 2, 1, 0, 3,         //Output_1-8
                                                    29, 31, 30, 28, 11, 8, 9, 10,       //Output_9-16
                                                    27, 24, 25, 26, 5, 7, 6, 4,         //Output_17-24
                                                    19, 16, 17, 18, 20, 22, 23, 21,};   //Output_25-32
//    static unsigned char lookUpChipMuxValues[32] = {13, 15, 14, 12, 2, 1, 0, 3,         //Output_1-8
//                                                    29, 31, 30, 28, 11, 8, 9, 10,       //Output_9-16
//                                                    27, 24, 25, 26, 5, 7, 6, 4,         //Output_17-24
//                                                    19, 16, 17, 18, 20, 22, 23, 21,};   //Output_25-32
    return lookUpChipMuxValues[channelToRead];
}

void selectADCChannelMux(uint8 channelToRead)
{
    unsigned char localMuxValue = 0;
    //localMuxValue = channelToRead;
    
    localMuxValue = getMuxValue(channelToRead);
    
    if(localMuxValue < 8)
    {

        RTest_BLOCK_1_EN_Write(0);                                  // Address Mux_1
        RTest_BLOCK_2_EN_Write(1);
        RTest_BLOCK_3_EN_Write(1);
        RTest_BLOCK_4_EN_Write(1);
        
        RTest_DEMUX_C_Write(((localMuxValue&0x04)>>2));
        RTest_DEMUX_B_Write(((localMuxValue&0x02)>>1));
        RTest_DEMUX_A_Write(localMuxValue&0x01);
 
    }
    
    else if( (localMuxValue >= 8) && (localMuxValue<16) )
    {

        RTest_BLOCK_1_EN_Write(1);                                  // Address Mux_1
        RTest_BLOCK_2_EN_Write(0);
        RTest_BLOCK_3_EN_Write(1);
        RTest_BLOCK_4_EN_Write(1);
        
        RTest_DEMUX_C_Write(((localMuxValue&0x04)>>2));
        RTest_DEMUX_B_Write(((localMuxValue&0x02)>>1));
        RTest_DEMUX_A_Write(localMuxValue&0x01);
        
    }
    
    else if( (localMuxValue >= 16) && (localMuxValue<24) )
    {

        RTest_BLOCK_1_EN_Write(1);                                  // Address Mux_1
        RTest_BLOCK_2_EN_Write(1);
        RTest_BLOCK_3_EN_Write(0);
        RTest_BLOCK_4_EN_Write(1);
        
        RTest_DEMUX_C_Write(((localMuxValue&0x04)>>2));
        RTest_DEMUX_B_Write(((localMuxValue&0x02)>>1));
        RTest_DEMUX_A_Write(localMuxValue&0x01);
        
    }
    
    else if( (localMuxValue >= 24) && (localMuxValue<32) )
    {

        RTest_BLOCK_1_EN_Write(1);                                  // Address Mux_1
        RTest_BLOCK_2_EN_Write(1);
        RTest_BLOCK_3_EN_Write(1);
        RTest_BLOCK_4_EN_Write(0);
        
        RTest_DEMUX_C_Write(((localMuxValue&0x04)>>2));
        RTest_DEMUX_B_Write(((localMuxValue&0x02)>>1));
        RTest_DEMUX_A_Write(localMuxValue&0x01);
        
    }

}



/* [] END OF FILE */
