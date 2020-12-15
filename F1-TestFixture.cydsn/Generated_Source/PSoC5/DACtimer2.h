/*******************************************************************************
* File Name: DACtimer2.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_DACtimer2_H)
#define CY_TIMER_DACtimer2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 DACtimer2_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define DACtimer2_Resolution                 16u
#define DACtimer2_UsingFixedFunction         0u
#define DACtimer2_UsingHWCaptureCounter      0u
#define DACtimer2_SoftwareCaptureMode        0u
#define DACtimer2_SoftwareTriggerMode        0u
#define DACtimer2_UsingHWEnable              0u
#define DACtimer2_EnableTriggerMode          0u
#define DACtimer2_InterruptOnCaptureCount    0u
#define DACtimer2_RunModeUsed                0u
#define DACtimer2_ControlRegRemoved          0u

#if defined(DACtimer2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define DACtimer2_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (DACtimer2_UsingFixedFunction)
    #define DACtimer2_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define DACtimer2_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End DACtimer2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!DACtimer2_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (DACtimer2_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!DACtimer2_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}DACtimer2_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    DACtimer2_Start(void) ;
void    DACtimer2_Stop(void) ;

void    DACtimer2_SetInterruptMode(uint8 interruptMode) ;
uint8   DACtimer2_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define DACtimer2_GetInterruptSource() DACtimer2_ReadStatusRegister()

#if(!DACtimer2_UDB_CONTROL_REG_REMOVED)
    uint8   DACtimer2_ReadControlRegister(void) ;
    void    DACtimer2_WriteControlRegister(uint8 control) ;
#endif /* (!DACtimer2_UDB_CONTROL_REG_REMOVED) */

uint16  DACtimer2_ReadPeriod(void) ;
void    DACtimer2_WritePeriod(uint16 period) ;
uint16  DACtimer2_ReadCounter(void) ;
void    DACtimer2_WriteCounter(uint16 counter) ;
uint16  DACtimer2_ReadCapture(void) ;
void    DACtimer2_SoftwareCapture(void) ;

#if(!DACtimer2_UsingFixedFunction) /* UDB Prototypes */
    #if (DACtimer2_SoftwareCaptureMode)
        void    DACtimer2_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!DACtimer2_UsingFixedFunction) */

    #if (DACtimer2_SoftwareTriggerMode)
        void    DACtimer2_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (DACtimer2_SoftwareTriggerMode) */

    #if (DACtimer2_EnableTriggerMode)
        void    DACtimer2_EnableTrigger(void) ;
        void    DACtimer2_DisableTrigger(void) ;
    #endif /* (DACtimer2_EnableTriggerMode) */


    #if(DACtimer2_InterruptOnCaptureCount)
        void    DACtimer2_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (DACtimer2_InterruptOnCaptureCount) */

    #if (DACtimer2_UsingHWCaptureCounter)
        void    DACtimer2_SetCaptureCount(uint8 captureCount) ;
        uint8   DACtimer2_ReadCaptureCount(void) ;
    #endif /* (DACtimer2_UsingHWCaptureCounter) */

    void DACtimer2_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void DACtimer2_Init(void)          ;
void DACtimer2_Enable(void)        ;
void DACtimer2_SaveConfig(void)    ;
void DACtimer2_RestoreConfig(void) ;
void DACtimer2_Sleep(void)         ;
void DACtimer2_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define DACtimer2__B_TIMER__CM_NONE 0
#define DACtimer2__B_TIMER__CM_RISINGEDGE 1
#define DACtimer2__B_TIMER__CM_FALLINGEDGE 2
#define DACtimer2__B_TIMER__CM_EITHEREDGE 3
#define DACtimer2__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define DACtimer2__B_TIMER__TM_NONE 0x00u
#define DACtimer2__B_TIMER__TM_RISINGEDGE 0x04u
#define DACtimer2__B_TIMER__TM_FALLINGEDGE 0x08u
#define DACtimer2__B_TIMER__TM_EITHEREDGE 0x0Cu
#define DACtimer2__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define DACtimer2_INIT_PERIOD             255u
#define DACtimer2_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << DACtimer2_CTRL_CAP_MODE_SHIFT))
#define DACtimer2_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << DACtimer2_CTRL_TRIG_MODE_SHIFT))
#if (DACtimer2_UsingFixedFunction)
    #define DACtimer2_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << DACtimer2_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << DACtimer2_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define DACtimer2_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << DACtimer2_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << DACtimer2_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << DACtimer2_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (DACtimer2_UsingFixedFunction) */
