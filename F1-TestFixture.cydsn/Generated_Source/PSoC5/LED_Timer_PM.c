/*******************************************************************************
* File Name: LED_Timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "LED_Timer.h"

static LED_Timer_backupStruct LED_Timer_backup;


/*******************************************************************************
* Function Name: LED_Timer_SaveConfig
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
*  LED_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LED_Timer_SaveConfig(void) 
{
    #if (!LED_Timer_UsingFixedFunction)
        LED_Timer_backup.TimerUdb = LED_Timer_ReadCounter();
        LED_Timer_backup.InterruptMaskValue = LED_Timer_STATUS_MASK;
        #if (LED_Timer_UsingHWCaptureCounter)
            LED_Timer_backup.TimerCaptureCounter = LED_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!LED_Timer_UDB_CONTROL_REG_REMOVED)
            LED_Timer_backup.TimerControlRegister = LED_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: LED_Timer_RestoreConfig
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
*  LED_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LED_Timer_RestoreConfig(void) 
{   
    #if (!LED_Timer_UsingFixedFunction)

        LED_Timer_WriteCounter(LED_Timer_backup.TimerUdb);
        LED_Timer_STATUS_MASK =LED_Timer_backup.InterruptMaskValue;
        #if (LED_Timer_UsingHWCaptureCounter)
            LED_Timer_SetCaptureCount(LED_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!LED_Timer_UDB_CONTROL_REG_REMOVED)
            LED_Timer_WriteControlRegister(LED_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: LED_Timer_Sleep
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
*  LED_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void LED_Timer_Sleep(void) 
{
    #if(!LED_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(LED_Timer_CTRL_ENABLE == (LED_Timer_CONTROL & LED_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            LED_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            LED_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    LED_Timer_Stop();
    LED_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_Timer_Wakeup
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
*  LED_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LED_Timer_Wakeup(void) 
{
    LED_Timer_RestoreConfig();
    #if(!LED_Timer_UDB_CONTROL_REG_REMOVED)
        if(LED_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                LED_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
