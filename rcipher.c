#include <stdio.h>
#include <stdint.h>

size_t slen(const uint8_t *);
void func(uint8_t c);
void encrypt(const uint8_t *);
void decrypt(uint32_t);

#define MAX_LENGTH_OF_TXT 256

int
main(void)
{
	/*our formula is (num - 2), we convert a character*/
	/*to it's respective ascii value the subtract 2 from it*/
	printf("RCipher\n");
	char buffer[MAX_LENGTH_OF_TXT];
	printf("Enter text to encrypt to numbers(max 256 chars): ");
	fgets(buffer, sizeof(buffer), stdin);
	buffer[slen(buffer) - 1] = '\0';
	encrypt(buffer);
	return 0;
}

size_t
slen(const uint8_t *str)
{
	size_t len = 0;
	while (*str++)
		len++;
	return len;
}

void
func(uint8_t c)
{
	uint32_t ascii_value = (int)c;
	uint32_t res = ascii_value - 2;
	printf("%u", res);
}

void
encrypt(const uint8_t *s)
{
	/*for now this will just print our number to the screen*/
	for (size_t i=0;i<slen(s);++i)
	{
		func(s[i]);	
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
