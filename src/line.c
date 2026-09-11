#include <stdio.h>

#include "line.h"
#include "memory.h"

void initLineArray(LineArray *array) {
    array->lines = NULL;
    array->capacity = 0;
    array->count = 0;
}

void writeLineArray(LineArray *array, Line line) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->lines =
            GROW_ARRAY(Line, array->lines, oldCapacity, array->capacity);
    }

    array->lines[array->count] = line;
    array->count++;
}

void freeLineArray(LineArray *array) {
    FREE_ARRAY(Line, array->lines, array->capacity);
    initLineArray(array);
}