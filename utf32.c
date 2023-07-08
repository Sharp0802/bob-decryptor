#include "utf32.h"

size_t UTF32(uint8_t* utf8, const uint32_t* utf32, size_t nSrc)
{
	for (size_t i = 0; i < nSrc; ++i)
	{
		if (utf32[i] > 0x10FFFF)
			return -1;
	}

	size_t length = 0;

	// Calculate the length of the UTF-8 string
	for (size_t i = 0; i < nSrc; ++i) {
		unsigned int c = utf32[i];

		if (c < 0x80) {
			length += 1;
		}
		else if (c < 0x800) {
			length += 2;
		}
		else if (c < 0x10000) {
			length += 3;
		}
		else {
			length += 4;
		}
	}

	utf8[length] = '\0';

	// Convert UTF-32 to UTF-8
	int size = 0;
	for (size_t i = 0; i < nSrc; ++i) {
		unsigned int c = utf32[i];

		if (c < 0x80) {
			utf8[size++] = c;
		}
		else if (c < 0x800) {
			utf8[size++] = 0xC0 | (c >> 6);
			utf8[size++] = 0x80 | (c & 0x3F);
		}
		else if (c < 0x10000) {
			utf8[size++] = 0xE0 | (c >> 12);
			utf8[size++] = 0x80 | ((c >> 6) & 0x3F);
			utf8[size++] = 0x80 | (c & 0x3F);
		}
		else {
			utf8[size++] = 0xF0 | (c >> 18);
			utf8[size++] = 0x80 | ((c >> 12) & 0x3F);
			utf8[size++] = 0x80 | ((c >> 6) & 0x3F);
			utf8[size++] = 0x80 | (c & 0x3F);
		}
	}

	return size;
}
