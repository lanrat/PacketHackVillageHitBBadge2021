#define F_CPU 2000000UL

#include <util/delay.h>

#include "oled.h"
#include "phv_ctf.h"
#include "hitb.h"
#include "handle.h"

int main()
{
	twi_init(); /* TWI initialization */
	oled_init();
	DDRA = 0b00000000;

	while (1)
	{
		if (bit_is_clear(PINA, PA2)) // Switch S1
		{
			oled_write_command(0x2E);
			insert_code();
		}
		else
		{ // mainloop
			oled_stop_scroll();
			display_handle();

			oled_stop_scroll();
			oled_clrscr();
			packet(); // PACKET HACK TEXT
			_delay_ms(3 * 5000);

			oled_stop_scroll();
			oled_clrscr();
			oled_image_phv(); // PACKET HACK LOGO
			_delay_ms(1 * 5000);
			vscroll_1();
			for (int one_v_scroll = 0; one_v_scroll <= 30; one_v_scroll++)
			{
				_delay_ms(1000);
			}

			oled_stop_scroll();
			oled_clrscr();
			oled_image_HitB(); // HitT LOGO
			vscroll_1();
			for (int one_v_scroll = 0; one_v_scroll <= 30; one_v_scroll++)
			{
				_delay_ms(1000);
			}
		}
	}
}
