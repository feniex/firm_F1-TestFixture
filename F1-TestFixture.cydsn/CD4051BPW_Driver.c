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

#define OTHER_CHIP_EN 33

void initDiagnostics(void)
{
    //DIAG_INH_1_Write(0);
    //DIAG_INH_2_Write(0);
    //DIAG_INH_3_Write(0);
}

static unsigned char getMuxValue(diagnostic_inputs_t channelToRead)
{
    static unsigned char lookUpChipMuxValues[40] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
                                                    0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
                                                    0, 0, 1, 1, 2, 3, 4, 5};
    
    return lookUpChipMuxValues[channelToRead];
}

void selectADCChannelMux(diagnostic_inputs_t channelToRead)
{
    unsigned char localMuxValue = 0;
    
    localMuxValue = getMuxValue(channelToRead);
    
    if(channelToRead<=CHANNEL16)
    {
//        DIAG_INH_1_Write(0);
//        DIAG_INH_2_Write(1);
//        DIAG_INH_3_Write(1);
        
//        DIAG_BCD_C_Write(((localMuxValue&0x04)>>2));
//        DIAG_BCD_B_Write(((localMuxValue&0x02)>>1));
//        DIAG_BCD_A_Write(localMuxValue&0x01);
    }
    else if(channelToRead>CHANNEL16 && channelToRead<=CHANNEL32)
    {
//        DIAG_INH_1_Write(1);
//        DIAG_INH_2_Write(0);
//        DIAG_INH_3_Write(1);
        
//        DIAG_BCD_C_Write(((localMuxValue&0x04)>>2));
//        DIAG_BCD_B_Write(((localMuxValue&0x02)>>1));
//        DIAG_BCD_A_Write(localMuxValue&0x01);
    }
    else if(channelToRead == VSENSEBATT)
    {
//        DIAG_INH_1_Write(1);
//        DIAG_INH_2_Write(1);
//        DIAG_INH_3_Write(0);
        
//        DIAG_BCD_C_Write(((localMuxValue&0x04)>>2));
//        DIAG_BCD_B_Write(((localMuxValue&0x02)>>1));
//        DIAG_BCD_A_Write(localMuxValue&0x01);
    }
    else if(channelToRead>CHANNEL32)
    {
//        DIAG_INH_1_Write(1);
//        DIAG_INH_2_Write(1);
//        DIAG_INH_3_Write(0);
        
//        DIAG_BCD_C_Write(((localMuxValue&0x04)>>2));
//        DIAG_BCD_B_Write(((localMuxValue&0x02)>>1));
//        DIAG_BCD_A_Write(localMuxValue&0x01);
    }
}



/* [] END OF FILE */
