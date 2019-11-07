#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "table.h"
#include "pager.h"

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

void remove_full_pages(Pager *pager, uint32_t num_full_pages);

void remove_partial_pages(Table *table, Pager *pager, uint32_t num_full_pages);

void clear_page(Pager *pager, uint32_t page_num, uint32_t size);

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

uint32_t table_max_rows() {
  return TABLE_MAX_ROWS;
}

Table *db_open(const char *filename) {
  Pager* pager = pager_open(filename);
  uint32_t num_rows = pager->file_length / ROW_SIZE;

  Table* table = malloc(sizeof(Table));
  table->pager = pager;
  table->num_rows = num_rows;

  return table;
}

void db_close(Table *table) {
  Pager* pager = table->pager;
  uint32_t num_full_pages = table->num_rows / ROWS_PER_PAGE;

  remove_full_pages(pager, num_full_pages);

  remove_partial_pages(table, pager, num_full_pages);

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

void remove_partial_pages(Table *table, Pager *pager, uint32_t num_full_pages) {
  uint32_t num_additional_rows = table->num_rows % ROWS_PER_PAGE;
  if(num_additional_rows > 0) {
    uint32_t page_num = num_full_pages;
    if(pager->pages[page_num] != NULL) {
      clear_page(pager, page_num, num_additional_rows * ROW_SIZE);
    }
  }
}

void remove_full_pages(Pager *pager, uint32_t num_full_pages) {
  for (uint32_t i = 0; i < num_full_pages; ++i) {
    if(pager->pages[i] == NULL){
      continue;
    }

    clear_page(pager, i, PAGE_SIZE);
  }
}

void clear_page(Pager *pager, uint32_t page_num, uint32_t size) {
  pager_flush(pager, page_num, size);
  free(pager->pages[page_num]);
  pager->pages[page_num] = NULL;
}


uint32_t row_size() {
  return ROW_SIZE;
}

uint32_t rows_per_page() {
  return ROWS_PER_PAGE;
}