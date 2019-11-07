#include "metaCommand.h"
#include "input.h"


MetaCommandResult do_meta_command(struct input_buffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}