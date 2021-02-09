/*******************************************************************************
* File Name: WaveDAC.h  
* Version 2.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the 8-bit Waveform DAC (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_WaveDAC8_WaveDAC_H) 
#define CY_WaveDAC8_WaveDAC_H

#include "cytypes.h"
#include "cyfitter.h"
#include <WaveDAC_Wave1_DMA_dma.h>
#include <WaveDAC_Wave2_DMA_dma.h>
#include <WaveDAC_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define WaveDAC_WAVE1_TYPE     (1u)     /* Waveform for wave1 */
#define WaveDAC_WAVE2_TYPE     (2u)     /* Waveform for wave2 */
#define WaveDAC_SINE_WAVE      (0u)
#define WaveDAC_SQUARE_WAVE    (1u)
#define WaveDAC_TRIANGLE_WAVE  (2u)
#define WaveDAC_SAWTOOTH_WAVE  (3u)
#define WaveDAC_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define WaveDAC_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define WaveDAC_WAVE1_LENGTH   (100u)   /* Length for wave1 */
#define WaveDAC_WAVE2_LENGTH   (100u)   /* Length for wave2 */
	
#define WaveDAC_DEFAULT_RANGE    (1u) /* Default DAC range */
#define WaveDAC_DAC_RANGE_1V     (0u)
#define WaveDAC_DAC_RANGE_1V_BUF (16u)
#define WaveDAC_DAC_RANGE_4V     (1u)
#define WaveDAC_DAC_RANGE_4V_BUF (17u)
#define WaveDAC_VOLT_MODE        (0u)
#define WaveDAC_CURRENT_MODE     (1u)
#define WaveDAC_DAC_MODE         (((WaveDAC_DEFAULT_RANGE == WaveDAC_DAC_RANGE_1V) || \
									  (WaveDAC_DEFAULT_RANGE == WaveDAC_DAC_RANGE_4V) || \
							  		  (WaveDAC_DEFAULT_RANGE == WaveDAC_DAC_RANGE_1V_BUF) || \
									  (WaveDAC_DEFAULT_RANGE == WaveDAC_DAC_RANGE_4V_BUF)) ? \
									   WaveDAC_VOLT_MODE : WaveDAC_CURRENT_MODE)

#define WaveDAC_DACMODE WaveDAC_DAC_MODE /* legacy definition for backward compatibility */

#define WaveDAC_DIRECT_MODE (0u)
#define WaveDAC_BUFFER_MODE (1u)
#define WaveDAC_OUT_MODE    (((WaveDAC_DEFAULT_RANGE == WaveDAC_DAC_RANGE_1V_BUF) || \
								 (WaveDAC_DEFAULT_RANGE == WaveDAC_DAC_RANGE_4V_BUF)) ? \
								  WaveDAC_BUFFER_MODE : WaveDAC_DIRECT_MODE)

#if(WaveDAC_OUT_MODE == WaveDAC_BUFFER_MODE)
    #include <WaveDAC_BuffAmp.h>
#endif /* WaveDAC_OUT_MODE == WaveDAC_BUFFER_MODE */

#define WaveDAC_CLOCK_INT      (1u)
#define WaveDAC_CLOCK_EXT      (0u)
#define WaveDAC_CLOCK_SRC      (1u)

#if(WaveDAC_CLOCK_SRC == WaveDAC_CLOCK_INT)  
	#include <WaveDAC_DacClk.h>
	#if defined(WaveDAC_DacClk_PHASE)
		#define WaveDAC_CLK_PHASE_0nS (1u)
	#endif /* defined(WaveDAC_DacClk_PHASE) */
#endif /* WaveDAC_CLOCK_SRC == WaveDAC_CLOCK_INT */

#if (CY_PSOC3)
	#define WaveDAC_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define WaveDAC_Wave1_DMA_BYTES_PER_BURST      (1u)
#define WaveDAC_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define WaveDAC_Wave2_DMA_BYTES_PER_BURST      (1u)
#define WaveDAC_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}WaveDAC_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void WaveDAC_Start(void)             ;
void WaveDAC_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void WaveDAC_Init(void)              ;
void WaveDAC_Enable(void)            ;
void WaveDAC_Stop(void)              ;

void WaveDAC_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void WaveDAC_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void WaveDAC_Sleep(void)             ;
void WaveDAC_Wakeup(void)            ;

#define WaveDAC_SetSpeed       WaveDAC_VDAC8_SetSpeed
#define WaveDAC_SetRange       WaveDAC_VDAC8_SetRange
#define WaveDAC_SetValue       WaveDAC_VDAC8_SetValue
#define WaveDAC_DacTrim        WaveDAC_VDAC8_DacTrim
#define WaveDAC_SaveConfig     WaveDAC_VDAC8_SaveConfig
#define WaveDAC_RestoreConfig  WaveDAC_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 WaveDAC_initVar;

extern const uint8 CYCODE WaveDAC_wave1[WaveDAC_WAVE1_LENGTH];
extern const uint8 CYCODE WaveDAC_wave2[WaveDAC_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(WaveDAC_DAC_MODE == WaveDAC_VOLT_MODE)
    #define WaveDAC_RANGE_1V       (0x00u)
    #define WaveDAC_RANGE_4V       (0x04u)
#else /* current mode */
    #define WaveDAC_RANGE_32uA     (0x00u)
    #define WaveDAC_RANGE_255uA    (0x04u)
    #define WaveDAC_RANGE_2mA      (0x08u)
    #define WaveDAC_RANGE_2048uA   WaveDAC_RANGE_2mA
#endif /* WaveDAC_DAC_MODE == WaveDAC_VOLT_MODE */

/* Power setting for SetSpeed API */
#define WaveDAC_LOWSPEED       (0x00u)
#define WaveDAC_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define WaveDAC_DAC8__D WaveDAC_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define WaveDAC_HS_MASK        (0x02u)
#define WaveDAC_HS_LOWPOWER    (0x00u)
#define WaveDAC_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define WaveDAC_MODE_MASK      (0x10u)
#define WaveDAC_MODE_V         (0x00u)
#define WaveDAC_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define WaveDAC_RANGE_MASK     (0x0Cu)
#define WaveDAC_RANGE_0        (0x00u)
#define WaveDAC_RANGE_1        (0x04u)
#define WaveDAC_RANGE_2        (0x08u)
#define WaveDAC_RANGE_3        (0x0Cu)
#define WaveDAC_IDIR_MASK      (0x04u)

#define WaveDAC_DAC_RANGE      ((uint8)(1u << 2u) & WaveDAC_RANGE_MASK)
#define WaveDAC_DAC_POL        ((uint8)(1u >> 1u) & WaveDAC_IDIR_MASK)


#endif /* CY_WaveDAC8_WaveDAC_H  */

/* [] END OF FILE */
