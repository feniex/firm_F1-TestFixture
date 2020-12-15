/*******************************************************************************
* File Name: QUAD.h
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


#if !defined(CY_UART_QUAD_H)
#define CY_UART_QUAD_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define QUAD_RX_ENABLED                     (1u)
#define QUAD_TX_ENABLED                     (0u)
#define QUAD_HD_ENABLED                     (0u)
#define QUAD_RX_INTERRUPT_ENABLED           (0u)
#define QUAD_TX_INTERRUPT_ENABLED           (0u)
#define QUAD_INTERNAL_CLOCK_USED            (1u)
#define QUAD_RXHW_ADDRESS_ENABLED           (0u)
#define QUAD_OVER_SAMPLE_COUNT              (8u)
#define QUAD_PARITY_TYPE                    (0u)
#define QUAD_PARITY_TYPE_SW                 (0u)
#define QUAD_BREAK_DETECT                   (0u)
#define QUAD_BREAK_BITS_TX                  (13u)
#define QUAD_BREAK_BITS_RX                  (13u)
#define QUAD_TXCLKGEN_DP                    (1u)
#define QUAD_USE23POLLING                   (1u)
#define QUAD_FLOW_CONTROL                   (0u)
#define QUAD_CLK_FREQ                       (0u)
#define QUAD_TX_BUFFER_SIZE                 (4u)
#define QUAD_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(QUAD_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define QUAD_CONTROL_REG_REMOVED            (0u)
#else
    #define QUAD_CONTROL_REG_REMOVED            (1u)
#endif /* End QUAD_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct QUAD_backupStruct_
{
    uint8 enableState;

    #if(QUAD_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End QUAD_CONTROL_REG_REMOVED */

} QUAD_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void QUAD_Start(void) ;
void QUAD_Stop(void) ;
uint8 QUAD_ReadControlRegister(void) ;
void QUAD_WriteControlRegister(uint8 control) ;

void QUAD_Init(void) ;
void QUAD_Enable(void) ;
void QUAD_SaveConfig(void) ;
void QUAD_RestoreConfig(void) ;
void QUAD_Sleep(void) ;
void QUAD_Wakeup(void) ;

/* Only if RX is enabled */
#if( (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) )

    #if (QUAD_RX_INTERRUPT_ENABLED)
        #define QUAD_EnableRxInt()  CyIntEnable (QUAD_RX_VECT_NUM)
        #define QUAD_DisableRxInt() CyIntDisable(QUAD_RX_VECT_NUM)
        CY_ISR_PROTO(QUAD_RXISR);
    #endif /* QUAD_RX_INTERRUPT_ENABLED */

    void QUAD_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void QUAD_SetRxAddress1(uint8 address) ;
    void QUAD_SetRxAddress2(uint8 address) ;

    void  QUAD_SetRxInterruptMode(uint8 intSrc) ;
    uint8 QUAD_ReadRxData(void) ;
    uint8 QUAD_ReadRxStatus(void) ;
    uint8 QUAD_GetChar(void) ;
    uint16 QUAD_GetByte(void) ;
    uint8 QUAD_GetRxBufferSize(void)
                                                            ;
    void QUAD_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define QUAD_GetRxInterruptSource   QUAD_ReadRxStatus

#endif /* End (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) */

/* Only if TX is enabled */
#if(QUAD_TX_ENABLED || QUAD_HD_ENABLED)

    #if(QUAD_TX_INTERRUPT_ENABLED)
        #define QUAD_EnableTxInt()  CyIntEnable (QUAD_TX_VECT_NUM)
        #define QUAD_DisableTxInt() CyIntDisable(QUAD_TX_VECT_NUM)
        #define QUAD_SetPendingTxInt() CyIntSetPending(QUAD_TX_VECT_NUM)
        #define QUAD_ClearPendingTxInt() CyIntClearPending(QUAD_TX_VECT_NUM)
        CY_ISR_PROTO(QUAD_TXISR);
    #endif /* QUAD_TX_INTERRUPT_ENABLED */

    void QUAD_SetTxInterruptMode(uint8 intSrc) ;
    void QUAD_WriteTxData(uint8 txDataByte) ;
    uint8 QUAD_ReadTxStatus(void) ;
    void QUAD_PutChar(uint8 txDataByte) ;
    void QUAD_PutString(const char8 string[]) ;
    void QUAD_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void QUAD_PutCRLF(uint8 txDataByte) ;
    void QUAD_ClearTxBuffer(void) ;
    void QUAD_SetTxAddressMode(uint8 addressMode) ;
    void QUAD_SendBreak(uint8 retMode) ;
    uint8 QUAD_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define QUAD_PutStringConst         QUAD_PutString
    #define QUAD_PutArrayConst          QUAD_PutArray
    #define QUAD_GetTxInterruptSource   QUAD_ReadTxStatus

