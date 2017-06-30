#ifndef MD5_H
#define MD5_H

// Para usar archivos mayores de 2 GB
#define __USE_LARGEFILE64
#define _LARGEFILE_SOURCE
#define _LARGEFILE64_SOURCE

// Macros funciones hash
#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((Z & X) | (~Z & Y))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))
#define UPDATE(A, B, C, D, X, S) (A = D, D = C, C = B, B += (X << S) | (X >> (32 - S)))

// Dependencias
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


int md5 (void *, const char*);

#endif
