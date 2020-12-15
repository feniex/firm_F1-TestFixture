/*******************************************************************************
* File Name: SIREN.h
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


#if !defined(CY_UART_SIREN_H)
#define CY_UART_SIREN_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define SIREN_RX_ENABLED                     (1u)
#define SIREN_TX_ENABLED                     (1u)
#define SIREN_HD_ENABLED                     (0u)
#define SIREN_RX_INTERRUPT_ENABLED           (1u)
#define SIREN_TX_INTERRUPT_ENABLED           (0u)
#define SIREN_INTERNAL_CLOCK_USED            (1u)
#define SIREN_RXHW_ADDRESS_ENABLED           (0u)
#define SIREN_OVER_SAMPLE_COUNT              (8u)
#define SIREN_PARITY_TYPE                    (0u)
#define SIREN_PARITY_TYPE_SW                 (0u)
#define SIREN_BREAK_DETECT                   (0u)
#define SIREN_BREAK_BITS_TX                  (13u)
#define SIREN_BREAK_BITS_RX                  (13u)
#define SIREN_TXCLKGEN_DP                    (1u)
#define SIREN_USE23POLLING                   (1u)
#define SIREN_FLOW_CONTROL                   (0u)
#define SIREN_CLK_FREQ                       (0u)
#define SIREN_TX_BUFFER_SIZE                 (4u)
#define SIREN_RX_BUFFER_SIZE                 (512u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(SIREN_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define SIREN_CONTROL_REG_REMOVED            (0u)
#else
    #define SIREN_CONTROL_REG_REMOVED            (1u)
#endif /* End SIREN_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct SIREN_backupStruct_
{
    uint8 enableState;

    #if(SIREN_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End SIREN_CONTROL_REG_REMOVED */

} SIREN_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void SIREN_Start(void) ;
void SIREN_Stop(void) ;
uint8 SIREN_ReadControlRegister(void) ;
void SIREN_WriteControlRegister(uint8 control) ;

void SIREN_Init(void) ;
void SIREN_Enable(void) ;
void SIREN_SaveConfig(void) ;
void SIREN_RestoreConfig(void) ;
void SIREN_Sleep(void) ;
void SIREN_Wakeup(void) ;

/* Only if RX is enabled */
#if( (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) )

    #if (SIREN_RX_INTERRUPT_ENABLED)
        #define SIREN_EnableRxInt()  CyIntEnable (SIREN_RX_VECT_NUM)
        #define SIREN_DisableRxInt() CyIntDisable(SIREN_RX_VECT_NUM)
        CY_ISR_PROTO(SIREN_RXISR);
    #endif /* SIREN_RX_INTERRUPT_ENABLED */

    void SIREN_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void SIREN_SetRxAddress1(uint8 address) ;
    void SIREN_SetRxAddress2(uint8 address) ;

    void  SIREN_SetRxInterruptMode(uint8 intSrc) ;
    uint8 SIREN_ReadRxData(void) ;
    uint8 SIREN_ReadRxStatus(void) ;
    uint8 SIREN_GetChar(void) ;
    uint16 SIREN_GetByte(void) ;
    uint16 SIREN_GetRxBufferSize(void)
                                                            ;
    void SIREN_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define SIREN_GetRxInterruptSource   SIREN_ReadRxStatus

#endif /* End (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) */

/* Only if TX is enabled */
#if(SIREN_TX_ENABLED || SIREN_HD_ENABLED)

    #if(SIREN_TX_INTERRUPT_ENABLED)
        #define SIREN_EnableTxInt()  CyIntEnable (SIREN_TX_VECT_NUM)
        #define SIREN_DisableTxInt() CyIntDisable(SIREN_TX_VECT_NUM)
        #define SIREN_SetPendingTxInt() CyIntSetPending(SIREN_TX_VECT_NUM)
        #define SIREN_ClearPendingTxInt() CyIntClearPending(SIREN_TX_VECT_NUM)
        CY_ISR_PROTO(SIREN_TXISR);
    #endif /* SIREN_TX_INTERRUPT_ENABLED */

    void SIREN_SetTxInterruptMode(uint8 intSrc) ;
    void SIREN_WriteTxData(uint8 txDataByte) ;
    uint8 SIREN_ReadTxStatus(void) ;
    void SIREN_PutChar(uint8 txDataByte) ;
    void SIREN_PutString(const char8 string[]) ;
    void SIREN_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void SIREN_PutCRLF(uint8 txDataByte) ;
    void SIREN_ClearTxBuffer(void) ;
    void SIREN_SetTxAddressMode(uint8 addressMode) ;
    void SIREN_SendBreak(uint8 retMode) ;
    uint8 SIREN_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define SIREN_PutStringConst         SIREN_PutString
    #define SIREN_PutArrayConst          SIREN_PutArray
    #define SIREN_GetTxInterruptSource   SIREN_ReadTxStatus

