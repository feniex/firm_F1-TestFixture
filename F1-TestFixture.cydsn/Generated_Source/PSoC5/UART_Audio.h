/*******************************************************************************
* File Name: UART_Audio.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_UART_Audio_H)
#define CY_UART_UART_Audio_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UART_Audio_RX_ENABLED                     (1u)
#define UART_Audio_TX_ENABLED                     (0u)
#define UART_Audio_HD_ENABLED                     (0u)
#define UART_Audio_RX_INTERRUPT_ENABLED           (0u)
#define UART_Audio_TX_INTERRUPT_ENABLED           (0u)
#define UART_Audio_INTERNAL_CLOCK_USED            (1u)
#define UART_Audio_RXHW_ADDRESS_ENABLED           (0u)
#define UART_Audio_OVER_SAMPLE_COUNT              (8u)
#define UART_Audio_PARITY_TYPE                    (0u)
#define UART_Audio_PARITY_TYPE_SW                 (0u)
#define UART_Audio_BREAK_DETECT                   (0u)
#define UART_Audio_BREAK_BITS_TX                  (13u)
#define UART_Audio_BREAK_BITS_RX                  (13u)
#define UART_Audio_TXCLKGEN_DP                    (1u)
#define UART_Audio_USE23POLLING                   (1u)
#define UART_Audio_FLOW_CONTROL                   (0u)
#define UART_Audio_CLK_FREQ                       (0u)
#define UART_Audio_TX_BUFFER_SIZE                 (4u)
#define UART_Audio_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(UART_Audio_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define UART_Audio_CONTROL_REG_REMOVED            (0u)
#else
    #define UART_Audio_CONTROL_REG_REMOVED            (1u)
#endif /* End UART_Audio_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UART_Audio_backupStruct_
{
    uint8 enableState;

    #if(UART_Audio_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UART_Audio_CONTROL_REG_REMOVED */

} UART_Audio_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UART_Audio_Start(void) ;
void UART_Audio_Stop(void) ;
uint8 UART_Audio_ReadControlRegister(void) ;
void UART_Audio_WriteControlRegister(uint8 control) ;

void UART_Audio_Init(void) ;
void UART_Audio_Enable(void) ;
void UART_Audio_SaveConfig(void) ;
void UART_Audio_RestoreConfig(void) ;
void UART_Audio_Sleep(void) ;
void UART_Audio_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) )

    #if (UART_Audio_RX_INTERRUPT_ENABLED)
        #define UART_Audio_EnableRxInt()  CyIntEnable (UART_Audio_RX_VECT_NUM)
        #define UART_Audio_DisableRxInt() CyIntDisable(UART_Audio_RX_VECT_NUM)
        CY_ISR_PROTO(UART_Audio_RXISR);
    #endif /* UART_Audio_RX_INTERRUPT_ENABLED */

    void UART_Audio_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UART_Audio_SetRxAddress1(uint8 address) ;
    void UART_Audio_SetRxAddress2(uint8 address) ;

    void  UART_Audio_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UART_Audio_ReadRxData(void) ;
    uint8 UART_Audio_ReadRxStatus(void) ;
    uint8 UART_Audio_GetChar(void) ;
    uint16 UART_Audio_GetByte(void) ;
    uint8 UART_Audio_GetRxBufferSize(void)
                                                            ;
    void UART_Audio_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UART_Audio_GetRxInterruptSource   UART_Audio_ReadRxStatus

#endif /* End (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) */

/* Only if TX is enabled */
#if(UART_Audio_TX_ENABLED || UART_Audio_HD_ENABLED)

    #if(UART_Audio_TX_INTERRUPT_ENABLED)
        #define UART_Audio_EnableTxInt()  CyIntEnable (UART_Audio_TX_VECT_NUM)
        #define UART_Audio_DisableTxInt() CyIntDisable(UART_Audio_TX_VECT_NUM)
        #define UART_Audio_SetPendingTxInt() CyIntSetPending(UART_Audio_TX_VECT_NUM)
        #define UART_Audio_ClearPendingTxInt() CyIntClearPending(UART_Audio_TX_VECT_NUM)
        CY_ISR_PROTO(UART_Audio_TXISR);
    #endif /* UART_Audio_TX_INTERRUPT_ENABLED */

    void UART_Audio_SetTxInterruptMode(uint8 intSrc) ;
    void UART_Audio_WriteTxData(uint8 txDataByte) ;
    uint8 UART_Audio_ReadTxStatus(void) ;
    void UART_Audio_PutChar(uint8 txDataByte) ;
    void UART_Audio_PutString(const char8 string[]) ;
    void UART_Audio_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UART_Audio_PutCRLF(uint8 txDataByte) ;
    void UART_Audio_ClearTxBuffer(void) ;
    void UART_Audio_SetTxAddressMode(uint8 addressMode) ;
    void UART_Audio_SendBreak(uint8 retMode) ;
    uint8 UART_Audio_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UART_Audio_PutStringConst         UART_Audio_PutString
    #define UART_Audio_PutArrayConst          UART_Audio_PutArray
    #define UART_Audio_GetTxInterruptSource   UART_Audio_ReadTxStatus

