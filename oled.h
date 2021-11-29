#ifndef OLED_H
#define OLED_H

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "fonts.h"

int ioled, joled;

#define screen_width 128
#define screen_height 64

#define first_char_ascii_code 32
#define no_of_bytes_char 21

#define char_pages_required 2
#define char_columns_required 9

char detc[90] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$', '%', '&', '(', ')', '*', '+', '-', ',', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '_', '{', '}', '|', '~'};

const char alpc[90][6] PROGMEM = {
	{0, 0, 0, 0, 0, 0},		   //space
	{126, 17, 17, 17, 126, 0}, //A
	{127, 73, 73, 73, 54, 0},  //B
	{62, 65, 65, 65, 34, 0},   //C
	{127, 65, 65, 34, 28, 0},  //D
	{127, 73, 73, 73, 65, 0},  //E
	{127, 9, 9, 9, 1, 0},	   //F
	{62, 65, 73, 73, 122, 0},  //G
	{127, 8, 8, 8, 127, 0},	   //H
	{0, 65, 127, 65, 0, 0},	   //I
	{32, 64, 65, 63, 1, 0},	   //J
	{127, 8, 20, 34, 65, 0},   //K
	{127, 64, 64, 64, 64, 0},  //L
	{127, 2, 12, 2, 127, 0},   //M
	{127, 4, 8, 16, 127, 0},   //N
	{62, 65, 65, 65, 62, 0},   //O
	{127, 9, 9, 9, 6, 0},	   //P
	{62, 65, 81, 33, 94, 0},   //Q
	{127, 9, 25, 41, 70, 0},   //R
	{70, 73, 73, 73, 49, 0},   //S
	{1, 1, 127, 1, 1, 0},	   //T
	{63, 64, 64, 64, 63, 0},   //U
	{31, 32, 64, 32, 31, 0},   //V
	{63, 64, 56, 64, 63, 0},   //W
	{99, 20, 8, 20, 99, 0},	   //X
	{7, 8, 112, 8, 7, 0},	   //Y
	{97, 81, 73, 69, 67, 0},   //Z
	{32, 84, 84, 84, 120, 0},  //a
	{127, 68, 68, 68, 120, 0}, //b
	{56, 68, 68, 68, 68, 0},   //c
	{56, 68, 68, 68, 127, 0},  //d
	{56, 84, 84, 84, 24, 0},   //e
	{4, 4, 126, 5, 5, 0},	   //f
	{8, 84, 84, 84, 60, 0},	   //g
	{127, 8, 4, 4, 120, 0},	   //h
	{0, 68, 125, 64, 0, 0},	   //i
	{32, 64, 68, 61, 0, 0},	   //j
	{127, 16, 40, 68, 0, 0},   //k
	{0, 65, 127, 64, 0, 0},	   //l
	{124, 4, 120, 4, 120, 0},  //m
	{124, 8, 4, 4, 120, 0},	   //n
	{56, 68, 68, 68, 56, 0},   //o
	{124, 20, 20, 20, 8, 0},   //p
	{8, 20, 20, 20, 124, 0},   //q
	{0, 124, 8, 4, 4, 0},	   //r
	{72, 84, 84, 84, 36, 0},   //s
	{4, 4, 63, 68, 68, 0},	   //t
	{60, 64, 64, 32, 124, 0},  //u
	{28, 32, 64, 32, 28, 0},   //v
	{60, 64, 48, 64, 60, 0},   //w
	{68, 40, 16, 40, 68, 0},   //x
	{12, 80, 80, 80, 60, 0},   //y
	{68, 100, 84, 76, 68, 0},  //z
	{62, 81, 73, 69, 62, 0},   //0
	{4, 2, 127, 0, 0, 0},	   //1
	{66, 97, 81, 73, 70, 0},   //2
	{34, 65, 73, 73, 54, 0},   //3
	{24, 20, 18, 127, 16, 0},  //4
	{39, 69, 69, 69, 57, 0},   //5
	{62, 73, 73, 73, 50, 0},   //6
	{1, 1, 113, 9, 7, 0},	   //7
	{54, 73, 73, 73, 54, 0},   //8
	{38, 73, 73, 73, 62, 0},   //9
	{0, 0, 95, 0, 0, 0},	   //!
	{20, 62, 20, 62, 20, 0},   //#
	{36, 42, 127, 42, 18, 0},  //$
	{67, 51, 8, 102, 97, 0},   //%
	{54, 73, 85, 34, 80, 0},   //&
	{0, 28, 34, 65, 0, 0},	   //(
	{0, 65, 34, 28, 0, 0},	   //)
	{20, 8, 62, 8, 20, 0},	   //*
	{8, 8, 62, 8, 8, 0},	   //+
	{8, 8, 8, 8, 8, 0},		   //-
	{0, 80, 48, 0, 0, 0},	   //,
	{0, 96, 96, 0, 0, 0},	   //.
	{32, 16, 8, 4, 2, 0},	   ///
	{0, 54, 54, 0, 0, 0},	   //:
	{0, 86, 54, 0, 0, 0},	   //;
	{8, 20, 34, 65, 0, 0},	   //<
	{20, 20, 20, 20, 20, 0},   //=
	{0, 65, 34, 20, 8, 0},	   //>
	{2, 1, 81, 9, 6, 0},	   //?
	{62, 65, 89, 85, 94, 0},   //@
	{0, 127, 65, 0, 0, 0},	   //[
	{0, 0, 65, 127, 0, 0},	   //]
	{64, 64, 64, 64, 64, 0},   //_
	{0, 8, 54, 65, 65, 0},	   //{
	{65, 65, 54, 8, 0, 0},	   //}
	{0, 0, 127, 0, 0, 0},	   //|
	{2, 1, 2, 4, 2, 0}		   //~
};

