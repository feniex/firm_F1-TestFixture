/*******************************************************************************
* File Name: ADC_AudioStream_PM.c
* Version 3.10
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

#include "ADC_AudioStream.h"


/***************************************
* Local data allocation
***************************************/

static ADC_AudioStream_BACKUP_STRUCT  ADC_AudioStream_backup =
{
    ADC_AudioStream_DISABLED
};


/*******************************************************************************
* Function Name: ADC_AudioStream_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_AudioStream_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_AudioStream_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_AudioStream_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_AudioStream_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ADC_AudioStream_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_AudioStream_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_AudioStream_Sleep(void)
{
    if((ADC_AudioStream_PWRMGR_SAR_REG  & ADC_AudioStream_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_AudioStream_SAR_CSR0_REG & ADC_AudioStream_SAR_SOF_START_CONV) != 0u)
        {
            ADC_AudioStream_backup.enableState = ADC_AudioStream_ENABLED | ADC_AudioStream_STARTED;
        }
        else
        {
            ADC_AudioStream_backup.enableState = ADC_AudioStream_ENABLED;
        }
        ADC_AudioStream_Stop();
    }
    else
    {
        ADC_AudioStream_backup.enableState = ADC_AudioStream_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_AudioStream_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ADC_AudioStream_Sleep() was called. If the component was enabled before the
*  ADC_AudioStream_Sleep() function was called, the
*  ADC_AudioStream_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_AudioStream_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_AudioStream_Wakeup(void)
{
    if(ADC_AudioStream_backup.enableState != ADC_AudioStream_DISABLED)
    {
        ADC_AudioStream_Enable();
        #if(ADC_AudioStream_DEFAULT_CONV_MODE != ADC_AudioStream__HARDWARE_TRIGGER)
            if((ADC_AudioStream_backup.enableState & ADC_AudioStream_STARTED) != 0u)
            {
                ADC_AudioStream_StartConvert();
            }
        #endif /* End ADC_AudioStream_DEFAULT_CONV_MODE != ADC_AudioStream__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
