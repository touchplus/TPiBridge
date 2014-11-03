//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvIR.c,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:57:11 $
//
// ---------------------------------------------------------------------------
// >>>>>>>>>>>>>>>>>>>>>>>>> COPYRIGHT NOTICE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ---------------------------------------------------------------------------
// Copyright 2014 (c) Touchplus information Corp.
//
// Touchplus information Corp. owns the sole copyright to this software.
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

//............................................................................

#define __IR_RECORDER__                     // global variable allocation
#include "iDrv\Include\drvIR.h"             // struc & define : g_wCaptureCnt


// ***************************************************************************
// ******************** START OF PRIVATE DATA DECLARATIONS *******************
// ***************************************************************************
static BYTE     cOverflow;


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
static void IrInterruptHandler(void);
static void   IrTimeoutHandler(void);


// Orchis2 -------------------------------------------------------------------
// IR interrupt (INT1) initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvIR_Init()
{
    int1ic = 7;                             // set INT1 interrupt priority (falling edge)

    ta1s   = 0;                             // stop timerA1
    ta1mr  = 0x40;                          // timer mode clocked by f8 ( 32MHz / 8 = 4MHz )
    ta1    = 20 - 1;                        // 200kHz (4MHz / 20) time base
    ta1s   = 1;                             // start timerA1

    ta2s   = 0;                             // stop timerA2
    ta2mr  = 0x41;                          // event counter mode (free-run type)
    ta2ud  = 1; ta2    = 0;                 // increment from 0
    ta2tgl = 0; ta2tgh = 1;                 // event from timerA1
    ta2ic  = 4;                             // set TimerA2 interrupt priority

    cOverflow = FALSE;                      // ready for new recording
}

//............................................................................

#pragma INTERRUPT INT1Handler               (vect=30)
void INT1Handler(void)      { IrInterruptHandler(); }

#pragma INTERRUPT TimerA2Handler            (vect=23)
void TimerA2Handler(void)   {   IrTimeoutHandler(); }


// ***************************************************************************
// **************** START OF PRIVATE PROCEDURE IMPLEMENTATIONS ***************
// ***************************************************************************
// Orchis2 -------------------------------------------------------------------
// IR pulse edge triggered interrupt handler
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
static void IrInterruptHandler(void)
{
    pol_int1ic ^= 1;                        // INT1 trigger edge polarity toggle
    if   (ta2s == 0) g_wCaptureCnt = 0;     // start new waveform recording or
    else {ta2s  = 0;                        // stop current pulse measurement


    // start new measurement after current pulse width recording..............

    if   (g_cIrRecorded || g_wCaptureCnt   >= IR_RECORD_SIZE) cOverflow = TRUE; 
    else  g_awIrCapture[   g_wCaptureCnt++] = ta2; ta2 = 0; }
    ta2s = 1;
}
// Orchis2 -------------------------------------------------------------------
// IR pulse width measurement timeout handler
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
static void IrTimeoutHandler(void)
{
    if(pol_int1ic) return;                  // keep waiting while IR active
    if(!cOverflow) g_cIrRecorded = TRUE;    // trigger IR waveform recognization
        cOverflow = FALSE; ta2s = 0;        // end of measurement after idle timeout
}
