//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvGPIO.c,v $
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


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
// Orchis2 -------------------------------------------------------------------
// GPIO initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvGPIO_Init(void)
{
    pd5 = p5 = 0x21;                        // P5_0 = DB_WR     ( default output)
                                            // P5_5 = DB_RD     ( default output)

    pd6 = p6 = 0x00;                        // P6_0 = DB0       ( default input )
                                            // P6_1 = DB1       ( default input )
                                            // P6_2 = DB2       ( default input )
                                            // P6_3 = DB3       ( default input )
                                            // P6_4 = DB4       ( default input )
                                            // P6_5 = DB5       ( default input )
                                            // P6_6 = DB6       ( default input )
                                            // P6_7 = DB7       ( default input )

    pd7 = p7 = 0x0c;                        // P7_0 = SDA       ( default input )
                                            // P7_1 = SCL       ( default input )
                                            // P7_2 = DB_CS     ( default output)
                                            // P7_3 = DB_RS     ( default output)
                                            // P7_4 = BTN0      ( default input )
                                            // P7_5 = BTN1      ( default input )
                                            // P7_6 = TXD       ( default input )
                                            // P7_7 = CLK       ( default input )

    pd8 = p8 = 0xc0;                        // P8_0 = RXD       ( default input )
                                            // P8_1 = CRS       ( default input )
                                            // P8_2 = INT       ( default input )
                                            // P8_3 = IR        ( default input )
                                            // P8_5 = VbusDTCT  ( default input )
                                            // P8_6 = LED0      ( default output)
                                            // P8_7 = LED1      ( default output)
}
