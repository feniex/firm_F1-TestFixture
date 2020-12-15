/*******************************************************************************
* File Name: QUAD_OBDII_AUDIO.h
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


#if !defined(CY_UART_QUAD_OBDII_AUDIO_H)
#define CY_UART_QUAD_OBDII_AUDIO_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define QUAD_OBDII_AUDIO_RX_ENABLED                     (1u)
#define QUAD_OBDII_AUDIO_TX_ENABLED                     (1u)
#define QUAD_OBDII_AUDIO_HD_ENABLED                     (0u)
#define QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED           (0u)
#define QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED           (0u)
#define QUAD_OBDII_AUDIO_INTERNAL_CLOCK_USED            (1u)
#define QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED           (0u)
#define QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT              (8u)
#define QUAD_OBDII_AUDIO_PARITY_TYPE                    (0u)
#define QUAD_OBDII_AUDIO_PARITY_TYPE_SW                 (0u)
#define QUAD_OBDII_AUDIO_BREAK_DETECT                   (0u)
#define QUAD_OBDII_AUDIO_BREAK_BITS_TX                  (13u)
#define QUAD_OBDII_AUDIO_BREAK_BITS_RX                  (13u)
#define QUAD_OBDII_AUDIO_TXCLKGEN_DP                    (1u)
#define QUAD_OBDII_AUDIO_USE23POLLING                   (1u)
#define QUAD_OBDII_AUDIO_FLOW_CONTROL                   (0u)
#define QUAD_OBDII_AUDIO_CLK_FREQ                       (0u)
#define QUAD_OBDII_AUDIO_TX_BUFFER_SIZE                 (4u)
#define QUAD_OBDII_AUDIO_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(QUAD_OBDII_AUDIO_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define QUAD_OBDII_AUDIO_CONTROL_REG_REMOVED            (0u)
#else
    #define QUAD_OBDII_AUDIO_CONTROL_REG_REMOVED            (1u)
#endif /* End QUAD_OBDII_AUDIO_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct QUAD_OBDII_AUDIO_backupStruct_
{
    uint8 enableState;

    #if(QUAD_OBDII_AUDIO_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End QUAD_OBDII_AUDIO_CONTROL_REG_REMOVED */

} QUAD_OBDII_AUDIO_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void QUAD_OBDII_AUDIO_Start(void) ;
void QUAD_OBDII_AUDIO_Stop(void) ;
uint8 QUAD_OBDII_AUDIO_ReadControlRegister(void) ;
void QUAD_OBDII_AUDIO_WriteControlRegister(uint8 control) ;

void QUAD_OBDII_AUDIO_Init(void) ;
void QUAD_OBDII_AUDIO_Enable(void) ;
void QUAD_OBDII_AUDIO_SaveConfig(void) ;
void QUAD_OBDII_AUDIO_RestoreConfig(void) ;
void QUAD_OBDII_AUDIO_Sleep(void) ;
void QUAD_OBDII_AUDIO_Wakeup(void) ;

/* Only if RX is enabled */
#if( (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) )

    #if (QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED)
        #define QUAD_OBDII_AUDIO_EnableRxInt()  CyIntEnable (QUAD_OBDII_AUDIO_RX_VECT_NUM)
        #define QUAD_OBDII_AUDIO_DisableRxInt() CyIntDisable(QUAD_OBDII_AUDIO_RX_VECT_NUM)
        CY_ISR_PROTO(QUAD_OBDII_AUDIO_RXISR);
    #endif /* QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED */

    void QUAD_OBDII_AUDIO_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void QUAD_OBDII_AUDIO_SetRxAddress1(uint8 address) ;
    void QUAD_OBDII_AUDIO_SetRxAddress2(uint8 address) ;

    void  QUAD_OBDII_AUDIO_SetRxInterruptMode(uint8 intSrc) ;
    uint8 QUAD_OBDII_AUDIO_ReadRxData(void) ;
    uint8 QUAD_OBDII_AUDIO_ReadRxStatus(void) ;
    uint8 QUAD_OBDII_AUDIO_GetChar(void) ;
    uint16 QUAD_OBDII_AUDIO_GetByte(void) ;
    uint8 QUAD_OBDII_AUDIO_GetRxBufferSize(void)
                                                            ;
    void QUAD_OBDII_AUDIO_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define QUAD_OBDII_AUDIO_GetRxInterruptSource   QUAD_OBDII_AUDIO_ReadRxStatus

