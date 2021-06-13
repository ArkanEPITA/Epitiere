CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0` -Wall -Wextra -pthread
LDLIBS = `pkg-config --libs glib-2.0`

EXE = chat_server client

all: $(EXE)

$(foreach f, $(EXE), $(eval $(f):))

.PHONY: clean

clean:
	${RM} $(EXE)