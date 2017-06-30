CFLAGS=-s -O3 -Wall -Wextra
CXXFLAGS=-s -O3 -Wall -Wextra

.PHONY: all clean

all: md5sum

md5sum: md5sum.c md5.o colors.h

md5.o: md5.c md5.h


clean:
	$(RM) md5sum md5.o