#endif /* End (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) */

/* Only if TX is enabled */
#if(QUAD_OBDII_AUDIO_TX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED)

    #if(QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED)
        #define QUAD_OBDII_AUDIO_EnableTxInt()  CyIntEnable (QUAD_OBDII_AUDIO_TX_VECT_NUM)
        #define QUAD_OBDII_AUDIO_DisableTxInt() CyIntDisable(QUAD_OBDII_AUDIO_TX_VECT_NUM)
        #define QUAD_OBDII_AUDIO_SetPendingTxInt() CyIntSetPending(QUAD_OBDII_AUDIO_TX_VECT_NUM)
        #define QUAD_OBDII_AUDIO_ClearPendingTxInt() CyIntClearPending(QUAD_OBDII_AUDIO_TX_VECT_NUM)
        CY_ISR_PROTO(QUAD_OBDII_AUDIO_TXISR);
    #endif /* QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED */

    void QUAD_OBDII_AUDIO_SetTxInterruptMode(uint8 intSrc) ;
    void QUAD_OBDII_AUDIO_WriteTxData(uint8 txDataByte) ;
    uint8 QUAD_OBDII_AUDIO_ReadTxStatus(void) ;
    void QUAD_OBDII_AUDIO_PutChar(uint8 txDataByte) ;
    void QUAD_OBDII_AUDIO_PutString(const char8 string[]) ;
    void QUAD_OBDII_AUDIO_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void QUAD_OBDII_AUDIO_PutCRLF(uint8 txDataByte) ;
    void QUAD_OBDII_AUDIO_ClearTxBuffer(void) ;
    void QUAD_OBDII_AUDIO_SetTxAddressMode(uint8 addressMode) ;
    void QUAD_OBDII_AUDIO_SendBreak(uint8 retMode) ;
    uint8 QUAD_OBDII_AUDIO_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define QUAD_OBDII_AUDIO_PutStringConst         QUAD_OBDII_AUDIO_PutString
    #define QUAD_OBDII_AUDIO_PutArrayConst          QUAD_OBDII_AUDIO_PutArray
    #define QUAD_OBDII_AUDIO_GetTxInterruptSource   QUAD_OBDII_AUDIO_ReadTxStatus

#endif /* End QUAD_OBDII_AUDIO_TX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED */

#if(QUAD_OBDII_AUDIO_HD_ENABLED)
    void QUAD_OBDII_AUDIO_LoadRxConfig(void) ;
    void QUAD_OBDII_AUDIO_LoadTxConfig(void) ;
#endif /* End QUAD_OBDII_AUDIO_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_QUAD_OBDII_AUDIO) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    QUAD_OBDII_AUDIO_CyBtldrCommStart(void) CYSMALL ;
    void    QUAD_OBDII_AUDIO_CyBtldrCommStop(void) CYSMALL ;
    void    QUAD_OBDII_AUDIO_CyBtldrCommReset(void) CYSMALL ;
    cystatus QUAD_OBDII_AUDIO_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus QUAD_OBDII_AUDIO_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_QUAD_OBDII_AUDIO)
        #define CyBtldrCommStart    QUAD_OBDII_AUDIO_CyBtldrCommStart
        #define CyBtldrCommStop     QUAD_OBDII_AUDIO_CyBtldrCommStop
        #define CyBtldrCommReset    QUAD_OBDII_AUDIO_CyBtldrCommReset
        #define CyBtldrCommWrite    QUAD_OBDII_AUDIO_CyBtldrCommWrite
        #define CyBtldrCommRead     QUAD_OBDII_AUDIO_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_QUAD_OBDII_AUDIO) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define QUAD_OBDII_AUDIO_BYTE2BYTE_TIME_OUT (25u)
    #define QUAD_OBDII_AUDIO_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define QUAD_OBDII_AUDIO_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define QUAD_OBDII_AUDIO_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define QUAD_OBDII_AUDIO_SET_SPACE      (0x00u)
