#include <stdint.h>

#ifndef HORACIODB_TREENODE_H
#define HORACIODB_TREENODE_H
struct cursor;
struct row;
struct table;

typedef enum {
  NODE_INTERNAL,
  NODE_LEAF
} NodeType;

uint32_t* leaf_node_num_cells(void* node);
void* leaf_node_cell(void* node, uint32_t cell_num);
uint32_t* leaf_node_key(void* node, uint32_t cell_num);
void* leaf_node_value(void* node, uint32_t cell_num);
void initialize_leaf_node(void* node);
NodeType get_node_type(void* node);
void set_node_type(void* node, NodeType type);
void leaf_node_insert(struct cursor* cursor, uint32_t key, struct row* value);
struct cursor* leaf_node_find(struct table* table, uint32_t page_num, uint32_t key);

void print_constants();
void print_leaf(void* node);

extern const uint32_t LEAF_NODE_MAX_CELLS;

#endif //HORACIODB_TREENODE_H
