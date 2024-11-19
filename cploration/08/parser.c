/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] Tyler Cozzocrea
 * [TERM] FALL 2024
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
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
void parse(FILE * file){

  char line[MAX_LINE_LENGTH] = "";
  char label[MAX_LABEL_LENGTH] = {0};

  unsigned int line_number = 0;
  unsigned int instr_num = 0;

  while (fgets(line, sizeof(line), file)) {
    line_number++;

    if (instr_num > MAX_INSTRUCTIONS) {
      exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
    }

    strip(line);
    if (!*line) {
      continue;
    }
    char inst_type = '\0';
    if (is_Atype(line)) {
      inst_type = 'A';
    } else if (is_label(line)) {
      inst_type = 'L';
      extract_label(line, label); // could be error here after taking extract_label out of str_cpy
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
      inst_type = 'C';
    }
    printf("%u: %c  %s\n", instr_num, inst_type, line);
    instr_num++;
    }

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