void twi_init()
{
	TWSR = 0x00;
	TWBR = 0x02;
}

unsigned char twi_send_repeated_start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
	return (TWSR & 0xf8);
	while ((TWSR & 0xf8) != 0x10)
		;
}

unsigned char twi_send_address_rw(unsigned char address_rw)
{
	TWDR = address_rw;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
	return (TWSR & 0xf8);
	while (((TWSR & 0xf8) != 0x18) || ((TWSR & 0xf8) != 0x40))
		;
}

unsigned char twi_master_send_data(unsigned char data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
	return (TWSR & 0xf8);
	while ((TWSR & 0xf8) != 0x28)
		;
}

unsigned char twi_master_send_string(unsigned char *string)
{
	while (*string)
	{
		TWDR = *string++;
		TWCR = (1 << TWINT) | (1 << TWEN);
		while (!(TWCR & (1 << TWINT)))
			;
		while ((TWSR & 0xf8) != 0x28)
			;
	}
	return (TWSR & 0xf8);
}

unsigned char twi_master_receive_data()
{
	TWCR = (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
	return (TWDR);
	while ((TWSR & 0xf8) != 0x50)
		;
}

unsigned char twi_master_receive_last_data()
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
	return (TWDR);
	while ((TWSR & 0xf8) != 0x58)
		;
}

void twi_send_stop()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while ((TWCR & (1 << TWSTO)))
		;
}

unsigned char twi_send_start()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
	return (TWSR & 0xf8);
	while ((TWSR & 0xf8) != 0x08)
		;
}

void oled_write_command(unsigned char oledcommand)
{
	twi_send_start();
	twi_send_address_rw(0x78);
	twi_master_send_data(0x80);
	twi_master_send_data(oledcommand);
	twi_send_stop();
}

void oled_goto(uint8_t x, uint8_t y)
{
	oled_write_command(0xB0 | y);
	oled_write_command(0x00 | (x & 0x0F));
	oled_write_command(0x10 | ((x >> 4) & 0x0F));
}

void oled_write_data(unsigned char oleddata)
{
	twi_send_start();
	twi_send_address_rw(0x78);
	twi_master_send_data(0x40);
	twi_master_send_data(oleddata);
	twi_send_stop();
}

void oled_clrscr()
{
	unsigned char clry = 0;
	unsigned char clrx = 0;
	for (clry = 0; clry <= 7; clry++)
	{
		for (clrx = 0; clrx <= 127; clrx++)
		{
			oled_goto(clrx, clry);
			oled_write_data(0x00);
		}
	}
}

