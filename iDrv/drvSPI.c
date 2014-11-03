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
#include "iDrv\Include\drvSPI.h"            // struc & define : CB_SPI


static CB_SPI   cbSPI;


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
static void SPInterruptHandler(void);


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
    pd7_7    = cMode;                   // CLK as output for master mode
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
    u5c0     = 0x90;                    // MSB first, output @ falling, input @ rising
    u5c1     = 0x00;                    // SPI disable

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

    dm1ic        = 4;                       // set DMA1 interrupt priority
}
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
void drvSPI_Go(BYTE * pacTxBuf, BYTE * pacRxBuf, WORD wCount, CB_SPI cb)
{
    BYTE    i;


    tcr1 = wCount - 1;                      // set reception count
    dar1 = (unsigned long)pacRxBuf;         // set reception buffer address
    dmae_dm1con   = 1;                      // enable DMA1

    tcr0 = wCount - 2;                      // set transmission count
    sar0 = (unsigned long)pacTxBuf + 1;     // set transmission buffer address
    dmae_dm0con   = 1;                      // enable DMA0

    u5c1  = 0x05;                           // SPI enable
    u5tb  = pacTxBuf[0];                    // ready for 1st byte transmission
    cbSPI = cb;                             // ready for callback after transmission done
}


#pragma INTERRUPT DMA1Handler               (vect=12)
void DMA1Handler(void)      { SPInterruptHandler(); }


// ***************************************************************************
// **************** START OF PRIVATE PROCEDURE IMPLEMENTATIONS ***************
// ***************************************************************************
// Orchis2 -------------------------------------------------------------------
// SPI transmission complete interrupt handler
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
static void SPInterruptHandler(void)
{
    u5c1 = 0x00;                            // SPI disable
    dmas_dm0con = 0;
    dmas_dm1con = 0;
    cbSPI();                                // application callback
}
