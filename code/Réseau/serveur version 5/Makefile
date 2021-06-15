CC = gcc
CFLAGS = -Wall -Wextra -pthread
LDLIBS = -ljansson -pthread


SRC = time.c ../API/json.c server.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: server

server : $(OBJ)

clean:
	${RM} $(OBJ) $(OBJ_TESTS) $(DEP) $(DEP_TESTS) server && clear