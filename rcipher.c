#include <stdio.h>
#include <stdint.h>

size_t slen(const uint8_t *);
void func(uint8_t c);
void encyrpt(const uint8_t *);
void decrypt(uint32_t *);

void
main(void)
{
	/*our formula is (num - 2), we convert a character*/
	/*to it's respective ascii value the subtract 2 from it*/
	printf("RCipher\n");
	printf("Enter text to encrypt to numbers: ");
	return;
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
func(char c)
{
	int ascii_value = (int)c;
	int res = ascii_value - 2;
	printf("%d", res);
}

void
encrypt(const uint8_t *s)
{
	/*for now this will just print our number to the screen*/
	for (size_t i=0;i<slen(s);++i)
	{
		func(s[i]);	
	}
}
