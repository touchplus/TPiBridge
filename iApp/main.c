//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: main.c,v $
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
#include "iDrv\Include\drvMCU.h"            // function usage : drvMCU_Init
#include "iDrv\Include\drvTimer.h"          // function usage : drvTimer_Init
#include "iDrv\Include\drvGPIO.h"           // function usage : drvGPIO_Init
#include "iDrv\Include\drvSPI.h"            // function usage : drvSPI_Init
#include "iDrv\Include\drvADC.h"            // function usage : drvADC_Init
#include "iDrv\Include\drvIR.h"             // function usage : drvIR_Init
#include "iDrv\Include\drvLCD.h"            // function usage : drvLCD_Init
#include "iLib\Include\TPiDE.h"             // function usage : USBCDC_Init


// ***************************************************************************
// ******************** START OF PRIVATE DATA DECLARATIONS *******************
// ***************************************************************************
volatile static BYTE    cCnt500ms;
volatile static BYTE    acSPI_TxBuf[16];
volatile static BYTE    acSPI_RxBuf[16];


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
// Orchis2 -------------------------------------------------------------------
// main program thread
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void main(void)
{
    BOOL        bIrReported = FALSE;
    BYTE        cAdcState   = 0;
    WORD        i, wDelay;
    BYTE        cConfigured = FALSE;
    BYTE        acAdcBuf[2];


    //!!!!!!!!!!!!!!!!! TPiBridge hardware initialization !!!!!!!!!!!!!!!!!!!!

     drvMCU_Init( );                        // TR16C0 system clock initialization
    drvGPIO_Init( );                        // TPiBridge I/O initialization
     drvSPI_Init(1);                        // TPiBridge SPI initialization
     drvADC_Init( );                        // TPiBridge ADC initialization
      drvIR_Init( );                        // TPiBridge IR receiver initialization
     drvLCD_Init( );                        // TPiBridge LCD initialization
     USBCDC_Init( );                        // TPiBridge USB (CDC) driver initialization

    for(i = 0; i < 16; i++) acSPI_TxBuf[i] = i;


    //!!!!!!!!!!!!!!!!!! user application initialization !!!!!!!!!!!!!!!!!!!!!

    drvTimer_Init(40000);                   // system timer initialization (10ms)
    drvMCU_IE();                            // global interrupt enable

    //________________________________________________________________________
    //
    //                              main thread
    //________________________________________________________________________
    //
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TPiDE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    while(1) {
        if(halIsUSBConfigOK()) {
        if(      !cConfigured) {
                  cConfigured = TRUE;

            g_dwRxSize = 0;
            USBCDC_Read_Async(ISP_BUFFER_SIZE, g_acISPBuf, CBDoneBulkRead);
            drvTPiDE_Init();
            drvTimerB0Start();
            drvTimerB0CountSet(0);
        }
        else {
            drvTPiDE_Scheduler(); if(!appKbHit() ||
            drvTimerB0CountGet() >= 2) {
            drvTimerB0CountSet(0);
            drvTPiDE_Ticking();
        }

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! USER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //
    // IR decorder waveform reporting

         if(g_cIrRecorded)   {
         if( !bIrReported)   {
         if(appUSB_IsIdle()) {
              bIrReported =    TRUE;
              g_pacInfo   =   (BYTE *)g_awIrCapture;
              g_wInfoCnt  =    g_wCaptureCnt * 2; } }
    else if(  g_wInfoCnt == 0) g_cIrRecorded = bIrReported = FALSE; }


    // ADC measurement result reporting.......................................

    else {  switch( cAdcState++) {
            case 0: drvADC_Go(0);                                           break;
            case 1: acAdcBuf[ 0] = VIN;                                     break;
            case 2: drvADC_Go(1);                                           break;
            case 3: acAdcBuf[ 1] = CIN; cAdcState = 0; if(!appUSB_IsIdle()) break;
                    g_pacInfo = acAdcBuf; g_wInfoCnt = 2;                   break;
    }   }   }   }

        wDelay = CIN * 10;                  // ADC test
        da0 = 0xff;                         // DAC test
        while(--wDelay);
        wDelay = CIN * 10;                  // ADC test
        da0 = 0x00;                         // DAC test
        while(--wDelay);
    }
}
// Orchis2 -------------------------------------------------------------------
// system timer interrupt handler
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void TimerInterruptHandler(void)
{
    drvSPI_Go(acSPI_TxBuf, acSPI_RxBuf, 16);
    if(++cCnt500ms == 50) { cCnt500ms = 0;
        LED0 ^= 1;
        if(LED0) drvLCD_WriteCommand(0x29);
        else     drvLCD_WriteCommand(0x28);
    }
}
