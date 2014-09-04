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
#include "iDrv\Include\drvTimer.h"          // function usage : drvTimer_Init
#include "iDrv\Include\drvGPIO.h"           // function usage : drvGPIO_Init
#include "iDrv\Include\drvADC.h"            // function usage : drvADC_Init
#include "iDrv\Include\drvIR.h"             // function usage : drvIR_Init
#include "iDrv\Include\drvLCD.h"            // function usage : drvLCD_Init


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
    WORD    i, wDelay;


    drvMCU_Init();                          // TR16C0 system clock initialization
    drvGPIO_Init();                         // TPiBridge I/O initialization
    drvADC_Init();                          // TPiBridge ADC initialization
    drvIR_Init();                           // TPiBridge IR receiver initialization
    drvLCD_Init();                          // TPiBridge LCD initialization
    drvTimer_Init(40000);                   // system timer initialization (10ms)
    drvMCU_IE();                            // global interrupt enable

    //________________________________________________________________________
    //
    //                              main thread
    //________________________________________________________________________
    //

    while(1)
    {
        if(g_cIrRecorded) { LED1 ^= 1; g_cIrRecorded = FALSE; }

        wDelay = CIN * 10;                  // ADC test
        da0 = 0xff;                         // DAC test
        while(--wDelay);
        wDelay = CIN * 10;                  // ADC test
        da0 = 0x00;                         // DAC test
        while(--wDelay);
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
        if(LED0) drvLCD_WriteCommand(0x29);
        else     drvLCD_WriteCommand(0x28);
    }
}

