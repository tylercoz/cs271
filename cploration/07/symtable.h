/****************************************
 * C-ploration for CS 271
 *
 * [NAME] Tyler Cozzocrea
 * [TERM] FALL 2024
 *
 ****************************************/

#include <stdio.h>
#include <stdint.h>

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

typedef struct {
    char* name;
    hack_addr addr;
} Symbol;

int hash(char *str);
Symbol *symtable_find(char * key);
void symtable_insert(char* key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();
