/*******************************************************************************
* File Name: ParkKillInput.c  
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
#include "ParkKillInput.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 ParkKillInput__PORT == 15 && ((ParkKillInput__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: ParkKillInput_Write
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
void ParkKillInput_Write(uint8 value) 
{
    uint8 staticBits = (ParkKillInput_DR & (uint8)(~ParkKillInput_MASK));
    ParkKillInput_DR = staticBits | ((uint8)(value << ParkKillInput_SHIFT) & ParkKillInput_MASK);
}


/*******************************************************************************
* Function Name: ParkKillInput_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ParkKillInput_DM_STRONG     Strong Drive 
*  ParkKillInput_DM_OD_HI      Open Drain, Drives High 
*  ParkKillInput_DM_OD_LO      Open Drain, Drives Low 
*  ParkKillInput_DM_RES_UP     Resistive Pull Up 
*  ParkKillInput_DM_RES_DWN    Resistive Pull Down 
*  ParkKillInput_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ParkKillInput_DM_DIG_HIZ    High Impedance Digital 
*  ParkKillInput_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ParkKillInput_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ParkKillInput_0, mode);
}


/*******************************************************************************
* Function Name: ParkKillInput_Read
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
*  Macro ParkKillInput_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ParkKillInput_Read(void) 
{
    return (ParkKillInput_PS & ParkKillInput_MASK) >> ParkKillInput_SHIFT;
}


/*******************************************************************************
* Function Name: ParkKillInput_ReadDataReg
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
uint8 ParkKillInput_ReadDataReg(void) 
{
    return (ParkKillInput_DR & ParkKillInput_MASK) >> ParkKillInput_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ParkKillInput_INTSTAT) 

    /*******************************************************************************
    * Function Name: ParkKillInput_ClearInterrupt
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
    uint8 ParkKillInput_ClearInterrupt(void) 
    {
        return (ParkKillInput_INTSTAT & ParkKillInput_MASK) >> ParkKillInput_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
