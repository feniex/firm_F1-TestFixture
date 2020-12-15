/*******************************************************************************
* File Name: QUAD.c
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

#include "QUAD.h"
#if (QUAD_INTERNAL_CLOCK_USED)
    #include "QUAD_IntClock.h"
#endif /* End QUAD_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 QUAD_initVar = 0u;

#if (QUAD_TX_INTERRUPT_ENABLED && QUAD_TX_ENABLED)
    volatile uint8 QUAD_txBuffer[QUAD_TX_BUFFER_SIZE];
    volatile uint8 QUAD_txBufferRead = 0u;
    uint8 QUAD_txBufferWrite = 0u;
#endif /* (QUAD_TX_INTERRUPT_ENABLED && QUAD_TX_ENABLED) */

#if (QUAD_RX_INTERRUPT_ENABLED && (QUAD_RX_ENABLED || QUAD_HD_ENABLED))
    uint8 QUAD_errorStatus = 0u;
    volatile uint8 QUAD_rxBuffer[QUAD_RX_BUFFER_SIZE];
    volatile uint8 QUAD_rxBufferRead  = 0u;
    volatile uint8 QUAD_rxBufferWrite = 0u;
    volatile uint8 QUAD_rxBufferLoopDetect = 0u;
    volatile uint8 QUAD_rxBufferOverflow   = 0u;
    #if (QUAD_RXHW_ADDRESS_ENABLED)
        volatile uint8 QUAD_rxAddressMode = QUAD_RX_ADDRESS_MODE;
        volatile uint8 QUAD_rxAddressDetected = 0u;
    #endif /* (QUAD_RXHW_ADDRESS_ENABLED) */
#endif /* (QUAD_RX_INTERRUPT_ENABLED && (QUAD_RX_ENABLED || QUAD_HD_ENABLED)) */


