/*******************************************************************************
* File Name: DATALINK.c
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

#include "DATALINK.h"
#if (DATALINK_INTERNAL_CLOCK_USED)
    #include "DATALINK_IntClock.h"
#endif /* End DATALINK_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 DATALINK_initVar = 0u;

#if (DATALINK_TX_INTERRUPT_ENABLED && DATALINK_TX_ENABLED)
    volatile uint8 DATALINK_txBuffer[DATALINK_TX_BUFFER_SIZE];
    volatile uint16 DATALINK_txBufferRead = 0u;
    uint16 DATALINK_txBufferWrite = 0u;
#endif /* (DATALINK_TX_INTERRUPT_ENABLED && DATALINK_TX_ENABLED) */

#if (DATALINK_RX_INTERRUPT_ENABLED && (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED))
    uint8 DATALINK_errorStatus = 0u;
    volatile uint8 DATALINK_rxBuffer[DATALINK_RX_BUFFER_SIZE];
    volatile uint8 DATALINK_rxBufferRead  = 0u;
    volatile uint8 DATALINK_rxBufferWrite = 0u;
    volatile uint8 DATALINK_rxBufferLoopDetect = 0u;
    volatile uint8 DATALINK_rxBufferOverflow   = 0u;
    #if (DATALINK_RXHW_ADDRESS_ENABLED)
        volatile uint8 DATALINK_rxAddressMode = DATALINK_RX_ADDRESS_MODE;
        volatile uint8 DATALINK_rxAddressDetected = 0u;
    #endif /* (DATALINK_RXHW_ADDRESS_ENABLED) */
#endif /* (DATALINK_RX_INTERRUPT_ENABLED && (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)) */


