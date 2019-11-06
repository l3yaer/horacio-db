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

typedef struct {
  StatementType type;
} Statement;


PrepareResult prepare_statement(struct input_buffer* input_buffer, Statement* statement);
void execute_statement(Statement* statement);
#endif //HORACIODB_STATEMENT_H