#endif /* End SIREN_TX_ENABLED || SIREN_HD_ENABLED */

#if(SIREN_HD_ENABLED)
    void SIREN_LoadRxConfig(void) ;
    void SIREN_LoadTxConfig(void) ;
#endif /* End SIREN_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SIREN) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    SIREN_CyBtldrCommStart(void) CYSMALL ;
    void    SIREN_CyBtldrCommStop(void) CYSMALL ;
    void    SIREN_CyBtldrCommReset(void) CYSMALL ;
    cystatus SIREN_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus SIREN_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SIREN)
        #define CyBtldrCommStart    SIREN_CyBtldrCommStart
        #define CyBtldrCommStop     SIREN_CyBtldrCommStop
        #define CyBtldrCommReset    SIREN_CyBtldrCommReset
        #define CyBtldrCommWrite    SIREN_CyBtldrCommWrite
        #define CyBtldrCommRead     SIREN_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SIREN) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define SIREN_BYTE2BYTE_TIME_OUT (25u)
    #define SIREN_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define SIREN_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define SIREN_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define SIREN_SET_SPACE      (0x00u)
#define SIREN_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (SIREN_TX_ENABLED) || (SIREN_HD_ENABLED) )
    #if(SIREN_TX_INTERRUPT_ENABLED)
        #define SIREN_TX_VECT_NUM            (uint8)SIREN_TXInternalInterrupt__INTC_NUMBER
        #define SIREN_TX_PRIOR_NUM           (uint8)SIREN_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* SIREN_TX_INTERRUPT_ENABLED */

    #define SIREN_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define SIREN_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define SIREN_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(SIREN_TX_ENABLED)
        #define SIREN_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (SIREN_HD_ENABLED) */
        #define SIREN_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (SIREN_TX_ENABLED) */

    #define SIREN_TX_STS_COMPLETE            (uint8)(0x01u << SIREN_TX_STS_COMPLETE_SHIFT)
    #define SIREN_TX_STS_FIFO_EMPTY          (uint8)(0x01u << SIREN_TX_STS_FIFO_EMPTY_SHIFT)
    #define SIREN_TX_STS_FIFO_FULL           (uint8)(0x01u << SIREN_TX_STS_FIFO_FULL_SHIFT)
    #define SIREN_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << SIREN_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (SIREN_TX_ENABLED) || (SIREN_HD_ENABLED)*/

#if( (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) )
    #if(SIREN_RX_INTERRUPT_ENABLED)
        #define SIREN_RX_VECT_NUM            (uint8)SIREN_RXInternalInterrupt__INTC_NUMBER
        #define SIREN_RX_PRIOR_NUM           (uint8)SIREN_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* SIREN_RX_INTERRUPT_ENABLED */
    #define SIREN_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define SIREN_RX_STS_BREAK_SHIFT             (0x01u)
    #define SIREN_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define SIREN_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define SIREN_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define SIREN_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define SIREN_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define SIREN_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define SIREN_RX_STS_MRKSPC           (uint8)(0x01u << SIREN_RX_STS_MRKSPC_SHIFT)
    #define SIREN_RX_STS_BREAK            (uint8)(0x01u << SIREN_RX_STS_BREAK_SHIFT)
    #define SIREN_RX_STS_PAR_ERROR        (uint8)(0x01u << SIREN_RX_STS_PAR_ERROR_SHIFT)
    #define SIREN_RX_STS_STOP_ERROR       (uint8)(0x01u << SIREN_RX_STS_STOP_ERROR_SHIFT)
    #define SIREN_RX_STS_OVERRUN          (uint8)(0x01u << SIREN_RX_STS_OVERRUN_SHIFT)
    #define SIREN_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << SIREN_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define SIREN_RX_STS_ADDR_MATCH       (uint8)(0x01u << SIREN_RX_STS_ADDR_MATCH_SHIFT)
    #define SIREN_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << SIREN_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define SIREN_RX_HW_MASK                     (0x7Fu)
