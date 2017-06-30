#include "md5.h"

int md5 (void *arr, const char* path) {
	uint32_t *hash = (uint32_t *)arr;
	struct stat64 info;
	FILE *file;
	
	memset(hash, 0, 16);
	if ((file = fopen(path, "rb")) == NULL) return -1;
	if ((fstat64(fileno(file), &info) == -1)) return -1;
	if (S_ISDIR(info.st_mode)) return -2;
	
	uint64_t len, bits = info.st_size * 8;
	for (len = bits + 65; len % 512 != 0; len++); len >>= 3;
	
	uint8_t data[64];
	uint32_t *word = (uint32_t *)data;
	
	uint32_t aux[4];
	hash[0] = 0x67452301; hash[1] = 0xEFCDAB89;
	hash[2] = 0x98BADCFE; hash[3] = 0x10325476;
	
	uint64_t offset;
	uint32_t i, x, bytes;
	for (offset = 0; offset < len; offset += 64) {
		bytes = fread(data, 1, 64, file);
		if (bytes < 64) {
			memset(data + bytes, 0, 64 - bytes);
			if (offset + bytes == (uint64_t)info.st_size) data[bytes] = 128;
			if (offset + 64 == len) memcpy(data + 56, (uint8_t *)&bits, 8);
		}
		
		memcpy(aux, hash, 16);
		
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xD76AA478 + word[ 0]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  7);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xE8C7B756 + word[ 1]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 12);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0x242070DB + word[ 2]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 17);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xC1BDCEEE + word[ 3]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 22);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xF57C0FAF + word[ 4]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  7);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0x4787C62A + word[ 5]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 12);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xA8304613 + word[ 6]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 17);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xFD469501 + word[ 7]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 22);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0x698098D8 + word[ 8]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  7);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0x8B44F7AF + word[ 9]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 12);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xFFFF5BB1 + word[10]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 17);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0x895CD7BE + word[11]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 22);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0x6B901122 + word[12]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  7);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xFD987193 + word[13]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 12);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0xA679438E + word[14]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 17);
		x = aux[0] + F(aux[1], aux[2], aux[3]) + 0x49B40821 + word[15]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 22);
		
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xF61E2562 + word[ 1]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  5);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xC040B340 + word[ 6]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  9);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0x265E5A51 + word[11]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 14);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xE9B6C7AA + word[ 0]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 20);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xD62F105D + word[ 5]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  5);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0x02441453 + word[10]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  9);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xD8A1E681 + word[15]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 14);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xE7D3FBC8 + word[ 4]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 20);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0x21E1CDE6 + word[ 9]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  5);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xC33707D6 + word[14]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  9);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xF4D50D87 + word[ 3]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 14);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0x455A14ED + word[ 8]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 20);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xA9E3E905 + word[13]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  5);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0xFCEFA3F8 + word[ 2]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  9);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0x676F02D9 + word[ 7]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 14);
		x = aux[0] + G(aux[1], aux[2], aux[3]) + 0x8D2A4C8A + word[12]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 20);
		
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xFFFA3942 + word[ 5]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  4);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0x8771F681 + word[ 8]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 11);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0x6D9D6122 + word[11]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 16);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xFDE5380C + word[14]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 23);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xA4BEEA44 + word[ 1]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  4);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0x4BDECFA9 + word[ 4]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 11);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xF6BB4B60 + word[ 7]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 16);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xBEBFBC70 + word[10]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 23);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0x289B7EC6 + word[13]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  4);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xEAA127FA + word[ 0]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 11);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xD4EF3085 + word[ 3]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 16);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0x04881D05 + word[ 6]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 23);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xD9D4D039 + word[ 9]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  4);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xE6DB99E5 + word[12]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 11);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0x1FA27CF8 + word[15]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 16);
		x = aux[0] + H(aux[1], aux[2], aux[3]) + 0xC4AC5665 + word[ 2]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 23);
		
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xF4292244 + word[ 0]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  6);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0x432AFF97 + word[ 7]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 10);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xAB9423A7 + word[14]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 15);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xFC93A039 + word[ 5]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 21);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0x655B59C3 + word[12]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  6);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0x8F0CCC92 + word[ 3]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 10);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xFFEFF47D + word[10]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 15);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0x85845DD1 + word[ 1]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 21);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0x6FA87E4F + word[ 8]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  6);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xFE2CE6E0 + word[15]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 10);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xA3014314 + word[ 6]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 15);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0x4E0811A1 + word[13]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 21);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xF7537E82 + word[ 4]; UPDATE(aux[0], aux[1], aux[2], aux[3], x,  6);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xBD3AF235 + word[11]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 10);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0x2AD7D2BB + word[ 2]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 15);
		x = aux[0] + I(aux[1], aux[2], aux[3]) + 0xEB86D391 + word[ 9]; UPDATE(aux[0], aux[1], aux[2], aux[3], x, 21);
		
		for (i = 0; i < 4; i++) hash[i] += aux[i];
	}
	
	fseek(file, 0, SEEK_SET);
	if (fread(data, 1, 4, file) < 4) return 0;
	x = !memcmp(data, "\x7F""ELF", 4) ? 1 : 0;
	fclose(file);
	
	return x;
}
