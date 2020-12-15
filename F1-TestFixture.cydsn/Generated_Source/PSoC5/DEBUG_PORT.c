/*******************************************************************************
* File Name: DEBUG_PORT.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUG_PORT.h"
#if (DEBUG_PORT_INTERNAL_CLOCK_USED)
    #include "DEBUG_PORT_IntClock.h"
#endif /* End DEBUG_PORT_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 DEBUG_PORT_initVar = 0u;

#if (DEBUG_PORT_TX_INTERRUPT_ENABLED && DEBUG_PORT_TX_ENABLED)
    volatile uint8 DEBUG_PORT_txBuffer[DEBUG_PORT_TX_BUFFER_SIZE];
    volatile uint8 DEBUG_PORT_txBufferRead = 0u;
    uint8 DEBUG_PORT_txBufferWrite = 0u;
#endif /* (DEBUG_PORT_TX_INTERRUPT_ENABLED && DEBUG_PORT_TX_ENABLED) */

#if (DEBUG_PORT_RX_INTERRUPT_ENABLED && (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED))
    uint8 DEBUG_PORT_errorStatus = 0u;
    volatile uint8 DEBUG_PORT_rxBuffer[DEBUG_PORT_RX_BUFFER_SIZE];
    volatile uint8 DEBUG_PORT_rxBufferRead  = 0u;
    volatile uint8 DEBUG_PORT_rxBufferWrite = 0u;
    volatile uint8 DEBUG_PORT_rxBufferLoopDetect = 0u;
    volatile uint8 DEBUG_PORT_rxBufferOverflow   = 0u;
    #if (DEBUG_PORT_RXHW_ADDRESS_ENABLED)
        volatile uint8 DEBUG_PORT_rxAddressMode = DEBUG_PORT_RX_ADDRESS_MODE;
        volatile uint8 DEBUG_PORT_rxAddressDetected = 0u;
    #endif /* (DEBUG_PORT_RXHW_ADDRESS_ENABLED) */
#endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED && (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED)) */


