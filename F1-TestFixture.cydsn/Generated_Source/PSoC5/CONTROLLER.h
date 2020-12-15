/*******************************************************************************
* File Name: CONTROLLER.h
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


#if !defined(CY_UART_CONTROLLER_H)
#define CY_UART_CONTROLLER_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define CONTROLLER_RX_ENABLED                     (1u)
#define CONTROLLER_TX_ENABLED                     (1u)
#define CONTROLLER_HD_ENABLED                     (0u)
#define CONTROLLER_RX_INTERRUPT_ENABLED           (0u)
#define CONTROLLER_TX_INTERRUPT_ENABLED           (1u)
#define CONTROLLER_INTERNAL_CLOCK_USED            (1u)
#define CONTROLLER_RXHW_ADDRESS_ENABLED           (0u)
#define CONTROLLER_OVER_SAMPLE_COUNT              (8u)
#define CONTROLLER_PARITY_TYPE                    (0u)
#define CONTROLLER_PARITY_TYPE_SW                 (0u)
#define CONTROLLER_BREAK_DETECT                   (0u)
#define CONTROLLER_BREAK_BITS_TX                  (13u)
#define CONTROLLER_BREAK_BITS_RX                  (13u)
#define CONTROLLER_TXCLKGEN_DP                    (1u)
#define CONTROLLER_USE23POLLING                   (1u)
#define CONTROLLER_FLOW_CONTROL                   (0u)
#define CONTROLLER_CLK_FREQ                       (0u)
#define CONTROLLER_TX_BUFFER_SIZE                 (1024u)
#define CONTROLLER_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(CONTROLLER_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define CONTROLLER_CONTROL_REG_REMOVED            (0u)
#else
    #define CONTROLLER_CONTROL_REG_REMOVED            (1u)
#endif /* End CONTROLLER_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct CONTROLLER_backupStruct_
{
    uint8 enableState;

    #if(CONTROLLER_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End CONTROLLER_CONTROL_REG_REMOVED */

} CONTROLLER_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void CONTROLLER_Start(void) ;
void CONTROLLER_Stop(void) ;
uint8 CONTROLLER_ReadControlRegister(void) ;
void CONTROLLER_WriteControlRegister(uint8 control) ;

void CONTROLLER_Init(void) ;
void CONTROLLER_Enable(void) ;
void CONTROLLER_SaveConfig(void) ;
void CONTROLLER_RestoreConfig(void) ;
void CONTROLLER_Sleep(void) ;
void CONTROLLER_Wakeup(void) ;

/* Only if RX is enabled */
#if( (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) )

    #if (CONTROLLER_RX_INTERRUPT_ENABLED)
        #define CONTROLLER_EnableRxInt()  CyIntEnable (CONTROLLER_RX_VECT_NUM)
        #define CONTROLLER_DisableRxInt() CyIntDisable(CONTROLLER_RX_VECT_NUM)
        CY_ISR_PROTO(CONTROLLER_RXISR);
    #endif /* CONTROLLER_RX_INTERRUPT_ENABLED */

    void CONTROLLER_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void CONTROLLER_SetRxAddress1(uint8 address) ;
    void CONTROLLER_SetRxAddress2(uint8 address) ;

    void  CONTROLLER_SetRxInterruptMode(uint8 intSrc) ;
    uint8 CONTROLLER_ReadRxData(void) ;
    uint8 CONTROLLER_ReadRxStatus(void) ;
    uint8 CONTROLLER_GetChar(void) ;
    uint16 CONTROLLER_GetByte(void) ;
    uint8 CONTROLLER_GetRxBufferSize(void)
                                                            ;
    void CONTROLLER_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define CONTROLLER_GetRxInterruptSource   CONTROLLER_ReadRxStatus

#endif /* End (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) */

