//
// Created by Yago Teixeira on 2019-11-06.
//

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef HORACIODB_INPUT_H
#define HORACIODB_INPUT_H

typedef struct input_buffer{
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* input_buffer_new();
void print_prompt();
void input_buffer_read(InputBuffer* input_buffer);
void input_buffer_close(InputBuffer* input_buffer);
#endif //HORACIODB_INPUT_H
