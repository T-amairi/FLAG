CC = gcc
CCFLAGS = -Wall -Werror -std=c99 -g -O3 -march=native
LIBFLAGS = -lm
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = project.out

all: $(EXEC)

#EXEC
$(EXEC): $(OBJ)
	$(CC) $^ $(LIBFLAGS) -o $@

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

#CLEAN
clean:
	rm -f $(OBJ) $(EXEC)