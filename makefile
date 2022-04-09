CC = gcc
CCFLAGS = -Wall -Werror -g -O3 
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