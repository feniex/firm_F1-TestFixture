/*******************************************************************************
* File Name: DEBUG_PORT.h
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


#if !defined(CY_UART_DEBUG_PORT_H)
#define CY_UART_DEBUG_PORT_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define DEBUG_PORT_RX_ENABLED                     (1u)
#define DEBUG_PORT_TX_ENABLED                     (1u)
#define DEBUG_PORT_HD_ENABLED                     (0u)
#define DEBUG_PORT_RX_INTERRUPT_ENABLED           (0u)
#define DEBUG_PORT_TX_INTERRUPT_ENABLED           (0u)
#define DEBUG_PORT_INTERNAL_CLOCK_USED            (1u)
#define DEBUG_PORT_RXHW_ADDRESS_ENABLED           (0u)
#define DEBUG_PORT_OVER_SAMPLE_COUNT              (8u)
#define DEBUG_PORT_PARITY_TYPE                    (0u)
#define DEBUG_PORT_PARITY_TYPE_SW                 (0u)
#define DEBUG_PORT_BREAK_DETECT                   (0u)
#define DEBUG_PORT_BREAK_BITS_TX                  (13u)
#define DEBUG_PORT_BREAK_BITS_RX                  (13u)
#define DEBUG_PORT_TXCLKGEN_DP                    (1u)
#define DEBUG_PORT_USE23POLLING                   (1u)
#define DEBUG_PORT_FLOW_CONTROL                   (0u)
#define DEBUG_PORT_CLK_FREQ                       (0u)
#define DEBUG_PORT_TX_BUFFER_SIZE                 (4u)
#define DEBUG_PORT_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(DEBUG_PORT_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define DEBUG_PORT_CONTROL_REG_REMOVED            (0u)
#else
    #define DEBUG_PORT_CONTROL_REG_REMOVED            (1u)
#endif /* End DEBUG_PORT_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct DEBUG_PORT_backupStruct_
{
    uint8 enableState;

    #if(DEBUG_PORT_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End DEBUG_PORT_CONTROL_REG_REMOVED */

} DEBUG_PORT_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void DEBUG_PORT_Start(void) ;
void DEBUG_PORT_Stop(void) ;
uint8 DEBUG_PORT_ReadControlRegister(void) ;
void DEBUG_PORT_WriteControlRegister(uint8 control) ;

void DEBUG_PORT_Init(void) ;
void DEBUG_PORT_Enable(void) ;
void DEBUG_PORT_SaveConfig(void) ;
void DEBUG_PORT_RestoreConfig(void) ;
void DEBUG_PORT_Sleep(void) ;
void DEBUG_PORT_Wakeup(void) ;

/* Only if RX is enabled */
#if( (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) )

    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
        #define DEBUG_PORT_EnableRxInt()  CyIntEnable (DEBUG_PORT_RX_VECT_NUM)
        #define DEBUG_PORT_DisableRxInt() CyIntDisable(DEBUG_PORT_RX_VECT_NUM)
        CY_ISR_PROTO(DEBUG_PORT_RXISR);
    #endif /* DEBUG_PORT_RX_INTERRUPT_ENABLED */

    void DEBUG_PORT_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void DEBUG_PORT_SetRxAddress1(uint8 address) ;
    void DEBUG_PORT_SetRxAddress2(uint8 address) ;

    void  DEBUG_PORT_SetRxInterruptMode(uint8 intSrc) ;
    uint8 DEBUG_PORT_ReadRxData(void) ;
    uint8 DEBUG_PORT_ReadRxStatus(void) ;
    uint8 DEBUG_PORT_GetChar(void) ;
    uint16 DEBUG_PORT_GetByte(void) ;
    uint8 DEBUG_PORT_GetRxBufferSize(void)
                                                            ;
    void DEBUG_PORT_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define DEBUG_PORT_GetRxInterruptSource   DEBUG_PORT_ReadRxStatus