#endif /* End QUAD_TX_ENABLED || QUAD_HD_ENABLED */

#if(QUAD_HD_ENABLED)
    void QUAD_LoadRxConfig(void) ;
    void QUAD_LoadTxConfig(void) ;
#endif /* End QUAD_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_QUAD) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    QUAD_CyBtldrCommStart(void) CYSMALL ;
    void    QUAD_CyBtldrCommStop(void) CYSMALL ;
    void    QUAD_CyBtldrCommReset(void) CYSMALL ;
    cystatus QUAD_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus QUAD_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_QUAD)
        #define CyBtldrCommStart    QUAD_CyBtldrCommStart
        #define CyBtldrCommStop     QUAD_CyBtldrCommStop
        #define CyBtldrCommReset    QUAD_CyBtldrCommReset
        #define CyBtldrCommWrite    QUAD_CyBtldrCommWrite
        #define CyBtldrCommRead     QUAD_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_QUAD) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define QUAD_BYTE2BYTE_TIME_OUT (25u)
    #define QUAD_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define QUAD_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define QUAD_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define QUAD_SET_SPACE      (0x00u)
#define QUAD_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (QUAD_TX_ENABLED) || (QUAD_HD_ENABLED) )
    #if(QUAD_TX_INTERRUPT_ENABLED)
        #define QUAD_TX_VECT_NUM            (uint8)QUAD_TXInternalInterrupt__INTC_NUMBER
        #define QUAD_TX_PRIOR_NUM           (uint8)QUAD_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* QUAD_TX_INTERRUPT_ENABLED */

    #define QUAD_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define QUAD_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define QUAD_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(QUAD_TX_ENABLED)
        #define QUAD_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (QUAD_HD_ENABLED) */
        #define QUAD_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (QUAD_TX_ENABLED) */

    #define QUAD_TX_STS_COMPLETE            (uint8)(0x01u << QUAD_TX_STS_COMPLETE_SHIFT)
    #define QUAD_TX_STS_FIFO_EMPTY          (uint8)(0x01u << QUAD_TX_STS_FIFO_EMPTY_SHIFT)
    #define QUAD_TX_STS_FIFO_FULL           (uint8)(0x01u << QUAD_TX_STS_FIFO_FULL_SHIFT)
    #define QUAD_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << QUAD_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (QUAD_TX_ENABLED) || (QUAD_HD_ENABLED)*/

#if( (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) )
    #if(QUAD_RX_INTERRUPT_ENABLED)
        #define QUAD_RX_VECT_NUM            (uint8)QUAD_RXInternalInterrupt__INTC_NUMBER
        #define QUAD_RX_PRIOR_NUM           (uint8)QUAD_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* QUAD_RX_INTERRUPT_ENABLED */
    #define QUAD_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define QUAD_RX_STS_BREAK_SHIFT             (0x01u)
    #define QUAD_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define QUAD_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define QUAD_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define QUAD_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define QUAD_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define QUAD_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define QUAD_RX_STS_MRKSPC           (uint8)(0x01u << QUAD_RX_STS_MRKSPC_SHIFT)
    #define QUAD_RX_STS_BREAK            (uint8)(0x01u << QUAD_RX_STS_BREAK_SHIFT)
    #define QUAD_RX_STS_PAR_ERROR        (uint8)(0x01u << QUAD_RX_STS_PAR_ERROR_SHIFT)
    #define QUAD_RX_STS_STOP_ERROR       (uint8)(0x01u << QUAD_RX_STS_STOP_ERROR_SHIFT)
    #define QUAD_RX_STS_OVERRUN          (uint8)(0x01u << QUAD_RX_STS_OVERRUN_SHIFT)
    #define QUAD_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << QUAD_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define QUAD_RX_STS_ADDR_MATCH       (uint8)(0x01u << QUAD_RX_STS_ADDR_MATCH_SHIFT)
    #define QUAD_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << QUAD_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define QUAD_RX_HW_MASK                     (0x7Fu)
