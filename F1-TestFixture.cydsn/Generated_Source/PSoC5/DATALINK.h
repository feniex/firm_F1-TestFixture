/*******************************************************************************
* File Name: DATALINK.h
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


#if !defined(CY_UART_DATALINK_H)
#define CY_UART_DATALINK_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define DATALINK_RX_ENABLED                     (1u)
#define DATALINK_TX_ENABLED                     (1u)
#define DATALINK_HD_ENABLED                     (0u)
#define DATALINK_RX_INTERRUPT_ENABLED           (0u)
#define DATALINK_TX_INTERRUPT_ENABLED           (1u)
#define DATALINK_INTERNAL_CLOCK_USED            (1u)
#define DATALINK_RXHW_ADDRESS_ENABLED           (0u)
#define DATALINK_OVER_SAMPLE_COUNT              (8u)
#define DATALINK_PARITY_TYPE                    (0u)
#define DATALINK_PARITY_TYPE_SW                 (0u)
#define DATALINK_BREAK_DETECT                   (0u)
#define DATALINK_BREAK_BITS_TX                  (13u)
#define DATALINK_BREAK_BITS_RX                  (13u)
#define DATALINK_TXCLKGEN_DP                    (1u)
#define DATALINK_USE23POLLING                   (1u)
#define DATALINK_FLOW_CONTROL                   (0u)
#define DATALINK_CLK_FREQ                       (0u)
#define DATALINK_TX_BUFFER_SIZE                 (1024u)
#define DATALINK_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(DATALINK_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define DATALINK_CONTROL_REG_REMOVED            (0u)
#else
    #define DATALINK_CONTROL_REG_REMOVED            (1u)
#endif /* End DATALINK_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct DATALINK_backupStruct_
{
    uint8 enableState;

    #if(DATALINK_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End DATALINK_CONTROL_REG_REMOVED */

} DATALINK_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void DATALINK_Start(void) ;
void DATALINK_Stop(void) ;
uint8 DATALINK_ReadControlRegister(void) ;
void DATALINK_WriteControlRegister(uint8 control) ;

void DATALINK_Init(void) ;
void DATALINK_Enable(void) ;
void DATALINK_SaveConfig(void) ;
void DATALINK_RestoreConfig(void) ;
void DATALINK_Sleep(void) ;
void DATALINK_Wakeup(void) ;

/* Only if RX is enabled */
#if( (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) )

    #if (DATALINK_RX_INTERRUPT_ENABLED)
        #define DATALINK_EnableRxInt()  CyIntEnable (DATALINK_RX_VECT_NUM)
        #define DATALINK_DisableRxInt() CyIntDisable(DATALINK_RX_VECT_NUM)
        CY_ISR_PROTO(DATALINK_RXISR);
    #endif /* DATALINK_RX_INTERRUPT_ENABLED */

    void DATALINK_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void DATALINK_SetRxAddress1(uint8 address) ;
    void DATALINK_SetRxAddress2(uint8 address) ;

    void  DATALINK_SetRxInterruptMode(uint8 intSrc) ;
    uint8 DATALINK_ReadRxData(void) ;
    uint8 DATALINK_ReadRxStatus(void) ;
    uint8 DATALINK_GetChar(void) ;
    uint16 DATALINK_GetByte(void) ;
    uint8 DATALINK_GetRxBufferSize(void)
                                                            ;
    void DATALINK_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define DATALINK_GetRxInterruptSource   DATALINK_ReadRxStatus

#endif /* End (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) */

/* Only if TX is enabled */
#if(DATALINK_TX_ENABLED || DATALINK_HD_ENABLED)

    #if(DATALINK_TX_INTERRUPT_ENABLED)
        #define DATALINK_EnableTxInt()  CyIntEnable (DATALINK_TX_VECT_NUM)
        #define DATALINK_DisableTxInt() CyIntDisable(DATALINK_TX_VECT_NUM)
        #define DATALINK_SetPendingTxInt() CyIntSetPending(DATALINK_TX_VECT_NUM)
        #define DATALINK_ClearPendingTxInt() CyIntClearPending(DATALINK_TX_VECT_NUM)
        CY_ISR_PROTO(DATALINK_TXISR);
    #endif /* DATALINK_TX_INTERRUPT_ENABLED */

    void DATALINK_SetTxInterruptMode(uint8 intSrc) ;
    void DATALINK_WriteTxData(uint8 txDataByte) ;
    uint8 DATALINK_ReadTxStatus(void) ;
    void DATALINK_PutChar(uint8 txDataByte) ;
    void DATALINK_PutString(const char8 string[]) ;
    void DATALINK_PutArray(const uint8 string[], uint16 byteCount)
                                                            ;
    void DATALINK_PutCRLF(uint8 txDataByte) ;
    void DATALINK_ClearTxBuffer(void) ;
    void DATALINK_SetTxAddressMode(uint8 addressMode) ;
    void DATALINK_SendBreak(uint8 retMode) ;
    uint16 DATALINK_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define DATALINK_PutStringConst         DATALINK_PutString
    #define DATALINK_PutArrayConst          DATALINK_PutArray
    #define DATALINK_GetTxInterruptSource   DATALINK_ReadTxStatus

