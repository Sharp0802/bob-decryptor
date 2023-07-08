#include "utf16.h"

#include <stdbool.h>

bool ValidateUTF16(const uint16_t* utf16, size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		uint16_t ch = utf16[i];

		if (ch >= 0xD800 && ch <= 0xDBFF)
		{
			if (i + 1 < length)
			{
				uint16_t next = utf16[i + 1];
				if (next >= 0xDC00 && next <= 0xDFFF)
				{
					i++;
					continue;
				}
			}
			return false;
		}

		if (ch >= 0xD800 && ch <= 0xDFFF)
		{
			return false;
		}
		if (ch == 0xFFFE || ch == 0xFFFF)
		{
			return false;
		}
	}

	return true; // All ch units are valid
}


size_t UTF16(uint8_t* utf8, const uint16_t* utf16, size_t nSrc)
{
	if (!ValidateUTF16(utf16, nSrc))
		return -1;

	size_t length = 0;
	for (size_t i = 0; i < nSrc; ++i)
	{
		if (utf16[i] < 0x80)
			length++;
		else if (utf16[i] < 0x800)
			length += 2;
		else
			length += 3;
	}

	utf8[length] = 0;
	size_t size = 0;
	for (size_t i = 0; i < nSrc; ++i)
	{
		uint16_t ch = utf16[i];
		if (ch < 0x80)
		{
			utf8[size++] = ch;
		}
		else if (ch < 0x800)
		{
			utf8[size++] = 0xC0 | (ch >> 6);
			utf8[size++] = 0x80 | (ch & 0x3F);
		}
		else
		{
			utf8[size++] = 0xE0 | (ch >> 12);
			utf8[size++] = 0x80 | ((ch >> 6) & 0x3F);
			utf8[size++] = 0x80 | (ch & 0x3F);
		}
	}

	return size;
}
