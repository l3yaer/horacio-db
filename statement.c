//
// Created by Yago Teixeira on 2019-11-06.
//
#include <stdio.h>
#include "statement.h"
#include "input.h"

PrepareResult prepare_statement(struct input_buffer* input_buffer, Statement* statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }
  if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
  switch(statement->type) {
    case STATEMENT_INSERT:
      printf("DO AN INSERT\n");
      break;
    case STATEMENT_SELECT:
      printf("DO A SELECT\n");
      break;
  }
}