#endif /* End UART_Audio_TX_ENABLED || UART_Audio_HD_ENABLED */

#if(UART_Audio_HD_ENABLED)
    void UART_Audio_LoadRxConfig(void) ;
    void UART_Audio_LoadTxConfig(void) ;
#endif /* End UART_Audio_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Audio) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UART_Audio_CyBtldrCommStart(void) CYSMALL ;
    void    UART_Audio_CyBtldrCommStop(void) CYSMALL ;
    void    UART_Audio_CyBtldrCommReset(void) CYSMALL ;
    cystatus UART_Audio_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UART_Audio_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Audio)
        #define CyBtldrCommStart    UART_Audio_CyBtldrCommStart
        #define CyBtldrCommStop     UART_Audio_CyBtldrCommStop
        #define CyBtldrCommReset    UART_Audio_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_Audio_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_Audio_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Audio) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UART_Audio_BYTE2BYTE_TIME_OUT (25u)
    #define UART_Audio_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define UART_Audio_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define UART_Audio_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UART_Audio_SET_SPACE      (0x00u)
#define UART_Audio_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (UART_Audio_TX_ENABLED) || (UART_Audio_HD_ENABLED) )
    #if(UART_Audio_TX_INTERRUPT_ENABLED)
        #define UART_Audio_TX_VECT_NUM            (uint8)UART_Audio_TXInternalInterrupt__INTC_NUMBER
        #define UART_Audio_TX_PRIOR_NUM           (uint8)UART_Audio_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_Audio_TX_INTERRUPT_ENABLED */

    #define UART_Audio_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define UART_Audio_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define UART_Audio_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(UART_Audio_TX_ENABLED)
        #define UART_Audio_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (UART_Audio_HD_ENABLED) */
        #define UART_Audio_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (UART_Audio_TX_ENABLED) */

    #define UART_Audio_TX_STS_COMPLETE            (uint8)(0x01u << UART_Audio_TX_STS_COMPLETE_SHIFT)
    #define UART_Audio_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UART_Audio_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART_Audio_TX_STS_FIFO_FULL           (uint8)(0x01u << UART_Audio_TX_STS_FIFO_FULL_SHIFT)
    #define UART_Audio_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UART_Audio_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UART_Audio_TX_ENABLED) || (UART_Audio_HD_ENABLED)*/

#if( (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) )
    #if(UART_Audio_RX_INTERRUPT_ENABLED)
        #define UART_Audio_RX_VECT_NUM            (uint8)UART_Audio_RXInternalInterrupt__INTC_NUMBER
        #define UART_Audio_RX_PRIOR_NUM           (uint8)UART_Audio_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_Audio_RX_INTERRUPT_ENABLED */
    #define UART_Audio_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UART_Audio_RX_STS_BREAK_SHIFT             (0x01u)
    #define UART_Audio_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UART_Audio_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UART_Audio_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UART_Audio_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UART_Audio_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UART_Audio_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UART_Audio_RX_STS_MRKSPC           (uint8)(0x01u << UART_Audio_RX_STS_MRKSPC_SHIFT)
    #define UART_Audio_RX_STS_BREAK            (uint8)(0x01u << UART_Audio_RX_STS_BREAK_SHIFT)
    #define UART_Audio_RX_STS_PAR_ERROR        (uint8)(0x01u << UART_Audio_RX_STS_PAR_ERROR_SHIFT)
    #define UART_Audio_RX_STS_STOP_ERROR       (uint8)(0x01u << UART_Audio_RX_STS_STOP_ERROR_SHIFT)
    #define UART_Audio_RX_STS_OVERRUN          (uint8)(0x01u << UART_Audio_RX_STS_OVERRUN_SHIFT)
    #define UART_Audio_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UART_Audio_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART_Audio_RX_STS_ADDR_MATCH       (uint8)(0x01u << UART_Audio_RX_STS_ADDR_MATCH_SHIFT)
    #define UART_Audio_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UART_Audio_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UART_Audio_RX_HW_MASK                     (0x7Fu)