#define QUAD_OBDII_AUDIO_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (QUAD_OBDII_AUDIO_TX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) )
    #if(QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED)
        #define QUAD_OBDII_AUDIO_TX_VECT_NUM            (uint8)QUAD_OBDII_AUDIO_TXInternalInterrupt__INTC_NUMBER
        #define QUAD_OBDII_AUDIO_TX_PRIOR_NUM           (uint8)QUAD_OBDII_AUDIO_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED */

    #define QUAD_OBDII_AUDIO_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define QUAD_OBDII_AUDIO_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define QUAD_OBDII_AUDIO_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(QUAD_OBDII_AUDIO_TX_ENABLED)
        #define QUAD_OBDII_AUDIO_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (QUAD_OBDII_AUDIO_HD_ENABLED) */
        #define QUAD_OBDII_AUDIO_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (QUAD_OBDII_AUDIO_TX_ENABLED) */

    #define QUAD_OBDII_AUDIO_TX_STS_COMPLETE            (uint8)(0x01u << QUAD_OBDII_AUDIO_TX_STS_COMPLETE_SHIFT)
    #define QUAD_OBDII_AUDIO_TX_STS_FIFO_EMPTY          (uint8)(0x01u << QUAD_OBDII_AUDIO_TX_STS_FIFO_EMPTY_SHIFT)
    #define QUAD_OBDII_AUDIO_TX_STS_FIFO_FULL           (uint8)(0x01u << QUAD_OBDII_AUDIO_TX_STS_FIFO_FULL_SHIFT)
    #define QUAD_OBDII_AUDIO_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << QUAD_OBDII_AUDIO_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (QUAD_OBDII_AUDIO_TX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED)*/

#if( (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) )
    #if(QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED)
        #define QUAD_OBDII_AUDIO_RX_VECT_NUM            (uint8)QUAD_OBDII_AUDIO_RXInternalInterrupt__INTC_NUMBER
        #define QUAD_OBDII_AUDIO_RX_PRIOR_NUM           (uint8)QUAD_OBDII_AUDIO_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED */
    #define QUAD_OBDII_AUDIO_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define QUAD_OBDII_AUDIO_RX_STS_BREAK_SHIFT             (0x01u)
    #define QUAD_OBDII_AUDIO_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define QUAD_OBDII_AUDIO_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define QUAD_OBDII_AUDIO_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define QUAD_OBDII_AUDIO_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define QUAD_OBDII_AUDIO_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define QUAD_OBDII_AUDIO_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define QUAD_OBDII_AUDIO_RX_STS_MRKSPC           (uint8)(0x01u << QUAD_OBDII_AUDIO_RX_STS_MRKSPC_SHIFT)
    #define QUAD_OBDII_AUDIO_RX_STS_BREAK            (uint8)(0x01u << QUAD_OBDII_AUDIO_RX_STS_BREAK_SHIFT)
    #define QUAD_OBDII_AUDIO_RX_STS_PAR_ERROR        (uint8)(0x01u << QUAD_OBDII_AUDIO_RX_STS_PAR_ERROR_SHIFT)
    #define QUAD_OBDII_AUDIO_RX_STS_STOP_ERROR       (uint8)(0x01u << QUAD_OBDII_AUDIO_RX_STS_STOP_ERROR_SHIFT)
    #define QUAD_OBDII_AUDIO_RX_STS_OVERRUN          (uint8)(0x01u << QUAD_OBDII_AUDIO_RX_STS_OVERRUN_SHIFT)
    #define QUAD_OBDII_AUDIO_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << QUAD_OBDII_AUDIO_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define QUAD_OBDII_AUDIO_RX_STS_ADDR_MATCH       (uint8)(0x01u << QUAD_OBDII_AUDIO_RX_STS_ADDR_MATCH_SHIFT)
    #define QUAD_OBDII_AUDIO_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << QUAD_OBDII_AUDIO_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define QUAD_OBDII_AUDIO_RX_HW_MASK                     (0x7Fu)
#endif /* End (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) */

