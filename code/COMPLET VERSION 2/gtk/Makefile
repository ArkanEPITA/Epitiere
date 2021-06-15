CC = gcc -rdynamic
CFLAGS = -Wall -Wextra -pthread
LDLIBS = `pkg-config --cflags --libs gtk+-3.0`


all: interface

interface: interface.c client.c

.PHONY: clean

clean:
	${RM} interface && clear
