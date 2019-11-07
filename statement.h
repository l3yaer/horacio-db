#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifndef HORACIODB_STATEMENT_H
#define HORACIODB_STATEMENT_H
struct input_buffer;
struct table;
struct statement;

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

typedef enum {
  EXECUTE_TABLE_FULL,
  EXECUTE_SUCCESS
} ExecuteResult;

struct statement* createStatement();
PrepareResult prepare_statement(struct input_buffer* input_buffer, struct statement* statement);
ExecuteResult execute_statement(struct statement* statement, struct table* table);
ExecuteResult execute_insert(struct statement* statement, struct table* table);
ExecuteResult execute_select(struct statement* statement, struct table* table);
#endif //HORACIODB_STATEMENT_H
