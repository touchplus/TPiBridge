//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvSPI.h,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:56:21 $
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
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


typedef void(*CB_SPI)(void);


// Orchis2 -------------------------------------------------------------------
// SPI function initialization
//
// Params:
// cMode        - 1 : SPI master
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvSPI_Init(BYTE cMode);


// Orchis2 -------------------------------------------------------------------
// start SPI communication
//
// Params:
// pacTxBuf     - pointer to transmission buffer
// pacRxBuf     - pointer to reception buffer
// wCount       - byte count
// cb           - callback function pointer
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvSPI_Go(BYTE * pacTxBuf, BYTE * pacRxBuf, WORD wCount, CB_SPI cb);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
