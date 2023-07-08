#include "cp949.h"
#include "cp949.g.h"
#include "utf32.h"

#include <stdlib.h>

size_t __CP949(uint32_t* utf32, const uint8_t* cp949, size_t nSrc)
{
	char buf[2];
	int bp = 0;

	size_t j = 0;
	for (size_t i = 0; i < nSrc; ++i)
	{
		if (bp == 1) // double-char tailing byte
		{
			buf[0] = cp949[i];
			utf32[j++] = __cp949[*(uint16_t*)buf];
			bp = 0;
		}
		else if (0x81 <= cp949[i] && cp949[i] <= 0xFE) // double-char leading byte
		{
			buf[1] = cp949[i];
			bp = 1;
		}
		else // single-char byte
		{
			utf32[j++] = __cp949[cp949[i]];
		}
	}

	// invalid data detecting
	for (size_t i = 0; i < j; ++i)
		if (utf32[i] == 0xFFFFFFFF)
			return -1;
	if (bp == 1)
		return -1;

	return j;
}

size_t CP949(uint8_t* utf8, const uint8_t* cp949, size_t nSrc)
{
	uint32_t* utf32 = malloc(sizeof(uint32_t) * nSrc);
	size_t written = __CP949(utf32, cp949, nSrc);
	if (written == (size_t)-1 || written == (size_t)-2)
		return -1;
	written = UTF32(utf8, utf32, written);
	free(utf32);
	return written;
}
