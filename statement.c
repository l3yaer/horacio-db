#include <stdio.h>
#include "statement.h"
#include "input.h"
#include "table.h"

typedef struct statement{
  StatementType type;
  Row row_to_insert;
} Statement;

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    return prepare_insert(input_buffer, statement);
  }
  if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult execute_statement(Statement* statement, Table* table) {
  switch(statement->type) {
    case STATEMENT_INSERT:
      return execute_insert(statement, table);
    case STATEMENT_SELECT:
      return execute_select(statement, table);
  }
}

ExecuteResult execute_insert(Statement *statement, Table *table) {
  if (table->num_rows >= table_max_rows()) {
    return EXECUTE_TABLE_FULL;
  }
  Row* row_to_insert = &(statement->row_to_insert);
  serialize_row(row_to_insert, row_slot(table, table->num_rows));
  table->num_rows += 1;
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *statement, Table *table) {
  Row row;
  for (uint32_t i = 0; i < table->num_rows; i++) {
    deserialize_row(row_slot(table, i), &row);
    print_row(&row);
  }
  return EXECUTE_SUCCESS;
}

Statement *createStatement() {
  Statement *statement = malloc(sizeof(Statement));
  return statement;
}

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement) {
  statement->type = STATEMENT_INSERT;

  char* keyword = strtok(input_buffer->buffer, " ");
  char* id_string = strtok(NULL, " ");
  char* username = strtok(NULL, " ");
  char* email = strtok(NULL, " ");

  if(id_string == NULL || username == NULL || email == NULL)
    return PREPARE_SYNTAX_ERROR;

  int id = atoi(id_string);
  if(strlen(username) > COLUMN_USERNAME_SIZE)
    return PREPARE_STRING_TOO_LONG;
  if(strlen(email) > COLUMN_EMAIL_SIZE)
    return PREPARE_STRING_TOO_LONG;
  if(id < 0)
    return PREPARE_NEGATIVE_ID;

  statement->row_to_insert.id = id;
  strcpy(statement->row_to_insert.username, username);
  strcpy(statement->row_to_insert.email,email);

  return PREPARE_SUCCESS;
}