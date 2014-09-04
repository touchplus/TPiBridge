//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvTimer.c,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/9/4 22:20:41 $
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


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
void TimerInterruptHandler(void);


// Orchis2 -------------------------------------------------------------------
// system timer (A0) initialization
//
// Params:
// wValue       - ta0 register setting
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvTimer_Init(UINT16 wValue)
{
    ta0s  = 0;                              // stop timerA0
    ta0mr = 0x40;                           // timer mode clocked by f8 ( 32MHz / 8 = 4MHz )
    ta0   = wValue - 1;                     // configurable time base
    ta0s  = 1;                              // start timer
    ta0ic = 4;                              // set TimerA0 interrupt priority
}

//............................................................................

#pragma INTERRUPT TimerA0Handler    (vect=21)
void TimerA0Handler(void) { TimerInterruptHandler(); }
