#ifndef COLORS_H
#define COLORS_H

// Códigos de escape ANSI para mostrar modificar la fuente en la terminal

// Color de la letra
#define BLACK   "\x1B[30m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define PINK    "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

// Color de fondo
#define BBLACK  "\x1B[40m"
#define BRED    "\x1B[41m"
#define BGREEN  "\x1B[42m"
#define BYELLOW "\x1B[43m"
#define BBLUE   "\x1B[44m"
#define BPINK   "\x1B[45m"
#define BCYAN   "\x1B[46m"
#define BWHITE  "\x1B[47m"

// Formato
#define BOLD    "\x1B[1m"
#define SUB     "\x1B[4m"

// Reestablecer
#define RESET   "\x1B[0m"

#endif
