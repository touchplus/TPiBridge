//----------------------------------------------------------------------------
// Touchplus information Corp.
//
// $RCSfile: drvLCD.c,v $
// $Revision: 0.9 $
// $Author: Albert Hu $
// $Date: 2014/10/30 PM 07:57:31 $
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
#include "iDrv\Include\drvGPIO.h"           // struc & define : DB
#include "iDrv\Include\drvLCD.h"            // function usage : drvLCD_WriteCommand


// ***************************************************************************
// **************** START OF PUBLIC PROCEDURE IMPLEMENTATIONS ****************
// ***************************************************************************
// Orchis2 -------------------------------------------------------------------
// LCD module initialization
//
// Params:
// none
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvLCD_Init(void)
{
    BYTE    acData[2];
    WORD    wDelay;

    drvLCD_WriteCommand(LCD_SLEEP_OUT);
    wDelay = 25000;
    while(wDelay) wDelay--;

    drvLCD_WriteCommand(LCD_GAMMA_SET);
    drvLCD_WriteData(0x04);
    drvLCD_WriteCommand(LCD_FRAME_NORMAL);
    drvLCD_WriteData(0x08);
    drvLCD_WriteData(0x10);
    drvLCD_WriteCommand(LCD_POWER_CTRL1);
    drvLCD_WriteData(0x10);
    drvLCD_WriteData(0x00);
    drvLCD_WriteCommand(LCD_POWER_CTRL2);
    drvLCD_WriteData(0x03);
    drvLCD_WriteCommand(LCD_VCOM_CTRL1);
    drvLCD_WriteData(0x4E);
    drvLCD_WriteData(0x30);
    drvLCD_WriteCommand(LCD_VCOM_OFFSET);
    drvLCD_WriteData(0xBC);
    drvLCD_WriteCommand(LCD_PIX_FORMAT);
    drvLCD_WriteData(0x05);
    drvLCD_WriteCommand(LCD_COLUMN_SET);
    drvLCD_WriteData(0x00);
    drvLCD_WriteData(0x00);
    drvLCD_WriteData(0x00);
    drvLCD_WriteData(0x7F);
    drvLCD_WriteCommand(LCD_PAGE_SET);
    drvLCD_WriteData(0x00);
    drvLCD_WriteData(0x00);
    drvLCD_WriteData(0x00);
    drvLCD_WriteData(0x9F);
    drvLCD_WriteCommand(LCD_INV_CTRL);
    drvLCD_WriteData(0x00);
    drvLCD_WriteCommand(LCD_MEM_CTRL);
    drvLCD_WriteData(0xC8);
    drvLCD_WriteCommand(0xEC);
    drvLCD_WriteData(0x0B);
    drvLCD_WriteCommand(LCD_GAM_R_SEL);
    drvLCD_WriteData(0x01);
    drvLCD_WriteCommand(LCD_POS_GAM_SET);
    drvLCD_WriteData(0x3F);
    drvLCD_WriteData(0x31);
    drvLCD_WriteData(0x2D);
    drvLCD_WriteData(0x2F);
    drvLCD_WriteData(0x28);
    drvLCD_WriteData(0x0D);
    drvLCD_WriteData(0x59);
    drvLCD_WriteData(0xA8);
    drvLCD_WriteData(0x44);
    drvLCD_WriteData(0x18);
    drvLCD_WriteData(0x1F);
    drvLCD_WriteData(0x10);
    drvLCD_WriteData(0x07);
    drvLCD_WriteData(0x02);
    drvLCD_WriteData(0x00);
    drvLCD_WriteCommand(LCD_NEG_GAM_SET);
    drvLCD_WriteData(0x00);
    drvLCD_WriteData(0x0E);
    drvLCD_WriteData(0x12);
    drvLCD_WriteData(0x10);
    drvLCD_WriteData(0x17);
    drvLCD_WriteData(0x12);
    drvLCD_WriteData(0x26);
    drvLCD_WriteData(0x57);
    drvLCD_WriteData(0x3B);
    drvLCD_WriteData(0x07);
    drvLCD_WriteData(0x20);
    drvLCD_WriteData(0x2F);
    drvLCD_WriteData(0x38);
    drvLCD_WriteData(0x3D);
    drvLCD_WriteData(0x3f);
    drvLCD_WriteCommand(LCD_DISPLAY_ON);
    drvLCD_WriteCommand(LCD_MEM_WRITE);

    acData[0] = 0x3f; acData[1] = 0x00;
    for(wDelay = 0; wDelay < 10000; wDelay++) { drvLCD_WriteDataN(acData, 2); }
}
// Orchis2 -------------------------------------------------------------------
// LCD command write (through 8-bit parallel interface)
//
// Params:
// cData        - command to write to
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvLCD_WriteCommand(BYTE cData)
{
    DB    = cData;
    DB_PD = 0xff;
    DB_RS = 0;
    DB_CS = 0;
    DB_WR = 0;
    DB_WR = 1;
    DB_CS = 1;
    DB_RS = 1;
    DB_PD = 0x00;
}
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
void drvLCD_WriteCommandN(BYTE * pacData, WORD wBytes)
{
    WORD    i;


    DB_PD = 0xff;
    DB_RS = 0;
    DB_CS = 0;

    for(i = 0; i < wBytes; i++) {
    DB    = pacData[i];
    DB_WR = 0;
    DB_WR = 1; }

    DB_CS = 1;
    DB_RS = 1;
    DB_PD = 0x00;
}
// Orchis2 -------------------------------------------------------------------
// LCD data write (through 8-bit parallel interface)
//
// Params:
// cData        - data to write to
//
// Return:
// none
// ---------------------------------------------------------------------------
void drvLCD_WriteData(BYTE cData)
{
    DB    = cData;
    DB_PD = 0xff;
    DB_CS = 0;
    DB_WR = 0;
    DB_WR = 1;
    DB_CS = 1;
    DB_PD = 0x00;
}
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
void drvLCD_WriteDataN(BYTE * pacData, WORD wBytes)
{
    WORD    i;


    DB_PD = 0xff;
    DB_CS = 0;

    for(i = 0; i < wBytes; i++) {
    DB    = pacData[i];
    DB_WR = 0;
    DB_WR = 1; }

    DB_CS = 1;
    DB_PD = 0x00;
}
