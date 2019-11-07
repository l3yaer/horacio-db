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
  uint32_t root_page_num;
} Table;

Table* db_open(const char* filename);
void db_close(Table *table);

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void print_row(Row* row);

static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
#endif //HORACIODB_TABLE_H