/* Control Register definitions */
#define QUAD_OBDII_AUDIO_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define QUAD_OBDII_AUDIO_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define QUAD_OBDII_AUDIO_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define QUAD_OBDII_AUDIO_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define QUAD_OBDII_AUDIO_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define QUAD_OBDII_AUDIO_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define QUAD_OBDII_AUDIO_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define QUAD_OBDII_AUDIO_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define QUAD_OBDII_AUDIO_CTRL_HD_SEND               (uint8)(0x01u << QUAD_OBDII_AUDIO_CTRL_HD_SEND_SHIFT)
#define QUAD_OBDII_AUDIO_CTRL_HD_SEND_BREAK         (uint8)(0x01u << QUAD_OBDII_AUDIO_CTRL_HD_SEND_BREAK_SHIFT)
#define QUAD_OBDII_AUDIO_CTRL_MARK                  (uint8)(0x01u << QUAD_OBDII_AUDIO_CTRL_MARK_SHIFT)
#define QUAD_OBDII_AUDIO_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << QUAD_OBDII_AUDIO_CTRL_PARITY_TYPE0_SHIFT)
#define QUAD_OBDII_AUDIO_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << QUAD_OBDII_AUDIO_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define QUAD_OBDII_AUDIO_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define QUAD_OBDII_AUDIO_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define QUAD_OBDII_AUDIO_SEND_BREAK                         (0x00u)
#define QUAD_OBDII_AUDIO_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define QUAD_OBDII_AUDIO_REINIT                             (0x02u)
#define QUAD_OBDII_AUDIO_SEND_WAIT_REINIT                   (0x03u)

#define QUAD_OBDII_AUDIO_OVER_SAMPLE_8                      (8u)
#define QUAD_OBDII_AUDIO_OVER_SAMPLE_16                     (16u)

#define QUAD_OBDII_AUDIO_BIT_CENTER                         (QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT - 2u)

#define QUAD_OBDII_AUDIO_FIFO_LENGTH                        (4u)
#define QUAD_OBDII_AUDIO_NUMBER_OF_START_BIT                (1u)
#define QUAD_OBDII_AUDIO_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define QUAD_OBDII_AUDIO_TXBITCTR_BREAKBITS8X   ((QUAD_OBDII_AUDIO_BREAK_BITS_TX * QUAD_OBDII_AUDIO_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define QUAD_OBDII_AUDIO_TXBITCTR_BREAKBITS ((QUAD_OBDII_AUDIO_BREAK_BITS_TX * QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT) - 1u)

#define QUAD_OBDII_AUDIO_HALF_BIT_COUNT   \
                            (((QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT / 2u) + (QUAD_OBDII_AUDIO_USE23POLLING * 1u)) - 2u)
#if (QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT == QUAD_OBDII_AUDIO_OVER_SAMPLE_8)
    #define QUAD_OBDII_AUDIO_HD_TXBITCTR_INIT   (((QUAD_OBDII_AUDIO_BREAK_BITS_TX + \
                            QUAD_OBDII_AUDIO_NUMBER_OF_START_BIT) * QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define QUAD_OBDII_AUDIO_RXBITCTR_INIT  ((((QUAD_OBDII_AUDIO_BREAK_BITS_RX + QUAD_OBDII_AUDIO_NUMBER_OF_START_BIT) \
                            * QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT) + QUAD_OBDII_AUDIO_HALF_BIT_COUNT) - 1u)

#else /* QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT == QUAD_OBDII_AUDIO_OVER_SAMPLE_16 */
    #define QUAD_OBDII_AUDIO_HD_TXBITCTR_INIT   ((8u * QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define QUAD_OBDII_AUDIO_RXBITCTR_INIT      (((7u * QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT) - 1u) + \
                                                      QUAD_OBDII_AUDIO_HALF_BIT_COUNT)
#endif /* End QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT */

#define QUAD_OBDII_AUDIO_HD_RXBITCTR_INIT                   QUAD_OBDII_AUDIO_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 QUAD_OBDII_AUDIO_initVar;
#if (QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED && QUAD_OBDII_AUDIO_TX_ENABLED)
    extern volatile uint8 QUAD_OBDII_AUDIO_txBuffer[QUAD_OBDII_AUDIO_TX_BUFFER_SIZE];
    extern volatile uint8 QUAD_OBDII_AUDIO_txBufferRead;
    extern uint8 QUAD_OBDII_AUDIO_txBufferWrite;