/*******************************************************************************
* Function Name: QUAD_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  QUAD_Start() sets the initVar variable, calls the
*  QUAD_Init() function, and then calls the
*  QUAD_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The QUAD_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time QUAD_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the QUAD_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(QUAD_initVar == 0u)
    {
        QUAD_Init();
        QUAD_initVar = 1u;
    }

    QUAD_Enable();
}


/*******************************************************************************
* Function Name: QUAD_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call QUAD_Init() because
*  the QUAD_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QUAD_Init(void) 
{
    #if(QUAD_RX_ENABLED || QUAD_HD_ENABLED)

        #if (QUAD_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(QUAD_RX_VECT_NUM, &QUAD_RXISR);
            CyIntSetPriority(QUAD_RX_VECT_NUM, QUAD_RX_PRIOR_NUM);
            QUAD_errorStatus = 0u;
        #endif /* (QUAD_RX_INTERRUPT_ENABLED) */

        #if (QUAD_RXHW_ADDRESS_ENABLED)
            QUAD_SetRxAddressMode(QUAD_RX_ADDRESS_MODE);
            QUAD_SetRxAddress1(QUAD_RX_HW_ADDRESS1);
            QUAD_SetRxAddress2(QUAD_RX_HW_ADDRESS2);
        #endif /* End QUAD_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        QUAD_RXBITCTR_PERIOD_REG = QUAD_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        QUAD_RXSTATUS_MASK_REG  = QUAD_INIT_RX_INTERRUPTS_MASK;
    #endif /* End QUAD_RX_ENABLED || QUAD_HD_ENABLED*/

    #if(QUAD_TX_ENABLED)
        #if (QUAD_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(QUAD_TX_VECT_NUM, &QUAD_TXISR);
            CyIntSetPriority(QUAD_TX_VECT_NUM, QUAD_TX_PRIOR_NUM);
        #endif /* (QUAD_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (QUAD_TXCLKGEN_DP)
            QUAD_TXBITCLKGEN_CTR_REG = QUAD_BIT_CENTER;
            QUAD_TXBITCLKTX_COMPLETE_REG = ((QUAD_NUMBER_OF_DATA_BITS +
                        QUAD_NUMBER_OF_START_BIT) * QUAD_OVER_SAMPLE_COUNT) - 1u;
        #else
            QUAD_TXBITCTR_PERIOD_REG = ((QUAD_NUMBER_OF_DATA_BITS +
                        QUAD_NUMBER_OF_START_BIT) * QUAD_OVER_SAMPLE_8) - 1u;
        #endif /* End QUAD_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (QUAD_TX_INTERRUPT_ENABLED)
            QUAD_TXSTATUS_MASK_REG = QUAD_TX_STS_FIFO_EMPTY;
        #else
            QUAD_TXSTATUS_MASK_REG = QUAD_INIT_TX_INTERRUPTS_MASK;
        #endif /*End QUAD_TX_INTERRUPT_ENABLED*/

    #endif /* End QUAD_TX_ENABLED */

    #if(QUAD_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        QUAD_WriteControlRegister( \
            (QUAD_ReadControlRegister() & (uint8)~QUAD_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(QUAD_PARITY_TYPE << QUAD_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End QUAD_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: QUAD_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call QUAD_Enable() because the QUAD_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void QUAD_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (QUAD_RX_ENABLED || QUAD_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        QUAD_RXBITCTR_CONTROL_REG |= QUAD_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        QUAD_RXSTATUS_ACTL_REG  |= QUAD_INT_ENABLE;

        #if (QUAD_RX_INTERRUPT_ENABLED)
            QUAD_EnableRxInt();

            #if (QUAD_RXHW_ADDRESS_ENABLED)
                QUAD_rxAddressDetected = 0u;
            #endif /* (QUAD_RXHW_ADDRESS_ENABLED) */
        #endif /* (QUAD_RX_INTERRUPT_ENABLED) */
    #endif /* (QUAD_RX_ENABLED || QUAD_HD_ENABLED) */

    #if(QUAD_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!QUAD_TXCLKGEN_DP)
            QUAD_TXBITCTR_CONTROL_REG |= QUAD_CNTR_ENABLE;
        #endif /* End QUAD_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        QUAD_TXSTATUS_ACTL_REG |= QUAD_INT_ENABLE;
        #if (QUAD_TX_INTERRUPT_ENABLED)
            QUAD_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            QUAD_EnableTxInt();
        #endif /* (QUAD_TX_INTERRUPT_ENABLED) */
     #endif /* (QUAD_TX_INTERRUPT_ENABLED) */

    #if (QUAD_INTERNAL_CLOCK_USED)
        QUAD_IntClock_Start();  /* Enable the clock */
    #endif /* (QUAD_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QUAD_Stop
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
void QUAD_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (QUAD_RX_ENABLED || QUAD_HD_ENABLED)
        QUAD_RXBITCTR_CONTROL_REG &= (uint8) ~QUAD_CNTR_ENABLE;
    #endif /* (QUAD_RX_ENABLED || QUAD_HD_ENABLED) */

    #if (QUAD_TX_ENABLED)
        #if(!QUAD_TXCLKGEN_DP)
            QUAD_TXBITCTR_CONTROL_REG &= (uint8) ~QUAD_CNTR_ENABLE;
        #endif /* (!QUAD_TXCLKGEN_DP) */
    #endif /* (QUAD_TX_ENABLED) */

    #if (QUAD_INTERNAL_CLOCK_USED)
        QUAD_IntClock_Stop();   /* Disable the clock */
    #endif /* (QUAD_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (QUAD_RX_ENABLED || QUAD_HD_ENABLED)
        QUAD_RXSTATUS_ACTL_REG  &= (uint8) ~QUAD_INT_ENABLE;

        #if (QUAD_RX_INTERRUPT_ENABLED)
            QUAD_DisableRxInt();
        #endif /* (QUAD_RX_INTERRUPT_ENABLED) */
    #endif /* (QUAD_RX_ENABLED || QUAD_HD_ENABLED) */

    #if (QUAD_TX_ENABLED)
        QUAD_TXSTATUS_ACTL_REG &= (uint8) ~QUAD_INT_ENABLE;

        #if (QUAD_TX_INTERRUPT_ENABLED)
            QUAD_DisableTxInt();
        #endif /* (QUAD_TX_INTERRUPT_ENABLED) */
    #endif /* (QUAD_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: QUAD_ReadControlRegister
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
uint8 QUAD_ReadControlRegister(void) 
{
    #if (QUAD_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(QUAD_CONTROL_REG);
    #endif /* (QUAD_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: QUAD_WriteControlRegister
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
void  QUAD_WriteControlRegister(uint8 control) 
{
    #if (QUAD_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       QUAD_CONTROL_REG = control;
    #endif /* (QUAD_CONTROL_REG_REMOVED) */
}


#if(QUAD_RX_ENABLED || QUAD_HD_ENABLED)
    /*******************************************************************************
    * Function Name: QUAD_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      QUAD_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      QUAD_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      QUAD_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      QUAD_RX_STS_BREAK            Interrupt on break.
    *      QUAD_RX_STS_OVERRUN          Interrupt on overrun error.
    *      QUAD_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      QUAD_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void QUAD_SetRxInterruptMode(uint8 intSrc) 
    {
        QUAD_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: QUAD_ReadRxData
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
    *  QUAD_rxBuffer - RAM buffer pointer for save received data.
    *  QUAD_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  QUAD_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  QUAD_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 QUAD_ReadRxData(void) 
    {
        uint8 rxData;

    #if (QUAD_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        QUAD_DisableRxInt();

        locRxBufferRead  = QUAD_rxBufferRead;
        locRxBufferWrite = QUAD_rxBufferWrite;

        if( (QUAD_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = QUAD_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= QUAD_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            QUAD_rxBufferRead = locRxBufferRead;

            if(QUAD_rxBufferLoopDetect != 0u)
            {
                QUAD_rxBufferLoopDetect = 0u;
                #if ((QUAD_RX_INTERRUPT_ENABLED) && (QUAD_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( QUAD_HD_ENABLED )
                        if((QUAD_CONTROL_REG & QUAD_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            QUAD_RXSTATUS_MASK_REG  |= QUAD_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        QUAD_RXSTATUS_MASK_REG  |= QUAD_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end QUAD_HD_ENABLED */
                #endif /* ((QUAD_RX_INTERRUPT_ENABLED) && (QUAD_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = QUAD_RXDATA_REG;
        }

        QUAD_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = QUAD_RXDATA_REG;

    #endif /* (QUAD_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: QUAD_ReadRxStatus
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
    *  QUAD_RX_STS_FIFO_NOTEMPTY.
    *  QUAD_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  QUAD_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   QUAD_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   QUAD_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 QUAD_ReadRxStatus(void) 
    {
        uint8 status;

        status = QUAD_RXSTATUS_REG & QUAD_RX_HW_MASK;

    #if (QUAD_RX_INTERRUPT_ENABLED)
        if(QUAD_rxBufferOverflow != 0u)
        {
            status |= QUAD_RX_STS_SOFT_BUFF_OVER;
            QUAD_rxBufferOverflow = 0u;
        }
    #endif /* (QUAD_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: QUAD_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. QUAD_GetChar() is
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
    *  QUAD_rxBuffer - RAM buffer pointer for save received data.
    *  QUAD_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  QUAD_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  QUAD_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 QUAD_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (QUAD_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        QUAD_DisableRxInt();

        locRxBufferRead  = QUAD_rxBufferRead;
        locRxBufferWrite = QUAD_rxBufferWrite;

        if( (QUAD_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = QUAD_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= QUAD_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            QUAD_rxBufferRead = locRxBufferRead;

            if(QUAD_rxBufferLoopDetect != 0u)
            {
                QUAD_rxBufferLoopDetect = 0u;
                #if( (QUAD_RX_INTERRUPT_ENABLED) && (QUAD_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( QUAD_HD_ENABLED )
                        if((QUAD_CONTROL_REG & QUAD_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            QUAD_RXSTATUS_MASK_REG |= QUAD_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        QUAD_RXSTATUS_MASK_REG |= QUAD_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end QUAD_HD_ENABLED */
                #endif /* QUAD_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = QUAD_RXSTATUS_REG;
            if((rxStatus & QUAD_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = QUAD_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (QUAD_RX_STS_BREAK | QUAD_RX_STS_PAR_ERROR |
                                QUAD_RX_STS_STOP_ERROR | QUAD_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        QUAD_EnableRxInt();

    #else

        rxStatus =QUAD_RXSTATUS_REG;
        if((rxStatus & QUAD_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = QUAD_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (QUAD_RX_STS_BREAK | QUAD_RX_STS_PAR_ERROR |
                            QUAD_RX_STS_STOP_ERROR | QUAD_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (QUAD_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: QUAD_GetByte
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
    uint16 QUAD_GetByte(void) 
    {
        
    #if (QUAD_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        QUAD_DisableRxInt();
        locErrorStatus = (uint16)QUAD_errorStatus;
        QUAD_errorStatus = 0u;
        QUAD_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | QUAD_ReadRxData() );
    #else
        return ( ((uint16)QUAD_ReadRxStatus() << 8u) | QUAD_ReadRxData() );
    #endif /* QUAD_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: QUAD_GetRxBufferSize
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
    *  QUAD_rxBufferWrite - used to calculate left bytes.
    *  QUAD_rxBufferRead - used to calculate left bytes.
    *  QUAD_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 QUAD_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (QUAD_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        QUAD_DisableRxInt();

        if(QUAD_rxBufferRead == QUAD_rxBufferWrite)
        {
            if(QUAD_rxBufferLoopDetect != 0u)
            {
                size = QUAD_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(QUAD_rxBufferRead < QUAD_rxBufferWrite)
        {
            size = (QUAD_rxBufferWrite - QUAD_rxBufferRead);
        }
        else
        {
            size = (QUAD_RX_BUFFER_SIZE - QUAD_rxBufferRead) + QUAD_rxBufferWrite;
        }

        QUAD_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((QUAD_RXSTATUS_REG & QUAD_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (QUAD_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: QUAD_ClearRxBuffer
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
    *  QUAD_rxBufferWrite - cleared to zero.
    *  QUAD_rxBufferRead - cleared to zero.
    *  QUAD_rxBufferLoopDetect - cleared to zero.
    *  QUAD_rxBufferOverflow - cleared to zero.
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
    void QUAD_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        QUAD_RXDATA_AUX_CTL_REG |= (uint8)  QUAD_RX_FIFO_CLR;
        QUAD_RXDATA_AUX_CTL_REG &= (uint8) ~QUAD_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (QUAD_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        QUAD_DisableRxInt();

        QUAD_rxBufferRead = 0u;
        QUAD_rxBufferWrite = 0u;
        QUAD_rxBufferLoopDetect = 0u;
        QUAD_rxBufferOverflow = 0u;

        QUAD_EnableRxInt();

    #endif /* (QUAD_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: QUAD_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  QUAD__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  QUAD__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  QUAD__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  QUAD__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  QUAD__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  QUAD_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  QUAD_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void QUAD_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(QUAD_RXHW_ADDRESS_ENABLED)
            #if(QUAD_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* QUAD_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = QUAD_CONTROL_REG & (uint8)~QUAD_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << QUAD_CTRL_RXADDR_MODE0_SHIFT);
                QUAD_CONTROL_REG = tmpCtrl;

                #if(QUAD_RX_INTERRUPT_ENABLED && \
                   (QUAD_RXBUFFERSIZE > QUAD_FIFO_LENGTH) )
                    QUAD_rxAddressMode = addressMode;
                    QUAD_rxAddressDetected = 0u;
                #endif /* End QUAD_RXBUFFERSIZE > QUAD_FIFO_LENGTH*/
            #endif /* End QUAD_CONTROL_REG_REMOVED */
        #else /* QUAD_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End QUAD_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: QUAD_SetRxAddress1
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
    void QUAD_SetRxAddress1(uint8 address) 
    {
        QUAD_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: QUAD_SetRxAddress2
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
    void QUAD_SetRxAddress2(uint8 address) 
    {
        QUAD_RXADDRESS2_REG = address;
    }

#endif  /* QUAD_RX_ENABLED || QUAD_HD_ENABLED*/


#if( (QUAD_TX_ENABLED) || (QUAD_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: QUAD_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   QUAD_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   QUAD_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   QUAD_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   QUAD_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void QUAD_SetTxInterruptMode(uint8 intSrc) 
    {
        QUAD_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: QUAD_WriteTxData
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
    *  QUAD_txBuffer - RAM buffer pointer for save data for transmission
    *  QUAD_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  QUAD_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  QUAD_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void QUAD_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(QUAD_initVar != 0u)
        {
        #if (QUAD_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            QUAD_DisableTxInt();

            if( (QUAD_txBufferRead == QUAD_txBufferWrite) &&
                ((QUAD_TXSTATUS_REG & QUAD_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                QUAD_TXDATA_REG = txDataByte;
            }
            else
            {
                if(QUAD_txBufferWrite >= QUAD_TX_BUFFER_SIZE)
                {
                    QUAD_txBufferWrite = 0u;
                }

                QUAD_txBuffer[QUAD_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                QUAD_txBufferWrite++;
            }

            QUAD_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            QUAD_TXDATA_REG = txDataByte;

        #endif /*(QUAD_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: QUAD_ReadTxStatus
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
    uint8 QUAD_ReadTxStatus(void) 
    {
        return(QUAD_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: QUAD_PutChar
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
    *  QUAD_txBuffer - RAM buffer pointer for save data for transmission
    *  QUAD_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  QUAD_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  QUAD_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void QUAD_PutChar(uint8 txDataByte) 
    {
    #if (QUAD_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((QUAD_TX_BUFFER_SIZE > QUAD_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            QUAD_DisableTxInt();
        #endif /* (QUAD_TX_BUFFER_SIZE > QUAD_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = QUAD_txBufferWrite;
            locTxBufferRead  = QUAD_txBufferRead;

        #if ((QUAD_TX_BUFFER_SIZE > QUAD_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            QUAD_EnableTxInt();
        #endif /* (QUAD_TX_BUFFER_SIZE > QUAD_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(QUAD_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((QUAD_TXSTATUS_REG & QUAD_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            QUAD_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= QUAD_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            QUAD_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((QUAD_TX_BUFFER_SIZE > QUAD_MAX_BYTE_VALUE) && (CY_PSOC3))
            QUAD_DisableTxInt();
        #endif /* (QUAD_TX_BUFFER_SIZE > QUAD_MAX_BYTE_VALUE) && (CY_PSOC3) */

            QUAD_txBufferWrite = locTxBufferWrite;

        #if ((QUAD_TX_BUFFER_SIZE > QUAD_MAX_BYTE_VALUE) && (CY_PSOC3))
            QUAD_EnableTxInt();
        #endif /* (QUAD_TX_BUFFER_SIZE > QUAD_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (QUAD_TXSTATUS_REG & QUAD_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                QUAD_SetPendingTxInt();
            }
        }

    #else

        while((QUAD_TXSTATUS_REG & QUAD_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        QUAD_TXDATA_REG = txDataByte;

    #endif /* QUAD_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: QUAD_PutString
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
    *  QUAD_initVar - checked to identify that the component has been
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
    void QUAD_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(QUAD_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                QUAD_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: QUAD_PutArray
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
    *  QUAD_initVar - checked to identify that the component has been
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
    void QUAD_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(QUAD_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                QUAD_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: QUAD_PutCRLF
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
    *  QUAD_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void QUAD_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(QUAD_initVar != 0u)
        {
            QUAD_PutChar(txDataByte);
            QUAD_PutChar(0x0Du);
            QUAD_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: QUAD_GetTxBufferSize
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
    *  QUAD_txBufferWrite - used to calculate left space.
    *  QUAD_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 QUAD_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (QUAD_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        QUAD_DisableTxInt();

        if(QUAD_txBufferRead == QUAD_txBufferWrite)
        {
            size = 0u;
        }
        else if(QUAD_txBufferRead < QUAD_txBufferWrite)
        {
            size = (QUAD_txBufferWrite - QUAD_txBufferRead);
        }
        else
        {
            size = (QUAD_TX_BUFFER_SIZE - QUAD_txBufferRead) +
                    QUAD_txBufferWrite;
        }

        QUAD_EnableTxInt();

    #else

        size = QUAD_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & QUAD_TX_STS_FIFO_FULL) != 0u)
        {
            size = QUAD_FIFO_LENGTH;
        }
        else if((size & QUAD_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (QUAD_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: QUAD_ClearTxBuffer
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
    *  QUAD_txBufferWrite - cleared to zero.
    *  QUAD_txBufferRead - cleared to zero.
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
    void QUAD_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        QUAD_TXDATA_AUX_CTL_REG |= (uint8)  QUAD_TX_FIFO_CLR;
        QUAD_TXDATA_AUX_CTL_REG &= (uint8) ~QUAD_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (QUAD_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        QUAD_DisableTxInt();

        QUAD_txBufferRead = 0u;
        QUAD_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        QUAD_EnableTxInt();

    #endif /* (QUAD_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: QUAD_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   QUAD_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   QUAD_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   QUAD_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   QUAD_SEND_WAIT_REINIT - Performs both options: 
    *      QUAD_SEND_BREAK and QUAD_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  QUAD_initVar - checked to identify that the component has been
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
    *     When interrupt appear with QUAD_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The QUAD_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void QUAD_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(QUAD_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(QUAD_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == QUAD_SEND_BREAK) ||
                (retMode == QUAD_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                QUAD_WriteControlRegister(QUAD_ReadControlRegister() |
                                                      QUAD_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                QUAD_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = QUAD_TXSTATUS_REG;
                }
                while((tmpStat & QUAD_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == QUAD_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == QUAD_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = QUAD_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & QUAD_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == QUAD_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == QUAD_REINIT) ||
                (retMode == QUAD_SEND_WAIT_REINIT) )
            {
                QUAD_WriteControlRegister(QUAD_ReadControlRegister() &
                                              (uint8)~QUAD_CTRL_HD_SEND_BREAK);
            }

        #else /* QUAD_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == QUAD_SEND_BREAK) ||
                (retMode == QUAD_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (QUAD_PARITY_TYPE != QUAD__B_UART__NONE_REVB) || \
                                    (QUAD_PARITY_TYPE_SW != 0u) )
                    QUAD_WriteControlRegister(QUAD_ReadControlRegister() |
                                                          QUAD_CTRL_HD_SEND_BREAK);
                #endif /* End QUAD_PARITY_TYPE != QUAD__B_UART__NONE_REVB  */

                #if(QUAD_TXCLKGEN_DP)
                    txPeriod = QUAD_TXBITCLKTX_COMPLETE_REG;
                    QUAD_TXBITCLKTX_COMPLETE_REG = QUAD_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = QUAD_TXBITCTR_PERIOD_REG;
                    QUAD_TXBITCTR_PERIOD_REG = QUAD_TXBITCTR_BREAKBITS8X;
                #endif /* End QUAD_TXCLKGEN_DP */

                /* Send zeros */
                QUAD_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = QUAD_TXSTATUS_REG;
                }
                while((tmpStat & QUAD_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == QUAD_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == QUAD_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = QUAD_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & QUAD_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == QUAD_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == QUAD_REINIT) ||
                (retMode == QUAD_SEND_WAIT_REINIT) )
            {

            #if(QUAD_TXCLKGEN_DP)
                QUAD_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                QUAD_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End QUAD_TXCLKGEN_DP */

            #if( (QUAD_PARITY_TYPE != QUAD__B_UART__NONE_REVB) || \
                 (QUAD_PARITY_TYPE_SW != 0u) )
                QUAD_WriteControlRegister(QUAD_ReadControlRegister() &
                                                      (uint8) ~QUAD_CTRL_HD_SEND_BREAK);
            #endif /* End QUAD_PARITY_TYPE != NONE */
            }
        #endif    /* End QUAD_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: QUAD_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       QUAD_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       QUAD_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears QUAD_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void QUAD_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( QUAD_CONTROL_REG_REMOVED == 0u )
            QUAD_WriteControlRegister(QUAD_ReadControlRegister() |
                                                  QUAD_CTRL_MARK);
        #endif /* End QUAD_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( QUAD_CONTROL_REG_REMOVED == 0u )
            QUAD_WriteControlRegister(QUAD_ReadControlRegister() &
                                                  (uint8) ~QUAD_CTRL_MARK);
        #endif /* End QUAD_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndQUAD_TX_ENABLED */

#if(QUAD_HD_ENABLED)


    /*******************************************************************************
    * Function Name: QUAD_LoadRxConfig
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
    void QUAD_LoadRxConfig(void) 
    {
        QUAD_WriteControlRegister(QUAD_ReadControlRegister() &
                                                (uint8)~QUAD_CTRL_HD_SEND);
        QUAD_RXBITCTR_PERIOD_REG = QUAD_HD_RXBITCTR_INIT;

    #if (QUAD_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        QUAD_SetRxInterruptMode(QUAD_INIT_RX_INTERRUPTS_MASK);
    #endif /* (QUAD_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: QUAD_LoadTxConfig
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
    void QUAD_LoadTxConfig(void) 
    {
    #if (QUAD_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        QUAD_SetRxInterruptMode(0u);
    #endif /* (QUAD_RX_INTERRUPT_ENABLED) */

        QUAD_WriteControlRegister(QUAD_ReadControlRegister() | QUAD_CTRL_HD_SEND);
        QUAD_RXBITCTR_PERIOD_REG = QUAD_HD_TXBITCTR_INIT;
    }

#endif  /* QUAD_HD_ENABLED */


/* [] END OF FILE */