#endif /* End (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) */

/* Control Register definitions */
#define QUAD_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define QUAD_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define QUAD_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define QUAD_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define QUAD_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define QUAD_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define QUAD_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define QUAD_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define QUAD_CTRL_HD_SEND               (uint8)(0x01u << QUAD_CTRL_HD_SEND_SHIFT)
#define QUAD_CTRL_HD_SEND_BREAK         (uint8)(0x01u << QUAD_CTRL_HD_SEND_BREAK_SHIFT)
#define QUAD_CTRL_MARK                  (uint8)(0x01u << QUAD_CTRL_MARK_SHIFT)
#define QUAD_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << QUAD_CTRL_PARITY_TYPE0_SHIFT)
#define QUAD_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << QUAD_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define QUAD_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define QUAD_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define QUAD_SEND_BREAK                         (0x00u)
#define QUAD_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define QUAD_REINIT                             (0x02u)
#define QUAD_SEND_WAIT_REINIT                   (0x03u)

#define QUAD_OVER_SAMPLE_8                      (8u)
#define QUAD_OVER_SAMPLE_16                     (16u)

#define QUAD_BIT_CENTER                         (QUAD_OVER_SAMPLE_COUNT - 2u)

#define QUAD_FIFO_LENGTH                        (4u)
#define QUAD_NUMBER_OF_START_BIT                (1u)
#define QUAD_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define QUAD_TXBITCTR_BREAKBITS8X   ((QUAD_BREAK_BITS_TX * QUAD_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define QUAD_TXBITCTR_BREAKBITS ((QUAD_BREAK_BITS_TX * QUAD_OVER_SAMPLE_COUNT) - 1u)

#define QUAD_HALF_BIT_COUNT   \
                            (((QUAD_OVER_SAMPLE_COUNT / 2u) + (QUAD_USE23POLLING * 1u)) - 2u)
#if (QUAD_OVER_SAMPLE_COUNT == QUAD_OVER_SAMPLE_8)
    #define QUAD_HD_TXBITCTR_INIT   (((QUAD_BREAK_BITS_TX + \
                            QUAD_NUMBER_OF_START_BIT) * QUAD_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define QUAD_RXBITCTR_INIT  ((((QUAD_BREAK_BITS_RX + QUAD_NUMBER_OF_START_BIT) \
                            * QUAD_OVER_SAMPLE_COUNT) + QUAD_HALF_BIT_COUNT) - 1u)

#else /* QUAD_OVER_SAMPLE_COUNT == QUAD_OVER_SAMPLE_16 */
    #define QUAD_HD_TXBITCTR_INIT   ((8u * QUAD_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define QUAD_RXBITCTR_INIT      (((7u * QUAD_OVER_SAMPLE_COUNT) - 1u) + \
                                                      QUAD_HALF_BIT_COUNT)
#endif /* End QUAD_OVER_SAMPLE_COUNT */

#define QUAD_HD_RXBITCTR_INIT                   QUAD_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 QUAD_initVar;
#if (QUAD_TX_INTERRUPT_ENABLED && QUAD_TX_ENABLED)
    extern volatile uint8 QUAD_txBuffer[QUAD_TX_BUFFER_SIZE];
    extern volatile uint8 QUAD_txBufferRead;
    extern uint8 QUAD_txBufferWrite;
#endif /* (QUAD_TX_INTERRUPT_ENABLED && QUAD_TX_ENABLED) */
#if (QUAD_RX_INTERRUPT_ENABLED && (QUAD_RX_ENABLED || QUAD_HD_ENABLED))
    extern uint8 QUAD_errorStatus;
    extern volatile uint8 QUAD_rxBuffer[QUAD_RX_BUFFER_SIZE];
    extern volatile uint8 QUAD_rxBufferRead;
    extern volatile uint8 QUAD_rxBufferWrite;
    extern volatile uint8 QUAD_rxBufferLoopDetect;
    extern volatile uint8 QUAD_rxBufferOverflow;
    #if (QUAD_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 QUAD_rxAddressMode;
        extern volatile uint8 QUAD_rxAddressDetected;
    #endif /* (QUAD_RXHW_ADDRESS_ENABLED) */
