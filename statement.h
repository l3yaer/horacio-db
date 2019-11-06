//
// Created by Yago Teixeira on 2019-11-06.
//
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef HORACIODB_STATEMENT_H
#define HORACIODB_STATEMENT_H
struct input_buffer;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT
} StatementType;

#define size_of_attribute(Struct,Attribute) sizeof(((Struct*)0)->Attribute)

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE];
  char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;


#define TABLE_MAX_PAGES 100

typedef struct {
  uint32_t num_rows;
  void* pages[TABLE_MAX_PAGES];
} Table;

Table* new_table();
void free_table(Table* table);

PrepareResult prepare_statement(struct input_buffer* input_buffer, Statement* statement);

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void print_row(Row* row);
void* row_slot(Table* table, uint32_t row_num);

typedef enum {
  EXECUTE_TABLE_FULL,
  EXECUTE_SUCCESS
} ExecuteResult;

ExecuteResult execute_statement(Statement* statement, Table* table);
ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);
#endif //HORACIODB_STATEMENT_H
