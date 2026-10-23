#include <stdio.h>
#include <stdint.h>
#include <string.h>

size_t slen(const uint8_t *);
int func(uint8_t c);
void encrypt(const uint8_t *, uint32_t *);
void decrypt(uint32_t);

#define MAX_LENGTH_OF_TXT 256

int
main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "RCipher: Needs output file to store Cipher\n");
		return 1;
	}
	const char *filename;
	if (argv[1])
	{
		if (strcmp(argv[1], "-o") == 0)
		{
			if (argc > 2 && argv[2])
				filename = strdup(argv[2]);
		}
	}
}

size_t
slen(const uint8_t *str)
{
	size_t len = 0;
	while (*str++)
		len++;
	return len;
}

int
func(uint8_t c)
{
	uint32_t ascii_value = (int)c;
	uint32_t res = ascii_value - 2;
	return res;
}

void
encrypt(const uint8_t *s, uint32_t *arr)
{
	/*for now this will just print our number to the screen*/
	for (size_t i=0;i<slen(s);++i)
	{
		arr[i] = func(s[i]);	
		printf("%u", arr[i]);
	}
	printf("\n");
}

void
decrypt(uint32_t av)
{
	uint32_t correct_ascii = av + 2;
	char c = (char)correct_ascii;
	printf("%c", c);
}/*basically the reverse of func(NOT encrypt in our case)*/
