CC = gcc
CFlagsHard = --std=c99 -Wall -Werror -Wextra -pedantic-errors
CFlags = --std=c99 -MMD

# 1. Just list your object files here
OBJS = build/main.o build/debug.o build/chunk.o build/value.o build/memory.o

bin/clox: $(OBJS)
	@mkdir -p bin
	$(CC) $(CFlags) -o bin/clox $^

# 2. This ONE rule replaces all 5 individual file blocks
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFlags) -c $< -o $@

clean:
	rm -rf build bin

-include build/*.d
