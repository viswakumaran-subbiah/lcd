#include <avr/io.h>
#include <Arduino.h>
#include "i2c.h"
#include "lcd.h"


unsigned char registerselect;

void lcd_initialize (void)
{
  
  lcd_command(0x03);delay(5);
  lcd_command(0x03);delay(5);
  lcd_command(0x03);delayMicroseconds(100);
  
  lcd_command(0x02);delayMicroseconds(100);
  lcd_command(0x28);delayMicroseconds(100);
  lcd_command(0x0C);delayMicroseconds(100);
  lcd_command(0x06);delayMicroseconds(100);
  lcd_command(0x01);delay(50);
}

void lcd_command(unsigned char command)
{
  registerselect = 0;
  lcd_allort(command & 0xF0); 
  lcd_allort((command << 4) & 0xF0); 
}

void lcd_write(unsigned char command, unsigned char data)
{
  lcd_command(command);
  registerselect = 1;
  lcd_allort(data & 0xF0);
  lcd_allort((data << 4) & 0xF0); 
}

void lcd_disp(unsigned char command, const char *data)
{
  while(*data)
  lcd_write(command++, *data++);
}


void lcd_allort(unsigned char data)
{
  i2c_start();
  i2c_write(0x4e);
  i2c_write(data | (0 << 2) | (1 << 3) | (registerselect << 0));
  i2c_write(data | (1 << 2) | (1 << 3) | (registerselect << 0));
  i2c_write(data | (0 << 2) | (1 << 3) | (registerselect << 0));
  i2c_stop();
} 
