/*******************************************************************************
* File Name: GPS.c
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

#include "GPS.h"
#if (GPS_INTERNAL_CLOCK_USED)
    #include "GPS_IntClock.h"
#endif /* End GPS_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 GPS_initVar = 0u;

#if (GPS_TX_INTERRUPT_ENABLED && GPS_TX_ENABLED)
    volatile uint8 GPS_txBuffer[GPS_TX_BUFFER_SIZE];
    volatile uint8 GPS_txBufferRead = 0u;
    uint8 GPS_txBufferWrite = 0u;
#endif /* (GPS_TX_INTERRUPT_ENABLED && GPS_TX_ENABLED) */

#if (GPS_RX_INTERRUPT_ENABLED && (GPS_RX_ENABLED || GPS_HD_ENABLED))
    uint8 GPS_errorStatus = 0u;
    volatile uint8 GPS_rxBuffer[GPS_RX_BUFFER_SIZE];
    volatile uint8 GPS_rxBufferRead  = 0u;
    volatile uint8 GPS_rxBufferWrite = 0u;
    volatile uint8 GPS_rxBufferLoopDetect = 0u;
    volatile uint8 GPS_rxBufferOverflow   = 0u;
    #if (GPS_RXHW_ADDRESS_ENABLED)
        volatile uint8 GPS_rxAddressMode = GPS_RX_ADDRESS_MODE;
        volatile uint8 GPS_rxAddressDetected = 0u;
    #endif /* (GPS_RXHW_ADDRESS_ENABLED) */
#endif /* (GPS_RX_INTERRUPT_ENABLED && (GPS_RX_ENABLED || GPS_HD_ENABLED)) */


