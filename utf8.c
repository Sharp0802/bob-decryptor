#include "utf8.h"

#include <stdbool.h>

int8_t UTF8Test(uint8_t ch)
{
	if ((ch & 0x7E) == ch)
		return 1;

	int8_t lv;
	for (lv = 6; lv > 1; --lv)
		if ((ch & (0xFF << (6 - lv))) == (0xFE << (6 - lv)))
			break;

	return lv;
}

bool UTF8Lead(uint8_t ch)
{
	return (ch & 0xC0) == 0x80;
}

size_t UTF8(const uint8_t* utf8, size_t n)
{
	int remaining = 0;
	for (size_t i = 0; i < n; ++i)
	{
		if (remaining)
		{
			remaining--;
			if (!UTF8Lead(utf8[i]))
				return -1;
		}
		else
		{
			// ASCII
			if ((utf8[i] & 0x7E) == utf8[i])
				continue;

			// Multi-Byte
			remaining = UTF8Test(utf8[i]) - 1;
			if (remaining == 1)
				return -1;
		}
	}

	// missing trailing-byte
	if (remaining)
		return -1;

	return n;
}
