#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "table.h"

#ifndef HORACIODB_STATEMENT_H
#define HORACIODB_STATEMENT_H
struct input_buffer;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT,
  PREPARE_STRING_TOO_LONG,
  PREPARE_NEGATIVE_ID
} PrepareResult;

typedef enum {
  STATEMENT_INSERT,
  STATEMENT_SELECT
} StatementType;

typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;


PrepareResult prepare_statement(struct input_buffer* input_buffer, Statement* statement);


typedef enum {
  EXECUTE_TABLE_FULL,
  EXECUTE_SUCCESS
} ExecuteResult;

ExecuteResult execute_statement(Statement* statement, Table* table);
ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);
#endif //HORACIODB_STATEMENT_H
