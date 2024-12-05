/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Tyler Cozzocrea
 * [TERM] FALL 2024
 *
 ****************************************/

#include <stdlib.h>
#include "parser.h"
#include "hack.h"
#include "symtable.h"
#include "error.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){

  char s_new[strlen(s)+1];
  int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if ((*s2 == '/') && (*(s2+1) == '/')) {
            break;
        }
        if (!isspace(*s2)) {
            s_new[i++] = *s2;
        }
    }

    s_new[i] = '\0';
    strcpy(s, s_new);
    return s;
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments.
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
 int parse(FILE * file, instruction *instructions) {

  char line[MAX_LINE_LENGTH] = "";
  char label[MAX_LABEL_LENGTH] = {0};

  unsigned int line_number = 0;
  unsigned int instr_num = 0;

  instruction instr;

  add_predefined_symbols();

  while (fgets(line, sizeof(line), file)) {
    line_number++;

    if (instr_num > MAX_INSTRUCTIONS) {
      exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
    }

    strip(line);
    if (!*line) {
      continue;
    }
    // char inst_type = '\0';
    if (is_Atype(line)) {
      // inst_type = 'A';
      if (!parse_A_instruction(line, &instr.a)){
          exit_program(EXIT_INVALID_A_INSTR, line_number, line);
       }
       instr.instruction_type = Atype;
       if (instr.a.is_addr) {
         printf("A: %d\n", instr.a.a_instruction.address);
       } else {
         printf("A: %s\n", instr.a.a_instruction.label);
       }
    } else if (is_label(line)) {
      // inst_type = 'L';
      extract_label(line, label);
      if (!isalpha(*label)) {
        exit_program(EXIT_INVALID_LABEL, line_number, label);
      }
      if (symtable_find(label) != NULL) {
        exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_number, label);
      }
      strcpy(line, label);
      symtable_insert(label, instr_num);
      continue;
    } else if (is_Ctype(line)) {
      // inst_type = 'C';
      char tmp_line[MAX_LINE_LENGTH];
      strcpy(tmp_line, line);
      parse_C_instruction(tmp_line, &instr.c);
      if (instr.c.c == COMP_INVALID) {
        exit_program(EXIT_INVALID_C_COMP, line_number, line);
      }
      if (instr.c.d == DEST_INVALID) {
        exit_program(EXIT_INVALID_C_DEST, line_number, line);
      }
      if (instr.c.j == JMP_INVALID) {
        exit_program(EXIT_INVALID_C_JUMP, line_number, line);
      }
      instr.instruction_type = Ctype;
      printf("C: d=%d, c=%d, j=%d\n", instr.c.d, instr.c.c, instr.c.j);
    }
    instructions[instr_num++] = instr;
    }
  return instr_num;
}

bool is_Atype(const char *line) {
    if (line[0] == '@') {
        return true;
    }
    return false;
}

bool is_label(const char *line) {
    size_t last_index = strlen(line) - 1;
    if ((line[0] == '(') && (line[last_index] ==')')) {
        return true;
    }
    return false;
}

bool is_Ctype(const char *line) {
    if ( (is_Atype(line)) || (is_label(line)) ) {
        return false;
    }
    return true;
}

char *extract_label(const char *line, char* label) {
    size_t last_index = strlen(line) - 1;

    int i = 0;
    for (i = 1; i < last_index; i++) {
        label[i-1] = line[i];
    }

    label[i-1] = '\0';

    return label;
}

void add_predefined_symbols() {
  for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
    predefined_symbol symbol = predefined_symbols[i];
    symtable_insert(symbol.name, symbol.address);
  }
}
/* Returns true if operation successful */
bool parse_A_instruction(const char *line, a_instruction *instr) {
  char *s = (char*) malloc(strlen(line));
  strcpy(s, line+1);

  char *s_end = NULL;
  long result = strtol(s, &s_end, 10);

  if (s == s_end) { // This means its a variable, not an address
    instr->a_instruction.label = (char *) malloc(strlen(line));
    strcpy(instr->a_instruction.label, s);
    instr->is_addr = false;

  } else if (*s_end != 0) { // mixture of digits and letters, not address
    return false;

  } else { // It's an address!
    instr->a_instruction.address = result;
    instr->is_addr = true;
  }

  free(s);
  return true;
}

void parse_C_instruction(char *line, c_instruction *instr) {
  char* temp = strtok(line, ";");
  char* jump = strtok(NULL, ";");
  char* dest = strtok(temp, "=");
  char* control = strtok(NULL, "=");

  if (!control) { // control bits are in dest if control is NULL (at this point)
    control = dest;
    dest = NULL;
  }

  int a_bit = 0;
  instr->d = str_to_destid(dest);
  instr->c = str_to_compid(control, &a_bit);
  instr->j = str_to_jumpid(jump);
  instr->a = a_bit;
}

void assemble(const char * file_name, instruction* instructions, int num_instructions) {

}
