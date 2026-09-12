#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"

void initChunk(Chunk *chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    initLineArray(&chunk->rle);
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeLineArray(&chunk->rle);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

static void addLine(Chunk *chunk, int line) {
    if (chunk->rle.capacity < chunk->rle.count + 1) {
        int oldCapacity = chunk->rle.capacity;
        chunk->rle.capacity = GROW_CAPACITY(oldCapacity);
        chunk->rle.lines = GROW_ARRAY(Line, chunk->rle.lines, oldCapacity,
                                      chunk->rle.capacity);
    }

    if (chunk->rle.count == 0 ||
        chunk->rle.lines[chunk->rle.count - 1].num != line) {
        chunk->rle.lines[chunk->rle.count++] = (Line){.num = line, .rep = 1};
        return;
    }

    chunk->rle.lines[chunk->rle.count - 1].rep++;
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code =
            GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    addLine(chunk, line);
    chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

int getLine(Chunk *chunk, int op_index) {
    Line *l = chunk->rle.lines;
    int sum = 0;
    while (l != NULL) {
        sum += l->rep;
        if (op_index + 1 <= sum)
            return l->num;
        l++;
    }
}
