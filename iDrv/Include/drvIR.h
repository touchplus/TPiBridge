//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvIR.h,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:55:41 $
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
#ifndef __DRV_IR_H__
#define __DRV_IR_H__


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#define IR_RECORD_SIZE  1024
#define IR_HEADER_SIZE  128


#ifdef  __IR_RECORDER__
        volatile BYTE   g_cIrRecorded;
        volatile WORD   g_wCaptureCnt;
        volatile WORD   g_awIrPattern[IR_HEADER_SIZE];
        volatile WORD   g_awIrCapture[IR_RECORD_SIZE];
#else
extern  volatile BYTE   g_cIrRecorded;
extern  volatile WORD   g_wCaptureCnt;
extern  volatile WORD   g_awIrPattern[IR_HEADER_SIZE];
extern  volatile WORD   g_awIrCapture[IR_RECORD_SIZE];
#endif


// Orchis2 -------------------------------------------------------------------
// IR interrupt (INT1) initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvIR_Init(void);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
