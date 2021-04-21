# Makefile

CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -pthread -fsanitize=address

all: time_test time signal2 signal

time_test: time_test.o
signal: signal2.o signal.o
time: time.o 

.PHONY: clean

clean:
	${RM} time_test time_test.o
	${RM} signal signal.o
	${RM} time time.o
	${RM} signal2 signal2.o 

# END