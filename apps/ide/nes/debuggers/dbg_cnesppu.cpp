//    NESICIDE - an IDE for the 8-bit NES.
//    Copyright (C) 2009  Christopher S. Pow

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "cnessystempalette.h"

#include "dbg_cnesppu.h"

#include "ccodedatalogger.h"

#include <QColor>

int8_t*          CPPUDBG::m_pCodeDataLoggerInspectorTV = NULL;

int8_t*          CPPUDBG::m_pCHRMEMInspectorTV = NULL;
QColor         CPPUDBG::m_chrMemColor[4];
int8_t*          CPPUDBG::m_pOAMInspectorTV = NULL;
int8_t*          CPPUDBG::m_pNameTableInspectorTV = NULL;

uint32_t CPPUDBG::m_iPPUViewerScanline = 0;
uint32_t CPPUDBG::m_iOAMViewerScanline = 0;
bool CPPUDBG::m_bPPUViewerShowVisible = true;
bool CPPUDBG::m_bOAMViewerShowVisible = false;

PpuStateSnapshot CPPUDBG::m_ppuState;

CPPUDBG::CPPUDBG()
{
}

CPPUDBG::~CPPUDBG()
{
}

static QColor color [] =
{
   QColor(255,0,0),  // eLogger_InstructionFetch,
   QColor(255,0,0),  // eLogger_OperandFetch,
   QColor(0,255,0),  // eLogger_DataRead,
   QColor(0,0,255),  // eLogger_DMA,
   QColor(255,255,0) // eLogger_DataWrite
};

static QColor renderColor = QColor(0,0,255);

void CPPUDBG::RENDERCODEDATALOGGER ( void )
{
   uint32_t idxx;
   uint32_t cycleDiff;
   uint32_t curCycle = CCodeDataLogger::GetCurCycle ();
   QColor lcolor;
   CCodeDataLogger* pLogger;
   LoggerInfo* pLogEntry;
   int8_t* pTV;

   pTV = (int8_t*)m_pCodeDataLoggerInspectorTV;

   // Show PPU memory...
   pLogger = nesGetPpuCodeDataLoggerDatabase();

   for ( idxx = 0; idxx < 0x4000; idxx++ )
   {
      pLogEntry = pLogger->GetLogEntry(idxx);
      cycleDiff = (curCycle-pLogEntry->cycle)/10000;

      if ( cycleDiff > 199 )
      {
         cycleDiff = 199;
      }
      cycleDiff = 255-cycleDiff;

      if ( pLogEntry->count )
      {
         // PPU fetches are one color, CPU fetches are others...
         if ( pLogEntry->source == eNESSource_PPU )
         {
            lcolor = renderColor;
         }
         else
         {
            lcolor = color[(int)pLogEntry->type];
         }

         if ( lcolor.red() )
         {
            lcolor.setRed(cycleDiff);
         }

         if ( lcolor.green() )
         {
            lcolor.setGreen(cycleDiff);
         }

         if ( lcolor.blue() )
         {
            lcolor.setBlue(cycleDiff);
         }

         *pTV = lcolor.red();
         *(pTV+1) = lcolor.green();
         *(pTV+2) = lcolor.blue();
      }
      else
      {
         *pTV = 0;
         *(pTV+1) = 0;
         *(pTV+2) = 0;
      }

      pTV += 4;
   }
}

void CPPUDBG::RENDERCHRMEM ( void )
{
   uint32_t ppuAddr = 0x0000;
   uint8_t patternData1;
   uint8_t patternData2;
   uint8_t bit1, bit2;
   uint8_t colorIdx;
   int32_t color[4][3];
   int8_t* pTV;

   pTV = (int8_t*)m_pCHRMEMInspectorTV;

   nesGetPpuSnapshot(&m_ppuState);

   color[0][0] = m_chrMemColor[0].red();
   color[0][1] = m_chrMemColor[0].green();
   color[0][2] = m_chrMemColor[0].blue();
   color[1][0] = m_chrMemColor[1].red();
   color[1][1] = m_chrMemColor[1].green();
   color[1][2] = m_chrMemColor[1].blue();
   color[2][0] = m_chrMemColor[2].red();
   color[2][1] = m_chrMemColor[2].green();
   color[2][2] = m_chrMemColor[2].blue();
   color[3][0] = m_chrMemColor[3].red();
   color[3][1] = m_chrMemColor[3].green();
   color[3][2] = m_chrMemColor[3].blue();

   for (int y = 0; y < 128; y++)
   {
      for (int x = 0; x < 256; x += 8)
      {
         ppuAddr = ((y>>3)<<8)+((x%128)<<1)+(y&0x7);

         if ( x >= 128 )
         {
            ppuAddr += 0x1000;
         }

         patternData1 = m_ppuState.memory[ppuAddr];
         patternData2 = m_ppuState.memory[ppuAddr+8];

         for ( int32_t xf = 0; xf < 8; xf++ )
         {
            bit1 = (patternData1>>(7-(xf)))&0x1;
            bit2 = (patternData2>>(7-(xf)))&0x1;
            colorIdx = (bit1|(bit2<<1));
            *pTV = color[colorIdx][0];
            *(pTV+1) = color[colorIdx][1];
            *(pTV+2) = color[colorIdx][2];

            pTV += 4;
         }
      }
   }
}

