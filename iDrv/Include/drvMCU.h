//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvMCU.h,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:56:08 $
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
#ifndef __DRV_MCU_H__
#define __DRV_MCU_H__


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// Orchis2 -------------------------------------------------------------------
// TR16C0 clock system initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvMCU_Init(void);


// Orchis2 -------------------------------------------------------------------
// TR16C0 global interrupt enable
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvMCU_IE(void);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
