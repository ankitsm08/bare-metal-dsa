CC        := gcc
CFLAGS    := -Wall -Wextra -Werror -Iinclude -g -MMD -fsanitize=address -fsanitize=undefined
LDFLAGS   := -fsanitize=address -fsanitize=undefined

SRC       := $(shell find src -name '*.c')
OBJ       := $(SRC:.c=.o)
DEP       := $(OBJ:.o=.d)

TEST_SRC  := $(shell find tests -name 'test_*.c')
TEST_BINS := $(patsubst tests/test_%.c, bin/test_%, $(TEST_SRC))

.PHONY: all clean

all: $(TEST_BINS)

-include $(DEP)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bin/test_%: tests/test_%.c $(OBJ)
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(LDFLAGS) $< $(OBJ) -o $@

clean:
	@rm -f $(OBJ) $(DEP)
	@rm -rf bin/*