void CPPUDBG::RENDEROAM ( void )
{
   int32_t x, xf, y, yf;
   uint16_t spritePatBase = 0x0000;
   uint8_t patternIdx;
   uint8_t spriteAttr;
   int32_t spriteSize;
   int32_t sprite;
   uint8_t spriteFlipVert;
   uint8_t spriteFlipHoriz;
   uint8_t patternData1;
   uint8_t patternData2;
   uint8_t attribData;
   uint8_t bit1, bit2;
   uint8_t colorIdx;
   uint8_t spriteY;
   QColor color[4];
   int8_t* pTV;

   pTV = (int8_t*)m_pOAMInspectorTV;

   nesGetPpuSnapshot(&m_ppuState);

   color[0] = CBasePalette::GetPalette ( 0x0D );
   color[1] = CBasePalette::GetPalette ( 0x10 );
   color[2] = CBasePalette::GetPalette ( 0x20 );
   color[3] = CBasePalette::GetPalette ( 0x30 );

   spriteSize = ((!!(m_ppuState.reg[PPUCTRL_REG]&PPUCTRL_SPRITE_SIZE))+1)<<3;

   if ( spriteSize == 8 )
   {
      spritePatBase = (!!(m_ppuState.reg[PPUCTRL_REG]&PPUCTRL_SPRITE_PAT_TBL_ADDR))<<12;
   }

   for ( y = 0; y < spriteSize<<1; y++ )
   {
      for ( x = 0; x < 256; x += PATTERN_SIZE ) // pattern-slice rendering...
      {
         sprite = (spriteSize==8)?((y>>3)<<5)+(x>>3):
                  ((y>>4)<<5)+(x>>3);
         spriteY = m_ppuState.oamMemory[(sprite<<2)+SPRITEY];

         if ( ((m_bOAMViewerShowVisible) && ((spriteY+1) < SPRITE_YMAX)) ||
               (!m_bOAMViewerShowVisible) )
         {
            patternIdx = m_ppuState.oamMemory[(sprite<<2)+SPRITEPAT];

            if ( spriteSize == 16 )
            {
               spritePatBase = (patternIdx&0x01)<<12;
               patternIdx &= 0xFE;
            }

            spriteAttr = m_ppuState.oamMemory[(sprite<<2)+SPRITEATT];
            spriteFlipVert = !!(spriteAttr&SPRITE_FLIP_VERT);
            spriteFlipHoriz = !!(spriteAttr&SPRITE_FLIP_HORIZ);
            attribData = (spriteAttr&SPRITE_PALETTE_IDX_MSK)<<2;

            // For 8x16 sprites...
            if ( (spriteSize == 16) &&
                  (((!spriteFlipVert) && (((y>>3)&1))) ||
                   ((spriteFlipVert) && (!((y>>3)&1)))) )
            {
               patternIdx++;
            }

            yf = y&0x7;

            if ( spriteFlipVert )
            {
               yf = (7-yf);
            }

            patternData1 = m_ppuState.memory[spritePatBase+(patternIdx<<4)+(yf)];
            patternData2 = m_ppuState.memory[spritePatBase+(patternIdx<<4)+(yf)+PATTERN_SIZE];

            for ( xf = 0; xf < PATTERN_SIZE; xf++ )
            {
               if ( spriteFlipHoriz )
               {
                  bit1 = (patternData1>>((xf)))&0x1;
                  bit2 = (patternData2>>((xf)))&0x1;
               }
               else
               {
                  bit1 = (patternData1>>(7-(xf)))&0x1;
                  bit2 = (patternData2>>(7-(xf)))&0x1;
               }

               colorIdx = (attribData|bit1|(bit2<<1));
               *pTV = CBasePalette::GetPaletteR(m_ppuState.paletteMemory[0x10+colorIdx]);
               *(pTV+1) = CBasePalette::GetPaletteG(m_ppuState.paletteMemory[0x10+colorIdx]);
               *(pTV+2) = CBasePalette::GetPaletteB(m_ppuState.paletteMemory[0x10+colorIdx]);

               pTV += 4;
            }
         }
         else
         {
            for ( xf = 0; xf < PATTERN_SIZE; xf++ )
            {
               *pTV = 0x00;
               *(pTV+1) = 0x00;
               *(pTV+2) = 0x00;

               pTV += 4;
            }
         }
      }
   }
}

