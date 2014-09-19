//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvSPI.c,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/9/19 22:32:34 $
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
// SPI function initialization
//
// Params:
// cMode        - 1 : SPI master
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvSPI_Init(BYTE cMode)
{
    pd7_7    = 1;                       // CLK as output
    pd7_6    = 1;                       // TXD as output
    pd8_0    = 0;                       // RXD as input


    // SPI clock configuration................................................

    uclksel0 = 0;                       // f1 as clock source
    prc0     = 1;                       // unprotect PCLKR
    pclk1    = 1;                       // f1SIO selection
    prc0     = 0;                       // protect PCLKR
    u5brg    = 1;                       // 16MHz baud rate (32MHz / 2)


    // SPI mode configuration.................................................

    u5mr     = cMode == 1 ? 0x01 : 0x09;// SPI mode
    u5c0     = 0xd0;                    // MSB first, output @ rising, input @ falling
    u5c1     = 0x05; 	                // SPI enable

    u5smr    = 0x00;                    // (unused)
    u5smr2   = 0x00;                    // (unused)
    u5smr3   = 0x00;                    // CLK as CMOS output
    u5smr4   = 0x00;                    // (unused)


    // DMA channel assignment.................................................

    dmae_dm0con  = 0;                       // disable DMA0
	dm0sl        = 0x11;                    // SPI  as DMA0 request source	
	dm0con       = 0x11;                    // 8-bit transfer
	dar0         = (unsigned long)&u5tb;    // fixed destination address

    dmae_dm1con  = 0;                       // disable DMA1
	dm1sl        = 0x12;                    // SPI  as DMA1 request source	
	dm1con       = 0x21;                    // 8-bit transfer
	sar1         = (unsigned long)&u5rb;    // fixed source address
}
// Orchis2 -------------------------------------------------------------------
// start SPI communication
//
// Params:
// pacTxBuf     - pointer to transmission buffer
// pacRxBuf     - pointer to reception buffer
// wCount       - byte count
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvSPI_Go(BYTE * pacTxBuf, BYTE * pacRxBuf, WORD wCount)
{
    dmae_dm1con   = 0;                      // disable DMA1
	tcr1 = wCount - 1;                      // set reception count
    dar1 = (unsigned long)pacRxBuf;         // set reception buffer address
    dmae_dm1con   = 1;                      // enable  DMA1

    dmae_dm0con   = 0;                      // disable DMA0
	tcr0 = wCount - 1;                      // set transmission count
    sar0 = (unsigned long)pacTxBuf;         // set transmission buffer address
    dmae_dm0con   = 1;                      // enable  DMA0
    u5tb = pacTxBuf[0];
}
