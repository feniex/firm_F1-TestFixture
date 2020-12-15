/*******************************************************************************
* File Name: HornInput.c  
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
#include "HornInput.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 HornInput__PORT == 15 && ((HornInput__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: HornInput_Write
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
void HornInput_Write(uint8 value) 
{
    uint8 staticBits = (HornInput_DR & (uint8)(~HornInput_MASK));
    HornInput_DR = staticBits | ((uint8)(value << HornInput_SHIFT) & HornInput_MASK);
}


/*******************************************************************************
* Function Name: HornInput_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  HornInput_DM_STRONG     Strong Drive 
*  HornInput_DM_OD_HI      Open Drain, Drives High 
*  HornInput_DM_OD_LO      Open Drain, Drives Low 
*  HornInput_DM_RES_UP     Resistive Pull Up 
*  HornInput_DM_RES_DWN    Resistive Pull Down 
*  HornInput_DM_RES_UPDWN  Resistive Pull Up/Down 
*  HornInput_DM_DIG_HIZ    High Impedance Digital 
*  HornInput_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void HornInput_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(HornInput_0, mode);
}


/*******************************************************************************
* Function Name: HornInput_Read
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
*  Macro HornInput_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 HornInput_Read(void) 
{
    return (HornInput_PS & HornInput_MASK) >> HornInput_SHIFT;
}


/*******************************************************************************
* Function Name: HornInput_ReadDataReg
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
uint8 HornInput_ReadDataReg(void) 
{
    return (HornInput_DR & HornInput_MASK) >> HornInput_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(HornInput_INTSTAT) 

    /*******************************************************************************
    * Function Name: HornInput_ClearInterrupt
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
    uint8 HornInput_ClearInterrupt(void) 
    {
        return (HornInput_INTSTAT & HornInput_MASK) >> HornInput_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
