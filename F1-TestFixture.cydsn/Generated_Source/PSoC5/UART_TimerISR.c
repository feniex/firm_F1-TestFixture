/*******************************************************************************
* File Name: UART_TimerISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <UART_TimerISR.h>
#include "cyapicallbacks.h"

#if !defined(UART_TimerISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START UART_TimerISR_intc` */
//#include "CommManager.h"
/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: UART_TimerISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void UART_TimerISR_Start(void)
{
    /* For all we know the interrupt is active. */
    UART_TimerISR_Disable();

    /* Set the ISR to point to the UART_TimerISR Interrupt. */
    UART_TimerISR_SetVector(&UART_TimerISR_Interrupt);

    /* Set the priority. */
    UART_TimerISR_SetPriority((uint8)UART_TimerISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    UART_TimerISR_Enable();
}


/*******************************************************************************
* Function Name: UART_TimerISR_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void UART_TimerISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    UART_TimerISR_Disable();

    /* Set the ISR to point to the UART_TimerISR Interrupt. */
    UART_TimerISR_SetVector(address);

    /* Set the priority. */
    UART_TimerISR_SetPriority((uint8)UART_TimerISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    UART_TimerISR_Enable();
}


/*******************************************************************************
* Function Name: UART_TimerISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void UART_TimerISR_Stop(void)
{
    /* Disable this interrupt. */
    UART_TimerISR_Disable();

    /* Set the ISR to point to the passive one. */
    UART_TimerISR_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: UART_TimerISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for UART_TimerISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(UART_TimerISR_Interrupt)
{
    #ifdef UART_TimerISR_INTERRUPT_INTERRUPT_CALLBACK
        UART_TimerISR_Interrupt_InterruptCallback();
    #endif /* UART_TimerISR_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START UART_TimerISR_Interrupt` */

//    processCommTimeoutRoutine();
    
    /* `#END` */
}


/*******************************************************************************
* Function Name: UART_TimerISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling UART_TimerISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use UART_TimerISR_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void UART_TimerISR_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)UART_TimerISR__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: UART_TimerISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress UART_TimerISR_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)UART_TimerISR__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: UART_TimerISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling UART_TimerISR_Start or UART_TimerISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after UART_TimerISR_Start or UART_TimerISR_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void UART_TimerISR_SetPriority(uint8 priority)
{
    *UART_TimerISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: UART_TimerISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 UART_TimerISR_GetPriority(void)
{
    uint8 priority;


    priority = *UART_TimerISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: UART_TimerISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void UART_TimerISR_Enable(void)
{
    /* Enable the general interrupt. */
    *UART_TimerISR_INTC_SET_EN = UART_TimerISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: UART_TimerISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 UART_TimerISR_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*UART_TimerISR_INTC_SET_EN & (uint32)UART_TimerISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: UART_TimerISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void UART_TimerISR_Disable(void)
{
    /* Disable the general interrupt. */
    *UART_TimerISR_INTC_CLR_EN = UART_TimerISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: UART_TimerISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void UART_TimerISR_SetPending(void)
{
    *UART_TimerISR_INTC_SET_PD = UART_TimerISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: UART_TimerISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void UART_TimerISR_ClearPending(void)
{
    *UART_TimerISR_INTC_CLR_PD = UART_TimerISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