#endif /* End (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) */

/* Control Register definitions */
#define SIREN_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define SIREN_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define SIREN_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define SIREN_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define SIREN_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define SIREN_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define SIREN_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define SIREN_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define SIREN_CTRL_HD_SEND               (uint8)(0x01u << SIREN_CTRL_HD_SEND_SHIFT)
#define SIREN_CTRL_HD_SEND_BREAK         (uint8)(0x01u << SIREN_CTRL_HD_SEND_BREAK_SHIFT)
#define SIREN_CTRL_MARK                  (uint8)(0x01u << SIREN_CTRL_MARK_SHIFT)
#define SIREN_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << SIREN_CTRL_PARITY_TYPE0_SHIFT)
#define SIREN_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << SIREN_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define SIREN_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define SIREN_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define SIREN_SEND_BREAK                         (0x00u)
#define SIREN_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define SIREN_REINIT                             (0x02u)
#define SIREN_SEND_WAIT_REINIT                   (0x03u)

#define SIREN_OVER_SAMPLE_8                      (8u)
#define SIREN_OVER_SAMPLE_16                     (16u)

#define SIREN_BIT_CENTER                         (SIREN_OVER_SAMPLE_COUNT - 2u)

#define SIREN_FIFO_LENGTH                        (4u)
#define SIREN_NUMBER_OF_START_BIT                (1u)
#define SIREN_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define SIREN_TXBITCTR_BREAKBITS8X   ((SIREN_BREAK_BITS_TX * SIREN_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define SIREN_TXBITCTR_BREAKBITS ((SIREN_BREAK_BITS_TX * SIREN_OVER_SAMPLE_COUNT) - 1u)

#define SIREN_HALF_BIT_COUNT   \
                            (((SIREN_OVER_SAMPLE_COUNT / 2u) + (SIREN_USE23POLLING * 1u)) - 2u)
#if (SIREN_OVER_SAMPLE_COUNT == SIREN_OVER_SAMPLE_8)
    #define SIREN_HD_TXBITCTR_INIT   (((SIREN_BREAK_BITS_TX + \
                            SIREN_NUMBER_OF_START_BIT) * SIREN_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define SIREN_RXBITCTR_INIT  ((((SIREN_BREAK_BITS_RX + SIREN_NUMBER_OF_START_BIT) \
                            * SIREN_OVER_SAMPLE_COUNT) + SIREN_HALF_BIT_COUNT) - 1u)

#else /* SIREN_OVER_SAMPLE_COUNT == SIREN_OVER_SAMPLE_16 */
    #define SIREN_HD_TXBITCTR_INIT   ((8u * SIREN_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define SIREN_RXBITCTR_INIT      (((7u * SIREN_OVER_SAMPLE_COUNT) - 1u) + \
                                                      SIREN_HALF_BIT_COUNT)
#endif /* End SIREN_OVER_SAMPLE_COUNT */

#define SIREN_HD_RXBITCTR_INIT                   SIREN_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 SIREN_initVar;
#if (SIREN_TX_INTERRUPT_ENABLED && SIREN_TX_ENABLED)
    extern volatile uint8 SIREN_txBuffer[SIREN_TX_BUFFER_SIZE];
    extern volatile uint8 SIREN_txBufferRead;
    extern uint8 SIREN_txBufferWrite;
#endif /* (SIREN_TX_INTERRUPT_ENABLED && SIREN_TX_ENABLED) */
#if (SIREN_RX_INTERRUPT_ENABLED && (SIREN_RX_ENABLED || SIREN_HD_ENABLED))
    extern uint8 SIREN_errorStatus;
    extern volatile uint8 SIREN_rxBuffer[SIREN_RX_BUFFER_SIZE];
    extern volatile uint16 SIREN_rxBufferRead;
    extern volatile uint16 SIREN_rxBufferWrite;
    extern volatile uint8 SIREN_rxBufferLoopDetect;
    extern volatile uint8 SIREN_rxBufferOverflow;
    #if (SIREN_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 SIREN_rxAddressMode;
        extern volatile uint8 SIREN_rxAddressDetected;
    #endif /* (SIREN_RXHW_ADDRESS_ENABLED) */