void CPPUDBG::RENDERNAMETABLE ( void )
{
   int32_t x, xf, y;
   int32_t lbx, ubx, lby, uby;

   uint32_t ppuAddr = 0x0000;
   uint16_t patternIdx;
   int32_t tileX;
   int32_t tileY;
   int32_t nameAddr;
   int32_t attribAddr;
   int32_t bkgndPatBase;
   uint8_t attribData;
   uint8_t patternData1;
   uint8_t patternData2;
   uint8_t bit1, bit2;
   uint8_t colorIdx;
   int8_t* pTV;

   pTV = (int8_t*)m_pNameTableInspectorTV;

   nesGetPpuSnapshot(&m_ppuState);

   for ( y = 0; y < 480; y++ )
   {
      for ( x = 0; x < 512; x += PATTERN_SIZE ) // pattern-slice rendering...
      {
         tileX = ppuAddr&0x001F;
         tileY = (ppuAddr&0x03E0)>>5;
         nameAddr = 0x2000 + (ppuAddr&0x0FFF);
         attribAddr = 0x2000 + (ppuAddr&0x0C00) + 0x03C0 + ((tileY&0xFFFC)<<1) + (tileX>>2);
         bkgndPatBase = (!!(m_ppuState.reg[PPUCTRL_REG]&PPUCTRL_BKGND_PAT_TBL_ADDR))<<12;

         patternIdx = bkgndPatBase+(m_ppuState.memory[nameAddr]<<4)+((ppuAddr&0x7000)>>12);
         attribData = m_ppuState.memory[attribAddr];
         patternData1 = m_ppuState.memory[patternIdx];
         patternData2 = m_ppuState.memory[patternIdx+PATTERN_SIZE];

         if ( (tileY&0x0002) == 0 )
         {
            if ( (tileX&0x0002) == 0 )
            {
               attribData = (attribData&0x03)<<2;
            }
            else
            {
               attribData = (attribData&0x0C);
            }
         }
         else
         {
            if ( (tileX&0x0002) == 0 )
            {
               attribData = (attribData&0x30)>>2;
            }
            else
            {
               attribData = (attribData&0xC0)>>4;
            }
         }

         for ( xf = 0; xf < PATTERN_SIZE; xf++ )
         {
            bit1 = (patternData1>>(7-(xf)))&0x1;
            bit2 = (patternData2>>(7-(xf)))&0x1;
            colorIdx = (attribData|bit1|(bit2<<1));
            *pTV = CBasePalette::GetPaletteR(m_ppuState.paletteMemory[colorIdx]);
            *(pTV+1) = CBasePalette::GetPaletteG(m_ppuState.paletteMemory[colorIdx]);
            *(pTV+2) = CBasePalette::GetPaletteB(m_ppuState.paletteMemory[colorIdx]);

            if ( m_bPPUViewerShowVisible )
            {
               lbx = *(*(m_ppuState.xOffset+((x+xf)&0xFF))+(y%240));
               ubx = lbx>>8?lbx&0xFF:lbx+255;
               lby = *(*(m_ppuState.yOffset+((x+xf)&0xFF))+(y%240));
               uby = lby/240?lby%240:lby+239;

               if ( !( (((lbx <= ubx) && ((x+xf) >= lbx) && ((x+xf) <= ubx)) ||
                        ((lbx > ubx) && (!(((x+xf) <= lbx) && ((x+xf) >= ubx))))) &&
                       (((lby <= uby) && (y >= lby) && (y <= uby)) ||
                        ((lby > uby) && (!((y <= lby) && (y >= uby))))) ) )
               {
                  *pTV &= 0xCF;
                  *(pTV+1) &= 0xCF;
                  *(pTV+2) &= 0xCF;
               }
            }

            pTV += 4;
         }

         ppuAddr++;

         if ( x == 248 || x == 504 )
         {
            ppuAddr ^= 0x400;
            ppuAddr -= 0x20;
         }
      }

      if ( (ppuAddr&0x7000) == 0x7000 )
      {
         ppuAddr &= 0x8FFF;

         if ( (ppuAddr&0x03E0) == 0x03A0 )
         {
            ppuAddr ^= 0x0800;
            ppuAddr &= 0xFC1F;
         }
         else
         {
            if ( (ppuAddr&0x03E0) == 0x03E0 )
            {
               ppuAddr &= 0xFC1F;
            }
            else
            {
               ppuAddr += 0x0020;
            }
         }
      }
      else
      {
         ppuAddr += 0x1000;
      }
   }
}