#endif /* End DATALINK_TX_ENABLED || DATALINK_HD_ENABLED */

#if(DATALINK_HD_ENABLED)
    void DATALINK_LoadRxConfig(void) ;
    void DATALINK_LoadTxConfig(void) ;
#endif /* End DATALINK_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DATALINK) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    DATALINK_CyBtldrCommStart(void) CYSMALL ;
    void    DATALINK_CyBtldrCommStop(void) CYSMALL ;
    void    DATALINK_CyBtldrCommReset(void) CYSMALL ;
    cystatus DATALINK_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus DATALINK_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DATALINK)
        #define CyBtldrCommStart    DATALINK_CyBtldrCommStart
        #define CyBtldrCommStop     DATALINK_CyBtldrCommStop
        #define CyBtldrCommReset    DATALINK_CyBtldrCommReset
        #define CyBtldrCommWrite    DATALINK_CyBtldrCommWrite
        #define CyBtldrCommRead     DATALINK_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DATALINK) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define DATALINK_BYTE2BYTE_TIME_OUT (25u)
    #define DATALINK_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define DATALINK_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define DATALINK_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define DATALINK_SET_SPACE      (0x00u)
#define DATALINK_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (DATALINK_TX_ENABLED) || (DATALINK_HD_ENABLED) )
    #if(DATALINK_TX_INTERRUPT_ENABLED)
        #define DATALINK_TX_VECT_NUM            (uint8)DATALINK_TXInternalInterrupt__INTC_NUMBER
        #define DATALINK_TX_PRIOR_NUM           (uint8)DATALINK_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* DATALINK_TX_INTERRUPT_ENABLED */

    #define DATALINK_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define DATALINK_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define DATALINK_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(DATALINK_TX_ENABLED)
        #define DATALINK_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (DATALINK_HD_ENABLED) */
        #define DATALINK_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (DATALINK_TX_ENABLED) */

    #define DATALINK_TX_STS_COMPLETE            (uint8)(0x01u << DATALINK_TX_STS_COMPLETE_SHIFT)
    #define DATALINK_TX_STS_FIFO_EMPTY          (uint8)(0x01u << DATALINK_TX_STS_FIFO_EMPTY_SHIFT)
    #define DATALINK_TX_STS_FIFO_FULL           (uint8)(0x01u << DATALINK_TX_STS_FIFO_FULL_SHIFT)
    #define DATALINK_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << DATALINK_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (DATALINK_TX_ENABLED) || (DATALINK_HD_ENABLED)*/

#if( (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) )
    #if(DATALINK_RX_INTERRUPT_ENABLED)
        #define DATALINK_RX_VECT_NUM            (uint8)DATALINK_RXInternalInterrupt__INTC_NUMBER
        #define DATALINK_RX_PRIOR_NUM           (uint8)DATALINK_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* DATALINK_RX_INTERRUPT_ENABLED */
    #define DATALINK_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define DATALINK_RX_STS_BREAK_SHIFT             (0x01u)
    #define DATALINK_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define DATALINK_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define DATALINK_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define DATALINK_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define DATALINK_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define DATALINK_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define DATALINK_RX_STS_MRKSPC           (uint8)(0x01u << DATALINK_RX_STS_MRKSPC_SHIFT)
    #define DATALINK_RX_STS_BREAK            (uint8)(0x01u << DATALINK_RX_STS_BREAK_SHIFT)
    #define DATALINK_RX_STS_PAR_ERROR        (uint8)(0x01u << DATALINK_RX_STS_PAR_ERROR_SHIFT)
    #define DATALINK_RX_STS_STOP_ERROR       (uint8)(0x01u << DATALINK_RX_STS_STOP_ERROR_SHIFT)
    #define DATALINK_RX_STS_OVERRUN          (uint8)(0x01u << DATALINK_RX_STS_OVERRUN_SHIFT)
    #define DATALINK_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << DATALINK_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define DATALINK_RX_STS_ADDR_MATCH       (uint8)(0x01u << DATALINK_RX_STS_ADDR_MATCH_SHIFT)
    #define DATALINK_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << DATALINK_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define DATALINK_RX_HW_MASK                     (0x7Fu)
