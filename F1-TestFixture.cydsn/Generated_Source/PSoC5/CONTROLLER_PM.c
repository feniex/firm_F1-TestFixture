/*******************************************************************************
* File Name: CONTROLLER_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CONTROLLER.h"


/***************************************
* Local data allocation
***************************************/

static CONTROLLER_BACKUP_STRUCT  CONTROLLER_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: CONTROLLER_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the CONTROLLER_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  CONTROLLER_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CONTROLLER_SaveConfig(void)
{
    #if(CONTROLLER_CONTROL_REG_REMOVED == 0u)
        CONTROLLER_backup.cr = CONTROLLER_CONTROL_REG;
    #endif /* End CONTROLLER_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: CONTROLLER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  CONTROLLER_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling CONTROLLER_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void CONTROLLER_RestoreConfig(void)
{
    #if(CONTROLLER_CONTROL_REG_REMOVED == 0u)
        CONTROLLER_CONTROL_REG = CONTROLLER_backup.cr;
    #endif /* End CONTROLLER_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: CONTROLLER_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The CONTROLLER_Sleep() API saves the current component state. Then it
*  calls the CONTROLLER_Stop() function and calls 
*  CONTROLLER_SaveConfig() to save the hardware configuration.
*  Call the CONTROLLER_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  CONTROLLER_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CONTROLLER_Sleep(void)
{
    #if(CONTROLLER_RX_ENABLED || CONTROLLER_HD_ENABLED)
        if((CONTROLLER_RXSTATUS_ACTL_REG  & CONTROLLER_INT_ENABLE) != 0u)
        {
            CONTROLLER_backup.enableState = 1u;
        }
        else
        {
            CONTROLLER_backup.enableState = 0u;
        }
    #else
        if((CONTROLLER_TXSTATUS_ACTL_REG  & CONTROLLER_INT_ENABLE) !=0u)
        {
            CONTROLLER_backup.enableState = 1u;
        }
        else
        {
            CONTROLLER_backup.enableState = 0u;
        }
    #endif /* End CONTROLLER_RX_ENABLED || CONTROLLER_HD_ENABLED*/

    CONTROLLER_Stop();
    CONTROLLER_SaveConfig();
}


/*******************************************************************************
* Function Name: CONTROLLER_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  CONTROLLER_Sleep() was called. The CONTROLLER_Wakeup() function
*  calls the CONTROLLER_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  CONTROLLER_Sleep() function was called, the CONTROLLER_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  CONTROLLER_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void CONTROLLER_Wakeup(void)
{
    CONTROLLER_RestoreConfig();
    #if( (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) )
        CONTROLLER_ClearRxBuffer();
    #endif /* End (CONTROLLER_RX_ENABLED) || (CONTROLLER_HD_ENABLED) */
    #if(CONTROLLER_TX_ENABLED || CONTROLLER_HD_ENABLED)
        CONTROLLER_ClearTxBuffer();
    #endif /* End CONTROLLER_TX_ENABLED || CONTROLLER_HD_ENABLED */

    if(CONTROLLER_backup.enableState != 0u)
    {
        CONTROLLER_Enable();
    }
}


/* [] END OF FILE */