#endif /* End (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) */

/* Control Register definitions */
#define UART_Audio_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UART_Audio_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UART_Audio_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UART_Audio_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UART_Audio_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UART_Audio_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UART_Audio_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UART_Audio_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UART_Audio_CTRL_HD_SEND               (uint8)(0x01u << UART_Audio_CTRL_HD_SEND_SHIFT)
#define UART_Audio_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UART_Audio_CTRL_HD_SEND_BREAK_SHIFT)
#define UART_Audio_CTRL_MARK                  (uint8)(0x01u << UART_Audio_CTRL_MARK_SHIFT)
#define UART_Audio_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UART_Audio_CTRL_PARITY_TYPE0_SHIFT)
#define UART_Audio_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UART_Audio_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UART_Audio_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UART_Audio_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UART_Audio_SEND_BREAK                         (0x00u)
#define UART_Audio_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UART_Audio_REINIT                             (0x02u)
#define UART_Audio_SEND_WAIT_REINIT                   (0x03u)

#define UART_Audio_OVER_SAMPLE_8                      (8u)
#define UART_Audio_OVER_SAMPLE_16                     (16u)

#define UART_Audio_BIT_CENTER                         (UART_Audio_OVER_SAMPLE_COUNT - 2u)

#define UART_Audio_FIFO_LENGTH                        (4u)
#define UART_Audio_NUMBER_OF_START_BIT                (1u)
#define UART_Audio_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define UART_Audio_TXBITCTR_BREAKBITS8X   ((UART_Audio_BREAK_BITS_TX * UART_Audio_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define UART_Audio_TXBITCTR_BREAKBITS ((UART_Audio_BREAK_BITS_TX * UART_Audio_OVER_SAMPLE_COUNT) - 1u)

#define UART_Audio_HALF_BIT_COUNT   \
                            (((UART_Audio_OVER_SAMPLE_COUNT / 2u) + (UART_Audio_USE23POLLING * 1u)) - 2u)
#if (UART_Audio_OVER_SAMPLE_COUNT == UART_Audio_OVER_SAMPLE_8)
    #define UART_Audio_HD_TXBITCTR_INIT   (((UART_Audio_BREAK_BITS_TX + \
                            UART_Audio_NUMBER_OF_START_BIT) * UART_Audio_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UART_Audio_RXBITCTR_INIT  ((((UART_Audio_BREAK_BITS_RX + UART_Audio_NUMBER_OF_START_BIT) \
                            * UART_Audio_OVER_SAMPLE_COUNT) + UART_Audio_HALF_BIT_COUNT) - 1u)

#else /* UART_Audio_OVER_SAMPLE_COUNT == UART_Audio_OVER_SAMPLE_16 */
    #define UART_Audio_HD_TXBITCTR_INIT   ((8u * UART_Audio_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define UART_Audio_RXBITCTR_INIT      (((7u * UART_Audio_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UART_Audio_HALF_BIT_COUNT)
#endif /* End UART_Audio_OVER_SAMPLE_COUNT */

#define UART_Audio_HD_RXBITCTR_INIT                   UART_Audio_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UART_Audio_initVar;
#if (UART_Audio_TX_INTERRUPT_ENABLED && UART_Audio_TX_ENABLED)
    extern volatile uint8 UART_Audio_txBuffer[UART_Audio_TX_BUFFER_SIZE];
    extern volatile uint8 UART_Audio_txBufferRead;
    extern uint8 UART_Audio_txBufferWrite;
#endif /* (UART_Audio_TX_INTERRUPT_ENABLED && UART_Audio_TX_ENABLED) */
#if (UART_Audio_RX_INTERRUPT_ENABLED && (UART_Audio_RX_ENABLED || UART_Audio_HD_ENABLED))
    extern uint8 UART_Audio_errorStatus;
    extern volatile uint8 UART_Audio_rxBuffer[UART_Audio_RX_BUFFER_SIZE];
    extern volatile uint8 UART_Audio_rxBufferRead;
    extern volatile uint8 UART_Audio_rxBufferWrite;
    extern volatile uint8 UART_Audio_rxBufferLoopDetect;
    extern volatile uint8 UART_Audio_rxBufferOverflow;
    #if (UART_Audio_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UART_Audio_rxAddressMode;
        extern volatile uint8 UART_Audio_rxAddressDetected;
    #endif /* (UART_Audio_RXHW_ADDRESS_ENABLED) */
