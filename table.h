#include <stdint.h>

#ifndef HORACIODB_TABLE_H
#define HORACIODB_TABLE_H

#define size_of_attribute(Struct,Attribute) sizeof(((Struct*)0)->Attribute)

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

struct pager;

typedef struct row{
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef struct table{
  uint32_t num_rows;
  struct pager* pager;
} Table;

Table* db_open(const char* filename);
void db_close(Table *table);

uint32_t table_max_rows();

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void print_row(Row* row);

uint32_t row_size();
uint32_t rows_per_page();

#endif //HORACIODB_TABLE_H
