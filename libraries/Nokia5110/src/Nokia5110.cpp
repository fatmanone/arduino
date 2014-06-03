

#include "Nokia5110.h"

Nokia5110::Nokia5110(byte pinSce, byte pinReset,byte pinDC, byte pinSDIN, byte pinSCLK, byte contrast)
{
	this->PIN_SCE = pinSce;
	this->PIN_RESET = pinReset;
	this->PIN_DC = pinDC;
	this->PIN_SDIN = pinSDIN;
	this->PIN_SCLK = pinSCLK;
	this->Contrast = contrast;
}

void Nokia5110::begin()
{
	this->Initialize();
}

void Nokia5110::Character(char character)
{
  this->Write(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    this->Write(LCD_D, NOKIA5110_ASCII[character - 0x20][index]);
  }
  this->Write(LCD_D, 0x00);
}

void Nokia5110::Clear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    this->Write(LCD_D, 0x00);
  }
}

void Nokia5110::GotoXY(int x, int y)
{
  this->Write( 0, 0x80 | x);  // Column.
  this->Write( 0, 0x40 | y);  // Row.
}

void Nokia5110::ClearGoToBegin(void)
{
  this->Clear();
  this->GotoXY(0,0);
}



void Nokia5110::WriteString(char *characters)
{
  while (*characters)
  {
    this->Character(*characters++);
  }
}


void Nokia5110::WriteString(String s)
{
  int l = s.length();
  for (int i = 0; i < l; i++)
  {
    this->Character(s[i]);
  }
}

void Nokia5110::Write(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}



void Nokia5110::Initialize(void)
{
  pinMode(this->PIN_SCE, OUTPUT);
  pinMode(this->PIN_RESET, OUTPUT);
  pinMode(this->PIN_DC, OUTPUT);
  pinMode(this->PIN_SDIN, OUTPUT);
  pinMode(this->PIN_SCLK, OUTPUT);
  digitalWrite(this->PIN_RESET, LOW);
  digitalWrite(this->PIN_RESET, HIGH);
  this->Write(LCD_C, 0x21 );  // LCD Extended Commands.
  if(this->Contrast>0x0F)
	this->Contrast = 0x0F;
  this->Write(LCD_C, 0xB1 + this->Contrast );  // Set LCD Vop (Contrast).
  this->Write(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  this->Write(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  this->Write(LCD_C, 0x0C );  // LCD in normal mode.
  this->Write(LCD_C, 0x20 );
  this->Write(LCD_C, 0x0C );
}
