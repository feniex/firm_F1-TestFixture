/*******************************************************************************
* File Name: DEMUX_CTRL_230400.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_DEMUX_CTRL_230400_H) /* CY_CONTROL_REG_DEMUX_CTRL_230400_H */
#define CY_CONTROL_REG_DEMUX_CTRL_230400_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} DEMUX_CTRL_230400_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    DEMUX_CTRL_230400_Write(uint8 control) ;
uint8   DEMUX_CTRL_230400_Read(void) ;

void DEMUX_CTRL_230400_SaveConfig(void) ;
void DEMUX_CTRL_230400_RestoreConfig(void) ;
void DEMUX_CTRL_230400_Sleep(void) ; 
void DEMUX_CTRL_230400_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define DEMUX_CTRL_230400_Control        (* (reg8 *) DEMUX_CTRL_230400_Sync_ctrl_reg__CONTROL_REG )
#define DEMUX_CTRL_230400_Control_PTR    (  (reg8 *) DEMUX_CTRL_230400_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_DEMUX_CTRL_230400_H */


/* [] END OF FILE */
