#ifndef clox_line_h
#define clox_line_h

typedef struct {
    int num, rep;
} Line;

typedef struct {
    int capacity;
    int count;
    Line *lines;
} LineArray;

void initLineArray(LineArray *array);
void writeLineArray(LineArray *array, Line line);
void freeLineArray(LineArray *array);

#endif