#endif /* (UART_Audio_RX_INTERRUPT_ENABLED && (UART_Audio_RX_ENABLED || UART_Audio_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART_Audio__B_UART__AM_SW_BYTE_BYTE 1
#define UART_Audio__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART_Audio__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART_Audio__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART_Audio__B_UART__AM_NONE 0

#define UART_Audio__B_UART__NONE_REVB 0
#define UART_Audio__B_UART__EVEN_REVB 1
#define UART_Audio__B_UART__ODD_REVB 2
#define UART_Audio__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UART_Audio_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UART_Audio_NUMBER_OF_STOP_BITS    (1u)

#if (UART_Audio_RXHW_ADDRESS_ENABLED)
    #define UART_Audio_RX_ADDRESS_MODE    (0u)
    #define UART_Audio_RX_HW_ADDRESS1     (0u)
    #define UART_Audio_RX_HW_ADDRESS2     (0u)
#endif /* (UART_Audio_RXHW_ADDRESS_ENABLED) */

#define UART_Audio_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << UART_Audio_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UART_Audio_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UART_Audio_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UART_Audio_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UART_Audio_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UART_Audio_RX_STS_BREAK_SHIFT) \
                                        | (0 << UART_Audio_RX_STS_OVERRUN_SHIFT))

