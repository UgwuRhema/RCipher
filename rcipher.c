#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

static size_t slen(const uint8_t *);
int encrypt(const uint8_t *, uint32_t *, size_t, FILE *);
int decrypt(uint32_t *, size_t);

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
	uint8_t txt_buffer[MAX_LEN];
	uint32_t cipher_buffer[MAX_LEN];
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
			if (!fd)
			{
				fprintf(stderr, "RCipher: Could not open file '%s'\n", filename);
				return 1;
			}
			printf("Enter TXT(max chars 256): ");
			if (!fgets(txt_buffer, sizeof(txt_buffer), stdin))
			{
				fprintf(stderr, "RCipher: Failed to read input from the standard input stream\n");
				fclose(fd);
				return 1;
			}
			txt_buffer[slen(txt_buffer) - 1] = '\0';
			size_t len = slen(txt_buffer);
			printf("Length of input: %zu\n", len);
			int e = encrypt(txt_buffer, cipher_buffer, len, fd);
			if (e < 0)
			{
				fprintf(stderr, "RCipher: Encrypt failed\n");
				return 1;
			}
			printf("Encryption successful, Cipher written to %s\n", filename);
			fclose(fd);
			return 0;
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
			if (!fd)
			{
				fprintf(stderr, "RCipher: File '%s' does not exist\n", filename);
				return 1;
			}
			char line[4 * MAX_LEN + 2];/*what is this?*/
			if (!fgets(line, sizeof(line), fd))
			{
				fprintf(stderr, "RCipher: Empty or Unreadable file\n");
				fclose(fd);
				return 1;
			}
			printf("Gotten Cipher text: %s\n", line);
			fclose(fd);
			size_t n = 0;
			printf("Decryption:\n");
			for (char *tok = strtok(line, ".\n"); tok && n < MAX_LEN; strtok(NULL, ".\n"))
				cipher_buffer[n++] = strtoul(tok, NULL, 10);
			int d = decrypt((uint32_t *)cipher_buffer, n);
			if (d < 0)
				return 1;
			putchar('\n');
		} else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
			printf("RCipher\n");
			printf("Usage: rcipher [options] <file>\n");
			printf("Options:\n");
			printf("\t-o <filename>: To Create a new Cipher\n");
			printf("\t-d <filename>: To Decrypt a Cipher found inside a file\n");
			printf("\t--help or -h: Display this message\n");
			return 0;
		} else {
			fprintf(stderr, "RCipher: Unknow command\n");
			return 1;
		}
	}
	return 0;
}

static size_t
slen(const uint8_t *str)
{
	size_t len = 0;
	while (*str++)
		len++;
	return len;
}

int
encrypt(const uint8_t *s, uint32_t *arr, size_t len, FILE *f)
{
	if (!s || !arr || !f)
		return -1;
	/*for now this will just print our number to the screen*/
	for (size_t i=0;i<len;++i)
	{
		arr[i] = (uint8_t)((s[i] - 2) & 0xff);
		fprintf(f, "%d.", arr[i]);
	}
	fprintf(f, "\n");
	return 0;/*success*/
}

int
decrypt(uint32_t *a, size_t len)
{
	if (!a)
		return -1;
	for (size_t i=0;i<len;++i)
	{
		uint32_t curr = a[i];
		uint32_t correct = curr + 2;
		char c = (char)correct;
		printf("%c", c);
	}
	return 0;
}/*basically the reverse of func(NOT encrypt in our case)*/