#endif /* (QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED && QUAD_OBDII_AUDIO_TX_ENABLED) */
#if (QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED && (QUAD_OBDII_AUDIO_RX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED))
    extern uint8 QUAD_OBDII_AUDIO_errorStatus;
    extern volatile uint8 QUAD_OBDII_AUDIO_rxBuffer[QUAD_OBDII_AUDIO_RX_BUFFER_SIZE];
    extern volatile uint8 QUAD_OBDII_AUDIO_rxBufferRead;
    extern volatile uint8 QUAD_OBDII_AUDIO_rxBufferWrite;
    extern volatile uint8 QUAD_OBDII_AUDIO_rxBufferLoopDetect;
    extern volatile uint8 QUAD_OBDII_AUDIO_rxBufferOverflow;
    #if (QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 QUAD_OBDII_AUDIO_rxAddressMode;
        extern volatile uint8 QUAD_OBDII_AUDIO_rxAddressDetected;
    #endif /* (QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED) */
#endif /* (QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED && (QUAD_OBDII_AUDIO_RX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define QUAD_OBDII_AUDIO__B_UART__AM_SW_BYTE_BYTE 1
#define QUAD_OBDII_AUDIO__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define QUAD_OBDII_AUDIO__B_UART__AM_HW_BYTE_BY_BYTE 3
#define QUAD_OBDII_AUDIO__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define QUAD_OBDII_AUDIO__B_UART__AM_NONE 0

#define QUAD_OBDII_AUDIO__B_UART__NONE_REVB 0
#define QUAD_OBDII_AUDIO__B_UART__EVEN_REVB 1
#define QUAD_OBDII_AUDIO__B_UART__ODD_REVB 2
#define QUAD_OBDII_AUDIO__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define QUAD_OBDII_AUDIO_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define QUAD_OBDII_AUDIO_NUMBER_OF_STOP_BITS    (1u)

#if (QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED)
    #define QUAD_OBDII_AUDIO_RX_ADDRESS_MODE    (0u)
    #define QUAD_OBDII_AUDIO_RX_HW_ADDRESS1     (0u)
    #define QUAD_OBDII_AUDIO_RX_HW_ADDRESS2     (0u)
#endif /* (QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED) */

#define QUAD_OBDII_AUDIO_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << QUAD_OBDII_AUDIO_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_RX_STS_BREAK_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_RX_STS_OVERRUN_SHIFT))

