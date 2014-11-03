//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvGPIO.h,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:55:32 $
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
#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#define DB_WR       p5_0
#define DB_RD       p5_5
#define DB_CS       p7_2
#define DB_RS       p7_3
#define DB_PD       pd6
#define DB          p6
#define LED0        p8_6
#define LED1        p8_7
#define RST         p9_7
#define CLK         p7_7

// Orchis2 -------------------------------------------------------------------
// GPIO initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvGPIO_Init(void);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
