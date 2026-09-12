#include "chunk.h"
#include "common.h"
#include "debug.h"
#include <stdio.h>

int main(int argc, const char *argv) {
    Chunk chunk;
    initChunk(&chunk);

    for (int i = 0; i < 256; i++) {
        int constant = addConstant(&chunk, 1.2);
        writeChunk(&chunk, OP_CONSTANT, 1);
        writeChunk(&chunk, constant, 150);
    }
    writeConstant(&chunk, 11189196, 2);

    writeChunk(&chunk, OP_RETURN, 3);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
