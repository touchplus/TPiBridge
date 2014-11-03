//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvLCD.h,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:55:54 $
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
#ifndef __DRV_LCD_H__
#define __DRV_LCD_H__


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define LCD_SLEEP_OUT       0x11
#define LCD_GAMMA_SET       0x26
#define LCD_FRAME_NORMAL    0xb1
#define LCD_POWER_CTRL1     0xc0
#define LCD_POWER_CTRL2     0xc1
#define LCD_VCOM_CTRL1      0xc5
#define LCD_VCOM_OFFSET     0xc7
#define LCD_PIX_FORMAT      0x3a
#define LCD_COLUMN_SET      0x2a
#define LCD_PAGE_SET        0x2b
#define LCD_INV_CTRL        0xb4
#define LCD_MEM_CTRL        0x36
#define LCD_GAM_R_SEL       0xf2
#define LCD_POS_GAM_SET     0xe0
#define LCD_NEG_GAM_SET     0xe1
#define LCD_DISPLAY_ON      0x29
#define LCD_MEM_WRITE       0x2c


// Orchis2 -------------------------------------------------------------------
// LCD module initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvLCD_Init(void);


// Orchis2 -------------------------------------------------------------------
// LCD command write (through 8-bit parallel interface)
//
// Params:
// cData        - command to write to
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvLCD_WriteCommand(BYTE cData);


// Orchis2 -------------------------------------------------------------------
// LCD command write (through 8-bit parallel interface)
//
// Params:
// pacData      - pointer to command buffer
// cBytes       - command byte count
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvLCD_WriteCommandN(BYTE * pacData, WORD wBytes);


// Orchis2 -------------------------------------------------------------------
// LCD data write (through 8-bit parallel interface)
//
// Params:
// cData        - data to write to
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvLCD_WriteData(BYTE cData);


// Orchis2 -------------------------------------------------------------------
// LCD data write (through 8-bit parallel interface)
//
// Params:
// pacData      - pointer to data buffer
// cBytes       - data byte count
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvLCD_WriteDataN(BYTE * pacData, WORD wBytes);


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
