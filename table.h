#include <stdint.h>

#ifndef HORACIODB_TABLE_H
#define HORACIODB_TABLE_H

#define size_of_attribute(Struct,Attribute) sizeof(((Struct*)0)->Attribute)

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE + 1];
  char email[COLUMN_EMAIL_SIZE + 1];
} Row;


#define TABLE_MAX_PAGES 100

typedef struct {
  uint32_t num_rows;
  void* pages[TABLE_MAX_PAGES];
} Table;

Table* new_table();
void free_table(Table* table);
uint32_t table_max_rows();

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void print_row(Row* row);
void* row_slot(Table* table, uint32_t row_num);

#endif //HORACIODB_TABLE_H
