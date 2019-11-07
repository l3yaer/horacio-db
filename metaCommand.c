#include "metaCommand.h"
#include "input.h"
#include "table.h"
#include "treeNode.h"
#include "pager.h"

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    db_close(table);
    exit(EXIT_SUCCESS);
  } else if(strcmp(input_buffer->buffer, ".constants") == 0) {
    print_constants();
    return META_COMMAND_SUCCESS;
  } else if(strcmp(input_buffer->buffer, ".btree") == 0) {
    print_leaf(get_page(table->pager, 0));
    return META_COMMAND_SUCCESS;
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}