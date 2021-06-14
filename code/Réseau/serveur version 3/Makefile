# Makefile

CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -pthread -fsanitize=address

all: client server

client: client.o
server: server.o

.PHONY: clean

clean:
	${RM} client client.o
	${RM} server server.o

# END