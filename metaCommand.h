#ifndef HORACIODB_METACOMMAND_H
#define HORACIODB_METACOMMAND_H
struct input_buffer;

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


MetaCommandResult do_meta_command(struct input_buffer* input_buffer);
#endif //HORACIODB_METACOMMAND_H
