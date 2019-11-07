#include <stdint.h>
#include <stdbool.h>

#ifndef HORACIODB_CURSOR_H
#define HORACIODB_CURSOR_H
struct table;

typedef struct cursor {
  struct table* table;
  uint32_t row_num;
  bool end_of_table;
} Cursor;

Cursor* table_start(struct table* table);
Cursor* table_end(struct table* table);
void* cursorValue(Cursor* cursor);
void cursor_advance(Cursor* cursor);

#endif //HORACIODB_CURSOR_H
