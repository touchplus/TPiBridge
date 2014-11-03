//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvADC.h,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:54:59 $
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
#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#define CH_VIN      0
#define CH_CIN      1
#define VIN         ad00
#define CIN         ad01


// Orchis2 -------------------------------------------------------------------
// ADC function initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvADC_Init(void);


// Orchis2 -------------------------------------------------------------------
// start ADC measurement
//
// Params:
// ch           - channel selection (0:ANEX0 / 1:ANEX1)
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvADC_Go(BYTE ch);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