#endif /* End (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) */

/* Only if TX is enabled */
#if(DEBUG_PORT_TX_ENABLED || DEBUG_PORT_HD_ENABLED)

    #if(DEBUG_PORT_TX_INTERRUPT_ENABLED)
        #define DEBUG_PORT_EnableTxInt()  CyIntEnable (DEBUG_PORT_TX_VECT_NUM)
        #define DEBUG_PORT_DisableTxInt() CyIntDisable(DEBUG_PORT_TX_VECT_NUM)
        #define DEBUG_PORT_SetPendingTxInt() CyIntSetPending(DEBUG_PORT_TX_VECT_NUM)
        #define DEBUG_PORT_ClearPendingTxInt() CyIntClearPending(DEBUG_PORT_TX_VECT_NUM)
        CY_ISR_PROTO(DEBUG_PORT_TXISR);
    #endif /* DEBUG_PORT_TX_INTERRUPT_ENABLED */

    void DEBUG_PORT_SetTxInterruptMode(uint8 intSrc) ;
    void DEBUG_PORT_WriteTxData(uint8 txDataByte) ;
    uint8 DEBUG_PORT_ReadTxStatus(void) ;
    void DEBUG_PORT_PutChar(uint8 txDataByte) ;
    void DEBUG_PORT_PutString(const char8 string[]) ;
    void DEBUG_PORT_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void DEBUG_PORT_PutCRLF(uint8 txDataByte) ;
    void DEBUG_PORT_ClearTxBuffer(void) ;
    void DEBUG_PORT_SetTxAddressMode(uint8 addressMode) ;
    void DEBUG_PORT_SendBreak(uint8 retMode) ;
    uint8 DEBUG_PORT_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define DEBUG_PORT_PutStringConst         DEBUG_PORT_PutString
    #define DEBUG_PORT_PutArrayConst          DEBUG_PORT_PutArray
    #define DEBUG_PORT_GetTxInterruptSource   DEBUG_PORT_ReadTxStatus

#endif /* End DEBUG_PORT_TX_ENABLED || DEBUG_PORT_HD_ENABLED */

#if(DEBUG_PORT_HD_ENABLED)
    void DEBUG_PORT_LoadRxConfig(void) ;
    void DEBUG_PORT_LoadTxConfig(void) ;
#endif /* End DEBUG_PORT_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUG_PORT) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    DEBUG_PORT_CyBtldrCommStart(void) CYSMALL ;
    void    DEBUG_PORT_CyBtldrCommStop(void) CYSMALL ;
    void    DEBUG_PORT_CyBtldrCommReset(void) CYSMALL ;
    cystatus DEBUG_PORT_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus DEBUG_PORT_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUG_PORT)
        #define CyBtldrCommStart    DEBUG_PORT_CyBtldrCommStart
        #define CyBtldrCommStop     DEBUG_PORT_CyBtldrCommStop
        #define CyBtldrCommReset    DEBUG_PORT_CyBtldrCommReset
        #define CyBtldrCommWrite    DEBUG_PORT_CyBtldrCommWrite
        #define CyBtldrCommRead     DEBUG_PORT_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUG_PORT) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define DEBUG_PORT_BYTE2BYTE_TIME_OUT (25u)
    #define DEBUG_PORT_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define DEBUG_PORT_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define DEBUG_PORT_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define DEBUG_PORT_SET_SPACE      (0x00u)
