/*******************************************************************************
* File Name: USBUART_VBUS.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "USBUART_VBUS.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 USBUART_VBUS__PORT == 15 && ((USBUART_VBUS__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: USBUART_VBUS_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void USBUART_VBUS_Write(uint8 value) 
{
    uint8 staticBits = (USBUART_VBUS_DR & (uint8)(~USBUART_VBUS_MASK));
    USBUART_VBUS_DR = staticBits | ((uint8)(value << USBUART_VBUS_SHIFT) & USBUART_VBUS_MASK);
}


/*******************************************************************************
* Function Name: USBUART_VBUS_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  USBUART_VBUS_DM_STRONG     Strong Drive 
*  USBUART_VBUS_DM_OD_HI      Open Drain, Drives High 
*  USBUART_VBUS_DM_OD_LO      Open Drain, Drives Low 
*  USBUART_VBUS_DM_RES_UP     Resistive Pull Up 
*  USBUART_VBUS_DM_RES_DWN    Resistive Pull Down 
*  USBUART_VBUS_DM_RES_UPDWN  Resistive Pull Up/Down 
*  USBUART_VBUS_DM_DIG_HIZ    High Impedance Digital 
*  USBUART_VBUS_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void USBUART_VBUS_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(USBUART_VBUS_0, mode);
}


/*******************************************************************************
* Function Name: USBUART_VBUS_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro USBUART_VBUS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 USBUART_VBUS_Read(void) 
{
    return (USBUART_VBUS_PS & USBUART_VBUS_MASK) >> USBUART_VBUS_SHIFT;
}


/*******************************************************************************
* Function Name: USBUART_VBUS_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 USBUART_VBUS_ReadDataReg(void) 
{
    return (USBUART_VBUS_DR & USBUART_VBUS_MASK) >> USBUART_VBUS_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(USBUART_VBUS_INTSTAT) 

    /*******************************************************************************
    * Function Name: USBUART_VBUS_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 USBUART_VBUS_ClearInterrupt(void) 
    {
        return (USBUART_VBUS_INTSTAT & USBUART_VBUS_MASK) >> USBUART_VBUS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