/*******************************************************************************
* Function Name: DEBUG_PORT_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  DEBUG_PORT_Start() sets the initVar variable, calls the
*  DEBUG_PORT_Init() function, and then calls the
*  DEBUG_PORT_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The DEBUG_PORT_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time DEBUG_PORT_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the DEBUG_PORT_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DEBUG_PORT_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(DEBUG_PORT_initVar == 0u)
    {
        DEBUG_PORT_Init();
        DEBUG_PORT_initVar = 1u;
    }

    DEBUG_PORT_Enable();
}


/*******************************************************************************
* Function Name: DEBUG_PORT_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call DEBUG_PORT_Init() because
*  the DEBUG_PORT_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DEBUG_PORT_Init(void) 
{
    #if(DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED)

        #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(DEBUG_PORT_RX_VECT_NUM, &DEBUG_PORT_RXISR);
            CyIntSetPriority(DEBUG_PORT_RX_VECT_NUM, DEBUG_PORT_RX_PRIOR_NUM);
            DEBUG_PORT_errorStatus = 0u;
        #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */

        #if (DEBUG_PORT_RXHW_ADDRESS_ENABLED)
            DEBUG_PORT_SetRxAddressMode(DEBUG_PORT_RX_ADDRESS_MODE);
            DEBUG_PORT_SetRxAddress1(DEBUG_PORT_RX_HW_ADDRESS1);
            DEBUG_PORT_SetRxAddress2(DEBUG_PORT_RX_HW_ADDRESS2);
        #endif /* End DEBUG_PORT_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        DEBUG_PORT_RXBITCTR_PERIOD_REG = DEBUG_PORT_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        DEBUG_PORT_RXSTATUS_MASK_REG  = DEBUG_PORT_INIT_RX_INTERRUPTS_MASK;
    #endif /* End DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED*/

    #if(DEBUG_PORT_TX_ENABLED)
        #if (DEBUG_PORT_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(DEBUG_PORT_TX_VECT_NUM, &DEBUG_PORT_TXISR);
            CyIntSetPriority(DEBUG_PORT_TX_VECT_NUM, DEBUG_PORT_TX_PRIOR_NUM);
        #endif /* (DEBUG_PORT_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (DEBUG_PORT_TXCLKGEN_DP)
            DEBUG_PORT_TXBITCLKGEN_CTR_REG = DEBUG_PORT_BIT_CENTER;
            DEBUG_PORT_TXBITCLKTX_COMPLETE_REG = ((DEBUG_PORT_NUMBER_OF_DATA_BITS +
                        DEBUG_PORT_NUMBER_OF_START_BIT) * DEBUG_PORT_OVER_SAMPLE_COUNT) - 1u;
        #else
            DEBUG_PORT_TXBITCTR_PERIOD_REG = ((DEBUG_PORT_NUMBER_OF_DATA_BITS +
                        DEBUG_PORT_NUMBER_OF_START_BIT) * DEBUG_PORT_OVER_SAMPLE_8) - 1u;
        #endif /* End DEBUG_PORT_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (DEBUG_PORT_TX_INTERRUPT_ENABLED)
            DEBUG_PORT_TXSTATUS_MASK_REG = DEBUG_PORT_TX_STS_FIFO_EMPTY;
        #else
            DEBUG_PORT_TXSTATUS_MASK_REG = DEBUG_PORT_INIT_TX_INTERRUPTS_MASK;
        #endif /*End DEBUG_PORT_TX_INTERRUPT_ENABLED*/

    #endif /* End DEBUG_PORT_TX_ENABLED */

    #if(DEBUG_PORT_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        DEBUG_PORT_WriteControlRegister( \
            (DEBUG_PORT_ReadControlRegister() & (uint8)~DEBUG_PORT_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(DEBUG_PORT_PARITY_TYPE << DEBUG_PORT_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End DEBUG_PORT_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: DEBUG_PORT_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call DEBUG_PORT_Enable() because the DEBUG_PORT_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_PORT_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void DEBUG_PORT_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        DEBUG_PORT_RXBITCTR_CONTROL_REG |= DEBUG_PORT_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        DEBUG_PORT_RXSTATUS_ACTL_REG  |= DEBUG_PORT_INT_ENABLE;

        #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
            DEBUG_PORT_EnableRxInt();

            #if (DEBUG_PORT_RXHW_ADDRESS_ENABLED)
                DEBUG_PORT_rxAddressDetected = 0u;
            #endif /* (DEBUG_PORT_RXHW_ADDRESS_ENABLED) */
        #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */
    #endif /* (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED) */

    #if(DEBUG_PORT_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!DEBUG_PORT_TXCLKGEN_DP)
            DEBUG_PORT_TXBITCTR_CONTROL_REG |= DEBUG_PORT_CNTR_ENABLE;
        #endif /* End DEBUG_PORT_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        DEBUG_PORT_TXSTATUS_ACTL_REG |= DEBUG_PORT_INT_ENABLE;
        #if (DEBUG_PORT_TX_INTERRUPT_ENABLED)
            DEBUG_PORT_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            DEBUG_PORT_EnableTxInt();
        #endif /* (DEBUG_PORT_TX_INTERRUPT_ENABLED) */
     #endif /* (DEBUG_PORT_TX_INTERRUPT_ENABLED) */

    #if (DEBUG_PORT_INTERNAL_CLOCK_USED)
        DEBUG_PORT_IntClock_Start();  /* Enable the clock */
    #endif /* (DEBUG_PORT_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DEBUG_PORT_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DEBUG_PORT_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED)
        DEBUG_PORT_RXBITCTR_CONTROL_REG &= (uint8) ~DEBUG_PORT_CNTR_ENABLE;
    #endif /* (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED) */

    #if (DEBUG_PORT_TX_ENABLED)
        #if(!DEBUG_PORT_TXCLKGEN_DP)
            DEBUG_PORT_TXBITCTR_CONTROL_REG &= (uint8) ~DEBUG_PORT_CNTR_ENABLE;
        #endif /* (!DEBUG_PORT_TXCLKGEN_DP) */
    #endif /* (DEBUG_PORT_TX_ENABLED) */

    #if (DEBUG_PORT_INTERNAL_CLOCK_USED)
        DEBUG_PORT_IntClock_Stop();   /* Disable the clock */
    #endif /* (DEBUG_PORT_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED)
        DEBUG_PORT_RXSTATUS_ACTL_REG  &= (uint8) ~DEBUG_PORT_INT_ENABLE;

        #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
            DEBUG_PORT_DisableRxInt();
        #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */
    #endif /* (DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED) */

    #if (DEBUG_PORT_TX_ENABLED)
        DEBUG_PORT_TXSTATUS_ACTL_REG &= (uint8) ~DEBUG_PORT_INT_ENABLE;

        #if (DEBUG_PORT_TX_INTERRUPT_ENABLED)
            DEBUG_PORT_DisableTxInt();
        #endif /* (DEBUG_PORT_TX_INTERRUPT_ENABLED) */
    #endif /* (DEBUG_PORT_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DEBUG_PORT_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 DEBUG_PORT_ReadControlRegister(void) 
{
    #if (DEBUG_PORT_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(DEBUG_PORT_CONTROL_REG);
    #endif /* (DEBUG_PORT_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: DEBUG_PORT_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  DEBUG_PORT_WriteControlRegister(uint8 control) 
{
    #if (DEBUG_PORT_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       DEBUG_PORT_CONTROL_REG = control;
    #endif /* (DEBUG_PORT_CONTROL_REG_REMOVED) */
}


#if(DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED)
    /*******************************************************************************
    * Function Name: DEBUG_PORT_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      DEBUG_PORT_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      DEBUG_PORT_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      DEBUG_PORT_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      DEBUG_PORT_RX_STS_BREAK            Interrupt on break.
    *      DEBUG_PORT_RX_STS_OVERRUN          Interrupt on overrun error.
    *      DEBUG_PORT_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      DEBUG_PORT_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void DEBUG_PORT_SetRxInterruptMode(uint8 intSrc) 
    {
        DEBUG_PORT_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  DEBUG_PORT_rxBuffer - RAM buffer pointer for save received data.
    *  DEBUG_PORT_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  DEBUG_PORT_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  DEBUG_PORT_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 DEBUG_PORT_ReadRxData(void) 
    {
        uint8 rxData;

    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        DEBUG_PORT_DisableRxInt();

        locRxBufferRead  = DEBUG_PORT_rxBufferRead;
        locRxBufferWrite = DEBUG_PORT_rxBufferWrite;

        if( (DEBUG_PORT_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = DEBUG_PORT_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= DEBUG_PORT_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            DEBUG_PORT_rxBufferRead = locRxBufferRead;

            if(DEBUG_PORT_rxBufferLoopDetect != 0u)
            {
                DEBUG_PORT_rxBufferLoopDetect = 0u;
                #if ((DEBUG_PORT_RX_INTERRUPT_ENABLED) && (DEBUG_PORT_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( DEBUG_PORT_HD_ENABLED )
                        if((DEBUG_PORT_CONTROL_REG & DEBUG_PORT_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            DEBUG_PORT_RXSTATUS_MASK_REG  |= DEBUG_PORT_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        DEBUG_PORT_RXSTATUS_MASK_REG  |= DEBUG_PORT_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end DEBUG_PORT_HD_ENABLED */
                #endif /* ((DEBUG_PORT_RX_INTERRUPT_ENABLED) && (DEBUG_PORT_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = DEBUG_PORT_RXDATA_REG;
        }

        DEBUG_PORT_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = DEBUG_PORT_RXDATA_REG;

    #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  DEBUG_PORT_RX_STS_FIFO_NOTEMPTY.
    *  DEBUG_PORT_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  DEBUG_PORT_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   DEBUG_PORT_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   DEBUG_PORT_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 DEBUG_PORT_ReadRxStatus(void) 
    {
        uint8 status;

        status = DEBUG_PORT_RXSTATUS_REG & DEBUG_PORT_RX_HW_MASK;

    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
        if(DEBUG_PORT_rxBufferOverflow != 0u)
        {
            status |= DEBUG_PORT_RX_STS_SOFT_BUFF_OVER;
            DEBUG_PORT_rxBufferOverflow = 0u;
        }
    #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. DEBUG_PORT_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  DEBUG_PORT_rxBuffer - RAM buffer pointer for save received data.
    *  DEBUG_PORT_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  DEBUG_PORT_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  DEBUG_PORT_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 DEBUG_PORT_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        DEBUG_PORT_DisableRxInt();

        locRxBufferRead  = DEBUG_PORT_rxBufferRead;
        locRxBufferWrite = DEBUG_PORT_rxBufferWrite;

        if( (DEBUG_PORT_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = DEBUG_PORT_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= DEBUG_PORT_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            DEBUG_PORT_rxBufferRead = locRxBufferRead;

            if(DEBUG_PORT_rxBufferLoopDetect != 0u)
            {
                DEBUG_PORT_rxBufferLoopDetect = 0u;
                #if( (DEBUG_PORT_RX_INTERRUPT_ENABLED) && (DEBUG_PORT_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( DEBUG_PORT_HD_ENABLED )
                        if((DEBUG_PORT_CONTROL_REG & DEBUG_PORT_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            DEBUG_PORT_RXSTATUS_MASK_REG |= DEBUG_PORT_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        DEBUG_PORT_RXSTATUS_MASK_REG |= DEBUG_PORT_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end DEBUG_PORT_HD_ENABLED */
                #endif /* DEBUG_PORT_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = DEBUG_PORT_RXSTATUS_REG;
            if((rxStatus & DEBUG_PORT_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = DEBUG_PORT_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (DEBUG_PORT_RX_STS_BREAK | DEBUG_PORT_RX_STS_PAR_ERROR |
                                DEBUG_PORT_RX_STS_STOP_ERROR | DEBUG_PORT_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        DEBUG_PORT_EnableRxInt();

    #else

        rxStatus =DEBUG_PORT_RXSTATUS_REG;
        if((rxStatus & DEBUG_PORT_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = DEBUG_PORT_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (DEBUG_PORT_RX_STS_BREAK | DEBUG_PORT_RX_STS_PAR_ERROR |
                            DEBUG_PORT_RX_STS_STOP_ERROR | DEBUG_PORT_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 DEBUG_PORT_GetByte(void) 
    {
        
    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        DEBUG_PORT_DisableRxInt();
        locErrorStatus = (uint16)DEBUG_PORT_errorStatus;
        DEBUG_PORT_errorStatus = 0u;
        DEBUG_PORT_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | DEBUG_PORT_ReadRxData() );
    #else
        return ( ((uint16)DEBUG_PORT_ReadRxStatus() << 8u) | DEBUG_PORT_ReadRxData() );
    #endif /* DEBUG_PORT_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  DEBUG_PORT_rxBufferWrite - used to calculate left bytes.
    *  DEBUG_PORT_rxBufferRead - used to calculate left bytes.
    *  DEBUG_PORT_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 DEBUG_PORT_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        DEBUG_PORT_DisableRxInt();

        if(DEBUG_PORT_rxBufferRead == DEBUG_PORT_rxBufferWrite)
        {
            if(DEBUG_PORT_rxBufferLoopDetect != 0u)
            {
                size = DEBUG_PORT_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(DEBUG_PORT_rxBufferRead < DEBUG_PORT_rxBufferWrite)
        {
            size = (DEBUG_PORT_rxBufferWrite - DEBUG_PORT_rxBufferRead);
        }
        else
        {
            size = (DEBUG_PORT_RX_BUFFER_SIZE - DEBUG_PORT_rxBufferRead) + DEBUG_PORT_rxBufferWrite;
        }

        DEBUG_PORT_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((DEBUG_PORT_RXSTATUS_REG & DEBUG_PORT_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DEBUG_PORT_rxBufferWrite - cleared to zero.
    *  DEBUG_PORT_rxBufferRead - cleared to zero.
    *  DEBUG_PORT_rxBufferLoopDetect - cleared to zero.
    *  DEBUG_PORT_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void DEBUG_PORT_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        DEBUG_PORT_RXDATA_AUX_CTL_REG |= (uint8)  DEBUG_PORT_RX_FIFO_CLR;
        DEBUG_PORT_RXDATA_AUX_CTL_REG &= (uint8) ~DEBUG_PORT_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        DEBUG_PORT_DisableRxInt();

        DEBUG_PORT_rxBufferRead = 0u;
        DEBUG_PORT_rxBufferWrite = 0u;
        DEBUG_PORT_rxBufferLoopDetect = 0u;
        DEBUG_PORT_rxBufferOverflow = 0u;

        DEBUG_PORT_EnableRxInt();

    #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  DEBUG_PORT__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  DEBUG_PORT__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  DEBUG_PORT__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  DEBUG_PORT__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  DEBUG_PORT__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DEBUG_PORT_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  DEBUG_PORT_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void DEBUG_PORT_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(DEBUG_PORT_RXHW_ADDRESS_ENABLED)
            #if(DEBUG_PORT_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* DEBUG_PORT_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = DEBUG_PORT_CONTROL_REG & (uint8)~DEBUG_PORT_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << DEBUG_PORT_CTRL_RXADDR_MODE0_SHIFT);
                DEBUG_PORT_CONTROL_REG = tmpCtrl;

                #if(DEBUG_PORT_RX_INTERRUPT_ENABLED && \
                   (DEBUG_PORT_RXBUFFERSIZE > DEBUG_PORT_FIFO_LENGTH) )
                    DEBUG_PORT_rxAddressMode = addressMode;
                    DEBUG_PORT_rxAddressDetected = 0u;
                #endif /* End DEBUG_PORT_RXBUFFERSIZE > DEBUG_PORT_FIFO_LENGTH*/
            #endif /* End DEBUG_PORT_CONTROL_REG_REMOVED */
        #else /* DEBUG_PORT_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End DEBUG_PORT_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void DEBUG_PORT_SetRxAddress1(uint8 address) 
    {
        DEBUG_PORT_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void DEBUG_PORT_SetRxAddress2(uint8 address) 
    {
        DEBUG_PORT_RXADDRESS2_REG = address;
    }

#endif  /* DEBUG_PORT_RX_ENABLED || DEBUG_PORT_HD_ENABLED*/


#if( (DEBUG_PORT_TX_ENABLED) || (DEBUG_PORT_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: DEBUG_PORT_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   DEBUG_PORT_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   DEBUG_PORT_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   DEBUG_PORT_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   DEBUG_PORT_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void DEBUG_PORT_SetTxInterruptMode(uint8 intSrc) 
    {
        DEBUG_PORT_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  DEBUG_PORT_txBuffer - RAM buffer pointer for save data for transmission
    *  DEBUG_PORT_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  DEBUG_PORT_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  DEBUG_PORT_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void DEBUG_PORT_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(DEBUG_PORT_initVar != 0u)
        {
        #if (DEBUG_PORT_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            DEBUG_PORT_DisableTxInt();

            if( (DEBUG_PORT_txBufferRead == DEBUG_PORT_txBufferWrite) &&
                ((DEBUG_PORT_TXSTATUS_REG & DEBUG_PORT_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                DEBUG_PORT_TXDATA_REG = txDataByte;
            }
            else
            {
                if(DEBUG_PORT_txBufferWrite >= DEBUG_PORT_TX_BUFFER_SIZE)
                {
                    DEBUG_PORT_txBufferWrite = 0u;
                }

                DEBUG_PORT_txBuffer[DEBUG_PORT_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                DEBUG_PORT_txBufferWrite++;
            }

            DEBUG_PORT_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            DEBUG_PORT_TXDATA_REG = txDataByte;

        #endif /*(DEBUG_PORT_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 DEBUG_PORT_ReadTxStatus(void) 
    {
        return(DEBUG_PORT_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DEBUG_PORT_txBuffer - RAM buffer pointer for save data for transmission
    *  DEBUG_PORT_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  DEBUG_PORT_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  DEBUG_PORT_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void DEBUG_PORT_PutChar(uint8 txDataByte) 
    {
    #if (DEBUG_PORT_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((DEBUG_PORT_TX_BUFFER_SIZE > DEBUG_PORT_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            DEBUG_PORT_DisableTxInt();
        #endif /* (DEBUG_PORT_TX_BUFFER_SIZE > DEBUG_PORT_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = DEBUG_PORT_txBufferWrite;
            locTxBufferRead  = DEBUG_PORT_txBufferRead;

        #if ((DEBUG_PORT_TX_BUFFER_SIZE > DEBUG_PORT_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            DEBUG_PORT_EnableTxInt();
        #endif /* (DEBUG_PORT_TX_BUFFER_SIZE > DEBUG_PORT_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(DEBUG_PORT_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((DEBUG_PORT_TXSTATUS_REG & DEBUG_PORT_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            DEBUG_PORT_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= DEBUG_PORT_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            DEBUG_PORT_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((DEBUG_PORT_TX_BUFFER_SIZE > DEBUG_PORT_MAX_BYTE_VALUE) && (CY_PSOC3))
            DEBUG_PORT_DisableTxInt();
        #endif /* (DEBUG_PORT_TX_BUFFER_SIZE > DEBUG_PORT_MAX_BYTE_VALUE) && (CY_PSOC3) */

            DEBUG_PORT_txBufferWrite = locTxBufferWrite;

        #if ((DEBUG_PORT_TX_BUFFER_SIZE > DEBUG_PORT_MAX_BYTE_VALUE) && (CY_PSOC3))
            DEBUG_PORT_EnableTxInt();
        #endif /* (DEBUG_PORT_TX_BUFFER_SIZE > DEBUG_PORT_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (DEBUG_PORT_TXSTATUS_REG & DEBUG_PORT_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                DEBUG_PORT_SetPendingTxInt();
            }
        }

    #else

        while((DEBUG_PORT_TXSTATUS_REG & DEBUG_PORT_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        DEBUG_PORT_TXDATA_REG = txDataByte;

    #endif /* DEBUG_PORT_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DEBUG_PORT_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void DEBUG_PORT_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(DEBUG_PORT_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                DEBUG_PORT_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DEBUG_PORT_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void DEBUG_PORT_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(DEBUG_PORT_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                DEBUG_PORT_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DEBUG_PORT_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void DEBUG_PORT_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(DEBUG_PORT_initVar != 0u)
        {
            DEBUG_PORT_PutChar(txDataByte);
            DEBUG_PORT_PutChar(0x0Du);
            DEBUG_PORT_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  DEBUG_PORT_txBufferWrite - used to calculate left space.
    *  DEBUG_PORT_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 DEBUG_PORT_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (DEBUG_PORT_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        DEBUG_PORT_DisableTxInt();

        if(DEBUG_PORT_txBufferRead == DEBUG_PORT_txBufferWrite)
        {
            size = 0u;
        }
        else if(DEBUG_PORT_txBufferRead < DEBUG_PORT_txBufferWrite)
        {
            size = (DEBUG_PORT_txBufferWrite - DEBUG_PORT_txBufferRead);
        }
        else
        {
            size = (DEBUG_PORT_TX_BUFFER_SIZE - DEBUG_PORT_txBufferRead) +
                    DEBUG_PORT_txBufferWrite;
        }

        DEBUG_PORT_EnableTxInt();

    #else

        size = DEBUG_PORT_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & DEBUG_PORT_TX_STS_FIFO_FULL) != 0u)
        {
            size = DEBUG_PORT_FIFO_LENGTH;
        }
        else if((size & DEBUG_PORT_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (DEBUG_PORT_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DEBUG_PORT_txBufferWrite - cleared to zero.
    *  DEBUG_PORT_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void DEBUG_PORT_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        DEBUG_PORT_TXDATA_AUX_CTL_REG |= (uint8)  DEBUG_PORT_TX_FIFO_CLR;
        DEBUG_PORT_TXDATA_AUX_CTL_REG &= (uint8) ~DEBUG_PORT_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (DEBUG_PORT_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        DEBUG_PORT_DisableTxInt();

        DEBUG_PORT_txBufferRead = 0u;
        DEBUG_PORT_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        DEBUG_PORT_EnableTxInt();

    #endif /* (DEBUG_PORT_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   DEBUG_PORT_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   DEBUG_PORT_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   DEBUG_PORT_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   DEBUG_PORT_SEND_WAIT_REINIT - Performs both options: 
    *      DEBUG_PORT_SEND_BREAK and DEBUG_PORT_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DEBUG_PORT_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with DEBUG_PORT_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The DEBUG_PORT_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void DEBUG_PORT_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(DEBUG_PORT_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(DEBUG_PORT_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == DEBUG_PORT_SEND_BREAK) ||
                (retMode == DEBUG_PORT_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                DEBUG_PORT_WriteControlRegister(DEBUG_PORT_ReadControlRegister() |
                                                      DEBUG_PORT_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                DEBUG_PORT_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = DEBUG_PORT_TXSTATUS_REG;
                }
                while((tmpStat & DEBUG_PORT_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == DEBUG_PORT_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == DEBUG_PORT_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = DEBUG_PORT_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & DEBUG_PORT_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == DEBUG_PORT_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == DEBUG_PORT_REINIT) ||
                (retMode == DEBUG_PORT_SEND_WAIT_REINIT) )
            {
                DEBUG_PORT_WriteControlRegister(DEBUG_PORT_ReadControlRegister() &
                                              (uint8)~DEBUG_PORT_CTRL_HD_SEND_BREAK);
            }

        #else /* DEBUG_PORT_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == DEBUG_PORT_SEND_BREAK) ||
                (retMode == DEBUG_PORT_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (DEBUG_PORT_PARITY_TYPE != DEBUG_PORT__B_UART__NONE_REVB) || \
                                    (DEBUG_PORT_PARITY_TYPE_SW != 0u) )
                    DEBUG_PORT_WriteControlRegister(DEBUG_PORT_ReadControlRegister() |
                                                          DEBUG_PORT_CTRL_HD_SEND_BREAK);
                #endif /* End DEBUG_PORT_PARITY_TYPE != DEBUG_PORT__B_UART__NONE_REVB  */

                #if(DEBUG_PORT_TXCLKGEN_DP)
                    txPeriod = DEBUG_PORT_TXBITCLKTX_COMPLETE_REG;
                    DEBUG_PORT_TXBITCLKTX_COMPLETE_REG = DEBUG_PORT_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = DEBUG_PORT_TXBITCTR_PERIOD_REG;
                    DEBUG_PORT_TXBITCTR_PERIOD_REG = DEBUG_PORT_TXBITCTR_BREAKBITS8X;
                #endif /* End DEBUG_PORT_TXCLKGEN_DP */

                /* Send zeros */
                DEBUG_PORT_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = DEBUG_PORT_TXSTATUS_REG;
                }
                while((tmpStat & DEBUG_PORT_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == DEBUG_PORT_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == DEBUG_PORT_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = DEBUG_PORT_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & DEBUG_PORT_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == DEBUG_PORT_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == DEBUG_PORT_REINIT) ||
                (retMode == DEBUG_PORT_SEND_WAIT_REINIT) )
            {

            #if(DEBUG_PORT_TXCLKGEN_DP)
                DEBUG_PORT_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                DEBUG_PORT_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End DEBUG_PORT_TXCLKGEN_DP */

            #if( (DEBUG_PORT_PARITY_TYPE != DEBUG_PORT__B_UART__NONE_REVB) || \
                 (DEBUG_PORT_PARITY_TYPE_SW != 0u) )
                DEBUG_PORT_WriteControlRegister(DEBUG_PORT_ReadControlRegister() &
                                                      (uint8) ~DEBUG_PORT_CTRL_HD_SEND_BREAK);
            #endif /* End DEBUG_PORT_PARITY_TYPE != NONE */
            }
        #endif    /* End DEBUG_PORT_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       DEBUG_PORT_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       DEBUG_PORT_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears DEBUG_PORT_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void DEBUG_PORT_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( DEBUG_PORT_CONTROL_REG_REMOVED == 0u )
            DEBUG_PORT_WriteControlRegister(DEBUG_PORT_ReadControlRegister() |
                                                  DEBUG_PORT_CTRL_MARK);
        #endif /* End DEBUG_PORT_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( DEBUG_PORT_CONTROL_REG_REMOVED == 0u )
            DEBUG_PORT_WriteControlRegister(DEBUG_PORT_ReadControlRegister() &
                                                  (uint8) ~DEBUG_PORT_CTRL_MARK);
        #endif /* End DEBUG_PORT_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndDEBUG_PORT_TX_ENABLED */

#if(DEBUG_PORT_HD_ENABLED)


    /*******************************************************************************
    * Function Name: DEBUG_PORT_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void DEBUG_PORT_LoadRxConfig(void) 
    {
        DEBUG_PORT_WriteControlRegister(DEBUG_PORT_ReadControlRegister() &
                                                (uint8)~DEBUG_PORT_CTRL_HD_SEND);
        DEBUG_PORT_RXBITCTR_PERIOD_REG = DEBUG_PORT_HD_RXBITCTR_INIT;

    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        DEBUG_PORT_SetRxInterruptMode(DEBUG_PORT_INIT_RX_INTERRUPTS_MASK);
    #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: DEBUG_PORT_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void DEBUG_PORT_LoadTxConfig(void) 
    {
    #if (DEBUG_PORT_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        DEBUG_PORT_SetRxInterruptMode(0u);
    #endif /* (DEBUG_PORT_RX_INTERRUPT_ENABLED) */

        DEBUG_PORT_WriteControlRegister(DEBUG_PORT_ReadControlRegister() | DEBUG_PORT_CTRL_HD_SEND);
        DEBUG_PORT_RXBITCTR_PERIOD_REG = DEBUG_PORT_HD_TXBITCTR_INIT;
    }

#endif  /* DEBUG_PORT_HD_ENABLED */


/* [] END OF FILE */
