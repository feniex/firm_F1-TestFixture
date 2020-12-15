/*******************************************************************************
* File Name: QUAD_1_PM.c
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

#include "QUAD_1.h"


/***************************************
* Local data allocation
***************************************/

static QUAD_1_BACKUP_STRUCT  QUAD_1_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: QUAD_1_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the QUAD_1_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_1_SaveConfig(void)
{
    #if(QUAD_1_CONTROL_REG_REMOVED == 0u)
        QUAD_1_backup.cr = QUAD_1_CONTROL_REG;
    #endif /* End QUAD_1_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: QUAD_1_RestoreConfig
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
*  QUAD_1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling QUAD_1_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void QUAD_1_RestoreConfig(void)
{
    #if(QUAD_1_CONTROL_REG_REMOVED == 0u)
        QUAD_1_CONTROL_REG = QUAD_1_backup.cr;
    #endif /* End QUAD_1_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: QUAD_1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The QUAD_1_Sleep() API saves the current component state. Then it
*  calls the QUAD_1_Stop() function and calls 
*  QUAD_1_SaveConfig() to save the hardware configuration.
*  Call the QUAD_1_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_1_Sleep(void)
{
    #if(QUAD_1_RX_ENABLED || QUAD_1_HD_ENABLED)
        if((QUAD_1_RXSTATUS_ACTL_REG  & QUAD_1_INT_ENABLE) != 0u)
        {
            QUAD_1_backup.enableState = 1u;
        }
        else
        {
            QUAD_1_backup.enableState = 0u;
        }
    #else
        if((QUAD_1_TXSTATUS_ACTL_REG  & QUAD_1_INT_ENABLE) !=0u)
        {
            QUAD_1_backup.enableState = 1u;
        }
        else
        {
            QUAD_1_backup.enableState = 0u;
        }
    #endif /* End QUAD_1_RX_ENABLED || QUAD_1_HD_ENABLED*/

    QUAD_1_Stop();
    QUAD_1_SaveConfig();
}


/*******************************************************************************
* Function Name: QUAD_1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  QUAD_1_Sleep() was called. The QUAD_1_Wakeup() function
*  calls the QUAD_1_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  QUAD_1_Sleep() function was called, the QUAD_1_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUAD_1_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUAD_1_Wakeup(void)
{
    QUAD_1_RestoreConfig();
    #if( (QUAD_1_RX_ENABLED) || (QUAD_1_HD_ENABLED) )
        QUAD_1_ClearRxBuffer();
    #endif /* End (QUAD_1_RX_ENABLED) || (QUAD_1_HD_ENABLED) */
    #if(QUAD_1_TX_ENABLED || QUAD_1_HD_ENABLED)
        QUAD_1_ClearTxBuffer();
    #endif /* End QUAD_1_TX_ENABLED || QUAD_1_HD_ENABLED */

    if(QUAD_1_backup.enableState != 0u)
    {
        QUAD_1_Enable();
    }
}


/* [] END OF FILE */
