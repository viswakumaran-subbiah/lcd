#ifndef _LCD_H
#define _LCD_H

extern void lcd_initialize(void);
extern void lcd_write( unsigned char command, unsigned char data);
extern void lcd_disp( unsigned char command,const char *data);
extern void lcd_allort(unsigned char data);
extern void lcd_command(unsigned char command);

#endif
