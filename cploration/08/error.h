#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>

#endif

enum exitcode {
    /*
     * Error code 1 represents that given file does not exist.
     */
    EXIT_INCORRECT_ARGUMENTS = 1,
    EXIT_CANNOT_OPEN_FILE = 2,
    EXIT_TOO_MANY_INSTRUCTIONS = 3,
    EXIT_INVALID_LABEL = 4,
    EXIT_SYMBOL_ALREADY_EXISTS = 5
};

void exit_program(enum exitcode code, ...);
