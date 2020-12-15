/*******************************************************************************
* File Name: CONTROLLERINT.c
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

#include "CONTROLLER.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (CONTROLLER_RX_INTERRUPT_ENABLED && (CONTROLLER_RX_ENABLED || CONTROLLER_HD_ENABLED))
    /*******************************************************************************
    * Function Name: CONTROLLER_RXISR
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
    *  CONTROLLER_rxBuffer - RAM buffer pointer for save received data.
    *  CONTROLLER_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  CONTROLLER_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  CONTROLLER_rxBufferOverflow - software overflow flag. Set to one
    *     when CONTROLLER_rxBufferWrite index overtakes
    *     CONTROLLER_rxBufferRead index.
    *  CONTROLLER_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when CONTROLLER_rxBufferWrite is equal to
    *    CONTROLLER_rxBufferRead
    *  CONTROLLER_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  CONTROLLER_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(CONTROLLER_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef CONTROLLER_RXISR_ENTRY_CALLBACK
        CONTROLLER_RXISR_EntryCallback();
    #endif /* CONTROLLER_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START CONTROLLER_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = CONTROLLER_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in CONTROLLER_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (CONTROLLER_RX_STS_BREAK | 
                            CONTROLLER_RX_STS_PAR_ERROR |
                            CONTROLLER_RX_STS_STOP_ERROR | 
                            CONTROLLER_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                CONTROLLER_errorStatus |= readStatus & ( CONTROLLER_RX_STS_BREAK | 
                                                            CONTROLLER_RX_STS_PAR_ERROR | 
                                                            CONTROLLER_RX_STS_STOP_ERROR | 
                                                            CONTROLLER_RX_STS_OVERRUN);
                /* `#START CONTROLLER_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef CONTROLLER_RXISR_ERROR_CALLBACK
                CONTROLLER_RXISR_ERROR_Callback();
            #endif /* CONTROLLER_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & CONTROLLER_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = CONTROLLER_RXDATA_REG;
            #if (CONTROLLER_RXHW_ADDRESS_ENABLED)
                if(CONTROLLER_rxAddressMode == (uint8)CONTROLLER__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & CONTROLLER_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & CONTROLLER_RX_STS_ADDR_MATCH) != 0u)
                        {
                            CONTROLLER_rxAddressDetected = 1u;
                        }
                        else
                        {
                            CONTROLLER_rxAddressDetected = 0u;
                        }
                    }
                    if(CONTROLLER_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        CONTROLLER_rxBuffer[CONTROLLER_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    CONTROLLER_rxBuffer[CONTROLLER_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                CONTROLLER_rxBuffer[CONTROLLER_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (CONTROLLER_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(CONTROLLER_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        CONTROLLER_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    CONTROLLER_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(CONTROLLER_rxBufferWrite >= CONTROLLER_RX_BUFFER_SIZE)
                    {
                        CONTROLLER_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(CONTROLLER_rxBufferWrite == CONTROLLER_rxBufferRead)
                    {
                        CONTROLLER_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (CONTROLLER_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            CONTROLLER_RXSTATUS_MASK_REG  &= (uint8)~CONTROLLER_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(CONTROLLER_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (CONTROLLER_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & CONTROLLER_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START CONTROLLER_RXISR_END` */

        /* `#END` */

    #ifdef CONTROLLER_RXISR_EXIT_CALLBACK
        CONTROLLER_RXISR_ExitCallback();
    #endif /* CONTROLLER_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (CONTROLLER_RX_INTERRUPT_ENABLED && (CONTROLLER_RX_ENABLED || CONTROLLER_HD_ENABLED)) */


#if (CONTROLLER_TX_INTERRUPT_ENABLED && CONTROLLER_TX_ENABLED)
    /*******************************************************************************
    * Function Name: CONTROLLER_TXISR
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
    *  CONTROLLER_txBuffer - RAM buffer pointer for transmit data from.
    *  CONTROLLER_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  CONTROLLER_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(CONTROLLER_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef CONTROLLER_TXISR_ENTRY_CALLBACK
        CONTROLLER_TXISR_EntryCallback();
    #endif /* CONTROLLER_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START CONTROLLER_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((CONTROLLER_txBufferRead != CONTROLLER_txBufferWrite) &&
             ((CONTROLLER_TXSTATUS_REG & CONTROLLER_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(CONTROLLER_txBufferRead >= CONTROLLER_TX_BUFFER_SIZE)
            {
                CONTROLLER_txBufferRead = 0u;
            }

            CONTROLLER_TXDATA_REG = CONTROLLER_txBuffer[CONTROLLER_txBufferRead];

            /* Set next pointer */
            CONTROLLER_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START CONTROLLER_TXISR_END` */

        /* `#END` */

    #ifdef CONTROLLER_TXISR_EXIT_CALLBACK
        CONTROLLER_TXISR_ExitCallback();
    #endif /* CONTROLLER_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (CONTROLLER_TX_INTERRUPT_ENABLED && CONTROLLER_TX_ENABLED) */


/* [] END OF FILE */
