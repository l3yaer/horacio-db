#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "table.h"
#include "pager.h"
#include "treeNode.h"

void serialize_row(Row* source, void* destination) {
  memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
  strncpy(destination + USERNAME_OFFSET, source->username, USERNAME_SIZE);
  strncpy(destination + EMAIL_OFFSET, source->email, EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination) {
  memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
  memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

void print_row(Row *row) {
  printf("( %d %s %s )\n", row->id, row->username, row->email);
}

Table *db_open(const char *filename) {
  Pager* pager = pager_open(filename);

  Table* table = malloc(sizeof(Table));
  table->pager = pager;
  table->root_page_num = 0;

  if(pager->num_pages == 0) {
    void* root_node = get_page(pager,0);
    initialize_leaf_node(root_node);
  }

  return table;
}

void db_close(Table *table) {
  Pager* pager = table->pager;

  for (uint32_t i = 0; i < pager->num_pages; ++i) {
    if(pager->pages[i] == NULL){
      continue;
    }

    pager_flush(pager, i);
    free(pager->pages[i]);
    pager->pages[i] = NULL;
  }

  int result = close(pager->file_descriptor);
  if(result == -1) {
    printf("Error closing db file.\n");
    exit(EXIT_FAILURE);
  }

  for (uint32_t j = 0; j < TABLE_MAX_PAGES; ++j) {
    void* page = pager->pages[j];
    if(page) {
      free(page);
      pager->pages[j] = NULL;
    }
  }

  free(pager);
  free(table);
}