//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: TPiDE.h,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/9/15 15:59:28 $
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
#ifndef __TPiDE_H__
#define __TPiDE_H__


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#define ISP_PAGE_SIZE       512
#define ISP_BUFFER_SIZE     516
typedef void(*CB_DONE_OUT)(INT16, DWORD);


// ***************************************************************************
// ******************** START OF PUBLIC DATA DECLARATIONS ********************
// ***************************************************************************
extern volatile DWORD       g_dwRxSize;
extern volatile BYTE        g_acISPBuf[ISP_PAGE_SIZE];
extern volatile WORD        g_wInfoCnt;
extern volatile BYTE *      g_pacInfo;


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
void    USBCDC_Init(void);
INT16   USBCDC_Read_Async(DWORD _BufferSize, BYTE* _Buffer, CB_DONE_OUT _cb);
void    CBDoneBulkRead(INT16 _err, DWORD _NumBytes);
BYTE    halIsUSBConfigOK(void);

//............................................................................

BYTE    appKbHit(void);
void    drvTPiDE_Init(void);
void    drvTPiDE_Ticking(void);
void    drvTPiDE_Scheduler(void);

//............................................................................

void    drvTimerB0Stop(void);
void    drvTimerB0Start(void);
void    drvTimerB0CountSet(WORD wDelay);
void    drvTimerB0RunTimeSet(DWORD dwDelay);
WORD    drvTimerB0CountGet(void);
DWORD   drvTimerB0RunTimeGet(void);


// Orchis2 -------------------------------------------------------------------
// check if USB busy writing (BULK IN)
//
// Params:
// none
//
// Return:
// BOOL         - TRUE : idle
// ---------------------------------------------------------------------------
BOOL appUSB_IsIdle(void);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
