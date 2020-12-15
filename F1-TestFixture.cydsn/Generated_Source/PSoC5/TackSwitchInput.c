/*******************************************************************************
* File Name: TackSwitchInput.c  
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
#include "TackSwitchInput.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 TackSwitchInput__PORT == 15 && ((TackSwitchInput__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: TackSwitchInput_Write
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
void TackSwitchInput_Write(uint8 value) 
{
    uint8 staticBits = (TackSwitchInput_DR & (uint8)(~TackSwitchInput_MASK));
    TackSwitchInput_DR = staticBits | ((uint8)(value << TackSwitchInput_SHIFT) & TackSwitchInput_MASK);
}


/*******************************************************************************
* Function Name: TackSwitchInput_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TackSwitchInput_DM_STRONG     Strong Drive 
*  TackSwitchInput_DM_OD_HI      Open Drain, Drives High 
*  TackSwitchInput_DM_OD_LO      Open Drain, Drives Low 
*  TackSwitchInput_DM_RES_UP     Resistive Pull Up 
*  TackSwitchInput_DM_RES_DWN    Resistive Pull Down 
*  TackSwitchInput_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TackSwitchInput_DM_DIG_HIZ    High Impedance Digital 
*  TackSwitchInput_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TackSwitchInput_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(TackSwitchInput_0, mode);
}


/*******************************************************************************
* Function Name: TackSwitchInput_Read
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
*  Macro TackSwitchInput_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TackSwitchInput_Read(void) 
{
    return (TackSwitchInput_PS & TackSwitchInput_MASK) >> TackSwitchInput_SHIFT;
}


/*******************************************************************************
* Function Name: TackSwitchInput_ReadDataReg
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
uint8 TackSwitchInput_ReadDataReg(void) 
{
    return (TackSwitchInput_DR & TackSwitchInput_MASK) >> TackSwitchInput_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TackSwitchInput_INTSTAT) 

    /*******************************************************************************
    * Function Name: TackSwitchInput_ClearInterrupt
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
    uint8 TackSwitchInput_ClearInterrupt(void) 
    {
        return (TackSwitchInput_INTSTAT & TackSwitchInput_MASK) >> TackSwitchInput_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
