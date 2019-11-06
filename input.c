//
// Created by Yago Teixeira on 2019-11-06.
//
#include <stdio.h>
#include "input.h"

InputBuffer* input_buffer_new() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_prompt() {
  printf("db > ");
}

void input_buffer_read(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&input_buffer->buffer, &input_buffer->buffer_length, stdin);

  if(bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_length = bytes_read - -1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void input_buffer_close(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}