#endif /* End (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) */

/* Control Register definitions */
#define DATALINK_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define DATALINK_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define DATALINK_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define DATALINK_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define DATALINK_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define DATALINK_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define DATALINK_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define DATALINK_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define DATALINK_CTRL_HD_SEND               (uint8)(0x01u << DATALINK_CTRL_HD_SEND_SHIFT)
#define DATALINK_CTRL_HD_SEND_BREAK         (uint8)(0x01u << DATALINK_CTRL_HD_SEND_BREAK_SHIFT)
#define DATALINK_CTRL_MARK                  (uint8)(0x01u << DATALINK_CTRL_MARK_SHIFT)
#define DATALINK_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << DATALINK_CTRL_PARITY_TYPE0_SHIFT)
#define DATALINK_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << DATALINK_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define DATALINK_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define DATALINK_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define DATALINK_SEND_BREAK                         (0x00u)
#define DATALINK_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define DATALINK_REINIT                             (0x02u)
#define DATALINK_SEND_WAIT_REINIT                   (0x03u)

#define DATALINK_OVER_SAMPLE_8                      (8u)
#define DATALINK_OVER_SAMPLE_16                     (16u)

#define DATALINK_BIT_CENTER                         (DATALINK_OVER_SAMPLE_COUNT - 2u)

#define DATALINK_FIFO_LENGTH                        (4u)
#define DATALINK_NUMBER_OF_START_BIT                (1u)
#define DATALINK_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define DATALINK_TXBITCTR_BREAKBITS8X   ((DATALINK_BREAK_BITS_TX * DATALINK_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define DATALINK_TXBITCTR_BREAKBITS ((DATALINK_BREAK_BITS_TX * DATALINK_OVER_SAMPLE_COUNT) - 1u)

#define DATALINK_HALF_BIT_COUNT   \
                            (((DATALINK_OVER_SAMPLE_COUNT / 2u) + (DATALINK_USE23POLLING * 1u)) - 2u)
#if (DATALINK_OVER_SAMPLE_COUNT == DATALINK_OVER_SAMPLE_8)
    #define DATALINK_HD_TXBITCTR_INIT   (((DATALINK_BREAK_BITS_TX + \
                            DATALINK_NUMBER_OF_START_BIT) * DATALINK_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define DATALINK_RXBITCTR_INIT  ((((DATALINK_BREAK_BITS_RX + DATALINK_NUMBER_OF_START_BIT) \
                            * DATALINK_OVER_SAMPLE_COUNT) + DATALINK_HALF_BIT_COUNT) - 1u)

#else /* DATALINK_OVER_SAMPLE_COUNT == DATALINK_OVER_SAMPLE_16 */
    #define DATALINK_HD_TXBITCTR_INIT   ((8u * DATALINK_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define DATALINK_RXBITCTR_INIT      (((7u * DATALINK_OVER_SAMPLE_COUNT) - 1u) + \
                                                      DATALINK_HALF_BIT_COUNT)
#endif /* End DATALINK_OVER_SAMPLE_COUNT */

#define DATALINK_HD_RXBITCTR_INIT                   DATALINK_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 DATALINK_initVar;
#if (DATALINK_TX_INTERRUPT_ENABLED && DATALINK_TX_ENABLED)
    extern volatile uint8 DATALINK_txBuffer[DATALINK_TX_BUFFER_SIZE];
    extern volatile uint16 DATALINK_txBufferRead;
    extern uint16 DATALINK_txBufferWrite;
#endif /* (DATALINK_TX_INTERRUPT_ENABLED && DATALINK_TX_ENABLED) */
#if (DATALINK_RX_INTERRUPT_ENABLED && (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED))
    extern uint8 DATALINK_errorStatus;
    extern volatile uint8 DATALINK_rxBuffer[DATALINK_RX_BUFFER_SIZE];
    extern volatile uint8 DATALINK_rxBufferRead;
    extern volatile uint8 DATALINK_rxBufferWrite;
    extern volatile uint8 DATALINK_rxBufferLoopDetect;
    extern volatile uint8 DATALINK_rxBufferOverflow;
    #if (DATALINK_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 DATALINK_rxAddressMode;
        extern volatile uint8 DATALINK_rxAddressDetected;
    #endif /* (DATALINK_RXHW_ADDRESS_ENABLED) */