/*******************************************************************************
* Function Name: GPS_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  GPS_Start() sets the initVar variable, calls the
*  GPS_Init() function, and then calls the
*  GPS_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The GPS_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time GPS_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the GPS_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void GPS_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(GPS_initVar == 0u)
    {
        GPS_Init();
        GPS_initVar = 1u;
    }

    GPS_Enable();
}


/*******************************************************************************
* Function Name: GPS_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call GPS_Init() because
*  the GPS_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void GPS_Init(void) 
{
    #if(GPS_RX_ENABLED || GPS_HD_ENABLED)

        #if (GPS_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(GPS_RX_VECT_NUM, &GPS_RXISR);
            CyIntSetPriority(GPS_RX_VECT_NUM, GPS_RX_PRIOR_NUM);
            GPS_errorStatus = 0u;
        #endif /* (GPS_RX_INTERRUPT_ENABLED) */

        #if (GPS_RXHW_ADDRESS_ENABLED)
            GPS_SetRxAddressMode(GPS_RX_ADDRESS_MODE);
            GPS_SetRxAddress1(GPS_RX_HW_ADDRESS1);
            GPS_SetRxAddress2(GPS_RX_HW_ADDRESS2);
        #endif /* End GPS_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        GPS_RXBITCTR_PERIOD_REG = GPS_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        GPS_RXSTATUS_MASK_REG  = GPS_INIT_RX_INTERRUPTS_MASK;
    #endif /* End GPS_RX_ENABLED || GPS_HD_ENABLED*/

    #if(GPS_TX_ENABLED)
        #if (GPS_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(GPS_TX_VECT_NUM, &GPS_TXISR);
            CyIntSetPriority(GPS_TX_VECT_NUM, GPS_TX_PRIOR_NUM);
        #endif /* (GPS_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (GPS_TXCLKGEN_DP)
            GPS_TXBITCLKGEN_CTR_REG = GPS_BIT_CENTER;
            GPS_TXBITCLKTX_COMPLETE_REG = ((GPS_NUMBER_OF_DATA_BITS +
                        GPS_NUMBER_OF_START_BIT) * GPS_OVER_SAMPLE_COUNT) - 1u;
        #else
            GPS_TXBITCTR_PERIOD_REG = ((GPS_NUMBER_OF_DATA_BITS +
                        GPS_NUMBER_OF_START_BIT) * GPS_OVER_SAMPLE_8) - 1u;
        #endif /* End GPS_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (GPS_TX_INTERRUPT_ENABLED)
            GPS_TXSTATUS_MASK_REG = GPS_TX_STS_FIFO_EMPTY;
        #else
            GPS_TXSTATUS_MASK_REG = GPS_INIT_TX_INTERRUPTS_MASK;
        #endif /*End GPS_TX_INTERRUPT_ENABLED*/

    #endif /* End GPS_TX_ENABLED */

    #if(GPS_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        GPS_WriteControlRegister( \
            (GPS_ReadControlRegister() & (uint8)~GPS_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(GPS_PARITY_TYPE << GPS_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End GPS_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: GPS_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call GPS_Enable() because the GPS_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  GPS_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void GPS_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (GPS_RX_ENABLED || GPS_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        GPS_RXBITCTR_CONTROL_REG |= GPS_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        GPS_RXSTATUS_ACTL_REG  |= GPS_INT_ENABLE;

        #if (GPS_RX_INTERRUPT_ENABLED)
            GPS_EnableRxInt();

            #if (GPS_RXHW_ADDRESS_ENABLED)
                GPS_rxAddressDetected = 0u;
            #endif /* (GPS_RXHW_ADDRESS_ENABLED) */
        #endif /* (GPS_RX_INTERRUPT_ENABLED) */
    #endif /* (GPS_RX_ENABLED || GPS_HD_ENABLED) */

    #if(GPS_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!GPS_TXCLKGEN_DP)
            GPS_TXBITCTR_CONTROL_REG |= GPS_CNTR_ENABLE;
        #endif /* End GPS_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        GPS_TXSTATUS_ACTL_REG |= GPS_INT_ENABLE;
        #if (GPS_TX_INTERRUPT_ENABLED)
            GPS_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            GPS_EnableTxInt();
        #endif /* (GPS_TX_INTERRUPT_ENABLED) */
     #endif /* (GPS_TX_INTERRUPT_ENABLED) */

    #if (GPS_INTERNAL_CLOCK_USED)
        GPS_IntClock_Start();  /* Enable the clock */
    #endif /* (GPS_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GPS_Stop
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
void GPS_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (GPS_RX_ENABLED || GPS_HD_ENABLED)
        GPS_RXBITCTR_CONTROL_REG &= (uint8) ~GPS_CNTR_ENABLE;
    #endif /* (GPS_RX_ENABLED || GPS_HD_ENABLED) */

    #if (GPS_TX_ENABLED)
        #if(!GPS_TXCLKGEN_DP)
            GPS_TXBITCTR_CONTROL_REG &= (uint8) ~GPS_CNTR_ENABLE;
        #endif /* (!GPS_TXCLKGEN_DP) */
    #endif /* (GPS_TX_ENABLED) */

    #if (GPS_INTERNAL_CLOCK_USED)
        GPS_IntClock_Stop();   /* Disable the clock */
    #endif /* (GPS_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (GPS_RX_ENABLED || GPS_HD_ENABLED)
        GPS_RXSTATUS_ACTL_REG  &= (uint8) ~GPS_INT_ENABLE;

        #if (GPS_RX_INTERRUPT_ENABLED)
            GPS_DisableRxInt();
        #endif /* (GPS_RX_INTERRUPT_ENABLED) */
    #endif /* (GPS_RX_ENABLED || GPS_HD_ENABLED) */

    #if (GPS_TX_ENABLED)
        GPS_TXSTATUS_ACTL_REG &= (uint8) ~GPS_INT_ENABLE;

        #if (GPS_TX_INTERRUPT_ENABLED)
            GPS_DisableTxInt();
        #endif /* (GPS_TX_INTERRUPT_ENABLED) */
    #endif /* (GPS_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GPS_ReadControlRegister
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
uint8 GPS_ReadControlRegister(void) 
{
    #if (GPS_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(GPS_CONTROL_REG);
    #endif /* (GPS_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: GPS_WriteControlRegister
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
void  GPS_WriteControlRegister(uint8 control) 
{
    #if (GPS_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       GPS_CONTROL_REG = control;
    #endif /* (GPS_CONTROL_REG_REMOVED) */
}


#if(GPS_RX_ENABLED || GPS_HD_ENABLED)
    /*******************************************************************************
    * Function Name: GPS_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      GPS_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      GPS_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      GPS_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      GPS_RX_STS_BREAK            Interrupt on break.
    *      GPS_RX_STS_OVERRUN          Interrupt on overrun error.
    *      GPS_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      GPS_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void GPS_SetRxInterruptMode(uint8 intSrc) 
    {
        GPS_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: GPS_ReadRxData
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
    *  GPS_rxBuffer - RAM buffer pointer for save received data.
    *  GPS_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  GPS_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  GPS_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 GPS_ReadRxData(void) 
    {
        uint8 rxData;

    #if (GPS_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        GPS_DisableRxInt();

        locRxBufferRead  = GPS_rxBufferRead;
        locRxBufferWrite = GPS_rxBufferWrite;

        if( (GPS_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = GPS_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= GPS_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            GPS_rxBufferRead = locRxBufferRead;

            if(GPS_rxBufferLoopDetect != 0u)
            {
                GPS_rxBufferLoopDetect = 0u;
                #if ((GPS_RX_INTERRUPT_ENABLED) && (GPS_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( GPS_HD_ENABLED )
                        if((GPS_CONTROL_REG & GPS_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            GPS_RXSTATUS_MASK_REG  |= GPS_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        GPS_RXSTATUS_MASK_REG  |= GPS_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end GPS_HD_ENABLED */
                #endif /* ((GPS_RX_INTERRUPT_ENABLED) && (GPS_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = GPS_RXDATA_REG;
        }

        GPS_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = GPS_RXDATA_REG;

    #endif /* (GPS_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: GPS_ReadRxStatus
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
    *  GPS_RX_STS_FIFO_NOTEMPTY.
    *  GPS_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  GPS_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   GPS_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   GPS_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 GPS_ReadRxStatus(void) 
    {
        uint8 status;

        status = GPS_RXSTATUS_REG & GPS_RX_HW_MASK;

    #if (GPS_RX_INTERRUPT_ENABLED)
        if(GPS_rxBufferOverflow != 0u)
        {
            status |= GPS_RX_STS_SOFT_BUFF_OVER;
            GPS_rxBufferOverflow = 0u;
        }
    #endif /* (GPS_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: GPS_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. GPS_GetChar() is
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
    *  GPS_rxBuffer - RAM buffer pointer for save received data.
    *  GPS_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  GPS_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  GPS_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 GPS_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (GPS_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        GPS_DisableRxInt();

        locRxBufferRead  = GPS_rxBufferRead;
        locRxBufferWrite = GPS_rxBufferWrite;

        if( (GPS_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = GPS_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= GPS_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            GPS_rxBufferRead = locRxBufferRead;

            if(GPS_rxBufferLoopDetect != 0u)
            {
                GPS_rxBufferLoopDetect = 0u;
                #if( (GPS_RX_INTERRUPT_ENABLED) && (GPS_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( GPS_HD_ENABLED )
                        if((GPS_CONTROL_REG & GPS_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            GPS_RXSTATUS_MASK_REG |= GPS_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        GPS_RXSTATUS_MASK_REG |= GPS_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end GPS_HD_ENABLED */
                #endif /* GPS_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = GPS_RXSTATUS_REG;
            if((rxStatus & GPS_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = GPS_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (GPS_RX_STS_BREAK | GPS_RX_STS_PAR_ERROR |
                                GPS_RX_STS_STOP_ERROR | GPS_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        GPS_EnableRxInt();

    #else

        rxStatus =GPS_RXSTATUS_REG;
        if((rxStatus & GPS_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = GPS_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (GPS_RX_STS_BREAK | GPS_RX_STS_PAR_ERROR |
                            GPS_RX_STS_STOP_ERROR | GPS_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (GPS_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: GPS_GetByte
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
    uint16 GPS_GetByte(void) 
    {
        
    #if (GPS_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        GPS_DisableRxInt();
        locErrorStatus = (uint16)GPS_errorStatus;
        GPS_errorStatus = 0u;
        GPS_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | GPS_ReadRxData() );
    #else
        return ( ((uint16)GPS_ReadRxStatus() << 8u) | GPS_ReadRxData() );
    #endif /* GPS_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: GPS_GetRxBufferSize
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
    *  GPS_rxBufferWrite - used to calculate left bytes.
    *  GPS_rxBufferRead - used to calculate left bytes.
    *  GPS_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 GPS_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (GPS_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        GPS_DisableRxInt();

        if(GPS_rxBufferRead == GPS_rxBufferWrite)
        {
            if(GPS_rxBufferLoopDetect != 0u)
            {
                size = GPS_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(GPS_rxBufferRead < GPS_rxBufferWrite)
        {
            size = (GPS_rxBufferWrite - GPS_rxBufferRead);
        }
        else
        {
            size = (GPS_RX_BUFFER_SIZE - GPS_rxBufferRead) + GPS_rxBufferWrite;
        }

        GPS_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((GPS_RXSTATUS_REG & GPS_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (GPS_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: GPS_ClearRxBuffer
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
    *  GPS_rxBufferWrite - cleared to zero.
    *  GPS_rxBufferRead - cleared to zero.
    *  GPS_rxBufferLoopDetect - cleared to zero.
    *  GPS_rxBufferOverflow - cleared to zero.
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
    void GPS_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        GPS_RXDATA_AUX_CTL_REG |= (uint8)  GPS_RX_FIFO_CLR;
        GPS_RXDATA_AUX_CTL_REG &= (uint8) ~GPS_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (GPS_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        GPS_DisableRxInt();

        GPS_rxBufferRead = 0u;
        GPS_rxBufferWrite = 0u;
        GPS_rxBufferLoopDetect = 0u;
        GPS_rxBufferOverflow = 0u;

        GPS_EnableRxInt();

    #endif /* (GPS_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: GPS_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  GPS__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  GPS__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  GPS__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  GPS__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  GPS__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  GPS_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  GPS_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void GPS_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(GPS_RXHW_ADDRESS_ENABLED)
            #if(GPS_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* GPS_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = GPS_CONTROL_REG & (uint8)~GPS_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << GPS_CTRL_RXADDR_MODE0_SHIFT);
                GPS_CONTROL_REG = tmpCtrl;

                #if(GPS_RX_INTERRUPT_ENABLED && \
                   (GPS_RXBUFFERSIZE > GPS_FIFO_LENGTH) )
                    GPS_rxAddressMode = addressMode;
                    GPS_rxAddressDetected = 0u;
                #endif /* End GPS_RXBUFFERSIZE > GPS_FIFO_LENGTH*/
            #endif /* End GPS_CONTROL_REG_REMOVED */
        #else /* GPS_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End GPS_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: GPS_SetRxAddress1
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
    void GPS_SetRxAddress1(uint8 address) 
    {
        GPS_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: GPS_SetRxAddress2
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
    void GPS_SetRxAddress2(uint8 address) 
    {
        GPS_RXADDRESS2_REG = address;
    }

#endif  /* GPS_RX_ENABLED || GPS_HD_ENABLED*/


#if( (GPS_TX_ENABLED) || (GPS_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: GPS_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   GPS_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   GPS_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   GPS_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   GPS_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void GPS_SetTxInterruptMode(uint8 intSrc) 
    {
        GPS_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: GPS_WriteTxData
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
    *  GPS_txBuffer - RAM buffer pointer for save data for transmission
    *  GPS_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  GPS_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  GPS_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void GPS_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(GPS_initVar != 0u)
        {
        #if (GPS_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            GPS_DisableTxInt();

            if( (GPS_txBufferRead == GPS_txBufferWrite) &&
                ((GPS_TXSTATUS_REG & GPS_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                GPS_TXDATA_REG = txDataByte;
            }
            else
            {
                if(GPS_txBufferWrite >= GPS_TX_BUFFER_SIZE)
                {
                    GPS_txBufferWrite = 0u;
                }

                GPS_txBuffer[GPS_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                GPS_txBufferWrite++;
            }

            GPS_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            GPS_TXDATA_REG = txDataByte;

        #endif /*(GPS_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: GPS_ReadTxStatus
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
    uint8 GPS_ReadTxStatus(void) 
    {
        return(GPS_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: GPS_PutChar
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
    *  GPS_txBuffer - RAM buffer pointer for save data for transmission
    *  GPS_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  GPS_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  GPS_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void GPS_PutChar(uint8 txDataByte) 
    {
    #if (GPS_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((GPS_TX_BUFFER_SIZE > GPS_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            GPS_DisableTxInt();
        #endif /* (GPS_TX_BUFFER_SIZE > GPS_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = GPS_txBufferWrite;
            locTxBufferRead  = GPS_txBufferRead;

        #if ((GPS_TX_BUFFER_SIZE > GPS_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            GPS_EnableTxInt();
        #endif /* (GPS_TX_BUFFER_SIZE > GPS_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(GPS_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((GPS_TXSTATUS_REG & GPS_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            GPS_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= GPS_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            GPS_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((GPS_TX_BUFFER_SIZE > GPS_MAX_BYTE_VALUE) && (CY_PSOC3))
            GPS_DisableTxInt();
        #endif /* (GPS_TX_BUFFER_SIZE > GPS_MAX_BYTE_VALUE) && (CY_PSOC3) */

            GPS_txBufferWrite = locTxBufferWrite;

        #if ((GPS_TX_BUFFER_SIZE > GPS_MAX_BYTE_VALUE) && (CY_PSOC3))
            GPS_EnableTxInt();
        #endif /* (GPS_TX_BUFFER_SIZE > GPS_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (GPS_TXSTATUS_REG & GPS_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                GPS_SetPendingTxInt();
            }
        }

    #else

        while((GPS_TXSTATUS_REG & GPS_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        GPS_TXDATA_REG = txDataByte;

    #endif /* GPS_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: GPS_PutString
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
    *  GPS_initVar - checked to identify that the component has been
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
    void GPS_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(GPS_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                GPS_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: GPS_PutArray
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
    *  GPS_initVar - checked to identify that the component has been
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
    void GPS_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(GPS_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                GPS_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: GPS_PutCRLF
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
    *  GPS_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void GPS_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(GPS_initVar != 0u)
        {
            GPS_PutChar(txDataByte);
            GPS_PutChar(0x0Du);
            GPS_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: GPS_GetTxBufferSize
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
    *  GPS_txBufferWrite - used to calculate left space.
    *  GPS_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 GPS_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (GPS_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        GPS_DisableTxInt();

        if(GPS_txBufferRead == GPS_txBufferWrite)
        {
            size = 0u;
        }
        else if(GPS_txBufferRead < GPS_txBufferWrite)
        {
            size = (GPS_txBufferWrite - GPS_txBufferRead);
        }
        else
        {
            size = (GPS_TX_BUFFER_SIZE - GPS_txBufferRead) +
                    GPS_txBufferWrite;
        }

        GPS_EnableTxInt();

    #else

        size = GPS_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & GPS_TX_STS_FIFO_FULL) != 0u)
        {
            size = GPS_FIFO_LENGTH;
        }
        else if((size & GPS_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (GPS_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: GPS_ClearTxBuffer
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
    *  GPS_txBufferWrite - cleared to zero.
    *  GPS_txBufferRead - cleared to zero.
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
    void GPS_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        GPS_TXDATA_AUX_CTL_REG |= (uint8)  GPS_TX_FIFO_CLR;
        GPS_TXDATA_AUX_CTL_REG &= (uint8) ~GPS_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (GPS_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        GPS_DisableTxInt();

        GPS_txBufferRead = 0u;
        GPS_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        GPS_EnableTxInt();

    #endif /* (GPS_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: GPS_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   GPS_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   GPS_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   GPS_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   GPS_SEND_WAIT_REINIT - Performs both options: 
    *      GPS_SEND_BREAK and GPS_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  GPS_initVar - checked to identify that the component has been
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
    *     When interrupt appear with GPS_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The GPS_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void GPS_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(GPS_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(GPS_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == GPS_SEND_BREAK) ||
                (retMode == GPS_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                GPS_WriteControlRegister(GPS_ReadControlRegister() |
                                                      GPS_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                GPS_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = GPS_TXSTATUS_REG;
                }
                while((tmpStat & GPS_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == GPS_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == GPS_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = GPS_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & GPS_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == GPS_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == GPS_REINIT) ||
                (retMode == GPS_SEND_WAIT_REINIT) )
            {
                GPS_WriteControlRegister(GPS_ReadControlRegister() &
                                              (uint8)~GPS_CTRL_HD_SEND_BREAK);
            }

        #else /* GPS_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == GPS_SEND_BREAK) ||
                (retMode == GPS_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (GPS_PARITY_TYPE != GPS__B_UART__NONE_REVB) || \
                                    (GPS_PARITY_TYPE_SW != 0u) )
                    GPS_WriteControlRegister(GPS_ReadControlRegister() |
                                                          GPS_CTRL_HD_SEND_BREAK);
                #endif /* End GPS_PARITY_TYPE != GPS__B_UART__NONE_REVB  */

                #if(GPS_TXCLKGEN_DP)
                    txPeriod = GPS_TXBITCLKTX_COMPLETE_REG;
                    GPS_TXBITCLKTX_COMPLETE_REG = GPS_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = GPS_TXBITCTR_PERIOD_REG;
                    GPS_TXBITCTR_PERIOD_REG = GPS_TXBITCTR_BREAKBITS8X;
                #endif /* End GPS_TXCLKGEN_DP */

                /* Send zeros */
                GPS_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = GPS_TXSTATUS_REG;
                }
                while((tmpStat & GPS_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == GPS_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == GPS_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = GPS_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & GPS_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == GPS_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == GPS_REINIT) ||
                (retMode == GPS_SEND_WAIT_REINIT) )
            {

            #if(GPS_TXCLKGEN_DP)
                GPS_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                GPS_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End GPS_TXCLKGEN_DP */

            #if( (GPS_PARITY_TYPE != GPS__B_UART__NONE_REVB) || \
                 (GPS_PARITY_TYPE_SW != 0u) )
                GPS_WriteControlRegister(GPS_ReadControlRegister() &
                                                      (uint8) ~GPS_CTRL_HD_SEND_BREAK);
            #endif /* End GPS_PARITY_TYPE != NONE */
            }
        #endif    /* End GPS_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: GPS_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       GPS_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       GPS_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears GPS_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void GPS_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( GPS_CONTROL_REG_REMOVED == 0u )
            GPS_WriteControlRegister(GPS_ReadControlRegister() |
                                                  GPS_CTRL_MARK);
        #endif /* End GPS_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( GPS_CONTROL_REG_REMOVED == 0u )
            GPS_WriteControlRegister(GPS_ReadControlRegister() &
                                                  (uint8) ~GPS_CTRL_MARK);
        #endif /* End GPS_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndGPS_TX_ENABLED */

#if(GPS_HD_ENABLED)


    /*******************************************************************************
    * Function Name: GPS_LoadRxConfig
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
    void GPS_LoadRxConfig(void) 
    {
        GPS_WriteControlRegister(GPS_ReadControlRegister() &
                                                (uint8)~GPS_CTRL_HD_SEND);
        GPS_RXBITCTR_PERIOD_REG = GPS_HD_RXBITCTR_INIT;

    #if (GPS_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        GPS_SetRxInterruptMode(GPS_INIT_RX_INTERRUPTS_MASK);
    #endif /* (GPS_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: GPS_LoadTxConfig
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
    void GPS_LoadTxConfig(void) 
    {
    #if (GPS_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        GPS_SetRxInterruptMode(0u);
    #endif /* (GPS_RX_INTERRUPT_ENABLED) */

        GPS_WriteControlRegister(GPS_ReadControlRegister() | GPS_CTRL_HD_SEND);
        GPS_RXBITCTR_PERIOD_REG = GPS_HD_TXBITCTR_INIT;
    }

#endif  /* GPS_HD_ENABLED */


/* [] END OF FILE */
