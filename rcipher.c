#include <stdio.h>
#include <stdint.h>
#include <string.h>

static size_t slen(const uint8_t *);
void encrypt(const uint8_t *, uint32_t *, FILE *);
void decrypt(uint32_t *, size_t);

#define MAX_LEN 256

int
main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "RCipher: Needs output file to store Cipher\n");
		return 1;
	}
	/*storage*/
	const char *filename;
	char txt_buffer[MAX_LEN];
	int cipher_buffer[MAX_LEN];
	if (argv[1])
	{
		if (strcmp(argv[1], "-o") == 0)
		{
			if (argc > 2 && argv[2])
				filename = strdup(argv[2]);
			else {
				fprintf(stderr, "RCipher: Output file cannot be empty\n");
				return 1;
			}
			/*we encrypt in the '-o' flag and decrpyt in the '-d' flag*/
			FILE *fd = fopen(filename, "w");
			printf("Enter TXT(max chars 256): ");
			fgets(txt_buffer, sizeof(txt_buffer), stdin);
			txt_buffer[slen(txt_buffer) - 1] = '\0';
			size_t len = slen(txt_buffer);
			printf("Length of input: %zu\n", len);
			encrypt(txt_buffer, cipher_buffer, fd);
			printf("Encryption successful, Cipher written to %s\n", filename);
			fclose(fd);
		} else if (strcmp(argv[1], "-d") == 0){
			/*this is decryption*/
			if (argc > 2 && argv[2])
				filename = strdup(argv[2]);
			else {
				fprintf(stderr, "RCipher: Please provide the file to Decipher\n");
				return 1;
			}
			/*we read the file but for nothing i guess*/
			/*let's use a cheap trick since the cipher_buffer is in a higher scope*/
			FILE *fd = fopen(filename, "r");
			fclose(fd);
		}
	}
}

static size_t
slen(const uint8_t *str)
{
	size_t len = 0;
	while (*str++)
		len++;
	return len;
}

void
encrypt(const uint8_t *s, uint32_t *arr, FILE *f)
{
	/*for now this will just print our number to the screen*/
	for (size_t i=0;i<slen(s);++i)
	{
		arr[i] = (uint8_t)((s[i] - 2) & 0xff);
		fprintf(f, "%d", arr[i]);
	}
	fprintf(f, "\n");
}

void
decrypt(uint32_t *a, size_t len)
{
	for (size_t i=0;i<len;++i)
	{
		uint32_t curr = a[i];
		uint32_t correct = curr + 2;
		char c = (char)correct;
		printf("%c", c);
	}
}/*basically the reverse of func(NOT encrypt in our case)*/