#endif /* (DATALINK_RX_INTERRUPT_ENABLED && (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define DATALINK__B_UART__AM_SW_BYTE_BYTE 1
#define DATALINK__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define DATALINK__B_UART__AM_HW_BYTE_BY_BYTE 3
#define DATALINK__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define DATALINK__B_UART__AM_NONE 0

#define DATALINK__B_UART__NONE_REVB 0
#define DATALINK__B_UART__EVEN_REVB 1
#define DATALINK__B_UART__ODD_REVB 2
#define DATALINK__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define DATALINK_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define DATALINK_NUMBER_OF_STOP_BITS    (1u)

#if (DATALINK_RXHW_ADDRESS_ENABLED)
    #define DATALINK_RX_ADDRESS_MODE    (0u)
    #define DATALINK_RX_HW_ADDRESS1     (0u)
    #define DATALINK_RX_HW_ADDRESS2     (0u)
#endif /* (DATALINK_RXHW_ADDRESS_ENABLED) */

#define DATALINK_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << DATALINK_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << DATALINK_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << DATALINK_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << DATALINK_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << DATALINK_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << DATALINK_RX_STS_BREAK_SHIFT) \
                                        | (0 << DATALINK_RX_STS_OVERRUN_SHIFT))

#define DATALINK_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << DATALINK_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << DATALINK_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << DATALINK_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << DATALINK_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef DATALINK_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define DATALINK_CONTROL_REG \
                            (* (reg8 *) DATALINK_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define DATALINK_CONTROL_PTR \
                            (  (reg8 *) DATALINK_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End DATALINK_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(DATALINK_TX_ENABLED)
    #define DATALINK_TXDATA_REG          (* (reg8 *) DATALINK_BUART_sTX_TxShifter_u0__F0_REG)
    #define DATALINK_TXDATA_PTR          (  (reg8 *) DATALINK_BUART_sTX_TxShifter_u0__F0_REG)
    #define DATALINK_TXDATA_AUX_CTL_REG  (* (reg8 *) DATALINK_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define DATALINK_TXDATA_AUX_CTL_PTR  (  (reg8 *) DATALINK_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define DATALINK_TXSTATUS_REG        (* (reg8 *) DATALINK_BUART_sTX_TxSts__STATUS_REG)
    #define DATALINK_TXSTATUS_PTR        (  (reg8 *) DATALINK_BUART_sTX_TxSts__STATUS_REG)
    #define DATALINK_TXSTATUS_MASK_REG   (* (reg8 *) DATALINK_BUART_sTX_TxSts__MASK_REG)
    #define DATALINK_TXSTATUS_MASK_PTR   (  (reg8 *) DATALINK_BUART_sTX_TxSts__MASK_REG)
    #define DATALINK_TXSTATUS_ACTL_REG   (* (reg8 *) DATALINK_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define DATALINK_TXSTATUS_ACTL_PTR   (  (reg8 *) DATALINK_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(DATALINK_TXCLKGEN_DP)
        #define DATALINK_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define DATALINK_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define DATALINK_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define DATALINK_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define DATALINK_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define DATALINK_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define DATALINK_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define DATALINK_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define DATALINK_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define DATALINK_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) DATALINK_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* DATALINK_TXCLKGEN_DP */

#endif /* End DATALINK_TX_ENABLED */

#if(DATALINK_HD_ENABLED)

    #define DATALINK_TXDATA_REG             (* (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__F1_REG )
    #define DATALINK_TXDATA_PTR             (  (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__F1_REG )
    #define DATALINK_TXDATA_AUX_CTL_REG     (* (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define DATALINK_TXDATA_AUX_CTL_PTR     (  (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define DATALINK_TXSTATUS_REG           (* (reg8 *) DATALINK_BUART_sRX_RxSts__STATUS_REG )
    #define DATALINK_TXSTATUS_PTR           (  (reg8 *) DATALINK_BUART_sRX_RxSts__STATUS_REG )
    #define DATALINK_TXSTATUS_MASK_REG      (* (reg8 *) DATALINK_BUART_sRX_RxSts__MASK_REG )
    #define DATALINK_TXSTATUS_MASK_PTR      (  (reg8 *) DATALINK_BUART_sRX_RxSts__MASK_REG )
    #define DATALINK_TXSTATUS_ACTL_REG      (* (reg8 *) DATALINK_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define DATALINK_TXSTATUS_ACTL_PTR      (  (reg8 *) DATALINK_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End DATALINK_HD_ENABLED */

#if( (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) )
    #define DATALINK_RXDATA_REG             (* (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__F0_REG )
    #define DATALINK_RXDATA_PTR             (  (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__F0_REG )
    #define DATALINK_RXADDRESS1_REG         (* (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__D0_REG )
    #define DATALINK_RXADDRESS1_PTR         (  (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__D0_REG )
    #define DATALINK_RXADDRESS2_REG         (* (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__D1_REG )
    #define DATALINK_RXADDRESS2_PTR         (  (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__D1_REG )
    #define DATALINK_RXDATA_AUX_CTL_REG     (* (reg8 *) DATALINK_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define DATALINK_RXBITCTR_PERIOD_REG    (* (reg8 *) DATALINK_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define DATALINK_RXBITCTR_PERIOD_PTR    (  (reg8 *) DATALINK_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define DATALINK_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) DATALINK_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define DATALINK_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) DATALINK_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define DATALINK_RXBITCTR_COUNTER_REG   (* (reg8 *) DATALINK_BUART_sRX_RxBitCounter__COUNT_REG )
    #define DATALINK_RXBITCTR_COUNTER_PTR   (  (reg8 *) DATALINK_BUART_sRX_RxBitCounter__COUNT_REG )

    #define DATALINK_RXSTATUS_REG           (* (reg8 *) DATALINK_BUART_sRX_RxSts__STATUS_REG )
    #define DATALINK_RXSTATUS_PTR           (  (reg8 *) DATALINK_BUART_sRX_RxSts__STATUS_REG )
    #define DATALINK_RXSTATUS_MASK_REG      (* (reg8 *) DATALINK_BUART_sRX_RxSts__MASK_REG )
    #define DATALINK_RXSTATUS_MASK_PTR      (  (reg8 *) DATALINK_BUART_sRX_RxSts__MASK_REG )
    #define DATALINK_RXSTATUS_ACTL_REG      (* (reg8 *) DATALINK_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define DATALINK_RXSTATUS_ACTL_PTR      (  (reg8 *) DATALINK_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) */

#if(DATALINK_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define DATALINK_INTCLOCK_CLKEN_REG     (* (reg8 *) DATALINK_IntClock__PM_ACT_CFG)
    #define DATALINK_INTCLOCK_CLKEN_PTR     (  (reg8 *) DATALINK_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define DATALINK_INTCLOCK_CLKEN_MASK    DATALINK_IntClock__PM_ACT_MSK
#endif /* End DATALINK_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(DATALINK_TX_ENABLED)
    #define DATALINK_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End DATALINK_TX_ENABLED */

#if(DATALINK_HD_ENABLED)
    #define DATALINK_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End DATALINK_HD_ENABLED */

#if( (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) )
    #define DATALINK_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define DATALINK_WAIT_1_MS      DATALINK_BL_CHK_DELAY_MS   

#define DATALINK_TXBUFFERSIZE   DATALINK_TX_BUFFER_SIZE
#define DATALINK_RXBUFFERSIZE   DATALINK_RX_BUFFER_SIZE

#if (DATALINK_RXHW_ADDRESS_ENABLED)
    #define DATALINK_RXADDRESSMODE  DATALINK_RX_ADDRESS_MODE
    #define DATALINK_RXHWADDRESS1   DATALINK_RX_HW_ADDRESS1
    #define DATALINK_RXHWADDRESS2   DATALINK_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define DATALINK_RXAddressMode  DATALINK_RXADDRESSMODE
#endif /* (DATALINK_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define DATALINK_initvar                    DATALINK_initVar

#define DATALINK_RX_Enabled                 DATALINK_RX_ENABLED
#define DATALINK_TX_Enabled                 DATALINK_TX_ENABLED
#define DATALINK_HD_Enabled                 DATALINK_HD_ENABLED
#define DATALINK_RX_IntInterruptEnabled     DATALINK_RX_INTERRUPT_ENABLED
#define DATALINK_TX_IntInterruptEnabled     DATALINK_TX_INTERRUPT_ENABLED
#define DATALINK_InternalClockUsed          DATALINK_INTERNAL_CLOCK_USED
#define DATALINK_RXHW_Address_Enabled       DATALINK_RXHW_ADDRESS_ENABLED
#define DATALINK_OverSampleCount            DATALINK_OVER_SAMPLE_COUNT
#define DATALINK_ParityType                 DATALINK_PARITY_TYPE

#if( DATALINK_TX_ENABLED && (DATALINK_TXBUFFERSIZE > DATALINK_FIFO_LENGTH))
    #define DATALINK_TXBUFFER               DATALINK_txBuffer
    #define DATALINK_TXBUFFERREAD           DATALINK_txBufferRead
    #define DATALINK_TXBUFFERWRITE          DATALINK_txBufferWrite
#endif /* End DATALINK_TX_ENABLED */
#if( ( DATALINK_RX_ENABLED || DATALINK_HD_ENABLED ) && \
     (DATALINK_RXBUFFERSIZE > DATALINK_FIFO_LENGTH) )
    #define DATALINK_RXBUFFER               DATALINK_rxBuffer
    #define DATALINK_RXBUFFERREAD           DATALINK_rxBufferRead
    #define DATALINK_RXBUFFERWRITE          DATALINK_rxBufferWrite
    #define DATALINK_RXBUFFERLOOPDETECT     DATALINK_rxBufferLoopDetect
    #define DATALINK_RXBUFFER_OVERFLOW      DATALINK_rxBufferOverflow
#endif /* End DATALINK_RX_ENABLED */

#ifdef DATALINK_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define DATALINK_CONTROL                DATALINK_CONTROL_REG
#endif /* End DATALINK_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(DATALINK_TX_ENABLED)
    #define DATALINK_TXDATA                 DATALINK_TXDATA_REG
    #define DATALINK_TXSTATUS               DATALINK_TXSTATUS_REG
    #define DATALINK_TXSTATUS_MASK          DATALINK_TXSTATUS_MASK_REG
    #define DATALINK_TXSTATUS_ACTL          DATALINK_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(DATALINK_TXCLKGEN_DP)
        #define DATALINK_TXBITCLKGEN_CTR        DATALINK_TXBITCLKGEN_CTR_REG
        #define DATALINK_TXBITCLKTX_COMPLETE    DATALINK_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define DATALINK_TXBITCTR_PERIOD        DATALINK_TXBITCTR_PERIOD_REG
        #define DATALINK_TXBITCTR_CONTROL       DATALINK_TXBITCTR_CONTROL_REG
        #define DATALINK_TXBITCTR_COUNTER       DATALINK_TXBITCTR_COUNTER_REG
    #endif /* DATALINK_TXCLKGEN_DP */
#endif /* End DATALINK_TX_ENABLED */

#if(DATALINK_HD_ENABLED)
    #define DATALINK_TXDATA                 DATALINK_TXDATA_REG
    #define DATALINK_TXSTATUS               DATALINK_TXSTATUS_REG
    #define DATALINK_TXSTATUS_MASK          DATALINK_TXSTATUS_MASK_REG
    #define DATALINK_TXSTATUS_ACTL          DATALINK_TXSTATUS_ACTL_REG
#endif /* End DATALINK_HD_ENABLED */

#if( (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) )
    #define DATALINK_RXDATA                 DATALINK_RXDATA_REG
    #define DATALINK_RXADDRESS1             DATALINK_RXADDRESS1_REG
    #define DATALINK_RXADDRESS2             DATALINK_RXADDRESS2_REG
    #define DATALINK_RXBITCTR_PERIOD        DATALINK_RXBITCTR_PERIOD_REG
    #define DATALINK_RXBITCTR_CONTROL       DATALINK_RXBITCTR_CONTROL_REG
    #define DATALINK_RXBITCTR_COUNTER       DATALINK_RXBITCTR_COUNTER_REG
    #define DATALINK_RXSTATUS               DATALINK_RXSTATUS_REG
    #define DATALINK_RXSTATUS_MASK          DATALINK_RXSTATUS_MASK_REG
    #define DATALINK_RXSTATUS_ACTL          DATALINK_RXSTATUS_ACTL_REG
#endif /* End  (DATALINK_RX_ENABLED) || (DATALINK_HD_ENABLED) */

#if(DATALINK_INTERNAL_CLOCK_USED)
    #define DATALINK_INTCLOCK_CLKEN         DATALINK_INTCLOCK_CLKEN_REG
#endif /* End DATALINK_INTERNAL_CLOCK_USED */

#define DATALINK_WAIT_FOR_COMLETE_REINIT    DATALINK_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_DATALINK_H */


/* [] END OF FILE */
