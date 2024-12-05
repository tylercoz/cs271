/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Tyler Cozzocrea
 * [TERM] FALL 2024
 *
 ****************************************/

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

char *extract_label(const char *line, char* label);

typedef enum {
    Invalid = -1,
    Atype,
    Ctype
} instr_type;

typedef struct {
    unsigned int a:1;
    opcode c:7;
    opcode d:4;
    opcode j:4;
} c_instruction;

typedef struct {
    union {
        int address;
        char *label;
    } a_instruction;
    bool is_addr;
} a_instruction;

typedef struct {
    union {
        a_instruction a;
        c_instruction c;
    };
    instr_type instruction_type;
} instruction;

/** function prototypes **/
char *strip(char *s);
int parse(FILE * file, instruction *instructions);

void add_predefined_symbols();
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);

void assemble(const char * file_name, instruction* instructions, int num_instructions);

#endif