/* Only if TX is enabled */
#if(CONTROLLER_TX_ENABLED || CONTROLLER_HD_ENABLED)

    #if(CONTROLLER_TX_INTERRUPT_ENABLED)
        #define CONTROLLER_EnableTxInt()  CyIntEnable (CONTROLLER_TX_VECT_NUM)
        #define CONTROLLER_DisableTxInt() CyIntDisable(CONTROLLER_TX_VECT_NUM)
        #define CONTROLLER_SetPendingTxInt() CyIntSetPending(CONTROLLER_TX_VECT_NUM)
        #define CONTROLLER_ClearPendingTxInt() CyIntClearPending(CONTROLLER_TX_VECT_NUM)
        CY_ISR_PROTO(CONTROLLER_TXISR);
    #endif /* CONTROLLER_TX_INTERRUPT_ENABLED */

    void CONTROLLER_SetTxInterruptMode(uint8 intSrc) ;
    void CONTROLLER_WriteTxData(uint8 txDataByte) ;
    uint8 CONTROLLER_ReadTxStatus(void) ;
    void CONTROLLER_PutChar(uint8 txDataByte) ;
    void CONTROLLER_PutString(const char8 string[]) ;
    void CONTROLLER_PutArray(const uint8 string[], uint16 byteCount)
                                                            ;
    void CONTROLLER_PutCRLF(uint8 txDataByte) ;
    void CONTROLLER_ClearTxBuffer(void) ;
    void CONTROLLER_SetTxAddressMode(uint8 addressMode) ;
    void CONTROLLER_SendBreak(uint8 retMode) ;
    uint16 CONTROLLER_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define CONTROLLER_PutStringConst         CONTROLLER_PutString
    #define CONTROLLER_PutArrayConst          CONTROLLER_PutArray
    #define CONTROLLER_GetTxInterruptSource   CONTROLLER_ReadTxStatus

#endif /* End CONTROLLER_TX_ENABLED || CONTROLLER_HD_ENABLED */

#if(CONTROLLER_HD_ENABLED)
    void CONTROLLER_LoadRxConfig(void) ;
    void CONTROLLER_LoadTxConfig(void) ;
#endif /* End CONTROLLER_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CONTROLLER) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    CONTROLLER_CyBtldrCommStart(void) CYSMALL ;
    void    CONTROLLER_CyBtldrCommStop(void) CYSMALL ;
    void    CONTROLLER_CyBtldrCommReset(void) CYSMALL ;
    cystatus CONTROLLER_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus CONTROLLER_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CONTROLLER)
        #define CyBtldrCommStart    CONTROLLER_CyBtldrCommStart
        #define CyBtldrCommStop     CONTROLLER_CyBtldrCommStop
        #define CyBtldrCommReset    CONTROLLER_CyBtldrCommReset
        #define CyBtldrCommWrite    CONTROLLER_CyBtldrCommWrite
        #define CyBtldrCommRead     CONTROLLER_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CONTROLLER) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define CONTROLLER_BYTE2BYTE_TIME_OUT (25u)
    #define CONTROLLER_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define CONTROLLER_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define CONTROLLER_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define CONTROLLER_SET_SPACE      (0x00u)
#define CONTROLLER_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (CONTROLLER_TX_ENABLED) || (CONTROLLER_HD_ENABLED) )
    #if(CONTROLLER_TX_INTERRUPT_ENABLED)
        #define CONTROLLER_TX_VECT_NUM            (uint8)CONTROLLER_TXInternalInterrupt__INTC_NUMBER
        #define CONTROLLER_TX_PRIOR_NUM           (uint8)CONTROLLER_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* CONTROLLER_TX_INTERRUPT_ENABLED */

    #define CONTROLLER_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define CONTROLLER_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define CONTROLLER_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(CONTROLLER_TX_ENABLED)
        #define CONTROLLER_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (CONTROLLER_HD_ENABLED) */
        #define CONTROLLER_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (CONTROLLER_TX_ENABLED) */

    #define CONTROLLER_TX_STS_COMPLETE            (uint8)(0x01u << CONTROLLER_TX_STS_COMPLETE_SHIFT)
    #define CONTROLLER_TX_STS_FIFO_EMPTY          (uint8)(0x01u << CONTROLLER_TX_STS_FIFO_EMPTY_SHIFT)
    #define CONTROLLER_TX_STS_FIFO_FULL           (uint8)(0x01u << CONTROLLER_TX_STS_FIFO_FULL_SHIFT)
    #define CONTROLLER_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << CONTROLLER_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (CONTROLLER_TX_ENABLED) || (CONTROLLER_HD_ENABLED)*/

