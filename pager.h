#include <stdint.h>

#ifndef HORACIODB_PAGER_H
#define HORACIODB_PAGER_H

#define TABLE_MAX_PAGES 100
#define PAGE_SIZE 4098

typedef struct pager {
  int file_descriptor;
  uint32_t file_length;
  uint32_t num_pages;
  void* pages[TABLE_MAX_PAGES];
} Pager;

Pager* pager_open(const char* filename);
void* get_page(Pager* pager, uint32_t page_num);
void pager_flush(Pager* pager, uint32_t page_num);

#endif //HORACIODB_PAGER_H
