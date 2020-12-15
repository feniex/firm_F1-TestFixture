/*******************************************************************************
* File Name: SIREN_PM.c
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

#include "SIREN.h"


/***************************************
* Local data allocation
***************************************/

static SIREN_BACKUP_STRUCT  SIREN_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: SIREN_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the SIREN_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SIREN_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SIREN_SaveConfig(void)
{
    #if(SIREN_CONTROL_REG_REMOVED == 0u)
        SIREN_backup.cr = SIREN_CONTROL_REG;
    #endif /* End SIREN_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: SIREN_RestoreConfig
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
*  SIREN_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling SIREN_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void SIREN_RestoreConfig(void)
{
    #if(SIREN_CONTROL_REG_REMOVED == 0u)
        SIREN_CONTROL_REG = SIREN_backup.cr;
    #endif /* End SIREN_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: SIREN_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The SIREN_Sleep() API saves the current component state. Then it
*  calls the SIREN_Stop() function and calls 
*  SIREN_SaveConfig() to save the hardware configuration.
*  Call the SIREN_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SIREN_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SIREN_Sleep(void)
{
    #if(SIREN_RX_ENABLED || SIREN_HD_ENABLED)
        if((SIREN_RXSTATUS_ACTL_REG  & SIREN_INT_ENABLE) != 0u)
        {
            SIREN_backup.enableState = 1u;
        }
        else
        {
            SIREN_backup.enableState = 0u;
        }
    #else
        if((SIREN_TXSTATUS_ACTL_REG  & SIREN_INT_ENABLE) !=0u)
        {
            SIREN_backup.enableState = 1u;
        }
        else
        {
            SIREN_backup.enableState = 0u;
        }
    #endif /* End SIREN_RX_ENABLED || SIREN_HD_ENABLED*/

    SIREN_Stop();
    SIREN_SaveConfig();
}


/*******************************************************************************
* Function Name: SIREN_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  SIREN_Sleep() was called. The SIREN_Wakeup() function
*  calls the SIREN_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  SIREN_Sleep() function was called, the SIREN_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SIREN_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SIREN_Wakeup(void)
{
    SIREN_RestoreConfig();
    #if( (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) )
        SIREN_ClearRxBuffer();
    #endif /* End (SIREN_RX_ENABLED) || (SIREN_HD_ENABLED) */
    #if(SIREN_TX_ENABLED || SIREN_HD_ENABLED)
        SIREN_ClearTxBuffer();
    #endif /* End SIREN_TX_ENABLED || SIREN_HD_ENABLED */

    if(SIREN_backup.enableState != 0u)
    {
        SIREN_Enable();
    }
}


/* [] END OF FILE */
