#include "metaCommand.h"
#include "input.h"
#include "table.h"


MetaCommandResult do_meta_command(struct input_buffer* input_buffer, struct table* table) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    db_close(table);
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}