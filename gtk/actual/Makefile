CC = gcc -rdynamic
CFLAGS = -Wall -Wextra
LDLIBS = `pkg-config --cflags --libs gtk+-3.0`

all: gtk

gtk: gtk.c

.PHONY: clean

clean:
	${RM} gtk
