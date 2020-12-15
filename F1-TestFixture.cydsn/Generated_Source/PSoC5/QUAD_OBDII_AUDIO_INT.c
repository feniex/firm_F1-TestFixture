/*******************************************************************************
* File Name: QUAD_OBDII_AUDIOINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "QUAD_OBDII_AUDIO.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED && (QUAD_OBDII_AUDIO_RX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED))
    /*******************************************************************************
    * Function Name: QUAD_OBDII_AUDIO_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  QUAD_OBDII_AUDIO_rxBuffer - RAM buffer pointer for save received data.
    *  QUAD_OBDII_AUDIO_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  QUAD_OBDII_AUDIO_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  QUAD_OBDII_AUDIO_rxBufferOverflow - software overflow flag. Set to one
    *     when QUAD_OBDII_AUDIO_rxBufferWrite index overtakes
    *     QUAD_OBDII_AUDIO_rxBufferRead index.
    *  QUAD_OBDII_AUDIO_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when QUAD_OBDII_AUDIO_rxBufferWrite is equal to
    *    QUAD_OBDII_AUDIO_rxBufferRead
    *  QUAD_OBDII_AUDIO_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  QUAD_OBDII_AUDIO_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(QUAD_OBDII_AUDIO_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef QUAD_OBDII_AUDIO_RXISR_ENTRY_CALLBACK
        QUAD_OBDII_AUDIO_RXISR_EntryCallback();
    #endif /* QUAD_OBDII_AUDIO_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START QUAD_OBDII_AUDIO_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = QUAD_OBDII_AUDIO_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in QUAD_OBDII_AUDIO_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (QUAD_OBDII_AUDIO_RX_STS_BREAK | 
                            QUAD_OBDII_AUDIO_RX_STS_PAR_ERROR |
                            QUAD_OBDII_AUDIO_RX_STS_STOP_ERROR | 
                            QUAD_OBDII_AUDIO_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                QUAD_OBDII_AUDIO_errorStatus |= readStatus & ( QUAD_OBDII_AUDIO_RX_STS_BREAK | 
                                                            QUAD_OBDII_AUDIO_RX_STS_PAR_ERROR | 
                                                            QUAD_OBDII_AUDIO_RX_STS_STOP_ERROR | 
                                                            QUAD_OBDII_AUDIO_RX_STS_OVERRUN);
                /* `#START QUAD_OBDII_AUDIO_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef QUAD_OBDII_AUDIO_RXISR_ERROR_CALLBACK
                QUAD_OBDII_AUDIO_RXISR_ERROR_Callback();
            #endif /* QUAD_OBDII_AUDIO_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & QUAD_OBDII_AUDIO_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = QUAD_OBDII_AUDIO_RXDATA_REG;
            #if (QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED)
                if(QUAD_OBDII_AUDIO_rxAddressMode == (uint8)QUAD_OBDII_AUDIO__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & QUAD_OBDII_AUDIO_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & QUAD_OBDII_AUDIO_RX_STS_ADDR_MATCH) != 0u)
                        {
                            QUAD_OBDII_AUDIO_rxAddressDetected = 1u;
                        }
                        else
                        {
                            QUAD_OBDII_AUDIO_rxAddressDetected = 0u;
                        }
                    }
                    if(QUAD_OBDII_AUDIO_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        QUAD_OBDII_AUDIO_rxBuffer[QUAD_OBDII_AUDIO_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    QUAD_OBDII_AUDIO_rxBuffer[QUAD_OBDII_AUDIO_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                QUAD_OBDII_AUDIO_rxBuffer[QUAD_OBDII_AUDIO_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (QUAD_OBDII_AUDIO_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(QUAD_OBDII_AUDIO_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        QUAD_OBDII_AUDIO_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    QUAD_OBDII_AUDIO_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(QUAD_OBDII_AUDIO_rxBufferWrite >= QUAD_OBDII_AUDIO_RX_BUFFER_SIZE)
                    {
                        QUAD_OBDII_AUDIO_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(QUAD_OBDII_AUDIO_rxBufferWrite == QUAD_OBDII_AUDIO_rxBufferRead)
                    {
                        QUAD_OBDII_AUDIO_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (QUAD_OBDII_AUDIO_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            QUAD_OBDII_AUDIO_RXSTATUS_MASK_REG  &= (uint8)~QUAD_OBDII_AUDIO_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(QUAD_OBDII_AUDIO_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (QUAD_OBDII_AUDIO_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & QUAD_OBDII_AUDIO_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START QUAD_OBDII_AUDIO_RXISR_END` */

        /* `#END` */

    #ifdef QUAD_OBDII_AUDIO_RXISR_EXIT_CALLBACK
        QUAD_OBDII_AUDIO_RXISR_ExitCallback();
    #endif /* QUAD_OBDII_AUDIO_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (QUAD_OBDII_AUDIO_RX_INTERRUPT_ENABLED && (QUAD_OBDII_AUDIO_RX_ENABLED || QUAD_OBDII_AUDIO_HD_ENABLED)) */


#if (QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED && QUAD_OBDII_AUDIO_TX_ENABLED)
    /*******************************************************************************
    * Function Name: QUAD_OBDII_AUDIO_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  QUAD_OBDII_AUDIO_txBuffer - RAM buffer pointer for transmit data from.
    *  QUAD_OBDII_AUDIO_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  QUAD_OBDII_AUDIO_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(QUAD_OBDII_AUDIO_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef QUAD_OBDII_AUDIO_TXISR_ENTRY_CALLBACK
        QUAD_OBDII_AUDIO_TXISR_EntryCallback();
    #endif /* QUAD_OBDII_AUDIO_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START QUAD_OBDII_AUDIO_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((QUAD_OBDII_AUDIO_txBufferRead != QUAD_OBDII_AUDIO_txBufferWrite) &&
             ((QUAD_OBDII_AUDIO_TXSTATUS_REG & QUAD_OBDII_AUDIO_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(QUAD_OBDII_AUDIO_txBufferRead >= QUAD_OBDII_AUDIO_TX_BUFFER_SIZE)
            {
                QUAD_OBDII_AUDIO_txBufferRead = 0u;
            }

            QUAD_OBDII_AUDIO_TXDATA_REG = QUAD_OBDII_AUDIO_txBuffer[QUAD_OBDII_AUDIO_txBufferRead];

            /* Set next pointer */
            QUAD_OBDII_AUDIO_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START QUAD_OBDII_AUDIO_TXISR_END` */

        /* `#END` */

    #ifdef QUAD_OBDII_AUDIO_TXISR_EXIT_CALLBACK
        QUAD_OBDII_AUDIO_TXISR_ExitCallback();
    #endif /* QUAD_OBDII_AUDIO_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (QUAD_OBDII_AUDIO_TX_INTERRUPT_ENABLED && QUAD_OBDII_AUDIO_TX_ENABLED) */


/* [] END OF FILE */
