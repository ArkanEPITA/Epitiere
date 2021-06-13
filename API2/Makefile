CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -ljansson


SRC = API.c json.c
OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)

all: API

API: $(OBJ)

clean: 
	${RM} $(OBJ) $(OBJ_TESTS) $(DEP) $(DEP_TESTS) API && clear