#define DACtimer2_INIT_CAPTURE_COUNT      (2u)
#define DACtimer2_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << DACtimer2_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (DACtimer2_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define DACtimer2_STATUS         (*(reg8 *) DACtimer2_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define DACtimer2_STATUS_MASK    (*(reg8 *) DACtimer2_TimerHW__SR0 )
    #define DACtimer2_CONTROL        (*(reg8 *) DACtimer2_TimerHW__CFG0)
    #define DACtimer2_CONTROL2       (*(reg8 *) DACtimer2_TimerHW__CFG1)
    #define DACtimer2_CONTROL2_PTR   ( (reg8 *) DACtimer2_TimerHW__CFG1)
    #define DACtimer2_RT1            (*(reg8 *) DACtimer2_TimerHW__RT1)
    #define DACtimer2_RT1_PTR        ( (reg8 *) DACtimer2_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define DACtimer2_CONTROL3       (*(reg8 *) DACtimer2_TimerHW__CFG2)
        #define DACtimer2_CONTROL3_PTR   ( (reg8 *) DACtimer2_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define DACtimer2_GLOBAL_ENABLE  (*(reg8 *) DACtimer2_TimerHW__PM_ACT_CFG)
    #define DACtimer2_GLOBAL_STBY_ENABLE  (*(reg8 *) DACtimer2_TimerHW__PM_STBY_CFG)

    #define DACtimer2_CAPTURE_LSB         (* (reg16 *) DACtimer2_TimerHW__CAP0 )
    #define DACtimer2_CAPTURE_LSB_PTR       ((reg16 *) DACtimer2_TimerHW__CAP0 )
    #define DACtimer2_PERIOD_LSB          (* (reg16 *) DACtimer2_TimerHW__PER0 )
    #define DACtimer2_PERIOD_LSB_PTR        ((reg16 *) DACtimer2_TimerHW__PER0 )
    #define DACtimer2_COUNTER_LSB         (* (reg16 *) DACtimer2_TimerHW__CNT_CMP0 )
    #define DACtimer2_COUNTER_LSB_PTR       ((reg16 *) DACtimer2_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define DACtimer2_BLOCK_EN_MASK                     DACtimer2_TimerHW__PM_ACT_MSK
    #define DACtimer2_BLOCK_STBY_EN_MASK                DACtimer2_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define DACtimer2_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define DACtimer2_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define DACtimer2_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define DACtimer2_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define DACtimer2_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define DACtimer2_CTRL_ENABLE                        ((uint8)((uint8)0x01u << DACtimer2_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define DACtimer2_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define DACtimer2_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << DACtimer2_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define DACtimer2_CTRL_MODE_SHIFT                 0x01u
        #define DACtimer2_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << DACtimer2_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define DACtimer2_CTRL_RCOD_SHIFT        0x02u
        #define DACtimer2_CTRL_ENBL_SHIFT        0x00u
        #define DACtimer2_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define DACtimer2_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << DACtimer2_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define DACtimer2_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << DACtimer2_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define DACtimer2_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << DACtimer2_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define DACtimer2_CTRL_RCOD       ((uint8)((uint8)0x03u << DACtimer2_CTRL_RCOD_SHIFT))
        #define DACtimer2_CTRL_ENBL       ((uint8)((uint8)0x80u << DACtimer2_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define DACtimer2_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define DACtimer2_RT1_MASK                        ((uint8)((uint8)0x03u << DACtimer2_RT1_SHIFT))
    #define DACtimer2_SYNC                            ((uint8)((uint8)0x03u << DACtimer2_RT1_SHIFT))
    #define DACtimer2_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define DACtimer2_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << DACtimer2_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define DACtimer2_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << DACtimer2_SYNCDSI_SHIFT))

    #define DACtimer2_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << DACtimer2_CTRL_MODE_SHIFT))
    #define DACtimer2_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << DACtimer2_CTRL_MODE_SHIFT))
    #define DACtimer2_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << DACtimer2_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define DACtimer2_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define DACtimer2_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define DACtimer2_STATUS_TC_INT_MASK_SHIFT        (DACtimer2_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define DACtimer2_STATUS_CAPTURE_INT_MASK_SHIFT   (DACtimer2_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define DACtimer2_STATUS_TC                       ((uint8)((uint8)0x01u << DACtimer2_STATUS_TC_SHIFT))
    #define DACtimer2_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << DACtimer2_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define DACtimer2_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << DACtimer2_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define DACtimer2_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << DACtimer2_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define DACtimer2_STATUS              (* (reg8 *) DACtimer2_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define DACtimer2_STATUS_MASK         (* (reg8 *) DACtimer2_TimerUDB_rstSts_stsreg__MASK_REG)
    #define DACtimer2_STATUS_AUX_CTRL     (* (reg8 *) DACtimer2_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define DACtimer2_CONTROL             (* (reg8 *) DACtimer2_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(DACtimer2_Resolution <= 8u) /* 8-bit Timer */
        #define DACtimer2_CAPTURE_LSB         (* (reg8 *) DACtimer2_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define DACtimer2_CAPTURE_LSB_PTR       ((reg8 *) DACtimer2_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define DACtimer2_PERIOD_LSB          (* (reg8 *) DACtimer2_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define DACtimer2_PERIOD_LSB_PTR        ((reg8 *) DACtimer2_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define DACtimer2_COUNTER_LSB         (* (reg8 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define DACtimer2_COUNTER_LSB_PTR       ((reg8 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(DACtimer2_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define DACtimer2_CAPTURE_LSB         (* (reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define DACtimer2_CAPTURE_LSB_PTR       ((reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define DACtimer2_PERIOD_LSB          (* (reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define DACtimer2_PERIOD_LSB_PTR        ((reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define DACtimer2_COUNTER_LSB         (* (reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define DACtimer2_COUNTER_LSB_PTR       ((reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define DACtimer2_CAPTURE_LSB         (* (reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define DACtimer2_CAPTURE_LSB_PTR       ((reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define DACtimer2_PERIOD_LSB          (* (reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define DACtimer2_PERIOD_LSB_PTR        ((reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define DACtimer2_COUNTER_LSB         (* (reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define DACtimer2_COUNTER_LSB_PTR       ((reg16 *) DACtimer2_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(DACtimer2_Resolution <= 24u)/* 24-bit Timer */
        #define DACtimer2_CAPTURE_LSB         (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define DACtimer2_CAPTURE_LSB_PTR       ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define DACtimer2_PERIOD_LSB          (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define DACtimer2_PERIOD_LSB_PTR        ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define DACtimer2_COUNTER_LSB         (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define DACtimer2_COUNTER_LSB_PTR       ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define DACtimer2_CAPTURE_LSB         (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define DACtimer2_CAPTURE_LSB_PTR       ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define DACtimer2_PERIOD_LSB          (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define DACtimer2_PERIOD_LSB_PTR        ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define DACtimer2_COUNTER_LSB         (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define DACtimer2_COUNTER_LSB_PTR       ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define DACtimer2_CAPTURE_LSB         (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define DACtimer2_CAPTURE_LSB_PTR       ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define DACtimer2_PERIOD_LSB          (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define DACtimer2_PERIOD_LSB_PTR        ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define DACtimer2_COUNTER_LSB         (* (reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define DACtimer2_COUNTER_LSB_PTR       ((reg32 *) DACtimer2_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define DACtimer2_COUNTER_LSB_PTR_8BIT       ((reg8 *) DACtimer2_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (DACtimer2_UsingHWCaptureCounter)
        #define DACtimer2_CAP_COUNT              (*(reg8 *) DACtimer2_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define DACtimer2_CAP_COUNT_PTR          ( (reg8 *) DACtimer2_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define DACtimer2_CAPTURE_COUNT_CTRL     (*(reg8 *) DACtimer2_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define DACtimer2_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) DACtimer2_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (DACtimer2_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define DACtimer2_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define DACtimer2_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define DACtimer2_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define DACtimer2_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define DACtimer2_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define DACtimer2_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << DACtimer2_CTRL_INTCNT_SHIFT))
    #define DACtimer2_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << DACtimer2_CTRL_TRIG_MODE_SHIFT))
    #define DACtimer2_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << DACtimer2_CTRL_TRIG_EN_SHIFT))
    #define DACtimer2_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << DACtimer2_CTRL_CAP_MODE_SHIFT))
    #define DACtimer2_CTRL_ENABLE                    ((uint8)((uint8)0x01u << DACtimer2_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define DACtimer2_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define DACtimer2_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define DACtimer2_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define DACtimer2_STATUS_TC_INT_MASK_SHIFT       DACtimer2_STATUS_TC_SHIFT
    #define DACtimer2_STATUS_CAPTURE_INT_MASK_SHIFT  DACtimer2_STATUS_CAPTURE_SHIFT
    #define DACtimer2_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define DACtimer2_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define DACtimer2_STATUS_FIFOFULL_INT_MASK_SHIFT DACtimer2_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define DACtimer2_STATUS_TC                      ((uint8)((uint8)0x01u << DACtimer2_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define DACtimer2_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << DACtimer2_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define DACtimer2_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << DACtimer2_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define DACtimer2_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << DACtimer2_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define DACtimer2_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << DACtimer2_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define DACtimer2_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << DACtimer2_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define DACtimer2_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << DACtimer2_STATUS_FIFOFULL_SHIFT))

    #define DACtimer2_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define DACtimer2_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define DACtimer2_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define DACtimer2_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define DACtimer2_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define DACtimer2_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_DACtimer2_H */


/* [] END OF FILE */