#define DEBUG_PORT_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (DEBUG_PORT_TX_ENABLED) || (DEBUG_PORT_HD_ENABLED) )
    #if(DEBUG_PORT_TX_INTERRUPT_ENABLED)
        #define DEBUG_PORT_TX_VECT_NUM            (uint8)DEBUG_PORT_TXInternalInterrupt__INTC_NUMBER
        #define DEBUG_PORT_TX_PRIOR_NUM           (uint8)DEBUG_PORT_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* DEBUG_PORT_TX_INTERRUPT_ENABLED */

    #define DEBUG_PORT_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define DEBUG_PORT_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define DEBUG_PORT_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(DEBUG_PORT_TX_ENABLED)
        #define DEBUG_PORT_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (DEBUG_PORT_HD_ENABLED) */
        #define DEBUG_PORT_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (DEBUG_PORT_TX_ENABLED) */

    #define DEBUG_PORT_TX_STS_COMPLETE            (uint8)(0x01u << DEBUG_PORT_TX_STS_COMPLETE_SHIFT)
    #define DEBUG_PORT_TX_STS_FIFO_EMPTY          (uint8)(0x01u << DEBUG_PORT_TX_STS_FIFO_EMPTY_SHIFT)
    #define DEBUG_PORT_TX_STS_FIFO_FULL           (uint8)(0x01u << DEBUG_PORT_TX_STS_FIFO_FULL_SHIFT)
    #define DEBUG_PORT_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << DEBUG_PORT_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (DEBUG_PORT_TX_ENABLED) || (DEBUG_PORT_HD_ENABLED)*/

#if( (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) )
    #if(DEBUG_PORT_RX_INTERRUPT_ENABLED)
        #define DEBUG_PORT_RX_VECT_NUM            (uint8)DEBUG_PORT_RXInternalInterrupt__INTC_NUMBER
        #define DEBUG_PORT_RX_PRIOR_NUM           (uint8)DEBUG_PORT_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* DEBUG_PORT_RX_INTERRUPT_ENABLED */
    #define DEBUG_PORT_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define DEBUG_PORT_RX_STS_BREAK_SHIFT             (0x01u)
    #define DEBUG_PORT_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define DEBUG_PORT_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define DEBUG_PORT_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define DEBUG_PORT_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define DEBUG_PORT_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define DEBUG_PORT_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define DEBUG_PORT_RX_STS_MRKSPC           (uint8)(0x01u << DEBUG_PORT_RX_STS_MRKSPC_SHIFT)
    #define DEBUG_PORT_RX_STS_BREAK            (uint8)(0x01u << DEBUG_PORT_RX_STS_BREAK_SHIFT)
    #define DEBUG_PORT_RX_STS_PAR_ERROR        (uint8)(0x01u << DEBUG_PORT_RX_STS_PAR_ERROR_SHIFT)
    #define DEBUG_PORT_RX_STS_STOP_ERROR       (uint8)(0x01u << DEBUG_PORT_RX_STS_STOP_ERROR_SHIFT)
    #define DEBUG_PORT_RX_STS_OVERRUN          (uint8)(0x01u << DEBUG_PORT_RX_STS_OVERRUN_SHIFT)
    #define DEBUG_PORT_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << DEBUG_PORT_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define DEBUG_PORT_RX_STS_ADDR_MATCH       (uint8)(0x01u << DEBUG_PORT_RX_STS_ADDR_MATCH_SHIFT)
    #define DEBUG_PORT_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << DEBUG_PORT_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define DEBUG_PORT_RX_HW_MASK                     (0x7Fu)
#endif /* End (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) */

/* Control Register definitions */
#define DEBUG_PORT_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define DEBUG_PORT_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define DEBUG_PORT_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define DEBUG_PORT_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define DEBUG_PORT_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define DEBUG_PORT_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define DEBUG_PORT_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define DEBUG_PORT_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define DEBUG_PORT_CTRL_HD_SEND               (uint8)(0x01u << DEBUG_PORT_CTRL_HD_SEND_SHIFT)
#define DEBUG_PORT_CTRL_HD_SEND_BREAK         (uint8)(0x01u << DEBUG_PORT_CTRL_HD_SEND_BREAK_SHIFT)
#define DEBUG_PORT_CTRL_MARK                  (uint8)(0x01u << DEBUG_PORT_CTRL_MARK_SHIFT)
#define DEBUG_PORT_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << DEBUG_PORT_CTRL_PARITY_TYPE0_SHIFT)
#define DEBUG_PORT_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << DEBUG_PORT_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define DEBUG_PORT_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define DEBUG_PORT_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define DEBUG_PORT_SEND_BREAK                         (0x00u)
#define DEBUG_PORT_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define DEBUG_PORT_REINIT                             (0x02u)
#define DEBUG_PORT_SEND_WAIT_REINIT                   (0x03u)

