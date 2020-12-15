/*******************************************************************************
* File Name: DATALINKINT.c
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

#include "DATALINK.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (DATALINK_RX_INTERRUPT_ENABLED && (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED))
    /*******************************************************************************
    * Function Name: DATALINK_RXISR
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
    *  DATALINK_rxBuffer - RAM buffer pointer for save received data.
    *  DATALINK_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  DATALINK_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  DATALINK_rxBufferOverflow - software overflow flag. Set to one
    *     when DATALINK_rxBufferWrite index overtakes
    *     DATALINK_rxBufferRead index.
    *  DATALINK_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when DATALINK_rxBufferWrite is equal to
    *    DATALINK_rxBufferRead
    *  DATALINK_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  DATALINK_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(DATALINK_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef DATALINK_RXISR_ENTRY_CALLBACK
        DATALINK_RXISR_EntryCallback();
    #endif /* DATALINK_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START DATALINK_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = DATALINK_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in DATALINK_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (DATALINK_RX_STS_BREAK | 
                            DATALINK_RX_STS_PAR_ERROR |
                            DATALINK_RX_STS_STOP_ERROR | 
                            DATALINK_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                DATALINK_errorStatus |= readStatus & ( DATALINK_RX_STS_BREAK | 
                                                            DATALINK_RX_STS_PAR_ERROR | 
                                                            DATALINK_RX_STS_STOP_ERROR | 
                                                            DATALINK_RX_STS_OVERRUN);
                /* `#START DATALINK_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef DATALINK_RXISR_ERROR_CALLBACK
                DATALINK_RXISR_ERROR_Callback();
            #endif /* DATALINK_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & DATALINK_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = DATALINK_RXDATA_REG;
            #if (DATALINK_RXHW_ADDRESS_ENABLED)
                if(DATALINK_rxAddressMode == (uint8)DATALINK__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & DATALINK_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & DATALINK_RX_STS_ADDR_MATCH) != 0u)
                        {
                            DATALINK_rxAddressDetected = 1u;
                        }
                        else
                        {
                            DATALINK_rxAddressDetected = 0u;
                        }
                    }
                    if(DATALINK_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        DATALINK_rxBuffer[DATALINK_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    DATALINK_rxBuffer[DATALINK_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                DATALINK_rxBuffer[DATALINK_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (DATALINK_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(DATALINK_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        DATALINK_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    DATALINK_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(DATALINK_rxBufferWrite >= DATALINK_RX_BUFFER_SIZE)
                    {
                        DATALINK_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(DATALINK_rxBufferWrite == DATALINK_rxBufferRead)
                    {
                        DATALINK_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (DATALINK_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            DATALINK_RXSTATUS_MASK_REG  &= (uint8)~DATALINK_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(DATALINK_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (DATALINK_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & DATALINK_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START DATALINK_RXISR_END` */

        /* `#END` */

    #ifdef DATALINK_RXISR_EXIT_CALLBACK
        DATALINK_RXISR_ExitCallback();
    #endif /* DATALINK_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (DATALINK_RX_INTERRUPT_ENABLED && (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)) */


#if (DATALINK_TX_INTERRUPT_ENABLED && DATALINK_TX_ENABLED)
    /*******************************************************************************
    * Function Name: DATALINK_TXISR
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
    *  DATALINK_txBuffer - RAM buffer pointer for transmit data from.
    *  DATALINK_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  DATALINK_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(DATALINK_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef DATALINK_TXISR_ENTRY_CALLBACK
        DATALINK_TXISR_EntryCallback();
    #endif /* DATALINK_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START DATALINK_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((DATALINK_txBufferRead != DATALINK_txBufferWrite) &&
             ((DATALINK_TXSTATUS_REG & DATALINK_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(DATALINK_txBufferRead >= DATALINK_TX_BUFFER_SIZE)
            {
                DATALINK_txBufferRead = 0u;
            }

            DATALINK_TXDATA_REG = DATALINK_txBuffer[DATALINK_txBufferRead];

            /* Set next pointer */
            DATALINK_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START DATALINK_TXISR_END` */

        /* `#END` */

    #ifdef DATALINK_TXISR_EXIT_CALLBACK
        DATALINK_TXISR_ExitCallback();
    #endif /* DATALINK_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (DATALINK_TX_INTERRUPT_ENABLED && DATALINK_TX_ENABLED) */


/* [] END OF FILE */
