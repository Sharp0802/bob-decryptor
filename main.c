
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cp949.h"
#include "utf8.h"
#include "utf16.h"
#include "utf32.h"

int main(int argc, char* argv[])
{
	fputs(
		"bobdec (BoBDec) 0.0.1\n"
		"Copyright (C) Sharp0802\n"
		"This is free software; see the source for copying conditions. There is NO  \n"
		"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n\n",
		stdout
	);

	if (argc < 2)
	{
		fputs("error: file name required\n", stdout);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fputs("error: open() failed\n", stdout);
		return 1;
	}

	struct stat st;
	fstat(fd, &st);
	char* data = malloc(st.st_size * 2); // safe-buffer
	ssize_t nb = read(fd, data, st.st_size);
	close(fd);

	// hex view
	for (size_t k = 0; k < (size_t)nb; ++k)
	{
		if (k % 16 == 0)
			fputc('\n', stdout);
		printf("%02hhX ", data[k]);
	}
	printf("\n");

	char* vCP[256];
	vCP[0] = data;
	size_t cCP = 1;
	for (ssize_t i = 0; i < nb; ++i)
	{
		if (data[i] != '\n') continue;
		vCP[cCP++] = data + i + 1;
	}

	for (size_t i = 0; i < cCP; ++i)
	{
		// fucking linebreak...
		size_t o = 0, j = 0;
		for (; o < (size_t)nb && vCP[i][o] == 0; ++o) {}
		for (; j < (size_t)nb && vCP[i][j] != 0x0A; ++j) {}
		size_t l = j - o;
		vCP[i] += o;
		vCP[i][l] = 0;

		printf("== %ld/%ld ========================", i + 1, cCP);

		for (size_t k = 0; k < l; ++k)
		{
			if (k % 16 == 0)
				fputc('\n', stdout);
			printf("%02hhX ", vCP[i][k]);
		}
		fputc('\n', stdout);

		uint8_t utf8[4096];
		ssize_t written;

		written = (ssize_t)UTF8((uint8_t*)vCP[i], l);
		if (written != -1)
			printf("U08:%ld: %s\n", written, vCP[i]);

		written = (ssize_t)UTF16(utf8, (uint16_t*)vCP[i], l / 2);
		if (written != -1)
			printf("U16:%ld: %s\n", written, utf8);

		written = (ssize_t)UTF32(utf8, (uint32_t*)vCP[i], l / 4);
		if (written != -1)
			printf("U32:%ld: %s\n", written, utf8);

		written = (ssize_t)CP949(utf8, (uint8_t*)vCP[i], l);
		if (written != -1)
			printf("949:%ld: %s\n\n", written, utf8);
	}

	free(data);

	return 0;
}