#define DEBUG_PORT_OVER_SAMPLE_8                      (8u)
#define DEBUG_PORT_OVER_SAMPLE_16                     (16u)

#define DEBUG_PORT_BIT_CENTER                         (DEBUG_PORT_OVER_SAMPLE_COUNT - 2u)

#define DEBUG_PORT_FIFO_LENGTH                        (4u)
#define DEBUG_PORT_NUMBER_OF_START_BIT                (1u)
#define DEBUG_PORT_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define DEBUG_PORT_TXBITCTR_BREAKBITS8X   ((DEBUG_PORT_BREAK_BITS_TX * DEBUG_PORT_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define DEBUG_PORT_TXBITCTR_BREAKBITS ((DEBUG_PORT_BREAK_BITS_TX * DEBUG_PORT_OVER_SAMPLE_COUNT) - 1u)

#define DEBUG_PORT_HALF_BIT_COUNT   \
                            (((DEBUG_PORT_OVER_SAMPLE_COUNT / 2u) + (DEBUG_PORT_USE23POLLING * 1u)) - 2u)
#if (DEBUG_PORT_OVER_SAMPLE_COUNT == DEBUG_PORT_OVER_SAMPLE_8)
    #define DEBUG_PORT_HD_TXBITCTR_INIT   (((DEBUG_PORT_BREAK_BITS_TX + \
                            DEBUG_PORT_NUMBER_OF_START_BIT) * DEBUG_PORT_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define DEBUG_PORT_RXBITCTR_INIT  ((((DEBUG_PORT_BREAK_BITS_RX + DEBUG_PORT_NUMBER_OF_START_BIT) \
                            * DEBUG_PORT_OVER_SAMPLE_COUNT) + DEBUG_PORT_HALF_BIT_COUNT) - 1u)

#else /* DEBUG_PORT_OVER_SAMPLE_COUNT == DEBUG_PORT_OVER_SAMPLE_16 */
    #define DEBUG_PORT_HD_TXBITCTR_INIT   ((8u * DEBUG_PORT_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define DEBUG_PORT_RXBITCTR_INIT      (((7u * DEBUG_PORT_OVER_SAMPLE_COUNT) - 1u) + \
                                                      DEBUG_PORT_HALF_BIT_COUNT)
#endif /* End DEBUG_PORT_OVER_SAMPLE_COUNT */

#define DEBUG_PORT_HD_RXBITCTR_INIT                   DEBUG_PORT_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 DEBUG_PORT_initVar;
#if (DEBUG_PORT_TX_INTERRUPT_ENABLED && DEBUG_PORT_TX_ENABLED)
    extern volatile uint8 DEBUG_PORT_txBuffer[DEBUG_PORT_TX_BUFFER_SIZE];
    extern volatile uint8 DEBUG_PORT_txBufferRead;
    extern uint8 DEBUG_PORT_txBufferWrite;
#endif /* (DEBUG_PORT_TX_INTERRUPT_ENABLED && DEBUG_PORT_TX_ENABLED) */
#if (DEBUG_PORT_RX_INTERRUPT_ENABLED && (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED))
    extern uint8 DEBUG_PORT_errorStatus;
    extern volatile uint8 DEBUG_PORT_rxBuffer[DEBUG_PORT_RX_BUFFER_SIZE];
    extern volatile uint8 DEBUG_PORT_rxBufferRead;
    extern volatile uint8 DEBUG_PORT_rxBufferWrite;
    extern volatile uint8 DEBUG_PORT_rxBufferLoopDetect;
    extern volatile uint8 DEBUG_PORT_rxBufferOverflow;
    #if (DEBUG_PORT_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 DEBUG_PORT_rxAddressMode;
        extern volatile uint8 DEBUG_PORT_rxAddressDetected;
    #endif /* (DEBUG_PORT_RXHW_ADDRESS_ENABLED) */
#endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED && (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define DEBUG_PORT__B_UART__AM_SW_BYTE_BYTE 1
#define DEBUG_PORT__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define DEBUG_PORT__B_UART__AM_HW_BYTE_BY_BYTE 3
#define DEBUG_PORT__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define DEBUG_PORT__B_UART__AM_NONE 0

#define DEBUG_PORT__B_UART__NONE_REVB 0
#define DEBUG_PORT__B_UART__EVEN_REVB 1
#define DEBUG_PORT__B_UART__ODD_REVB 2
#define DEBUG_PORT__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define DEBUG_PORT_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define DEBUG_PORT_NUMBER_OF_STOP_BITS    (1u)

#if (DEBUG_PORT_RXHW_ADDRESS_ENABLED)
    #define DEBUG_PORT_RX_ADDRESS_MODE    (0u)
    #define DEBUG_PORT_RX_HW_ADDRESS1     (0u)
    #define DEBUG_PORT_RX_HW_ADDRESS2     (0u)
#endif /* (DEBUG_PORT_RXHW_ADDRESS_ENABLED) */

#define DEBUG_PORT_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << DEBUG_PORT_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << DEBUG_PORT_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << DEBUG_PORT_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << DEBUG_PORT_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << DEBUG_PORT_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << DEBUG_PORT_RX_STS_BREAK_SHIFT) \
                                        | (0 << DEBUG_PORT_RX_STS_OVERRUN_SHIFT))

