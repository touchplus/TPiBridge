//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvADC.c,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:53:28 $
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


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
// Orchis2 -------------------------------------------------------------------
// ADC function initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvADC_Init(void)
{
    adst_ad0con0 = 0;
         ad0con2 = 0x00;                    // fixed fAD = f1
         ad0con1 = 0xb0;                    // default channel selection (ADEX1)
         ad0con0 = 0x08;                    // fixed repeat mode
}
// Orchis2 -------------------------------------------------------------------
// start ADC measurement
//
// Params:
// ch           - channel selection (0:ANEX0 / 1:ANEX1)
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvADC_Go(BYTE ch)
{
    adst_ad0con0 = 0;                       // stop current measurement
         ad0con1 = (ch == 0) ? 0x70 : 0xb0; // ANEX0 / ANEX1 selection
    adst_ad0con0 = 1;                       // start new measurement
}
