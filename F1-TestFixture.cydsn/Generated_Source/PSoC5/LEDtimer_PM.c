/*******************************************************************************
* File Name: LEDtimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "LEDtimer.h"

static LEDtimer_backupStruct LEDtimer_backup;


/*******************************************************************************
* Function Name: LEDtimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  LEDtimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LEDtimer_SaveConfig(void) 
{
    #if (!LEDtimer_UsingFixedFunction)
        LEDtimer_backup.TimerUdb = LEDtimer_ReadCounter();
        LEDtimer_backup.InterruptMaskValue = LEDtimer_STATUS_MASK;
        #if (LEDtimer_UsingHWCaptureCounter)
            LEDtimer_backup.TimerCaptureCounter = LEDtimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!LEDtimer_UDB_CONTROL_REG_REMOVED)
            LEDtimer_backup.TimerControlRegister = LEDtimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: LEDtimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  LEDtimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LEDtimer_RestoreConfig(void) 
{   
    #if (!LEDtimer_UsingFixedFunction)

        LEDtimer_WriteCounter(LEDtimer_backup.TimerUdb);
        LEDtimer_STATUS_MASK =LEDtimer_backup.InterruptMaskValue;
        #if (LEDtimer_UsingHWCaptureCounter)
            LEDtimer_SetCaptureCount(LEDtimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!LEDtimer_UDB_CONTROL_REG_REMOVED)
            LEDtimer_WriteControlRegister(LEDtimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: LEDtimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  LEDtimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void LEDtimer_Sleep(void) 
{
    #if(!LEDtimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(LEDtimer_CTRL_ENABLE == (LEDtimer_CONTROL & LEDtimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            LEDtimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            LEDtimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    LEDtimer_Stop();
    LEDtimer_SaveConfig();
}


/*******************************************************************************
* Function Name: LEDtimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  LEDtimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LEDtimer_Wakeup(void) 
{
    LEDtimer_RestoreConfig();
    #if(!LEDtimer_UDB_CONTROL_REG_REMOVED)
        if(LEDtimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                LEDtimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
