#ifndef HANDLE_H
#define HANDLE_H

#include <util/delay.h>
#include <string.h>

#include "oled.h"

#define max_name_len 12

//#define USER_HANDLE "_BADGE_NAME_"

int getPos(char *str)
{
  int l = strlen(str);
  int pos = (screen_width - (l * char_columns_required)) / 2;
  return pos;
}

void display_handle()
{
#ifdef USER_HANDLE
  oled_clrscr();
  // TOCO crop names longer than max_name_len
  int x = getPos(USER_HANDLE);
  print_fstring(USER_HANDLE, x, 3);
  _delay_ms(3 * 5000);
#endif
}

#endif