/*******************************************************************************
* Function Name: DATALINK_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  DATALINK_Start() sets the initVar variable, calls the
*  DATALINK_Init() function, and then calls the
*  DATALINK_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The DATALINK_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time DATALINK_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the DATALINK_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DATALINK_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(DATALINK_initVar == 0u)
    {
        DATALINK_Init();
        DATALINK_initVar = 1u;
    }

    DATALINK_Enable();
}


/*******************************************************************************
* Function Name: DATALINK_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call DATALINK_Init() because
*  the DATALINK_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DATALINK_Init(void) 
{
    #if(DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)

        #if (DATALINK_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(DATALINK_RX_VECT_NUM, &DATALINK_RXISR);
            CyIntSetPriority(DATALINK_RX_VECT_NUM, DATALINK_RX_PRIOR_NUM);
            DATALINK_errorStatus = 0u;
        #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */

        #if (DATALINK_RXHW_ADDRESS_ENABLED)
            DATALINK_SetRxAddressMode(DATALINK_RX_ADDRESS_MODE);
            DATALINK_SetRxAddress1(DATALINK_RX_HW_ADDRESS1);
            DATALINK_SetRxAddress2(DATALINK_RX_HW_ADDRESS2);
        #endif /* End DATALINK_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        DATALINK_RXBITCTR_PERIOD_REG = DATALINK_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        DATALINK_RXSTATUS_MASK_REG  = DATALINK_INIT_RX_INTERRUPTS_MASK;
    #endif /* End DATALINK_RX_ENABLED || DATALINK_HD_ENABLED*/

    #if(DATALINK_TX_ENABLED)
        #if (DATALINK_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(DATALINK_TX_VECT_NUM, &DATALINK_TXISR);
            CyIntSetPriority(DATALINK_TX_VECT_NUM, DATALINK_TX_PRIOR_NUM);
        #endif /* (DATALINK_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (DATALINK_TXCLKGEN_DP)
            DATALINK_TXBITCLKGEN_CTR_REG = DATALINK_BIT_CENTER;
            DATALINK_TXBITCLKTX_COMPLETE_REG = ((DATALINK_NUMBER_OF_DATA_BITS +
                        DATALINK_NUMBER_OF_START_BIT) * DATALINK_OVER_SAMPLE_COUNT) - 1u;
        #else
            DATALINK_TXBITCTR_PERIOD_REG = ((DATALINK_NUMBER_OF_DATA_BITS +
                        DATALINK_NUMBER_OF_START_BIT) * DATALINK_OVER_SAMPLE_8) - 1u;
        #endif /* End DATALINK_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (DATALINK_TX_INTERRUPT_ENABLED)
            DATALINK_TXSTATUS_MASK_REG = DATALINK_TX_STS_FIFO_EMPTY;
        #else
            DATALINK_TXSTATUS_MASK_REG = DATALINK_INIT_TX_INTERRUPTS_MASK;
        #endif /*End DATALINK_TX_INTERRUPT_ENABLED*/

    #endif /* End DATALINK_TX_ENABLED */

    #if(DATALINK_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        DATALINK_WriteControlRegister( \
            (DATALINK_ReadControlRegister() & (uint8)~DATALINK_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(DATALINK_PARITY_TYPE << DATALINK_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End DATALINK_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: DATALINK_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call DATALINK_Enable() because the DATALINK_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DATALINK_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void DATALINK_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        DATALINK_RXBITCTR_CONTROL_REG |= DATALINK_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        DATALINK_RXSTATUS_ACTL_REG  |= DATALINK_INT_ENABLE;

        #if (DATALINK_RX_INTERRUPT_ENABLED)
            DATALINK_EnableRxInt();

            #if (DATALINK_RXHW_ADDRESS_ENABLED)
                DATALINK_rxAddressDetected = 0u;
            #endif /* (DATALINK_RXHW_ADDRESS_ENABLED) */
        #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */
    #endif /* (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED) */

    #if(DATALINK_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!DATALINK_TXCLKGEN_DP)
            DATALINK_TXBITCTR_CONTROL_REG |= DATALINK_CNTR_ENABLE;
        #endif /* End DATALINK_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        DATALINK_TXSTATUS_ACTL_REG |= DATALINK_INT_ENABLE;
        #if (DATALINK_TX_INTERRUPT_ENABLED)
            DATALINK_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            DATALINK_EnableTxInt();
        #endif /* (DATALINK_TX_INTERRUPT_ENABLED) */
     #endif /* (DATALINK_TX_INTERRUPT_ENABLED) */

    #if (DATALINK_INTERNAL_CLOCK_USED)
        DATALINK_IntClock_Start();  /* Enable the clock */
    #endif /* (DATALINK_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DATALINK_Stop
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
void DATALINK_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)
        DATALINK_RXBITCTR_CONTROL_REG &= (uint8) ~DATALINK_CNTR_ENABLE;
    #endif /* (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED) */

    #if (DATALINK_TX_ENABLED)
        #if(!DATALINK_TXCLKGEN_DP)
            DATALINK_TXBITCTR_CONTROL_REG &= (uint8) ~DATALINK_CNTR_ENABLE;
        #endif /* (!DATALINK_TXCLKGEN_DP) */
    #endif /* (DATALINK_TX_ENABLED) */

    #if (DATALINK_INTERNAL_CLOCK_USED)
        DATALINK_IntClock_Stop();   /* Disable the clock */
    #endif /* (DATALINK_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)
        DATALINK_RXSTATUS_ACTL_REG  &= (uint8) ~DATALINK_INT_ENABLE;

        #if (DATALINK_RX_INTERRUPT_ENABLED)
            DATALINK_DisableRxInt();
        #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */
    #endif /* (DATALINK_RX_ENABLED || DATALINK_HD_ENABLED) */

    #if (DATALINK_TX_ENABLED)
        DATALINK_TXSTATUS_ACTL_REG &= (uint8) ~DATALINK_INT_ENABLE;

        #if (DATALINK_TX_INTERRUPT_ENABLED)
            DATALINK_DisableTxInt();
        #endif /* (DATALINK_TX_INTERRUPT_ENABLED) */
    #endif /* (DATALINK_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: DATALINK_ReadControlRegister
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
uint8 DATALINK_ReadControlRegister(void) 
{
    #if (DATALINK_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(DATALINK_CONTROL_REG);
    #endif /* (DATALINK_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: DATALINK_WriteControlRegister
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
void  DATALINK_WriteControlRegister(uint8 control) 
{
    #if (DATALINK_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       DATALINK_CONTROL_REG = control;
    #endif /* (DATALINK_CONTROL_REG_REMOVED) */
}


#if(DATALINK_RX_ENABLED || DATALINK_HD_ENABLED)
    /*******************************************************************************
    * Function Name: DATALINK_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      DATALINK_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      DATALINK_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      DATALINK_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      DATALINK_RX_STS_BREAK            Interrupt on break.
    *      DATALINK_RX_STS_OVERRUN          Interrupt on overrun error.
    *      DATALINK_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      DATALINK_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void DATALINK_SetRxInterruptMode(uint8 intSrc) 
    {
        DATALINK_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: DATALINK_ReadRxData
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
    *  DATALINK_rxBuffer - RAM buffer pointer for save received data.
    *  DATALINK_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  DATALINK_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  DATALINK_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 DATALINK_ReadRxData(void) 
    {
        uint8 rxData;

    #if (DATALINK_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        DATALINK_DisableRxInt();

        locRxBufferRead  = DATALINK_rxBufferRead;
        locRxBufferWrite = DATALINK_rxBufferWrite;

        if( (DATALINK_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = DATALINK_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= DATALINK_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            DATALINK_rxBufferRead = locRxBufferRead;

            if(DATALINK_rxBufferLoopDetect != 0u)
            {
                DATALINK_rxBufferLoopDetect = 0u;
                #if ((DATALINK_RX_INTERRUPT_ENABLED) && (DATALINK_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( DATALINK_HD_ENABLED )
                        if((DATALINK_CONTROL_REG & DATALINK_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            DATALINK_RXSTATUS_MASK_REG  |= DATALINK_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        DATALINK_RXSTATUS_MASK_REG  |= DATALINK_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end DATALINK_HD_ENABLED */
                #endif /* ((DATALINK_RX_INTERRUPT_ENABLED) && (DATALINK_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = DATALINK_RXDATA_REG;
        }

        DATALINK_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = DATALINK_RXDATA_REG;

    #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: DATALINK_ReadRxStatus
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
    *  DATALINK_RX_STS_FIFO_NOTEMPTY.
    *  DATALINK_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  DATALINK_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   DATALINK_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   DATALINK_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 DATALINK_ReadRxStatus(void) 
    {
        uint8 status;

        status = DATALINK_RXSTATUS_REG & DATALINK_RX_HW_MASK;

    #if (DATALINK_RX_INTERRUPT_ENABLED)
        if(DATALINK_rxBufferOverflow != 0u)
        {
            status |= DATALINK_RX_STS_SOFT_BUFF_OVER;
            DATALINK_rxBufferOverflow = 0u;
        }
    #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: DATALINK_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. DATALINK_GetChar() is
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
    *  DATALINK_rxBuffer - RAM buffer pointer for save received data.
    *  DATALINK_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  DATALINK_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  DATALINK_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 DATALINK_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (DATALINK_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        DATALINK_DisableRxInt();

        locRxBufferRead  = DATALINK_rxBufferRead;
        locRxBufferWrite = DATALINK_rxBufferWrite;

        if( (DATALINK_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = DATALINK_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= DATALINK_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            DATALINK_rxBufferRead = locRxBufferRead;

            if(DATALINK_rxBufferLoopDetect != 0u)
            {
                DATALINK_rxBufferLoopDetect = 0u;
                #if( (DATALINK_RX_INTERRUPT_ENABLED) && (DATALINK_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( DATALINK_HD_ENABLED )
                        if((DATALINK_CONTROL_REG & DATALINK_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            DATALINK_RXSTATUS_MASK_REG |= DATALINK_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        DATALINK_RXSTATUS_MASK_REG |= DATALINK_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end DATALINK_HD_ENABLED */
                #endif /* DATALINK_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = DATALINK_RXSTATUS_REG;
            if((rxStatus & DATALINK_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = DATALINK_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (DATALINK_RX_STS_BREAK | DATALINK_RX_STS_PAR_ERROR |
                                DATALINK_RX_STS_STOP_ERROR | DATALINK_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        DATALINK_EnableRxInt();

    #else

        rxStatus =DATALINK_RXSTATUS_REG;
        if((rxStatus & DATALINK_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = DATALINK_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (DATALINK_RX_STS_BREAK | DATALINK_RX_STS_PAR_ERROR |
                            DATALINK_RX_STS_STOP_ERROR | DATALINK_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: DATALINK_GetByte
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
    uint16 DATALINK_GetByte(void) 
    {
        
    #if (DATALINK_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        DATALINK_DisableRxInt();
        locErrorStatus = (uint16)DATALINK_errorStatus;
        DATALINK_errorStatus = 0u;
        DATALINK_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | DATALINK_ReadRxData() );
    #else
        return ( ((uint16)DATALINK_ReadRxStatus() << 8u) | DATALINK_ReadRxData() );
    #endif /* DATALINK_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: DATALINK_GetRxBufferSize
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
    *  DATALINK_rxBufferWrite - used to calculate left bytes.
    *  DATALINK_rxBufferRead - used to calculate left bytes.
    *  DATALINK_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 DATALINK_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (DATALINK_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        DATALINK_DisableRxInt();

        if(DATALINK_rxBufferRead == DATALINK_rxBufferWrite)
        {
            if(DATALINK_rxBufferLoopDetect != 0u)
            {
                size = DATALINK_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(DATALINK_rxBufferRead < DATALINK_rxBufferWrite)
        {
            size = (DATALINK_rxBufferWrite - DATALINK_rxBufferRead);
        }
        else
        {
            size = (DATALINK_RX_BUFFER_SIZE - DATALINK_rxBufferRead) + DATALINK_rxBufferWrite;
        }

        DATALINK_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((DATALINK_RXSTATUS_REG & DATALINK_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: DATALINK_ClearRxBuffer
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
    *  DATALINK_rxBufferWrite - cleared to zero.
    *  DATALINK_rxBufferRead - cleared to zero.
    *  DATALINK_rxBufferLoopDetect - cleared to zero.
    *  DATALINK_rxBufferOverflow - cleared to zero.
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
    void DATALINK_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        DATALINK_RXDATA_AUX_CTL_REG |= (uint8)  DATALINK_RX_FIFO_CLR;
        DATALINK_RXDATA_AUX_CTL_REG &= (uint8) ~DATALINK_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (DATALINK_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        DATALINK_DisableRxInt();

        DATALINK_rxBufferRead = 0u;
        DATALINK_rxBufferWrite = 0u;
        DATALINK_rxBufferLoopDetect = 0u;
        DATALINK_rxBufferOverflow = 0u;

        DATALINK_EnableRxInt();

    #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: DATALINK_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  DATALINK__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  DATALINK__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  DATALINK__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  DATALINK__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  DATALINK__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DATALINK_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  DATALINK_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void DATALINK_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(DATALINK_RXHW_ADDRESS_ENABLED)
            #if(DATALINK_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* DATALINK_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = DATALINK_CONTROL_REG & (uint8)~DATALINK_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << DATALINK_CTRL_RXADDR_MODE0_SHIFT);
                DATALINK_CONTROL_REG = tmpCtrl;

                #if(DATALINK_RX_INTERRUPT_ENABLED && \
                   (DATALINK_RXBUFFERSIZE > DATALINK_FIFO_LENGTH) )
                    DATALINK_rxAddressMode = addressMode;
                    DATALINK_rxAddressDetected = 0u;
                #endif /* End DATALINK_RXBUFFERSIZE > DATALINK_FIFO_LENGTH*/
            #endif /* End DATALINK_CONTROL_REG_REMOVED */
        #else /* DATALINK_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End DATALINK_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: DATALINK_SetRxAddress1
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
    void DATALINK_SetRxAddress1(uint8 address) 
    {
        DATALINK_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: DATALINK_SetRxAddress2
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
    void DATALINK_SetRxAddress2(uint8 address) 
    {
        DATALINK_RXADDRESS2_REG = address;
    }

#endif  /* DATALINK_RX_ENABLED || DATALINK_HD_ENABLED*/


#if( (DATALINK_TX_ENABLED) || (DATALINK_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: DATALINK_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   DATALINK_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   DATALINK_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   DATALINK_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   DATALINK_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void DATALINK_SetTxInterruptMode(uint8 intSrc) 
    {
        DATALINK_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: DATALINK_WriteTxData
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
    *  DATALINK_txBuffer - RAM buffer pointer for save data for transmission
    *  DATALINK_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  DATALINK_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  DATALINK_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void DATALINK_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(DATALINK_initVar != 0u)
        {
        #if (DATALINK_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            DATALINK_DisableTxInt();

            if( (DATALINK_txBufferRead == DATALINK_txBufferWrite) &&
                ((DATALINK_TXSTATUS_REG & DATALINK_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                DATALINK_TXDATA_REG = txDataByte;
            }
            else
            {
                if(DATALINK_txBufferWrite >= DATALINK_TX_BUFFER_SIZE)
                {
                    DATALINK_txBufferWrite = 0u;
                }

                DATALINK_txBuffer[DATALINK_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                DATALINK_txBufferWrite++;
            }

            DATALINK_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            DATALINK_TXDATA_REG = txDataByte;

        #endif /*(DATALINK_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: DATALINK_ReadTxStatus
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
    uint8 DATALINK_ReadTxStatus(void) 
    {
        return(DATALINK_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: DATALINK_PutChar
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
    *  DATALINK_txBuffer - RAM buffer pointer for save data for transmission
    *  DATALINK_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  DATALINK_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  DATALINK_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void DATALINK_PutChar(uint8 txDataByte) 
    {
    #if (DATALINK_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint16 locTxBufferWrite;
        uint16 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((DATALINK_TX_BUFFER_SIZE > DATALINK_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            DATALINK_DisableTxInt();
        #endif /* (DATALINK_TX_BUFFER_SIZE > DATALINK_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = DATALINK_txBufferWrite;
            locTxBufferRead  = DATALINK_txBufferRead;

        #if ((DATALINK_TX_BUFFER_SIZE > DATALINK_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            DATALINK_EnableTxInt();
        #endif /* (DATALINK_TX_BUFFER_SIZE > DATALINK_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint16)(DATALINK_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((DATALINK_TXSTATUS_REG & DATALINK_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            DATALINK_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= DATALINK_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            DATALINK_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((DATALINK_TX_BUFFER_SIZE > DATALINK_MAX_BYTE_VALUE) && (CY_PSOC3))
            DATALINK_DisableTxInt();
        #endif /* (DATALINK_TX_BUFFER_SIZE > DATALINK_MAX_BYTE_VALUE) && (CY_PSOC3) */

            DATALINK_txBufferWrite = locTxBufferWrite;

        #if ((DATALINK_TX_BUFFER_SIZE > DATALINK_MAX_BYTE_VALUE) && (CY_PSOC3))
            DATALINK_EnableTxInt();
        #endif /* (DATALINK_TX_BUFFER_SIZE > DATALINK_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (DATALINK_TXSTATUS_REG & DATALINK_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                DATALINK_SetPendingTxInt();
            }
        }

    #else

        while((DATALINK_TXSTATUS_REG & DATALINK_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        DATALINK_TXDATA_REG = txDataByte;

    #endif /* DATALINK_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: DATALINK_PutString
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
    *  DATALINK_initVar - checked to identify that the component has been
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
    void DATALINK_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(DATALINK_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                DATALINK_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: DATALINK_PutArray
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
    *  DATALINK_initVar - checked to identify that the component has been
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
    void DATALINK_PutArray(const uint8 string[], uint16 byteCount)
                                                                    
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(DATALINK_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                DATALINK_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: DATALINK_PutCRLF
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
    *  DATALINK_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void DATALINK_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(DATALINK_initVar != 0u)
        {
            DATALINK_PutChar(txDataByte);
            DATALINK_PutChar(0x0Du);
            DATALINK_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: DATALINK_GetTxBufferSize
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
    *  DATALINK_txBufferWrite - used to calculate left space.
    *  DATALINK_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint16 DATALINK_GetTxBufferSize(void)
                                                            
    {
        uint16 size;

    #if (DATALINK_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        DATALINK_DisableTxInt();

        if(DATALINK_txBufferRead == DATALINK_txBufferWrite)
        {
            size = 0u;
        }
        else if(DATALINK_txBufferRead < DATALINK_txBufferWrite)
        {
            size = (DATALINK_txBufferWrite - DATALINK_txBufferRead);
        }
        else
        {
            size = (DATALINK_TX_BUFFER_SIZE - DATALINK_txBufferRead) +
                    DATALINK_txBufferWrite;
        }

        DATALINK_EnableTxInt();

    #else

        size = DATALINK_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & DATALINK_TX_STS_FIFO_FULL) != 0u)
        {
            size = DATALINK_FIFO_LENGTH;
        }
        else if((size & DATALINK_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (DATALINK_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: DATALINK_ClearTxBuffer
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
    *  DATALINK_txBufferWrite - cleared to zero.
    *  DATALINK_txBufferRead - cleared to zero.
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
    void DATALINK_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        DATALINK_TXDATA_AUX_CTL_REG |= (uint8)  DATALINK_TX_FIFO_CLR;
        DATALINK_TXDATA_AUX_CTL_REG &= (uint8) ~DATALINK_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (DATALINK_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        DATALINK_DisableTxInt();

        DATALINK_txBufferRead = 0u;
        DATALINK_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        DATALINK_EnableTxInt();

    #endif /* (DATALINK_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: DATALINK_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   DATALINK_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   DATALINK_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   DATALINK_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   DATALINK_SEND_WAIT_REINIT - Performs both options: 
    *      DATALINK_SEND_BREAK and DATALINK_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  DATALINK_initVar - checked to identify that the component has been
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
    *     When interrupt appear with DATALINK_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The DATALINK_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void DATALINK_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(DATALINK_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(DATALINK_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == DATALINK_SEND_BREAK) ||
                (retMode == DATALINK_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                DATALINK_WriteControlRegister(DATALINK_ReadControlRegister() |
                                                      DATALINK_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                DATALINK_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = DATALINK_TXSTATUS_REG;
                }
                while((tmpStat & DATALINK_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == DATALINK_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == DATALINK_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = DATALINK_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & DATALINK_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == DATALINK_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == DATALINK_REINIT) ||
                (retMode == DATALINK_SEND_WAIT_REINIT) )
            {
                DATALINK_WriteControlRegister(DATALINK_ReadControlRegister() &
                                              (uint8)~DATALINK_CTRL_HD_SEND_BREAK);
            }

        #else /* DATALINK_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == DATALINK_SEND_BREAK) ||
                (retMode == DATALINK_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (DATALINK_PARITY_TYPE != DATALINK__B_UART__NONE_REVB) || \
                                    (DATALINK_PARITY_TYPE_SW != 0u) )
                    DATALINK_WriteControlRegister(DATALINK_ReadControlRegister() |
                                                          DATALINK_CTRL_HD_SEND_BREAK);
                #endif /* End DATALINK_PARITY_TYPE != DATALINK__B_UART__NONE_REVB  */

                #if(DATALINK_TXCLKGEN_DP)
                    txPeriod = DATALINK_TXBITCLKTX_COMPLETE_REG;
                    DATALINK_TXBITCLKTX_COMPLETE_REG = DATALINK_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = DATALINK_TXBITCTR_PERIOD_REG;
                    DATALINK_TXBITCTR_PERIOD_REG = DATALINK_TXBITCTR_BREAKBITS8X;
                #endif /* End DATALINK_TXCLKGEN_DP */

                /* Send zeros */
                DATALINK_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = DATALINK_TXSTATUS_REG;
                }
                while((tmpStat & DATALINK_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == DATALINK_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == DATALINK_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = DATALINK_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & DATALINK_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == DATALINK_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == DATALINK_REINIT) ||
                (retMode == DATALINK_SEND_WAIT_REINIT) )
            {

            #if(DATALINK_TXCLKGEN_DP)
                DATALINK_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                DATALINK_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End DATALINK_TXCLKGEN_DP */

            #if( (DATALINK_PARITY_TYPE != DATALINK__B_UART__NONE_REVB) || \
                 (DATALINK_PARITY_TYPE_SW != 0u) )
                DATALINK_WriteControlRegister(DATALINK_ReadControlRegister() &
                                                      (uint8) ~DATALINK_CTRL_HD_SEND_BREAK);
            #endif /* End DATALINK_PARITY_TYPE != NONE */
            }
        #endif    /* End DATALINK_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: DATALINK_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       DATALINK_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       DATALINK_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears DATALINK_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void DATALINK_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( DATALINK_CONTROL_REG_REMOVED == 0u )
            DATALINK_WriteControlRegister(DATALINK_ReadControlRegister() |
                                                  DATALINK_CTRL_MARK);
        #endif /* End DATALINK_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( DATALINK_CONTROL_REG_REMOVED == 0u )
            DATALINK_WriteControlRegister(DATALINK_ReadControlRegister() &
                                                  (uint8) ~DATALINK_CTRL_MARK);
        #endif /* End DATALINK_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndDATALINK_TX_ENABLED */

#if(DATALINK_HD_ENABLED)


    /*******************************************************************************
    * Function Name: DATALINK_LoadRxConfig
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
    void DATALINK_LoadRxConfig(void) 
    {
        DATALINK_WriteControlRegister(DATALINK_ReadControlRegister() &
                                                (uint8)~DATALINK_CTRL_HD_SEND);
        DATALINK_RXBITCTR_PERIOD_REG = DATALINK_HD_RXBITCTR_INIT;

    #if (DATALINK_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        DATALINK_SetRxInterruptMode(DATALINK_INIT_RX_INTERRUPTS_MASK);
    #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: DATALINK_LoadTxConfig
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
    void DATALINK_LoadTxConfig(void) 
    {
    #if (DATALINK_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        DATALINK_SetRxInterruptMode(0u);
    #endif /* (DATALINK_RX_INTERRUPT_ENABLED) */

        DATALINK_WriteControlRegister(DATALINK_ReadControlRegister() | DATALINK_CTRL_HD_SEND);
        DATALINK_RXBITCTR_PERIOD_REG = DATALINK_HD_TXBITCTR_INIT;
    }

#endif  /* DATALINK_HD_ENABLED */


/* [] END OF FILE */