#endif /* (SIREN_RX_INTERRUPT_ENABLED && (SIREN_RX_ENABLED || SIREN_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define SIREN__B_UART__AM_SW_BYTE_BYTE 1
#define SIREN__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define SIREN__B_UART__AM_HW_BYTE_BY_BYTE 3
#define SIREN__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define SIREN__B_UART__AM_NONE 0

#define SIREN__B_UART__NONE_REVB 0
#define SIREN__B_UART__EVEN_REVB 1
#define SIREN__B_UART__ODD_REVB 2
#define SIREN__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define SIREN_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define SIREN_NUMBER_OF_STOP_BITS    (1u)

#if (SIREN_RXHW_ADDRESS_ENABLED)
    #define SIREN_RX_ADDRESS_MODE    (0u)
    #define SIREN_RX_HW_ADDRESS1     (0u)
    #define SIREN_RX_HW_ADDRESS2     (0u)
#endif /* (SIREN_RXHW_ADDRESS_ENABLED) */

#define SIREN_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << SIREN_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << SIREN_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << SIREN_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << SIREN_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << SIREN_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << SIREN_RX_STS_BREAK_SHIFT) \
                                        | (0 << SIREN_RX_STS_OVERRUN_SHIFT))

#define SIREN_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << SIREN_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << SIREN_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << SIREN_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << SIREN_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef SIREN_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define SIREN_CONTROL_REG \
                            (* (reg8 *) SIREN_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define SIREN_CONTROL_PTR \
                            (  (reg8 *) SIREN_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End SIREN_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(SIREN_TX_ENABLED)
    #define SIREN_TXDATA_REG          (* (reg8 *) SIREN_BUART_sTX_TxShifter_u0__F0_REG)
    #define SIREN_TXDATA_PTR          (  (reg8 *) SIREN_BUART_sTX_TxShifter_u0__F0_REG)
    #define SIREN_TXDATA_AUX_CTL_REG  (* (reg8 *) SIREN_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define SIREN_TXDATA_AUX_CTL_PTR  (  (reg8 *) SIREN_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define SIREN_TXSTATUS_REG        (* (reg8 *) SIREN_BUART_sTX_TxSts__STATUS_REG)
    #define SIREN_TXSTATUS_PTR        (  (reg8 *) SIREN_BUART_sTX_TxSts__STATUS_REG)
    #define SIREN_TXSTATUS_MASK_REG   (* (reg8 *) SIREN_BUART_sTX_TxSts__MASK_REG)
    #define SIREN_TXSTATUS_MASK_PTR   (  (reg8 *) SIREN_BUART_sTX_TxSts__MASK_REG)
    #define SIREN_TXSTATUS_ACTL_REG   (* (reg8 *) SIREN_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define SIREN_TXSTATUS_ACTL_PTR   (  (reg8 *) SIREN_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(SIREN_TXCLKGEN_DP)
        #define SIREN_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define SIREN_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define SIREN_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define SIREN_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define SIREN_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define SIREN_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define SIREN_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define SIREN_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define SIREN_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define SIREN_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) SIREN_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* SIREN_TXCLKGEN_DP */

#endif /* End SIREN_TX_ENABLED */

#if(SIREN_HD_ENABLED)

    #define SIREN_TXDATA_REG             (* (reg8 *) SIREN_BUART_sRX_RxShifter_u0__F1_REG )
    #define SIREN_TXDATA_PTR             (  (reg8 *) SIREN_BUART_sRX_RxShifter_u0__F1_REG )
    #define SIREN_TXDATA_AUX_CTL_REG     (* (reg8 *) SIREN_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define SIREN_TXDATA_AUX_CTL_PTR     (  (reg8 *) SIREN_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define SIREN_TXSTATUS_REG           (* (reg8 *) SIREN_BUART_sRX_RxSts__STATUS_REG )
    #define SIREN_TXSTATUS_PTR           (  (reg8 *) SIREN_BUART_sRX_RxSts__STATUS_REG )
    #define SIREN_TXSTATUS_MASK_REG      (* (reg8 *) SIREN_BUART_sRX_RxSts__MASK_REG )
    #define SIREN_TXSTATUS_MASK_PTR      (  (reg8 *) SIREN_BUART_sRX_RxSts__MASK_REG )
    #define SIREN_TXSTATUS_ACTL_REG      (* (reg8 *) SIREN_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define SIREN_TXSTATUS_ACTL_PTR      (  (reg8 *) SIREN_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End SIREN_HD_ENABLED */

#if( (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) )
    #define SIREN_RXDATA_REG             (* (reg8 *) SIREN_BUART_sRX_RxShifter_u0__F0_REG )
    #define SIREN_RXDATA_PTR             (  (reg8 *) SIREN_BUART_sRX_RxShifter_u0__F0_REG )
    #define SIREN_RXADDRESS1_REG         (* (reg8 *) SIREN_BUART_sRX_RxShifter_u0__D0_REG )
    #define SIREN_RXADDRESS1_PTR         (  (reg8 *) SIREN_BUART_sRX_RxShifter_u0__D0_REG )
    #define SIREN_RXADDRESS2_REG         (* (reg8 *) SIREN_BUART_sRX_RxShifter_u0__D1_REG )
    #define SIREN_RXADDRESS2_PTR         (  (reg8 *) SIREN_BUART_sRX_RxShifter_u0__D1_REG )
    #define SIREN_RXDATA_AUX_CTL_REG     (* (reg8 *) SIREN_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define SIREN_RXBITCTR_PERIOD_REG    (* (reg8 *) SIREN_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define SIREN_RXBITCTR_PERIOD_PTR    (  (reg8 *) SIREN_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define SIREN_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) SIREN_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define SIREN_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) SIREN_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define SIREN_RXBITCTR_COUNTER_REG   (* (reg8 *) SIREN_BUART_sRX_RxBitCounter__COUNT_REG )
    #define SIREN_RXBITCTR_COUNTER_PTR   (  (reg8 *) SIREN_BUART_sRX_RxBitCounter__COUNT_REG )

    #define SIREN_RXSTATUS_REG           (* (reg8 *) SIREN_BUART_sRX_RxSts__STATUS_REG )
    #define SIREN_RXSTATUS_PTR           (  (reg8 *) SIREN_BUART_sRX_RxSts__STATUS_REG )
    #define SIREN_RXSTATUS_MASK_REG      (* (reg8 *) SIREN_BUART_sRX_RxSts__MASK_REG )
    #define SIREN_RXSTATUS_MASK_PTR      (  (reg8 *) SIREN_BUART_sRX_RxSts__MASK_REG )
    #define SIREN_RXSTATUS_ACTL_REG      (* (reg8 *) SIREN_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define SIREN_RXSTATUS_ACTL_PTR      (  (reg8 *) SIREN_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) */

#if(SIREN_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define SIREN_INTCLOCK_CLKEN_REG     (* (reg8 *) SIREN_IntClock__PM_ACT_CFG)
    #define SIREN_INTCLOCK_CLKEN_PTR     (  (reg8 *) SIREN_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define SIREN_INTCLOCK_CLKEN_MASK    SIREN_IntClock__PM_ACT_MSK
#endif /* End SIREN_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(SIREN_TX_ENABLED)
    #define SIREN_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End SIREN_TX_ENABLED */

#if(SIREN_HD_ENABLED)
    #define SIREN_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End SIREN_HD_ENABLED */

#if( (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) )
    #define SIREN_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define SIREN_WAIT_1_MS      SIREN_BL_CHK_DELAY_MS   

#define SIREN_TXBUFFERSIZE   SIREN_TX_BUFFER_SIZE
#define SIREN_RXBUFFERSIZE   SIREN_RX_BUFFER_SIZE

#if (SIREN_RXHW_ADDRESS_ENABLED)
    #define SIREN_RXADDRESSMODE  SIREN_RX_ADDRESS_MODE
    #define SIREN_RXHWADDRESS1   SIREN_RX_HW_ADDRESS1
    #define SIREN_RXHWADDRESS2   SIREN_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define SIREN_RXAddressMode  SIREN_RXADDRESSMODE
#endif /* (SIREN_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define SIREN_initvar                    SIREN_initVar

#define SIREN_RX_Enabled                 SIREN_RX_ENABLED
#define SIREN_TX_Enabled                 SIREN_TX_ENABLED
#define SIREN_HD_Enabled                 SIREN_HD_ENABLED
#define SIREN_RX_IntInterruptEnabled     SIREN_RX_INTERRUPT_ENABLED
#define SIREN_TX_IntInterruptEnabled     SIREN_TX_INTERRUPT_ENABLED
#define SIREN_InternalClockUsed          SIREN_INTERNAL_CLOCK_USED
#define SIREN_RXHW_Address_Enabled       SIREN_RXHW_ADDRESS_ENABLED
#define SIREN_OverSampleCount            SIREN_OVER_SAMPLE_COUNT
#define SIREN_ParityType                 SIREN_PARITY_TYPE

#if( SIREN_TX_ENABLED && (SIREN_TXBUFFERSIZE > SIREN_FIFO_LENGTH))
    #define SIREN_TXBUFFER               SIREN_txBuffer
    #define SIREN_TXBUFFERREAD           SIREN_txBufferRead
    #define SIREN_TXBUFFERWRITE          SIREN_txBufferWrite
#endif /* End SIREN_TX_ENABLED */
#if( ( SIREN_RX_ENABLED || SIREN_HD_ENABLED ) && \
     (SIREN_RXBUFFERSIZE > SIREN_FIFO_LENGTH) )
    #define SIREN_RXBUFFER               SIREN_rxBuffer
    #define SIREN_RXBUFFERREAD           SIREN_rxBufferRead
    #define SIREN_RXBUFFERWRITE          SIREN_rxBufferWrite
    #define SIREN_RXBUFFERLOOPDETECT     SIREN_rxBufferLoopDetect
    #define SIREN_RXBUFFER_OVERFLOW      SIREN_rxBufferOverflow
#endif /* End SIREN_RX_ENABLED */

#ifdef SIREN_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define SIREN_CONTROL                SIREN_CONTROL_REG
#endif /* End SIREN_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(SIREN_TX_ENABLED)
    #define SIREN_TXDATA                 SIREN_TXDATA_REG
    #define SIREN_TXSTATUS               SIREN_TXSTATUS_REG
    #define SIREN_TXSTATUS_MASK          SIREN_TXSTATUS_MASK_REG
    #define SIREN_TXSTATUS_ACTL          SIREN_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(SIREN_TXCLKGEN_DP)
        #define SIREN_TXBITCLKGEN_CTR        SIREN_TXBITCLKGEN_CTR_REG
        #define SIREN_TXBITCLKTX_COMPLETE    SIREN_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define SIREN_TXBITCTR_PERIOD        SIREN_TXBITCTR_PERIOD_REG
        #define SIREN_TXBITCTR_CONTROL       SIREN_TXBITCTR_CONTROL_REG
        #define SIREN_TXBITCTR_COUNTER       SIREN_TXBITCTR_COUNTER_REG
    #endif /* SIREN_TXCLKGEN_DP */
#endif /* End SIREN_TX_ENABLED */

#if(SIREN_HD_ENABLED)
    #define SIREN_TXDATA                 SIREN_TXDATA_REG
    #define SIREN_TXSTATUS               SIREN_TXSTATUS_REG
    #define SIREN_TXSTATUS_MASK          SIREN_TXSTATUS_MASK_REG
    #define SIREN_TXSTATUS_ACTL          SIREN_TXSTATUS_ACTL_REG
#endif /* End SIREN_HD_ENABLED */

#if( (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) )
    #define SIREN_RXDATA                 SIREN_RXDATA_REG
    #define SIREN_RXADDRESS1             SIREN_RXADDRESS1_REG
    #define SIREN_RXADDRESS2             SIREN_RXADDRESS2_REG
    #define SIREN_RXBITCTR_PERIOD        SIREN_RXBITCTR_PERIOD_REG
    #define SIREN_RXBITCTR_CONTROL       SIREN_RXBITCTR_CONTROL_REG
    #define SIREN_RXBITCTR_COUNTER       SIREN_RXBITCTR_COUNTER_REG
    #define SIREN_RXSTATUS               SIREN_RXSTATUS_REG
    #define SIREN_RXSTATUS_MASK          SIREN_RXSTATUS_MASK_REG
    #define SIREN_RXSTATUS_ACTL          SIREN_RXSTATUS_ACTL_REG
#endif /* End  (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) */

#if(SIREN_INTERNAL_CLOCK_USED)
    #define SIREN_INTCLOCK_CLKEN         SIREN_INTCLOCK_CLKEN_REG
#endif /* End SIREN_INTERNAL_CLOCK_USED */

#define SIREN_WAIT_FOR_COMLETE_REINIT    SIREN_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_SIREN_H */


/* [] END OF FILE */