#if( (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) )
    #if(CONTROLLER_RX_INTERRUPT_ENABLED)
        #define CONTROLLER_RX_VECT_NUM            (uint8)CONTROLLER_RXInternalInterrupt__INTC_NUMBER
        #define CONTROLLER_RX_PRIOR_NUM           (uint8)CONTROLLER_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* CONTROLLER_RX_INTERRUPT_ENABLED */
    #define CONTROLLER_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define CONTROLLER_RX_STS_BREAK_SHIFT             (0x01u)
    #define CONTROLLER_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define CONTROLLER_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define CONTROLLER_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define CONTROLLER_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define CONTROLLER_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define CONTROLLER_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define CONTROLLER_RX_STS_MRKSPC           (uint8)(0x01u << CONTROLLER_RX_STS_MRKSPC_SHIFT)
    #define CONTROLLER_RX_STS_BREAK            (uint8)(0x01u << CONTROLLER_RX_STS_BREAK_SHIFT)
    #define CONTROLLER_RX_STS_PAR_ERROR        (uint8)(0x01u << CONTROLLER_RX_STS_PAR_ERROR_SHIFT)
    #define CONTROLLER_RX_STS_STOP_ERROR       (uint8)(0x01u << CONTROLLER_RX_STS_STOP_ERROR_SHIFT)
    #define CONTROLLER_RX_STS_OVERRUN          (uint8)(0x01u << CONTROLLER_RX_STS_OVERRUN_SHIFT)
    #define CONTROLLER_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << CONTROLLER_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define CONTROLLER_RX_STS_ADDR_MATCH       (uint8)(0x01u << CONTROLLER_RX_STS_ADDR_MATCH_SHIFT)
    #define CONTROLLER_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << CONTROLLER_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define CONTROLLER_RX_HW_MASK                     (0x7Fu)
#endif /* End (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) */

/* Control Register definitions */
#define CONTROLLER_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define CONTROLLER_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define CONTROLLER_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define CONTROLLER_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define CONTROLLER_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define CONTROLLER_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define CONTROLLER_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define CONTROLLER_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define CONTROLLER_CTRL_HD_SEND               (uint8)(0x01u << CONTROLLER_CTRL_HD_SEND_SHIFT)
#define CONTROLLER_CTRL_HD_SEND_BREAK         (uint8)(0x01u << CONTROLLER_CTRL_HD_SEND_BREAK_SHIFT)
#define CONTROLLER_CTRL_MARK                  (uint8)(0x01u << CONTROLLER_CTRL_MARK_SHIFT)
#define CONTROLLER_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << CONTROLLER_CTRL_PARITY_TYPE0_SHIFT)
#define CONTROLLER_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << CONTROLLER_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define CONTROLLER_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define CONTROLLER_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define CONTROLLER_SEND_BREAK                         (0x00u)
#define CONTROLLER_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define CONTROLLER_REINIT                             (0x02u)
#define CONTROLLER_SEND_WAIT_REINIT                   (0x03u)

#define CONTROLLER_OVER_SAMPLE_8                      (8u)
#define CONTROLLER_OVER_SAMPLE_16                     (16u)

#define CONTROLLER_BIT_CENTER                         (CONTROLLER_OVER_SAMPLE_COUNT - 2u)

#define CONTROLLER_FIFO_LENGTH                        (4u)
#define CONTROLLER_NUMBER_OF_START_BIT                (1u)
#define CONTROLLER_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define CONTROLLER_TXBITCTR_BREAKBITS8X   ((CONTROLLER_BREAK_BITS_TX * CONTROLLER_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define CONTROLLER_TXBITCTR_BREAKBITS ((CONTROLLER_BREAK_BITS_TX * CONTROLLER_OVER_SAMPLE_COUNT) - 1u)

#define CONTROLLER_HALF_BIT_COUNT   \
                            (((CONTROLLER_OVER_SAMPLE_COUNT / 2u) + (CONTROLLER_USE23POLLING * 1u)) - 2u)
