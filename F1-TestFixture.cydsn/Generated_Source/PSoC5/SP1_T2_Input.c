/*******************************************************************************
* File Name: SP1_T2_Input.c  
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
#include "SP1_T2_Input.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SP1_T2_Input__PORT == 15 && ((SP1_T2_Input__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SP1_T2_Input_Write
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
void SP1_T2_Input_Write(uint8 value) 
{
    uint8 staticBits = (SP1_T2_Input_DR & (uint8)(~SP1_T2_Input_MASK));
    SP1_T2_Input_DR = staticBits | ((uint8)(value << SP1_T2_Input_SHIFT) & SP1_T2_Input_MASK);
}


/*******************************************************************************
* Function Name: SP1_T2_Input_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SP1_T2_Input_DM_STRONG     Strong Drive 
*  SP1_T2_Input_DM_OD_HI      Open Drain, Drives High 
*  SP1_T2_Input_DM_OD_LO      Open Drain, Drives Low 
*  SP1_T2_Input_DM_RES_UP     Resistive Pull Up 
*  SP1_T2_Input_DM_RES_DWN    Resistive Pull Down 
*  SP1_T2_Input_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SP1_T2_Input_DM_DIG_HIZ    High Impedance Digital 
*  SP1_T2_Input_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SP1_T2_Input_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SP1_T2_Input_0, mode);
}


/*******************************************************************************
* Function Name: SP1_T2_Input_Read
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
*  Macro SP1_T2_Input_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SP1_T2_Input_Read(void) 
{
    return (SP1_T2_Input_PS & SP1_T2_Input_MASK) >> SP1_T2_Input_SHIFT;
}


/*******************************************************************************
* Function Name: SP1_T2_Input_ReadDataReg
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
uint8 SP1_T2_Input_ReadDataReg(void) 
{
    return (SP1_T2_Input_DR & SP1_T2_Input_MASK) >> SP1_T2_Input_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SP1_T2_Input_INTSTAT) 

    /*******************************************************************************
    * Function Name: SP1_T2_Input_ClearInterrupt
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
    uint8 SP1_T2_Input_ClearInterrupt(void) 
    {
        return (SP1_T2_Input_INTSTAT & SP1_T2_Input_MASK) >> SP1_T2_Input_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
