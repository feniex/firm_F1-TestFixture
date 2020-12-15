/*******************************************************************************
* File Name: QUAD_PM.c
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

#include "QUAD.h"


/***************************************
* Local data allocation
***************************************/

static QUAD_BACKUP_STRUCT  QUAD_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: QUAD_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the QUAD_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_SaveConfig(void)
{
    #if(QUAD_CONTROL_REG_REMOVED == 0u)
        QUAD_backup.cr = QUAD_CONTROL_REG;
    #endif /* End QUAD_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: QUAD_RestoreConfig
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
*  QUAD_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling QUAD_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void QUAD_RestoreConfig(void)
{
    #if(QUAD_CONTROL_REG_REMOVED == 0u)
        QUAD_CONTROL_REG = QUAD_backup.cr;
    #endif /* End QUAD_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: QUAD_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The QUAD_Sleep() API saves the current component state. Then it
*  calls the QUAD_Stop() function and calls 
*  QUAD_SaveConfig() to save the hardware configuration.
*  Call the QUAD_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_Sleep(void)
{
    #if(QUAD_RX_ENABLED || QUAD_HD_ENABLED)
        if((QUAD_RXSTATUS_ACTL_REG  & QUAD_INT_ENABLE) != 0u)
        {
            QUAD_backup.enableState = 1u;
        }
        else
        {
            QUAD_backup.enableState = 0u;
        }
    #else
        if((QUAD_TXSTATUS_ACTL_REG  & QUAD_INT_ENABLE) !=0u)
        {
            QUAD_backup.enableState = 1u;
        }
        else
        {
            QUAD_backup.enableState = 0u;
        }
    #endif /* End QUAD_RX_ENABLED || QUAD_HD_ENABLED*/

    QUAD_Stop();
    QUAD_SaveConfig();
}


/*******************************************************************************
* Function Name: QUAD_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  QUAD_Sleep() was called. The QUAD_Wakeup() function
*  calls the QUAD_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  QUAD_Sleep() function was called, the QUAD_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_Wakeup(void)
{
    QUAD_RestoreConfig();
    #if( (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) )
        QUAD_ClearRxBuffer();
    #endif /* End (QUAD_RX_ENABLED) || (QUAD_HD_ENABLED) */
    #if(QUAD_TX_ENABLED || QUAD_HD_ENABLED)
        QUAD_ClearTxBuffer();
    #endif /* End QUAD_TX_ENABLED || QUAD_HD_ENABLED */

    if(QUAD_backup.enableState != 0u)
    {
        QUAD_Enable();
    }
}


/* [] END OF FILE */