#if (CONTROLLER_OVER_SAMPLE_COUNT == CONTROLLER_OVER_SAMPLE_8)
    #define CONTROLLER_HD_TXBITCTR_INIT   (((CONTROLLER_BREAK_BITS_TX + \
                            CONTROLLER_NUMBER_OF_START_BIT) * CONTROLLER_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define CONTROLLER_RXBITCTR_INIT  ((((CONTROLLER_BREAK_BITS_RX + CONTROLLER_NUMBER_OF_START_BIT) \
                            * CONTROLLER_OVER_SAMPLE_COUNT) + CONTROLLER_HALF_BIT_COUNT) - 1u)

#else /* CONTROLLER_OVER_SAMPLE_COUNT == CONTROLLER_OVER_SAMPLE_16 */
    #define CONTROLLER_HD_TXBITCTR_INIT   ((8u * CONTROLLER_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define CONTROLLER_RXBITCTR_INIT      (((7u * CONTROLLER_OVER_SAMPLE_COUNT) - 1u) + \
                                                      CONTROLLER_HALF_BIT_COUNT)
#endif /* End CONTROLLER_OVER_SAMPLE_COUNT */

#define CONTROLLER_HD_RXBITCTR_INIT                   CONTROLLER_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 CONTROLLER_initVar;
#if (CONTROLLER_TX_INTERRUPT_ENABLED && CONTROLLER_TX_ENABLED)
    extern volatile uint8 CONTROLLER_txBuffer[CONTROLLER_TX_BUFFER_SIZE];
    extern volatile uint16 CONTROLLER_txBufferRead;
    extern uint16 CONTROLLER_txBufferWrite;
#endif /* (CONTROLLER_TX_INTERRUPT_ENABLED && CONTROLLER_TX_ENABLED) */
#if (CONTROLLER_RX_INTERRUPT_ENABLED && (CONTROLLER_RX_ENABLED || CONTROLLER_HD_ENABLED))
    extern uint8 CONTROLLER_errorStatus;
    extern volatile uint8 CONTROLLER_rxBuffer[CONTROLLER_RX_BUFFER_SIZE];
    extern volatile uint8 CONTROLLER_rxBufferRead;
    extern volatile uint8 CONTROLLER_rxBufferWrite;
    extern volatile uint8 CONTROLLER_rxBufferLoopDetect;
    extern volatile uint8 CONTROLLER_rxBufferOverflow;
    #if (CONTROLLER_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 CONTROLLER_rxAddressMode;
        extern volatile uint8 CONTROLLER_rxAddressDetected;
    #endif /* (CONTROLLER_RXHW_ADDRESS_ENABLED) */
#endif /* (CONTROLLER_RX_INTERRUPT_ENABLED && (CONTROLLER_RX_ENABLED || CONTROLLER_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define CONTROLLER__B_UART__AM_SW_BYTE_BYTE 1
#define CONTROLLER__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define CONTROLLER__B_UART__AM_HW_BYTE_BY_BYTE 3
#define CONTROLLER__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define CONTROLLER__B_UART__AM_NONE 0

#define CONTROLLER__B_UART__NONE_REVB 0
#define CONTROLLER__B_UART__EVEN_REVB 1
#define CONTROLLER__B_UART__ODD_REVB 2
#define CONTROLLER__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define CONTROLLER_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define CONTROLLER_NUMBER_OF_STOP_BITS    (1u)

#if (CONTROLLER_RXHW_ADDRESS_ENABLED)
    #define CONTROLLER_RX_ADDRESS_MODE    (0u)
    #define CONTROLLER_RX_HW_ADDRESS1     (0u)
    #define CONTROLLER_RX_HW_ADDRESS2     (0u)
#endif /* (CONTROLLER_RXHW_ADDRESS_ENABLED) */

#define CONTROLLER_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << CONTROLLER_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << CONTROLLER_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << CONTROLLER_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << CONTROLLER_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << CONTROLLER_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << CONTROLLER_RX_STS_BREAK_SHIFT) \
                                        | (0 << CONTROLLER_RX_STS_OVERRUN_SHIFT))