#define UART_Audio_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << UART_Audio_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << UART_Audio_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UART_Audio_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UART_Audio_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UART_Audio_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_Audio_CONTROL_REG \
                            (* (reg8 *) UART_Audio_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UART_Audio_CONTROL_PTR \
                            (  (reg8 *) UART_Audio_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UART_Audio_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_Audio_TX_ENABLED)
    #define UART_Audio_TXDATA_REG          (* (reg8 *) UART_Audio_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_Audio_TXDATA_PTR          (  (reg8 *) UART_Audio_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_Audio_TXDATA_AUX_CTL_REG  (* (reg8 *) UART_Audio_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_Audio_TXDATA_AUX_CTL_PTR  (  (reg8 *) UART_Audio_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_Audio_TXSTATUS_REG        (* (reg8 *) UART_Audio_BUART_sTX_TxSts__STATUS_REG)
    #define UART_Audio_TXSTATUS_PTR        (  (reg8 *) UART_Audio_BUART_sTX_TxSts__STATUS_REG)
    #define UART_Audio_TXSTATUS_MASK_REG   (* (reg8 *) UART_Audio_BUART_sTX_TxSts__MASK_REG)
    #define UART_Audio_TXSTATUS_MASK_PTR   (  (reg8 *) UART_Audio_BUART_sTX_TxSts__MASK_REG)
    #define UART_Audio_TXSTATUS_ACTL_REG   (* (reg8 *) UART_Audio_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UART_Audio_TXSTATUS_ACTL_PTR   (  (reg8 *) UART_Audio_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UART_Audio_TXCLKGEN_DP)
        #define UART_Audio_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_Audio_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_Audio_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UART_Audio_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UART_Audio_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_Audio_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_Audio_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_Audio_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_Audio_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UART_Audio_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UART_Audio_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UART_Audio_TXCLKGEN_DP */

#endif /* End UART_Audio_TX_ENABLED */

#if(UART_Audio_HD_ENABLED)

    #define UART_Audio_TXDATA_REG             (* (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_Audio_TXDATA_PTR             (  (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_Audio_TXDATA_AUX_CTL_REG     (* (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UART_Audio_TXDATA_AUX_CTL_PTR     (  (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_Audio_TXSTATUS_REG           (* (reg8 *) UART_Audio_BUART_sRX_RxSts__STATUS_REG )
    #define UART_Audio_TXSTATUS_PTR           (  (reg8 *) UART_Audio_BUART_sRX_RxSts__STATUS_REG )
    #define UART_Audio_TXSTATUS_MASK_REG      (* (reg8 *) UART_Audio_BUART_sRX_RxSts__MASK_REG )
    #define UART_Audio_TXSTATUS_MASK_PTR      (  (reg8 *) UART_Audio_BUART_sRX_RxSts__MASK_REG )
    #define UART_Audio_TXSTATUS_ACTL_REG      (* (reg8 *) UART_Audio_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_Audio_TXSTATUS_ACTL_PTR      (  (reg8 *) UART_Audio_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UART_Audio_HD_ENABLED */

#if( (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) )
    #define UART_Audio_RXDATA_REG             (* (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_Audio_RXDATA_PTR             (  (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_Audio_RXADDRESS1_REG         (* (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_Audio_RXADDRESS1_PTR         (  (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_Audio_RXADDRESS2_REG         (* (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_Audio_RXADDRESS2_PTR         (  (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_Audio_RXDATA_AUX_CTL_REG     (* (reg8 *) UART_Audio_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_Audio_RXBITCTR_PERIOD_REG    (* (reg8 *) UART_Audio_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_Audio_RXBITCTR_PERIOD_PTR    (  (reg8 *) UART_Audio_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_Audio_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_Audio_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_Audio_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_Audio_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_Audio_RXBITCTR_COUNTER_REG   (* (reg8 *) UART_Audio_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UART_Audio_RXBITCTR_COUNTER_PTR   (  (reg8 *) UART_Audio_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UART_Audio_RXSTATUS_REG           (* (reg8 *) UART_Audio_BUART_sRX_RxSts__STATUS_REG )
    #define UART_Audio_RXSTATUS_PTR           (  (reg8 *) UART_Audio_BUART_sRX_RxSts__STATUS_REG )
    #define UART_Audio_RXSTATUS_MASK_REG      (* (reg8 *) UART_Audio_BUART_sRX_RxSts__MASK_REG )
    #define UART_Audio_RXSTATUS_MASK_PTR      (  (reg8 *) UART_Audio_BUART_sRX_RxSts__MASK_REG )
    #define UART_Audio_RXSTATUS_ACTL_REG      (* (reg8 *) UART_Audio_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_Audio_RXSTATUS_ACTL_PTR      (  (reg8 *) UART_Audio_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) */

#if(UART_Audio_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UART_Audio_INTCLOCK_CLKEN_REG     (* (reg8 *) UART_Audio_IntClock__PM_ACT_CFG)
    #define UART_Audio_INTCLOCK_CLKEN_PTR     (  (reg8 *) UART_Audio_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UART_Audio_INTCLOCK_CLKEN_MASK    UART_Audio_IntClock__PM_ACT_MSK
#endif /* End UART_Audio_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UART_Audio_TX_ENABLED)
    #define UART_Audio_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UART_Audio_TX_ENABLED */

#if(UART_Audio_HD_ENABLED)
    #define UART_Audio_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UART_Audio_HD_ENABLED */

#if( (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) )
    #define UART_Audio_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define UART_Audio_WAIT_1_MS      UART_Audio_BL_CHK_DELAY_MS   

#define UART_Audio_TXBUFFERSIZE   UART_Audio_TX_BUFFER_SIZE
#define UART_Audio_RXBUFFERSIZE   UART_Audio_RX_BUFFER_SIZE

#if (UART_Audio_RXHW_ADDRESS_ENABLED)
    #define UART_Audio_RXADDRESSMODE  UART_Audio_RX_ADDRESS_MODE
    #define UART_Audio_RXHWADDRESS1   UART_Audio_RX_HW_ADDRESS1
    #define UART_Audio_RXHWADDRESS2   UART_Audio_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define UART_Audio_RXAddressMode  UART_Audio_RXADDRESSMODE
#endif /* (UART_Audio_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define UART_Audio_initvar                    UART_Audio_initVar

#define UART_Audio_RX_Enabled                 UART_Audio_RX_ENABLED
#define UART_Audio_TX_Enabled                 UART_Audio_TX_ENABLED
#define UART_Audio_HD_Enabled                 UART_Audio_HD_ENABLED
#define UART_Audio_RX_IntInterruptEnabled     UART_Audio_RX_INTERRUPT_ENABLED
#define UART_Audio_TX_IntInterruptEnabled     UART_Audio_TX_INTERRUPT_ENABLED
#define UART_Audio_InternalClockUsed          UART_Audio_INTERNAL_CLOCK_USED
#define UART_Audio_RXHW_Address_Enabled       UART_Audio_RXHW_ADDRESS_ENABLED
#define UART_Audio_OverSampleCount            UART_Audio_OVER_SAMPLE_COUNT
#define UART_Audio_ParityType                 UART_Audio_PARITY_TYPE

#if( UART_Audio_TX_ENABLED && (UART_Audio_TXBUFFERSIZE > UART_Audio_FIFO_LENGTH))
    #define UART_Audio_TXBUFFER               UART_Audio_txBuffer
    #define UART_Audio_TXBUFFERREAD           UART_Audio_txBufferRead
    #define UART_Audio_TXBUFFERWRITE          UART_Audio_txBufferWrite
#endif /* End UART_Audio_TX_ENABLED */
#if( ( UART_Audio_RX_ENABLED || UART_Audio_HD_ENABLED ) && \
     (UART_Audio_RXBUFFERSIZE > UART_Audio_FIFO_LENGTH) )
    #define UART_Audio_RXBUFFER               UART_Audio_rxBuffer
    #define UART_Audio_RXBUFFERREAD           UART_Audio_rxBufferRead
    #define UART_Audio_RXBUFFERWRITE          UART_Audio_rxBufferWrite
    #define UART_Audio_RXBUFFERLOOPDETECT     UART_Audio_rxBufferLoopDetect
    #define UART_Audio_RXBUFFER_OVERFLOW      UART_Audio_rxBufferOverflow