#endif /* (QUAD_RX_INTERRUPT_ENABLED && (QUAD_RX_ENABLED || QUAD_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define QUAD__B_UART__AM_SW_BYTE_BYTE 1
#define QUAD__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define QUAD__B_UART__AM_HW_BYTE_BY_BYTE 3
#define QUAD__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define QUAD__B_UART__AM_NONE 0

#define QUAD__B_UART__NONE_REVB 0
#define QUAD__B_UART__EVEN_REVB 1
#define QUAD__B_UART__ODD_REVB 2
#define QUAD__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define QUAD_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define QUAD_NUMBER_OF_STOP_BITS    (1u)

#if (QUAD_RXHW_ADDRESS_ENABLED)
    #define QUAD_RX_ADDRESS_MODE    (0u)
    #define QUAD_RX_HW_ADDRESS1     (0u)
    #define QUAD_RX_HW_ADDRESS2     (0u)
#endif /* (QUAD_RXHW_ADDRESS_ENABLED) */

#define QUAD_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << QUAD_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << QUAD_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << QUAD_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << QUAD_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << QUAD_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << QUAD_RX_STS_BREAK_SHIFT) \
                                        | (0 << QUAD_RX_STS_OVERRUN_SHIFT))

#define QUAD_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << QUAD_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << QUAD_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << QUAD_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << QUAD_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef QUAD_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define QUAD_CONTROL_REG \
                            (* (reg8 *) QUAD_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define QUAD_CONTROL_PTR \
                            (  (reg8 *) QUAD_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End QUAD_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(QUAD_TX_ENABLED)
    #define QUAD_TXDATA_REG          (* (reg8 *) QUAD_BUART_sTX_TxShifter_u0__F0_REG)
    #define QUAD_TXDATA_PTR          (  (reg8 *) QUAD_BUART_sTX_TxShifter_u0__F0_REG)
    #define QUAD_TXDATA_AUX_CTL_REG  (* (reg8 *) QUAD_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define QUAD_TXDATA_AUX_CTL_PTR  (  (reg8 *) QUAD_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define QUAD_TXSTATUS_REG        (* (reg8 *) QUAD_BUART_sTX_TxSts__STATUS_REG)
    #define QUAD_TXSTATUS_PTR        (  (reg8 *) QUAD_BUART_sTX_TxSts__STATUS_REG)
    #define QUAD_TXSTATUS_MASK_REG   (* (reg8 *) QUAD_BUART_sTX_TxSts__MASK_REG)
    #define QUAD_TXSTATUS_MASK_PTR   (  (reg8 *) QUAD_BUART_sTX_TxSts__MASK_REG)
    #define QUAD_TXSTATUS_ACTL_REG   (* (reg8 *) QUAD_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define QUAD_TXSTATUS_ACTL_PTR   (  (reg8 *) QUAD_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(QUAD_TXCLKGEN_DP)
        #define QUAD_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define QUAD_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define QUAD_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define QUAD_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define QUAD_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define QUAD_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define QUAD_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define QUAD_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define QUAD_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define QUAD_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) QUAD_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* QUAD_TXCLKGEN_DP */

#endif /* End QUAD_TX_ENABLED */

#if(QUAD_HD_ENABLED)

    #define QUAD_TXDATA_REG             (* (reg8 *) QUAD_BUART_sRX_RxShifter_u0__F1_REG )
    #define QUAD_TXDATA_PTR             (  (reg8 *) QUAD_BUART_sRX_RxShifter_u0__F1_REG )
    #define QUAD_TXDATA_AUX_CTL_REG     (* (reg8 *) QUAD_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define QUAD_TXDATA_AUX_CTL_PTR     (  (reg8 *) QUAD_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define QUAD_TXSTATUS_REG           (* (reg8 *) QUAD_BUART_sRX_RxSts__STATUS_REG )
    #define QUAD_TXSTATUS_PTR           (  (reg8 *) QUAD_BUART_sRX_RxSts__STATUS_REG )
    #define QUAD_TXSTATUS_MASK_REG      (* (reg8 *) QUAD_BUART_sRX_RxSts__MASK_REG )
    #define QUAD_TXSTATUS_MASK_PTR      (  (reg8 *) QUAD_BUART_sRX_RxSts__MASK_REG )
    #define QUAD_TXSTATUS_ACTL_REG      (* (reg8 *) QUAD_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define QUAD_TXSTATUS_ACTL_PTR      (  (reg8 *) QUAD_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End QUAD_HD_ENABLED */

#if( (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) )
    #define QUAD_RXDATA_REG             (* (reg8 *) QUAD_BUART_sRX_RxShifter_u0__F0_REG )
    #define QUAD_RXDATA_PTR             (  (reg8 *) QUAD_BUART_sRX_RxShifter_u0__F0_REG )
    #define QUAD_RXADDRESS1_REG         (* (reg8 *) QUAD_BUART_sRX_RxShifter_u0__D0_REG )
    #define QUAD_RXADDRESS1_PTR         (  (reg8 *) QUAD_BUART_sRX_RxShifter_u0__D0_REG )
    #define QUAD_RXADDRESS2_REG         (* (reg8 *) QUAD_BUART_sRX_RxShifter_u0__D1_REG )
    #define QUAD_RXADDRESS2_PTR         (  (reg8 *) QUAD_BUART_sRX_RxShifter_u0__D1_REG )
    #define QUAD_RXDATA_AUX_CTL_REG     (* (reg8 *) QUAD_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define QUAD_RXBITCTR_PERIOD_REG    (* (reg8 *) QUAD_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define QUAD_RXBITCTR_PERIOD_PTR    (  (reg8 *) QUAD_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define QUAD_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) QUAD_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define QUAD_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) QUAD_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define QUAD_RXBITCTR_COUNTER_REG   (* (reg8 *) QUAD_BUART_sRX_RxBitCounter__COUNT_REG )
    #define QUAD_RXBITCTR_COUNTER_PTR   (  (reg8 *) QUAD_BUART_sRX_RxBitCounter__COUNT_REG )

    #define QUAD_RXSTATUS_REG           (* (reg8 *) QUAD_BUART_sRX_RxSts__STATUS_REG )
    #define QUAD_RXSTATUS_PTR           (  (reg8 *) QUAD_BUART_sRX_RxSts__STATUS_REG )
    #define QUAD_RXSTATUS_MASK_REG      (* (reg8 *) QUAD_BUART_sRX_RxSts__MASK_REG )
    #define QUAD_RXSTATUS_MASK_PTR      (  (reg8 *) QUAD_BUART_sRX_RxSts__MASK_REG )
    #define QUAD_RXSTATUS_ACTL_REG      (* (reg8 *) QUAD_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define QUAD_RXSTATUS_ACTL_PTR      (  (reg8 *) QUAD_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) */

#if(QUAD_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define QUAD_INTCLOCK_CLKEN_REG     (* (reg8 *) QUAD_IntClock__PM_ACT_CFG)
    #define QUAD_INTCLOCK_CLKEN_PTR     (  (reg8 *) QUAD_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define QUAD_INTCLOCK_CLKEN_MASK    QUAD_IntClock__PM_ACT_MSK
#endif /* End QUAD_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(QUAD_TX_ENABLED)
    #define QUAD_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End QUAD_TX_ENABLED */

#if(QUAD_HD_ENABLED)
    #define QUAD_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End QUAD_HD_ENABLED */

#if( (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) )
    #define QUAD_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define QUAD_WAIT_1_MS      QUAD_BL_CHK_DELAY_MS   

#define QUAD_TXBUFFERSIZE   QUAD_TX_BUFFER_SIZE
#define QUAD_RXBUFFERSIZE   QUAD_RX_BUFFER_SIZE

#if (QUAD_RXHW_ADDRESS_ENABLED)
    #define QUAD_RXADDRESSMODE  QUAD_RX_ADDRESS_MODE
    #define QUAD_RXHWADDRESS1   QUAD_RX_HW_ADDRESS1
    #define QUAD_RXHWADDRESS2   QUAD_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define QUAD_RXAddressMode  QUAD_RXADDRESSMODE
#endif /* (QUAD_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define QUAD_initvar                    QUAD_initVar

#define QUAD_RX_Enabled                 QUAD_RX_ENABLED
#define QUAD_TX_Enabled                 QUAD_TX_ENABLED
#define QUAD_HD_Enabled                 QUAD_HD_ENABLED
#define QUAD_RX_IntInterruptEnabled     QUAD_RX_INTERRUPT_ENABLED
#define QUAD_TX_IntInterruptEnabled     QUAD_TX_INTERRUPT_ENABLED
#define QUAD_InternalClockUsed          QUAD_INTERNAL_CLOCK_USED
#define QUAD_RXHW_Address_Enabled       QUAD_RXHW_ADDRESS_ENABLED
#define QUAD_OverSampleCount            QUAD_OVER_SAMPLE_COUNT
#define QUAD_ParityType                 QUAD_PARITY_TYPE

#if( QUAD_TX_ENABLED && (QUAD_TXBUFFERSIZE > QUAD_FIFO_LENGTH))
    #define QUAD_TXBUFFER               QUAD_txBuffer
    #define QUAD_TXBUFFERREAD           QUAD_txBufferRead
    #define QUAD_TXBUFFERWRITE          QUAD_txBufferWrite
#endif /* End QUAD_TX_ENABLED */
#if( ( QUAD_RX_ENABLED || QUAD_HD_ENABLED ) && \
     (QUAD_RXBUFFERSIZE > QUAD_FIFO_LENGTH) )
    #define QUAD_RXBUFFER               QUAD_rxBuffer
    #define QUAD_RXBUFFERREAD           QUAD_rxBufferRead
    #define QUAD_RXBUFFERWRITE          QUAD_rxBufferWrite
    #define QUAD_RXBUFFERLOOPDETECT     QUAD_rxBufferLoopDetect
    #define QUAD_RXBUFFER_OVERFLOW      QUAD_rxBufferOverflow
#endif /* End QUAD_RX_ENABLED */

#ifdef QUAD_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define QUAD_CONTROL                QUAD_CONTROL_REG
#endif /* End QUAD_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(QUAD_TX_ENABLED)
    #define QUAD_TXDATA                 QUAD_TXDATA_REG
    #define QUAD_TXSTATUS               QUAD_TXSTATUS_REG
    #define QUAD_TXSTATUS_MASK          QUAD_TXSTATUS_MASK_REG
    #define QUAD_TXSTATUS_ACTL          QUAD_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(QUAD_TXCLKGEN_DP)
        #define QUAD_TXBITCLKGEN_CTR        QUAD_TXBITCLKGEN_CTR_REG
        #define QUAD_TXBITCLKTX_COMPLETE    QUAD_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define QUAD_TXBITCTR_PERIOD        QUAD_TXBITCTR_PERIOD_REG
        #define QUAD_TXBITCTR_CONTROL       QUAD_TXBITCTR_CONTROL_REG
        #define QUAD_TXBITCTR_COUNTER       QUAD_TXBITCTR_COUNTER_REG
    #endif /* QUAD_TXCLKGEN_DP */
#endif /* End QUAD_TX_ENABLED */

#if(QUAD_HD_ENABLED)
    #define QUAD_TXDATA                 QUAD_TXDATA_REG
    #define QUAD_TXSTATUS               QUAD_TXSTATUS_REG
    #define QUAD_TXSTATUS_MASK          QUAD_TXSTATUS_MASK_REG
    #define QUAD_TXSTATUS_ACTL          QUAD_TXSTATUS_ACTL_REG
#endif /* End QUAD_HD_ENABLED */

#if( (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) )
    #define QUAD_RXDATA                 QUAD_RXDATA_REG
    #define QUAD_RXADDRESS1             QUAD_RXADDRESS1_REG
    #define QUAD_RXADDRESS2             QUAD_RXADDRESS2_REG
    #define QUAD_RXBITCTR_PERIOD        QUAD_RXBITCTR_PERIOD_REG
    #define QUAD_RXBITCTR_CONTROL       QUAD_RXBITCTR_CONTROL_REG
    #define QUAD_RXBITCTR_COUNTER       QUAD_RXBITCTR_COUNTER_REG
    #define QUAD_RXSTATUS               QUAD_RXSTATUS_REG
    #define QUAD_RXSTATUS_MASK          QUAD_RXSTATUS_MASK_REG
    #define QUAD_RXSTATUS_ACTL          QUAD_RXSTATUS_ACTL_REG
#endif /* End  (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) */

#if(QUAD_INTERNAL_CLOCK_USED)
    #define QUAD_INTCLOCK_CLKEN         QUAD_INTCLOCK_CLKEN_REG
#endif /* End QUAD_INTERNAL_CLOCK_USED */

#define QUAD_WAIT_FOR_COMLETE_REINIT    QUAD_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_QUAD_H */


/* [] END OF FILE */
