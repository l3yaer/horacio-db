#include <stdlib.h>
#include "cursor.h"
#include "table.h"
#include "pager.h"

Cursor* table_start(struct table* table) {
  Cursor* cursor = malloc(sizeof(Cursor));
  cursor->table = table;
  cursor->row_num = 0;
  cursor->end_of_table = (table->num_rows == 0);

  return cursor;
}

Cursor* table_end(struct table* table) {
  Cursor* cursor = malloc(sizeof(Cursor));
  cursor->table = table;
  cursor->row_num = table->num_rows;
  cursor->end_of_table = true;

  return cursor;
}

void* cursorValue(Cursor* cursor) {
  uint32_t row_num = cursor->row_num;
  uint32_t page_num = row_num / rows_per_page();
  void* page = get_page(cursor->table->pager, page_num);
  uint32_t row_offset = row_num % rows_per_page();
  uint32_t byte_offset = row_offset * row_size();
  return page + byte_offset;
}

void cursor_advance(Cursor* cursor) {
  cursor->row_num += 1;
  if(cursor->row_num >= cursor->table->num_rows) {
    cursor->end_of_table = true;
  }
}