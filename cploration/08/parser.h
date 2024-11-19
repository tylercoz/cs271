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

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

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
    opcode a:1;
    opcode c:6;
    opcode d:3;
    opcode j:3;
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

#endif
