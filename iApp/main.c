//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: main.c,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/8/25 18:30:41 $
//
// ---------------------------------------------------------------------------
// >>>>>>>>>>>>>>>>>>>>>>>>> COPYRIGHT NOTICE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ---------------------------------------------------------------------------
// Copyright 2014 (c) Touchplus information Corp.
//
// Touchplus information Corp. owns the sole copyright to this software.
// Under international copyright laws you
// ---------------------------------------------------------------------------
// >>>>>>>>>>>>>>>>>>>>>>>>>>>> WARRANTEE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ---------------------------------------------------------------------------
// Touchplus information Corp. MAKES NO WARRANTY OF ANY KIND WITH REGARD TO
// THE USE OF THIS SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY OR
// FITNESS FOR A PARTICULAR PURPOSE.
// ---------------------------------------------------------------------------
#include "sfr6c.h"                          // TR16C0 special function register
#include "iLib\Include\Orchis.h"            // Orchis standard type definition
#include "iDrv\Include\drvMCU.h"            // function usage : drvMCU_Init
#include "iDrv\Include\drvGPIO.h"           // function usage : drvGPIO_Init
#include "iDrv\Include\drvTimer.h"          // function usage : drvTimer_Init


// ***************************************************************************
// ******************** START OF PRIVATE DATA DECLARATIONS *******************
// ***************************************************************************
volatile static BYTE    cCnt500ms;


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
// Orchis2 -------------------------------------------------------------------
// main program thread
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void main(void)
{
    drvMCU_Init();                          // system clock initialization
    drvGPIO_Init();                         // TPiBridge IO initialization
    drvTimer_Init(40000);                   // system timer initialization (10ms)
    drvMCU_IE();                            // global interrupt enable

    //________________________________________________________________________
    //
    //                              main thread
    //________________________________________________________________________

    while(1)
    {
    }
}
// Orchis2 -------------------------------------------------------------------
// system timer interrupt handler
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void TimerInterruptHandler(void)
{
    if(++cCnt500ms == 50) { cCnt500ms = 0;
        LED0 ^= 1;
        LED1 ^= 1;
    }
}