#endif /* End UART_Audio_RX_ENABLED */

#ifdef UART_Audio_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_Audio_CONTROL                UART_Audio_CONTROL_REG
#endif /* End UART_Audio_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_Audio_TX_ENABLED)
    #define UART_Audio_TXDATA                 UART_Audio_TXDATA_REG
    #define UART_Audio_TXSTATUS               UART_Audio_TXSTATUS_REG
    #define UART_Audio_TXSTATUS_MASK          UART_Audio_TXSTATUS_MASK_REG
    #define UART_Audio_TXSTATUS_ACTL          UART_Audio_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UART_Audio_TXCLKGEN_DP)
        #define UART_Audio_TXBITCLKGEN_CTR        UART_Audio_TXBITCLKGEN_CTR_REG
        #define UART_Audio_TXBITCLKTX_COMPLETE    UART_Audio_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UART_Audio_TXBITCTR_PERIOD        UART_Audio_TXBITCTR_PERIOD_REG
        #define UART_Audio_TXBITCTR_CONTROL       UART_Audio_TXBITCTR_CONTROL_REG
        #define UART_Audio_TXBITCTR_COUNTER       UART_Audio_TXBITCTR_COUNTER_REG
    #endif /* UART_Audio_TXCLKGEN_DP */
#endif /* End UART_Audio_TX_ENABLED */

#if(UART_Audio_HD_ENABLED)
    #define UART_Audio_TXDATA                 UART_Audio_TXDATA_REG
    #define UART_Audio_TXSTATUS               UART_Audio_TXSTATUS_REG
    #define UART_Audio_TXSTATUS_MASK          UART_Audio_TXSTATUS_MASK_REG
    #define UART_Audio_TXSTATUS_ACTL          UART_Audio_TXSTATUS_ACTL_REG
#endif /* End UART_Audio_HD_ENABLED */

#if( (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) )
    #define UART_Audio_RXDATA                 UART_Audio_RXDATA_REG
    #define UART_Audio_RXADDRESS1             UART_Audio_RXADDRESS1_REG
    #define UART_Audio_RXADDRESS2             UART_Audio_RXADDRESS2_REG
    #define UART_Audio_RXBITCTR_PERIOD        UART_Audio_RXBITCTR_PERIOD_REG
    #define UART_Audio_RXBITCTR_CONTROL       UART_Audio_RXBITCTR_CONTROL_REG
    #define UART_Audio_RXBITCTR_COUNTER       UART_Audio_RXBITCTR_COUNTER_REG
    #define UART_Audio_RXSTATUS               UART_Audio_RXSTATUS_REG
    #define UART_Audio_RXSTATUS_MASK          UART_Audio_RXSTATUS_MASK_REG
    #define UART_Audio_RXSTATUS_ACTL          UART_Audio_RXSTATUS_ACTL_REG
#endif /* End  (UART_Audio_RX_ENABLED) || (UART_Audio_HD_ENABLED) */

#if(UART_Audio_INTERNAL_CLOCK_USED)
    #define UART_Audio_INTCLOCK_CLKEN         UART_Audio_INTCLOCK_CLKEN_REG
#endif /* End UART_Audio_INTERNAL_CLOCK_USED */

#define UART_Audio_WAIT_FOR_COMLETE_REINIT    UART_Audio_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UART_Audio_H */


/* [] END OF FILE */
