#include <stdio.h>
#include "md5.h"
#include "colors.h"

int main (const int argc, const char **argv) {
	if (argc < 2) {
		printf("Uso: %s <path1> ... <path2>\n", argv[0]);
		return 1;
	}
	
	int i = 1, j, flag;
	uint8_t hash[16];
	for (; i < argc; i++, flag = 0) {
		flag = md5(hash, argv[i]);
		switch (flag) {
			case 1: case  0:
					for (j = 0; j < 16; j++) printf("%02X", hash[j]);
					if (flag == 1) printf(BOLD GREEN);
				break;
			case -1: printf("%-54s", BOLD RED "Error:" RESET " no se puede abrir" BOLD WHITE); break;
			case -2: printf("%-54s", BOLD PINK "Aviso:" RESET " es un directorio" BOLD BLUE);
		}
		
		printf("  %s\n" RESET, argv[i]);
	}
	
	return 0;
}
