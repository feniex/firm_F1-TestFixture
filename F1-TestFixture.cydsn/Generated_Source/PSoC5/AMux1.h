/*******************************************************************************
* File Name: AMux1.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_AMux1_H)
#define CY_AMUX_AMux1_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void AMux1_Start(void) ;
#define AMux1_Init() AMux1_Start()
void AMux1_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void AMux1_Stop(void); */
/* void AMux1_Select(uint8 channel); */
/* void AMux1_Connect(uint8 channel); */
/* void AMux1_Disconnect(uint8 channel); */
/* void AMux1_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define AMux1_CHANNELS  2u
#define AMux1_MUXTYPE   1
#define AMux1_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define AMux1_NULL_CHANNEL 0xFFu
#define AMux1_MUX_SINGLE   1
#define AMux1_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMux1_MUXTYPE == AMux1_MUX_SINGLE
# if !AMux1_ATMOSTONE
#  define AMux1_Connect(channel) AMux1_Set(channel)
# endif
# define AMux1_Disconnect(channel) AMux1_Unset(channel)
#else
# if !AMux1_ATMOSTONE
void AMux1_Connect(uint8 channel) ;
# endif
void AMux1_Disconnect(uint8 channel) ;
#endif

#if AMux1_ATMOSTONE
# define AMux1_Stop() AMux1_DisconnectAll()
# define AMux1_Select(channel) AMux1_FastSelect(channel)
void AMux1_DisconnectAll(void) ;
#else
# define AMux1_Stop() AMux1_Start()
void AMux1_Select(uint8 channel) ;
# define AMux1_DisconnectAll() AMux1_Start()
#endif

#endif /* CY_AMUX_AMux1_H */


/* [] END OF FILE */
