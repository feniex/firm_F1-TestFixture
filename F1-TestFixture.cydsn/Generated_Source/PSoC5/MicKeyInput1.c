/*******************************************************************************
* File Name: MicKeyInput1.c  
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
#include "MicKeyInput1.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 MicKeyInput1__PORT == 15 && ((MicKeyInput1__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: MicKeyInput1_Write
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
void MicKeyInput1_Write(uint8 value) 
{
    uint8 staticBits = (MicKeyInput1_DR & (uint8)(~MicKeyInput1_MASK));
    MicKeyInput1_DR = staticBits | ((uint8)(value << MicKeyInput1_SHIFT) & MicKeyInput1_MASK);
}


/*******************************************************************************
* Function Name: MicKeyInput1_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MicKeyInput1_DM_STRONG     Strong Drive 
*  MicKeyInput1_DM_OD_HI      Open Drain, Drives High 
*  MicKeyInput1_DM_OD_LO      Open Drain, Drives Low 
*  MicKeyInput1_DM_RES_UP     Resistive Pull Up 
*  MicKeyInput1_DM_RES_DWN    Resistive Pull Down 
*  MicKeyInput1_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MicKeyInput1_DM_DIG_HIZ    High Impedance Digital 
*  MicKeyInput1_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MicKeyInput1_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(MicKeyInput1_0, mode);
}


/*******************************************************************************
* Function Name: MicKeyInput1_Read
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
*  Macro MicKeyInput1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MicKeyInput1_Read(void) 
{
    return (MicKeyInput1_PS & MicKeyInput1_MASK) >> MicKeyInput1_SHIFT;
}


/*******************************************************************************
* Function Name: MicKeyInput1_ReadDataReg
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
uint8 MicKeyInput1_ReadDataReg(void) 
{
    return (MicKeyInput1_DR & MicKeyInput1_MASK) >> MicKeyInput1_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MicKeyInput1_INTSTAT) 

    /*******************************************************************************
    * Function Name: MicKeyInput1_ClearInterrupt
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
    uint8 MicKeyInput1_ClearInterrupt(void) 
    {
        return (MicKeyInput1_INTSTAT & MicKeyInput1_MASK) >> MicKeyInput1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
