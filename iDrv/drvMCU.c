//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvMCU.c,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/9/15 13:32:42 $
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
// TR16C0 clock system initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvMCU_Init(void)
{
	UINT16  delay = 2500;


	prc0 	= 1;							// enable access to clock registers
	cm21 	= 0;							// set system clock to be the main clock
	plc0	= 0x12;							// PLL frequency synthesizer divider = 2 ( 12MHz / 2 = 6MHz )
	plc06	= 1;							// enable PLLFCK ( the output must be set to 48MHz )
	plcf	= 0x04;							// PLLFCK multiplier = 8 (  6MHz x 8 = 48MH )
											// PLL divider = 3 ( 48MHz x 2 / 3 = 32MHz )

	// PLL clock stablization..............................................


	plc07	= 1;							// enable PLL
	while(delay > 0) delay--;				// wait for PLL to stabilize ( max. 20ms )
	cm11	= 1;							// set system clock to be the PLL clock
	cm21	= 0;							// default divider = 8


	// system clock up from 4MHz to 32MHz..................................


	cm1		= 0xa2;							// set PLL clock divider to 4
	cm06	= 0;							// enable CM16 & CM17 selection
	cm1		= 0x62;							// set PLL clock divider to 2
	cm1		= 0x22;							// set PLL clock divider to 1
	prc0	= 0;							// protect clock control register
}
// Orchis2 -------------------------------------------------------------------
// TR16C0 global interrupt enable
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvMCU_IE(void)
{
	ifsr2a = 0x00;							// must set this to 0 before interrupt enable
	asm("fset i");							// enable interrupts by setting i flag
}