void oled_init()
{
	oled_write_command(0xA8); //Set MUX ratio
	oled_write_command(0x3F); //SET MUX RATIO
	oled_write_command(0xD3); //SET DISPLAY OFFSET
	oled_write_command(0x00); //SET DISPLAY OFFSET
	oled_write_command(0x40); //SET DISPLAY START LINE
	oled_write_command(0xA1); //SET SEGMENT RE-MAP
	oled_write_command(0xC8); //SET COM OUTPUT SCAN DIRECTION
	oled_write_command(0xDA); //SET COM PINS HARDWARE CONFIGURATION
	oled_write_command(0x12); //SET COM PINS HARDWARE CONFIGURATION
	oled_write_command(0x81); //SET CONTRAST CONTROL
	oled_write_command(0x7F); //SET CONTRAST CONTROL
	oled_write_command(0xA4); //DISABLE ENTIRE DISPLAY ON
	oled_write_command(0xA6); //SET NORMAL DISPLAY
	oled_write_command(0xD5); //SET OSCILLATOR FREQUENCY
	oled_write_command(0x80); //SET OSCILLATOR FREQUENCY
	oled_write_command(0x8D); //ENABLE CHARGE PUMP REGULATOR
	oled_write_command(0x14); //ENABLE CHARGE PUMP REGULATOR
	oled_write_command(0xAF); //DISPLAY ON

	oled_clrscr();
}

void oled_scroll_ver()
{
	oled_write_command(0x29); //VERTICAL AND RIGHT HORIZONTAL SCROLL
	oled_write_command(0x00); //DUMMY BYTE SET TO 00H
	oled_write_command(0x00); //STAR PAGE (000 - 111)
	oled_write_command(0x00); //FRAME INTERVAL (00H 5 FRAMES)
	oled_write_command(0x07); //END PAGE (000 - 111)
	oled_write_command(0x01); //SET VERTICAL OFFSET AS 1 ROW
	oled_write_command(0x2F); //ACTIVATE SCROLLING
}

void vscroll_1()
{
	oled_scroll_ver();
	oled_scroll_ver();
}

void oled_stop_scroll()
{
	oled_write_command(0x2E); // Stop scroll mode.
}

void oled_printc(char det)
{
	int loc = 0;
	for (ioled = 0; ioled <= 89; ioled++)
	{
		if (detc[ioled] == det)
		{
			loc = ioled;
			for (joled = 0; joled <= 5; joled++)
			{
				oled_write_data(pgm_read_byte(&(alpc[loc][joled])));
			}
			break;
		}
	}
}

void oled_prints(char *data)
{
	while (*data)
	{
		oled_printc(*data);
		data++;
	}
}

void oled_printi(int value)
{
	char buffer[5] = {'0', '0', '0', '0', '0'};
	itoa(value, buffer, 10);
	oled_prints(buffer);
}

void oled_fillscr()
{
	unsigned char filly = 0;
	unsigned char fillx = 0;
	for (filly = 0; filly <= 7; filly++)
	{
		for (fillx = 0; fillx <= 127; fillx++)
		{
			oled_goto(fillx, filly);
			oled_write_data(0xff);
		}
	}
}

void oled_write_idata(unsigned char oleddata)
{
	twi_send_start();
	twi_send_address_rw(0x78);
	twi_master_send_data(0x40);
	twi_master_send_data(~oleddata);
	twi_send_stop();
}

void print_fchar(char ch, unsigned char x_cord, unsigned char y_cord)
{
	unsigned char ascii_to_array_index = ch - first_char_ascii_code;
	int char_start_in_array = ((ascii_to_array_index * no_of_bytes_char) + 1);

	for (unsigned char jff = x_cord; jff < (x_cord + char_columns_required); jff++)
	{
		for (unsigned char iff = y_cord; iff < (y_cord + char_pages_required); iff++)
		{
			oled_goto(jff, iff);
			int array_index = char_start_in_array + (jff - x_cord) * char_pages_required + (iff - y_cord);
			unsigned char char_byte = pgm_read_byte(&font2[array_index]);
			oled_write_data(char_byte);
		}
	}
}

void print_fstring(char *stringf, unsigned char x_cordf, unsigned char y_cordf)
{
	while (*stringf)
	{
		print_fchar(*stringf, x_cordf, y_cordf);
		x_cordf = (x_cordf + char_columns_required);
		stringf++;
	}
}

#endif
