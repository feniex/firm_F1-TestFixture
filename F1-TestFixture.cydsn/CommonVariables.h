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
#ifndef COMMON_VARIABLES_H_
#define COMMON_VARIABLES_H_
    
#include <project.h>
#include <stdbool.h>
    
#define SPEAKER_COUNT               2
#define CHANNEL_COUNT_PER_SPEAKER   6
    
#define SPEAKER_1   0
#define SPEAKER_2   1
    
#define PWM_MODE    0
#define DAC_MODE    1
    
#define TONE_TYPE_LIST_SIZE         23

enum ToneType
{
    NO_TONE,            //0 
    
    WAIL,               //1
    SLOW_YELP,          //2
    FAST_YELP,          //3
    PHASER,             //4
    HORN,               //5
    
    MECHANICAL,         //6
    MANUAL_WAIL,        //7    
    HIGH_LOW,           //8
    PCALL_SLOW,         //9
    PCALL_FAST,         //10
    
    HORN_PHASER,        //11
    HORN_YELP,          //12
    PHASER_YELP,        //13
   
    ECTOSIREN,          //14
    //GHOSTBUSTERS,       //15
    COPS_SONG,          //16
    
    MOVE_OUT,           //17
    PULL_OVER,          //18
    STEP_OUT,           //19
    STEP_OUT_HANDS_UP,  //20
    REMAIN_IN_VEHICLE,  //21
    REMAIN_WINDOW_DOWN, //22
    
    TEST_TONE
    //MECHANICAL_DAC      //Should not be used in final version
};

#endif
/* [] END OF FILE */