#define DEBUG_PORT_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << DEBUG_PORT_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << DEBUG_PORT_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << DEBUG_PORT_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << DEBUG_PORT_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef DEBUG_PORT_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define DEBUG_PORT_CONTROL_REG \
                            (* (reg8 *) DEBUG_PORT_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define DEBUG_PORT_CONTROL_PTR \
                            (  (reg8 *) DEBUG_PORT_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End DEBUG_PORT_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(DEBUG_PORT_TX_ENABLED)
    #define DEBUG_PORT_TXDATA_REG          (* (reg8 *) DEBUG_PORT_BUART_sTX_TxShifter_u0__F0_REG)
    #define DEBUG_PORT_TXDATA_PTR          (  (reg8 *) DEBUG_PORT_BUART_sTX_TxShifter_u0__F0_REG)
    #define DEBUG_PORT_TXDATA_AUX_CTL_REG  (* (reg8 *) DEBUG_PORT_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define DEBUG_PORT_TXDATA_AUX_CTL_PTR  (  (reg8 *) DEBUG_PORT_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define DEBUG_PORT_TXSTATUS_REG        (* (reg8 *) DEBUG_PORT_BUART_sTX_TxSts__STATUS_REG)
    #define DEBUG_PORT_TXSTATUS_PTR        (  (reg8 *) DEBUG_PORT_BUART_sTX_TxSts__STATUS_REG)
    #define DEBUG_PORT_TXSTATUS_MASK_REG   (* (reg8 *) DEBUG_PORT_BUART_sTX_TxSts__MASK_REG)
    #define DEBUG_PORT_TXSTATUS_MASK_PTR   (  (reg8 *) DEBUG_PORT_BUART_sTX_TxSts__MASK_REG)
    #define DEBUG_PORT_TXSTATUS_ACTL_REG   (* (reg8 *) DEBUG_PORT_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define DEBUG_PORT_TXSTATUS_ACTL_PTR   (  (reg8 *) DEBUG_PORT_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(DEBUG_PORT_TXCLKGEN_DP)
        #define DEBUG_PORT_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define DEBUG_PORT_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define DEBUG_PORT_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define DEBUG_PORT_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define DEBUG_PORT_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define DEBUG_PORT_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define DEBUG_PORT_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define DEBUG_PORT_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define DEBUG_PORT_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define DEBUG_PORT_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) DEBUG_PORT_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* DEBUG_PORT_TXCLKGEN_DP */

#endif /* End DEBUG_PORT_TX_ENABLED */

#if(DEBUG_PORT_HD_ENABLED)

    #define DEBUG_PORT_TXDATA_REG             (* (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__F1_REG )
    #define DEBUG_PORT_TXDATA_PTR             (  (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__F1_REG )
    #define DEBUG_PORT_TXDATA_AUX_CTL_REG     (* (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define DEBUG_PORT_TXDATA_AUX_CTL_PTR     (  (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define DEBUG_PORT_TXSTATUS_REG           (* (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__STATUS_REG )
    #define DEBUG_PORT_TXSTATUS_PTR           (  (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__STATUS_REG )
    #define DEBUG_PORT_TXSTATUS_MASK_REG      (* (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__MASK_REG )
    #define DEBUG_PORT_TXSTATUS_MASK_PTR      (  (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__MASK_REG )
    #define DEBUG_PORT_TXSTATUS_ACTL_REG      (* (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define DEBUG_PORT_TXSTATUS_ACTL_PTR      (  (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End DEBUG_PORT_HD_ENABLED */

#if( (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) )
    #define DEBUG_PORT_RXDATA_REG             (* (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__F0_REG )
    #define DEBUG_PORT_RXDATA_PTR             (  (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__F0_REG )
    #define DEBUG_PORT_RXADDRESS1_REG         (* (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__D0_REG )
    #define DEBUG_PORT_RXADDRESS1_PTR         (  (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__D0_REG )
    #define DEBUG_PORT_RXADDRESS2_REG         (* (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__D1_REG )
    #define DEBUG_PORT_RXADDRESS2_PTR         (  (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__D1_REG )
    #define DEBUG_PORT_RXDATA_AUX_CTL_REG     (* (reg8 *) DEBUG_PORT_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define DEBUG_PORT_RXBITCTR_PERIOD_REG    (* (reg8 *) DEBUG_PORT_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define DEBUG_PORT_RXBITCTR_PERIOD_PTR    (  (reg8 *) DEBUG_PORT_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define DEBUG_PORT_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) DEBUG_PORT_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define DEBUG_PORT_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) DEBUG_PORT_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define DEBUG_PORT_RXBITCTR_COUNTER_REG   (* (reg8 *) DEBUG_PORT_BUART_sRX_RxBitCounter__COUNT_REG )
    #define DEBUG_PORT_RXBITCTR_COUNTER_PTR   (  (reg8 *) DEBUG_PORT_BUART_sRX_RxBitCounter__COUNT_REG )

    #define DEBUG_PORT_RXSTATUS_REG           (* (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__STATUS_REG )
    #define DEBUG_PORT_RXSTATUS_PTR           (  (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__STATUS_REG )
    #define DEBUG_PORT_RXSTATUS_MASK_REG      (* (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__MASK_REG )
    #define DEBUG_PORT_RXSTATUS_MASK_PTR      (  (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__MASK_REG )
    #define DEBUG_PORT_RXSTATUS_ACTL_REG      (* (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define DEBUG_PORT_RXSTATUS_ACTL_PTR      (  (reg8 *) DEBUG_PORT_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) */

#if(DEBUG_PORT_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define DEBUG_PORT_INTCLOCK_CLKEN_REG     (* (reg8 *) DEBUG_PORT_IntClock__PM_ACT_CFG)
    #define DEBUG_PORT_INTCLOCK_CLKEN_PTR     (  (reg8 *) DEBUG_PORT_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define DEBUG_PORT_INTCLOCK_CLKEN_MASK    DEBUG_PORT_IntClock__PM_ACT_MSK
#endif /* End DEBUG_PORT_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(DEBUG_PORT_TX_ENABLED)
    #define DEBUG_PORT_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End DEBUG_PORT_TX_ENABLED */

#if(DEBUG_PORT_HD_ENABLED)
    #define DEBUG_PORT_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End DEBUG_PORT_HD_ENABLED */

#if( (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) )
    #define DEBUG_PORT_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define DEBUG_PORT_WAIT_1_MS      DEBUG_PORT_BL_CHK_DELAY_MS   

#define DEBUG_PORT_TXBUFFERSIZE   DEBUG_PORT_TX_BUFFER_SIZE
#define DEBUG_PORT_RXBUFFERSIZE   DEBUG_PORT_RX_BUFFER_SIZE

#if (DEBUG_PORT_RXHW_ADDRESS_ENABLED)
    #define DEBUG_PORT_RXADDRESSMODE  DEBUG_PORT_RX_ADDRESS_MODE
    #define DEBUG_PORT_RXHWADDRESS1   DEBUG_PORT_RX_HW_ADDRESS1
    #define DEBUG_PORT_RXHWADDRESS2   DEBUG_PORT_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define DEBUG_PORT_RXAddressMode  DEBUG_PORT_RXADDRESSMODE
#endif /* (DEBUG_PORT_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define DEBUG_PORT_initvar                    DEBUG_PORT_initVar

#define DEBUG_PORT_RX_Enabled                 DEBUG_PORT_RX_ENABLED
#define DEBUG_PORT_TX_Enabled                 DEBUG_PORT_TX_ENABLED
#define DEBUG_PORT_HD_Enabled                 DEBUG_PORT_HD_ENABLED
#define DEBUG_PORT_RX_IntInterruptEnabled     DEBUG_PORT_RX_INTERRUPT_ENABLED
#define DEBUG_PORT_TX_IntInterruptEnabled     DEBUG_PORT_TX_INTERRUPT_ENABLED
#define DEBUG_PORT_InternalClockUsed          DEBUG_PORT_INTERNAL_CLOCK_USED
#define DEBUG_PORT_RXHW_Address_Enabled       DEBUG_PORT_RXHW_ADDRESS_ENABLED
#define DEBUG_PORT_OverSampleCount            DEBUG_PORT_OVER_SAMPLE_COUNT
#define DEBUG_PORT_ParityType                 DEBUG_PORT_PARITY_TYPE

#if( DEBUG_PORT_TX_ENABLED && (DEBUG_PORT_TXBUFFERSIZE > DEBUG_PORT_FIFO_LENGTH))
    #define DEBUG_PORT_TXBUFFER               DEBUG_PORT_txBuffer
    #define DEBUG_PORT_TXBUFFERREAD           DEBUG_PORT_txBufferRead
    #define DEBUG_PORT_TXBUFFERWRITE          DEBUG_PORT_txBufferWrite
#endif /* End DEBUG_PORT_TX_ENABLED */
#if( ( DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED ) && \
     (DEBUG_PORT_RXBUFFERSIZE > DEBUG_PORT_FIFO_LENGTH) )
    #define DEBUG_PORT_RXBUFFER               DEBUG_PORT_rxBuffer
    #define DEBUG_PORT_RXBUFFERREAD           DEBUG_PORT_rxBufferRead
    #define DEBUG_PORT_RXBUFFERWRITE          DEBUG_PORT_rxBufferWrite
    #define DEBUG_PORT_RXBUFFERLOOPDETECT     DEBUG_PORT_rxBufferLoopDetect
    #define DEBUG_PORT_RXBUFFER_OVERFLOW      DEBUG_PORT_rxBufferOverflow
#endif /* End DEBUG_PORT_RX_ENABLED */

#ifdef DEBUG_PORT_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define DEBUG_PORT_CONTROL                DEBUG_PORT_CONTROL_REG
#endif /* End DEBUG_PORT_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(DEBUG_PORT_TX_ENABLED)
    #define DEBUG_PORT_TXDATA                 DEBUG_PORT_TXDATA_REG
    #define DEBUG_PORT_TXSTATUS               DEBUG_PORT_TXSTATUS_REG
    #define DEBUG_PORT_TXSTATUS_MASK          DEBUG_PORT_TXSTATUS_MASK_REG
    #define DEBUG_PORT_TXSTATUS_ACTL          DEBUG_PORT_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(DEBUG_PORT_TXCLKGEN_DP)
        #define DEBUG_PORT_TXBITCLKGEN_CTR        DEBUG_PORT_TXBITCLKGEN_CTR_REG
        #define DEBUG_PORT_TXBITCLKTX_COMPLETE    DEBUG_PORT_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define DEBUG_PORT_TXBITCTR_PERIOD        DEBUG_PORT_TXBITCTR_PERIOD_REG
        #define DEBUG_PORT_TXBITCTR_CONTROL       DEBUG_PORT_TXBITCTR_CONTROL_REG
        #define DEBUG_PORT_TXBITCTR_COUNTER       DEBUG_PORT_TXBITCTR_COUNTER_REG
    #endif /* DEBUG_PORT_TXCLKGEN_DP */
#endif /* End DEBUG_PORT_TX_ENABLED */

#if(DEBUG_PORT_HD_ENABLED)
    #define DEBUG_PORT_TXDATA                 DEBUG_PORT_TXDATA_REG
    #define DEBUG_PORT_TXSTATUS               DEBUG_PORT_TXSTATUS_REG
    #define DEBUG_PORT_TXSTATUS_MASK          DEBUG_PORT_TXSTATUS_MASK_REG
    #define DEBUG_PORT_TXSTATUS_ACTL          DEBUG_PORT_TXSTATUS_ACTL_REG
#endif /* End DEBUG_PORT_HD_ENABLED */

#if( (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) )
    #define DEBUG_PORT_RXDATA                 DEBUG_PORT_RXDATA_REG
    #define DEBUG_PORT_RXADDRESS1             DEBUG_PORT_RXADDRESS1_REG
    #define DEBUG_PORT_RXADDRESS2             DEBUG_PORT_RXADDRESS2_REG
    #define DEBUG_PORT_RXBITCTR_PERIOD        DEBUG_PORT_RXBITCTR_PERIOD_REG
    #define DEBUG_PORT_RXBITCTR_CONTROL       DEBUG_PORT_RXBITCTR_CONTROL_REG
    #define DEBUG_PORT_RXBITCTR_COUNTER       DEBUG_PORT_RXBITCTR_COUNTER_REG
    #define DEBUG_PORT_RXSTATUS               DEBUG_PORT_RXSTATUS_REG
    #define DEBUG_PORT_RXSTATUS_MASK          DEBUG_PORT_RXSTATUS_MASK_REG
    #define DEBUG_PORT_RXSTATUS_ACTL          DEBUG_PORT_RXSTATUS_ACTL_REG
#endif /* End  (DEBUG_PORT_RX_ENABLED) || (DEBUG_PORT_HD_ENABLED) */

#if(DEBUG_PORT_INTERNAL_CLOCK_USED)
    #define DEBUG_PORT_INTCLOCK_CLKEN         DEBUG_PORT_INTCLOCK_CLKEN_REG
#endif /* End DEBUG_PORT_INTERNAL_CLOCK_USED */

#define DEBUG_PORT_WAIT_FOR_COMLETE_REINIT    DEBUG_PORT_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_DEBUG_PORT_H */


/* [] END OF FILE */