#define QUAD_OBDII_AUDIO_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << QUAD_OBDII_AUDIO_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << QUAD_OBDII_AUDIO_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef QUAD_OBDII_AUDIO_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define QUAD_OBDII_AUDIO_CONTROL_REG \
                            (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define QUAD_OBDII_AUDIO_CONTROL_PTR \
                            (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End QUAD_OBDII_AUDIO_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(QUAD_OBDII_AUDIO_TX_ENABLED)
    #define QUAD_OBDII_AUDIO_TXDATA_REG          (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxShifter_u0__F0_REG)
    #define QUAD_OBDII_AUDIO_TXDATA_PTR          (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxShifter_u0__F0_REG)
    #define QUAD_OBDII_AUDIO_TXDATA_AUX_CTL_REG  (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define QUAD_OBDII_AUDIO_TXDATA_AUX_CTL_PTR  (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define QUAD_OBDII_AUDIO_TXSTATUS_REG        (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxSts__STATUS_REG)
    #define QUAD_OBDII_AUDIO_TXSTATUS_PTR        (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxSts__STATUS_REG)
    #define QUAD_OBDII_AUDIO_TXSTATUS_MASK_REG   (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxSts__MASK_REG)
    #define QUAD_OBDII_AUDIO_TXSTATUS_MASK_PTR   (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxSts__MASK_REG)
    #define QUAD_OBDII_AUDIO_TXSTATUS_ACTL_REG   (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define QUAD_OBDII_AUDIO_TXSTATUS_ACTL_PTR   (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(QUAD_OBDII_AUDIO_TXCLKGEN_DP)
        #define QUAD_OBDII_AUDIO_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define QUAD_OBDII_AUDIO_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define QUAD_OBDII_AUDIO_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define QUAD_OBDII_AUDIO_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define QUAD_OBDII_AUDIO_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define QUAD_OBDII_AUDIO_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define QUAD_OBDII_AUDIO_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define QUAD_OBDII_AUDIO_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define QUAD_OBDII_AUDIO_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define QUAD_OBDII_AUDIO_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* QUAD_OBDII_AUDIO_TXCLKGEN_DP */

#endif /* End QUAD_OBDII_AUDIO_TX_ENABLED */

#if(QUAD_OBDII_AUDIO_HD_ENABLED)

    #define QUAD_OBDII_AUDIO_TXDATA_REG             (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__F1_REG )
    #define QUAD_OBDII_AUDIO_TXDATA_PTR             (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__F1_REG )
    #define QUAD_OBDII_AUDIO_TXDATA_AUX_CTL_REG     (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define QUAD_OBDII_AUDIO_TXDATA_AUX_CTL_PTR     (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define QUAD_OBDII_AUDIO_TXSTATUS_REG           (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__STATUS_REG )
    #define QUAD_OBDII_AUDIO_TXSTATUS_PTR           (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__STATUS_REG )
    #define QUAD_OBDII_AUDIO_TXSTATUS_MASK_REG      (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__MASK_REG )
    #define QUAD_OBDII_AUDIO_TXSTATUS_MASK_PTR      (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__MASK_REG )
    #define QUAD_OBDII_AUDIO_TXSTATUS_ACTL_REG      (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define QUAD_OBDII_AUDIO_TXSTATUS_ACTL_PTR      (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End QUAD_OBDII_AUDIO_HD_ENABLED */

#if( (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) )
    #define QUAD_OBDII_AUDIO_RXDATA_REG             (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__F0_REG )
    #define QUAD_OBDII_AUDIO_RXDATA_PTR             (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__F0_REG )
    #define QUAD_OBDII_AUDIO_RXADDRESS1_REG         (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__D0_REG )
    #define QUAD_OBDII_AUDIO_RXADDRESS1_PTR         (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__D0_REG )
    #define QUAD_OBDII_AUDIO_RXADDRESS2_REG         (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__D1_REG )
    #define QUAD_OBDII_AUDIO_RXADDRESS2_PTR         (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__D1_REG )
    #define QUAD_OBDII_AUDIO_RXDATA_AUX_CTL_REG     (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define QUAD_OBDII_AUDIO_RXBITCTR_PERIOD_REG    (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define QUAD_OBDII_AUDIO_RXBITCTR_PERIOD_PTR    (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define QUAD_OBDII_AUDIO_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define QUAD_OBDII_AUDIO_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define QUAD_OBDII_AUDIO_RXBITCTR_COUNTER_REG   (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxBitCounter__COUNT_REG )
    #define QUAD_OBDII_AUDIO_RXBITCTR_COUNTER_PTR   (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxBitCounter__COUNT_REG )

    #define QUAD_OBDII_AUDIO_RXSTATUS_REG           (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__STATUS_REG )
    #define QUAD_OBDII_AUDIO_RXSTATUS_PTR           (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__STATUS_REG )
    #define QUAD_OBDII_AUDIO_RXSTATUS_MASK_REG      (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__MASK_REG )
    #define QUAD_OBDII_AUDIO_RXSTATUS_MASK_PTR      (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__MASK_REG )
    #define QUAD_OBDII_AUDIO_RXSTATUS_ACTL_REG      (* (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define QUAD_OBDII_AUDIO_RXSTATUS_ACTL_PTR      (  (reg8 *) QUAD_OBDII_AUDIO_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) */

#if(QUAD_OBDII_AUDIO_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define QUAD_OBDII_AUDIO_INTCLOCK_CLKEN_REG     (* (reg8 *) QUAD_OBDII_AUDIO_IntClock__PM_ACT_CFG)
    #define QUAD_OBDII_AUDIO_INTCLOCK_CLKEN_PTR     (  (reg8 *) QUAD_OBDII_AUDIO_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define QUAD_OBDII_AUDIO_INTCLOCK_CLKEN_MASK    QUAD_OBDII_AUDIO_IntClock__PM_ACT_MSK
#endif /* End QUAD_OBDII_AUDIO_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(QUAD_OBDII_AUDIO_TX_ENABLED)
    #define QUAD_OBDII_AUDIO_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End QUAD_OBDII_AUDIO_TX_ENABLED */

#if(QUAD_OBDII_AUDIO_HD_ENABLED)
    #define QUAD_OBDII_AUDIO_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End QUAD_OBDII_AUDIO_HD_ENABLED */

#if( (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) )
    #define QUAD_OBDII_AUDIO_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define QUAD_OBDII_AUDIO_WAIT_1_MS      QUAD_OBDII_AUDIO_BL_CHK_DELAY_MS   

#define QUAD_OBDII_AUDIO_TXBUFFERSIZE   QUAD_OBDII_AUDIO_TX_BUFFER_SIZE
#define QUAD_OBDII_AUDIO_RXBUFFERSIZE   QUAD_OBDII_AUDIO_RX_BUFFER_SIZE

#if (QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED)
    #define QUAD_OBDII_AUDIO_RXADDRESSMODE  QUAD_OBDII_AUDIO_RX_ADDRESS_MODE
    #define QUAD_OBDII_AUDIO_RXHWADDRESS1   QUAD_OBDII_AUDIO_RX_HW_ADDRESS1
    #define QUAD_OBDII_AUDIO_RXHWADDRESS2   QUAD_OBDII_AUDIO_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define QUAD_OBDII_AUDIO_RXAddressMode  QUAD_OBDII_AUDIO_RXADDRESSMODE
#endif /* (QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define QUAD_OBDII_AUDIO_initvar                    QUAD_OBDII_AUDIO_initVar

#define QUAD_OBDII_AUDIO_RX_Enabled                 QUAD_OBDII_AUDIO_RX_ENABLED
#define QUAD_OBDII_AUDIO_TX_Enabled                 QUAD_OBDII_AUDIO_TX_ENABLED
#define QUAD_OBDII_AUDIO_HD_Enabled                 QUAD_OBDII_AUDIO_HD_ENABLED
#define QUAD_OBDII_AUDIO_RX_IntInterruptEnabled     QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED
#define QUAD_OBDII_AUDIO_TX_IntInterruptEnabled     QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED
#define QUAD_OBDII_AUDIO_InternalClockUsed          QUAD_OBDII_AUDIO_INTERNAL_CLOCK_USED
#define QUAD_OBDII_AUDIO_RXHW_Address_Enabled       QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED
#define QUAD_OBDII_AUDIO_OverSampleCount            QUAD_OBDII_AUDIO_OVER_SAMPLE_COUNT
#define QUAD_OBDII_AUDIO_ParityType                 QUAD_OBDII_AUDIO_PARITY_TYPE

#if( QUAD_OBDII_AUDIO_TX_ENABLED && (QUAD_OBDII_AUDIO_TXBUFFERSIZE > QUAD_OBDII_AUDIO_FIFO_LENGTH))
    #define QUAD_OBDII_AUDIO_TXBUFFER               QUAD_OBDII_AUDIO_txBuffer
    #define QUAD_OBDII_AUDIO_TXBUFFERREAD           QUAD_OBDII_AUDIO_txBufferRead
    #define QUAD_OBDII_AUDIO_TXBUFFERWRITE          QUAD_OBDII_AUDIO_txBufferWrite
#endif /* End QUAD_OBDII_AUDIO_TX_ENABLED */
#if( ( QUAD_OBDII_AUDIO_RX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED ) && \
     (QUAD_OBDII_AUDIO_RXBUFFERSIZE > QUAD_OBDII_AUDIO_FIFO_LENGTH) )
    #define QUAD_OBDII_AUDIO_RXBUFFER               QUAD_OBDII_AUDIO_rxBuffer
    #define QUAD_OBDII_AUDIO_RXBUFFERREAD           QUAD_OBDII_AUDIO_rxBufferRead
    #define QUAD_OBDII_AUDIO_RXBUFFERWRITE          QUAD_OBDII_AUDIO_rxBufferWrite
    #define QUAD_OBDII_AUDIO_RXBUFFERLOOPDETECT     QUAD_OBDII_AUDIO_rxBufferLoopDetect
    #define QUAD_OBDII_AUDIO_RXBUFFER_OVERFLOW      QUAD_OBDII_AUDIO_rxBufferOverflow
#endif /* End QUAD_OBDII_AUDIO_RX_ENABLED */

#ifdef QUAD_OBDII_AUDIO_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define QUAD_OBDII_AUDIO_CONTROL                QUAD_OBDII_AUDIO_CONTROL_REG
#endif /* End QUAD_OBDII_AUDIO_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(QUAD_OBDII_AUDIO_TX_ENABLED)
    #define QUAD_OBDII_AUDIO_TXDATA                 QUAD_OBDII_AUDIO_TXDATA_REG
    #define QUAD_OBDII_AUDIO_TXSTATUS               QUAD_OBDII_AUDIO_TXSTATUS_REG
    #define QUAD_OBDII_AUDIO_TXSTATUS_MASK          QUAD_OBDII_AUDIO_TXSTATUS_MASK_REG
    #define QUAD_OBDII_AUDIO_TXSTATUS_ACTL          QUAD_OBDII_AUDIO_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(QUAD_OBDII_AUDIO_TXCLKGEN_DP)
        #define QUAD_OBDII_AUDIO_TXBITCLKGEN_CTR        QUAD_OBDII_AUDIO_TXBITCLKGEN_CTR_REG
        #define QUAD_OBDII_AUDIO_TXBITCLKTX_COMPLETE    QUAD_OBDII_AUDIO_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define QUAD_OBDII_AUDIO_TXBITCTR_PERIOD        QUAD_OBDII_AUDIO_TXBITCTR_PERIOD_REG
        #define QUAD_OBDII_AUDIO_TXBITCTR_CONTROL       QUAD_OBDII_AUDIO_TXBITCTR_CONTROL_REG
        #define QUAD_OBDII_AUDIO_TXBITCTR_COUNTER       QUAD_OBDII_AUDIO_TXBITCTR_COUNTER_REG
    #endif /* QUAD_OBDII_AUDIO_TXCLKGEN_DP */
#endif /* End QUAD_OBDII_AUDIO_TX_ENABLED */

#if(QUAD_OBDII_AUDIO_HD_ENABLED)
    #define QUAD_OBDII_AUDIO_TXDATA                 QUAD_OBDII_AUDIO_TXDATA_REG
    #define QUAD_OBDII_AUDIO_TXSTATUS               QUAD_OBDII_AUDIO_TXSTATUS_REG
    #define QUAD_OBDII_AUDIO_TXSTATUS_MASK          QUAD_OBDII_AUDIO_TXSTATUS_MASK_REG
    #define QUAD_OBDII_AUDIO_TXSTATUS_ACTL          QUAD_OBDII_AUDIO_TXSTATUS_ACTL_REG
#endif /* End QUAD_OBDII_AUDIO_HD_ENABLED */

#if( (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) )
    #define QUAD_OBDII_AUDIO_RXDATA                 QUAD_OBDII_AUDIO_RXDATA_REG
    #define QUAD_OBDII_AUDIO_RXADDRESS1             QUAD_OBDII_AUDIO_RXADDRESS1_REG
    #define QUAD_OBDII_AUDIO_RXADDRESS2             QUAD_OBDII_AUDIO_RXADDRESS2_REG
    #define QUAD_OBDII_AUDIO_RXBITCTR_PERIOD        QUAD_OBDII_AUDIO_RXBITCTR_PERIOD_REG
    #define QUAD_OBDII_AUDIO_RXBITCTR_CONTROL       QUAD_OBDII_AUDIO_RXBITCTR_CONTROL_REG
    #define QUAD_OBDII_AUDIO_RXBITCTR_COUNTER       QUAD_OBDII_AUDIO_RXBITCTR_COUNTER_REG
    #define QUAD_OBDII_AUDIO_RXSTATUS               QUAD_OBDII_AUDIO_RXSTATUS_REG
    #define QUAD_OBDII_AUDIO_RXSTATUS_MASK          QUAD_OBDII_AUDIO_RXSTATUS_MASK_REG
    #define QUAD_OBDII_AUDIO_RXSTATUS_ACTL          QUAD_OBDII_AUDIO_RXSTATUS_ACTL_REG
#endif /* End  (QUAD_OBDII_AUDIO_RX_ENABLED) || (QUAD_OBDII_AUDIO_HD_ENABLED) */

#if(QUAD_OBDII_AUDIO_INTERNAL_CLOCK_USED)
    #define QUAD_OBDII_AUDIO_INTCLOCK_CLKEN         QUAD_OBDII_AUDIO_INTCLOCK_CLKEN_REG
#endif /* End QUAD_OBDII_AUDIO_INTERNAL_CLOCK_USED */

#define QUAD_OBDII_AUDIO_WAIT_FOR_COMLETE_REINIT    QUAD_OBDII_AUDIO_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_QUAD_OBDII_AUDIO_H */


/* [] END OF FILE */