#define CONTROLLER_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << CONTROLLER_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << CONTROLLER_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << CONTROLLER_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << CONTROLLER_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef CONTROLLER_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define CONTROLLER_CONTROL_REG \
                            (* (reg8 *) CONTROLLER_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define CONTROLLER_CONTROL_PTR \
                            (  (reg8 *) CONTROLLER_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End CONTROLLER_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(CONTROLLER_TX_ENABLED)
    #define CONTROLLER_TXDATA_REG          (* (reg8 *) CONTROLLER_BUART_sTX_TxShifter_u0__F0_REG)
    #define CONTROLLER_TXDATA_PTR          (  (reg8 *) CONTROLLER_BUART_sTX_TxShifter_u0__F0_REG)
    #define CONTROLLER_TXDATA_AUX_CTL_REG  (* (reg8 *) CONTROLLER_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define CONTROLLER_TXDATA_AUX_CTL_PTR  (  (reg8 *) CONTROLLER_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define CONTROLLER_TXSTATUS_REG        (* (reg8 *) CONTROLLER_BUART_sTX_TxSts__STATUS_REG)
    #define CONTROLLER_TXSTATUS_PTR        (  (reg8 *) CONTROLLER_BUART_sTX_TxSts__STATUS_REG)
    #define CONTROLLER_TXSTATUS_MASK_REG   (* (reg8 *) CONTROLLER_BUART_sTX_TxSts__MASK_REG)
    #define CONTROLLER_TXSTATUS_MASK_PTR   (  (reg8 *) CONTROLLER_BUART_sTX_TxSts__MASK_REG)
    #define CONTROLLER_TXSTATUS_ACTL_REG   (* (reg8 *) CONTROLLER_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define CONTROLLER_TXSTATUS_ACTL_PTR   (  (reg8 *) CONTROLLER_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(CONTROLLER_TXCLKGEN_DP)
        #define CONTROLLER_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define CONTROLLER_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define CONTROLLER_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define CONTROLLER_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define CONTROLLER_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define CONTROLLER_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define CONTROLLER_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define CONTROLLER_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define CONTROLLER_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define CONTROLLER_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) CONTROLLER_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* CONTROLLER_TXCLKGEN_DP */

#endif /* End CONTROLLER_TX_ENABLED */

#if(CONTROLLER_HD_ENABLED)

    #define CONTROLLER_TXDATA_REG             (* (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__F1_REG )
    #define CONTROLLER_TXDATA_PTR             (  (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__F1_REG )
    #define CONTROLLER_TXDATA_AUX_CTL_REG     (* (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define CONTROLLER_TXDATA_AUX_CTL_PTR     (  (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define CONTROLLER_TXSTATUS_REG           (* (reg8 *) CONTROLLER_BUART_sRX_RxSts__STATUS_REG )
    #define CONTROLLER_TXSTATUS_PTR           (  (reg8 *) CONTROLLER_BUART_sRX_RxSts__STATUS_REG )
    #define CONTROLLER_TXSTATUS_MASK_REG      (* (reg8 *) CONTROLLER_BUART_sRX_RxSts__MASK_REG )
    #define CONTROLLER_TXSTATUS_MASK_PTR      (  (reg8 *) CONTROLLER_BUART_sRX_RxSts__MASK_REG )
    #define CONTROLLER_TXSTATUS_ACTL_REG      (* (reg8 *) CONTROLLER_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define CONTROLLER_TXSTATUS_ACTL_PTR      (  (reg8 *) CONTROLLER_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End CONTROLLER_HD_ENABLED */

#if( (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) )
    #define CONTROLLER_RXDATA_REG             (* (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__F0_REG )
    #define CONTROLLER_RXDATA_PTR             (  (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__F0_REG )
    #define CONTROLLER_RXADDRESS1_REG         (* (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__D0_REG )
    #define CONTROLLER_RXADDRESS1_PTR         (  (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__D0_REG )
    #define CONTROLLER_RXADDRESS2_REG         (* (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__D1_REG )
    #define CONTROLLER_RXADDRESS2_PTR         (  (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__D1_REG )
    #define CONTROLLER_RXDATA_AUX_CTL_REG     (* (reg8 *) CONTROLLER_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define CONTROLLER_RXBITCTR_PERIOD_REG    (* (reg8 *) CONTROLLER_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define CONTROLLER_RXBITCTR_PERIOD_PTR    (  (reg8 *) CONTROLLER_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define CONTROLLER_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) CONTROLLER_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define CONTROLLER_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) CONTROLLER_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define CONTROLLER_RXBITCTR_COUNTER_REG   (* (reg8 *) CONTROLLER_BUART_sRX_RxBitCounter__COUNT_REG )
    #define CONTROLLER_RXBITCTR_COUNTER_PTR   (  (reg8 *) CONTROLLER_BUART_sRX_RxBitCounter__COUNT_REG )

    #define CONTROLLER_RXSTATUS_REG           (* (reg8 *) CONTROLLER_BUART_sRX_RxSts__STATUS_REG )
    #define CONTROLLER_RXSTATUS_PTR           (  (reg8 *) CONTROLLER_BUART_sRX_RxSts__STATUS_REG )
    #define CONTROLLER_RXSTATUS_MASK_REG      (* (reg8 *) CONTROLLER_BUART_sRX_RxSts__MASK_REG )
    #define CONTROLLER_RXSTATUS_MASK_PTR      (  (reg8 *) CONTROLLER_BUART_sRX_RxSts__MASK_REG )
    #define CONTROLLER_RXSTATUS_ACTL_REG      (* (reg8 *) CONTROLLER_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define CONTROLLER_RXSTATUS_ACTL_PTR      (  (reg8 *) CONTROLLER_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) */

#if(CONTROLLER_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define CONTROLLER_INTCLOCK_CLKEN_REG     (* (reg8 *) CONTROLLER_IntClock__PM_ACT_CFG)
    #define CONTROLLER_INTCLOCK_CLKEN_PTR     (  (reg8 *) CONTROLLER_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define CONTROLLER_INTCLOCK_CLKEN_MASK    CONTROLLER_IntClock__PM_ACT_MSK
#endif /* End CONTROLLER_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(CONTROLLER_TX_ENABLED)
    #define CONTROLLER_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End CONTROLLER_TX_ENABLED */

#if(CONTROLLER_HD_ENABLED)
    #define CONTROLLER_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End CONTROLLER_HD_ENABLED */

#if( (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) )
    #define CONTROLLER_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define CONTROLLER_WAIT_1_MS      CONTROLLER_BL_CHK_DELAY_MS   

#define CONTROLLER_TXBUFFERSIZE   CONTROLLER_TX_BUFFER_SIZE
#define CONTROLLER_RXBUFFERSIZE   CONTROLLER_RX_BUFFER_SIZE

#if (CONTROLLER_RXHW_ADDRESS_ENABLED)
    #define CONTROLLER_RXADDRESSMODE  CONTROLLER_RX_ADDRESS_MODE
    #define CONTROLLER_RXHWADDRESS1   CONTROLLER_RX_HW_ADDRESS1
    #define CONTROLLER_RXHWADDRESS2   CONTROLLER_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define CONTROLLER_RXAddressMode  CONTROLLER_RXADDRESSMODE
#endif /* (CONTROLLER_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define CONTROLLER_initvar                    CONTROLLER_initVar

#define CONTROLLER_RX_Enabled                 CONTROLLER_RX_ENABLED
#define CONTROLLER_TX_Enabled                 CONTROLLER_TX_ENABLED
#define CONTROLLER_HD_Enabled                 CONTROLLER_HD_ENABLED
#define CONTROLLER_RX_IntInterruptEnabled     CONTROLLER_RX_INTERRUPT_ENABLED
#define CONTROLLER_TX_IntInterruptEnabled     CONTROLLER_TX_INTERRUPT_ENABLED
#define CONTROLLER_InternalClockUsed          CONTROLLER_INTERNAL_CLOCK_USED
#define CONTROLLER_RXHW_Address_Enabled       CONTROLLER_RXHW_ADDRESS_ENABLED
#define CONTROLLER_OverSampleCount            CONTROLLER_OVER_SAMPLE_COUNT
#define CONTROLLER_ParityType                 CONTROLLER_PARITY_TYPE

#if( CONTROLLER_TX_ENABLED && (CONTROLLER_TXBUFFERSIZE > CONTROLLER_FIFO_LENGTH))
    #define CONTROLLER_TXBUFFER               CONTROLLER_txBuffer
    #define CONTROLLER_TXBUFFERREAD           CONTROLLER_txBufferRead
    #define CONTROLLER_TXBUFFERWRITE          CONTROLLER_txBufferWrite
#endif /* End CONTROLLER_TX_ENABLED */
#if( ( CONTROLLER_RX_ENABLED || CONTROLLER_HD_ENABLED ) && \
     (CONTROLLER_RXBUFFERSIZE > CONTROLLER_FIFO_LENGTH) )
    #define CONTROLLER_RXBUFFER               CONTROLLER_rxBuffer
    #define CONTROLLER_RXBUFFERREAD           CONTROLLER_rxBufferRead
    #define CONTROLLER_RXBUFFERWRITE          CONTROLLER_rxBufferWrite
    #define CONTROLLER_RXBUFFERLOOPDETECT     CONTROLLER_rxBufferLoopDetect
    #define CONTROLLER_RXBUFFER_OVERFLOW      CONTROLLER_rxBufferOverflow
#endif /* End CONTROLLER_RX_ENABLED */

#ifdef CONTROLLER_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define CONTROLLER_CONTROL                CONTROLLER_CONTROL_REG
#endif /* End CONTROLLER_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(CONTROLLER_TX_ENABLED)
    #define CONTROLLER_TXDATA                 CONTROLLER_TXDATA_REG
    #define CONTROLLER_TXSTATUS               CONTROLLER_TXSTATUS_REG
    #define CONTROLLER_TXSTATUS_MASK          CONTROLLER_TXSTATUS_MASK_REG
    #define CONTROLLER_TXSTATUS_ACTL          CONTROLLER_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(CONTROLLER_TXCLKGEN_DP)
        #define CONTROLLER_TXBITCLKGEN_CTR        CONTROLLER_TXBITCLKGEN_CTR_REG
        #define CONTROLLER_TXBITCLKTX_COMPLETE    CONTROLLER_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define CONTROLLER_TXBITCTR_PERIOD        CONTROLLER_TXBITCTR_PERIOD_REG
        #define CONTROLLER_TXBITCTR_CONTROL       CONTROLLER_TXBITCTR_CONTROL_REG
        #define CONTROLLER_TXBITCTR_COUNTER       CONTROLLER_TXBITCTR_COUNTER_REG
    #endif /* CONTROLLER_TXCLKGEN_DP */
#endif /* End CONTROLLER_TX_ENABLED */

#if(CONTROLLER_HD_ENABLED)
    #define CONTROLLER_TXDATA                 CONTROLLER_TXDATA_REG
    #define CONTROLLER_TXSTATUS               CONTROLLER_TXSTATUS_REG
    #define CONTROLLER_TXSTATUS_MASK          CONTROLLER_TXSTATUS_MASK_REG
    #define CONTROLLER_TXSTATUS_ACTL          CONTROLLER_TXSTATUS_ACTL_REG
#endif /* End CONTROLLER_HD_ENABLED */

#if( (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) )
    #define CONTROLLER_RXDATA                 CONTROLLER_RXDATA_REG
    #define CONTROLLER_RXADDRESS1             CONTROLLER_RXADDRESS1_REG
    #define CONTROLLER_RXADDRESS2             CONTROLLER_RXADDRESS2_REG
    #define CONTROLLER_RXBITCTR_PERIOD        CONTROLLER_RXBITCTR_PERIOD_REG
    #define CONTROLLER_RXBITCTR_CONTROL       CONTROLLER_RXBITCTR_CONTROL_REG
    #define CONTROLLER_RXBITCTR_COUNTER       CONTROLLER_RXBITCTR_COUNTER_REG
    #define CONTROLLER_RXSTATUS               CONTROLLER_RXSTATUS_REG
    #define CONTROLLER_RXSTATUS_MASK          CONTROLLER_RXSTATUS_MASK_REG
    #define CONTROLLER_RXSTATUS_ACTL          CONTROLLER_RXSTATUS_ACTL_REG
#endif /* End  (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) */

#if(CONTROLLER_INTERNAL_CLOCK_USED)
    #define CONTROLLER_INTCLOCK_CLKEN         CONTROLLER_INTCLOCK_CLKEN_REG
#endif /* End CONTROLLER_INTERNAL_CLOCK_USED */

#define CONTROLLER_WAIT_FOR_COMLETE_REINIT    CONTROLLER_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_CONTROLLER_H */


/* [] END OF FILE */
