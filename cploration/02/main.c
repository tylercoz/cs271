/****************************************
 * C-ploration 2 for CS 271
 *
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 *
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIMIT 200  /* max size for static string */


/* Function: length
 * -------------
 * find the length of a char* string from scratch
 *   note: do not use strlen() library function!
 *
 * txt: the string (character array)
 *
 * returns: the length of the string
 */
int length(char* txt) {
	int len = 0;
	int i = 0;

	while (txt[i] != '\0') {
    	len++;
    	i++;
	}

	return len;
}


/* Function: welcome
 * -------------
 * concatenates a welcome message together
 *   - add hello variable
 *   - add a single space (between words)
 *   - add user provided name
 *   - add a single exclamation point
 *
 * hello: string containing "hello"
 * name: string containing the name
 *
 * returns: "Hello NAME!", based on a given NAME
 */
char *welcome(char* hello, char* name) {
	// dynamically allocate a new string
	char *message = malloc(sizeof(char)*MAX_LIMIT);

	strcat(message, hello);
	strcat(message, " ");
	strcat(message, name);
	strcat(message, "!");

	return message;
}


/* Function: reverse
 * -------------
 * reverses a string
 *   note: we are using "pass-by-pointer" to save result
 *
 * txt: string to reverse
 * result: empty string in which to store result
 *
 * returns: nothing. result contains the reversed string.
 */
void reverse(char* txt, char* result) {
    int len = length(txt);
    int i = len - 1;
    int j = 0;
    while (i >= 0) {
        result[j] = txt[i];
        i--;
        j++;
    }
}


/* Function: vowels
 * -------------
 * count the number of vowels in the string
 *   - a, e, i, o, or u
 *
 * txt: string in which to count vowels
 *
 * returns: integer count of vowels
 */
int vowels(char* txt) {
    int vowel = 0;
    char possible_vowels[] = {'a', 'e', 'i', 'o', 'u',
                              'A', 'E', 'I', 'O', 'U'};

    for (int i = 0; i < length(txt); i++) {
        for (int j = 0; j < length(possible_vowels); j++) {
            if (possible_vowels[j] == txt[i]) {
                vowel++;
            }
        }
    }

	return vowel;
}


/* Function: quartile
 * -------------
 * determines which quarter of the alphabet we find the name
 *   - A-F => 1
 *   - G-L => 2
 *   - M-R => 3
 *   - S-Z => 4
 *
 * Use the strcmp method from string.h
 *
 * name: string to check place in alphabet
 *
 * returns: integer quarter [1..4]
 */
int quartile(char* name) {
    // Compares first letter of name to ASCII values of characters,
    // finds what quartile of the alphabet the name is in.

    char first_letter = name[0];

    if ((first_letter <=64) || (first_letter >= 123)) {
        printf("Invalid first letter. Only the standard\
                English alphabet is allowed.");
        exit(EXIT_FAILURE);
    }

    // A-F
    if (first_letter <= 'F') {
        return 1;
    }
    // G-L
    if (first_letter <= 'L') {
        return 2;
    }
    // M-R
    if (first_letter <= 'R') {
        return 3;
    }
    // S-Z
    if (first_letter <= 'Z') {
        return 4;
    }
    printf("\nNo quartile found.\n");
    return -1;
}


/* Function: main
 * -------------
 * parses command line arguments and executes appropriate function.
 *
 * =========================
 * DO NOT EDIT MAIN FUNCTION
 * =========================
 *
 * argc: number of arguments
 * argv: array of arguments (array of array of chars)
 *
 * returns: 0 if no errors, 1 otherwise.
 */
int main(int argc, char** argv)
{
	// declare a string with value
	char hello[] = "Hello";
	// declare an empty string of max size
	char name[MAX_LIMIT];

	// prompt user for name
	printf("What is your name? ");
	// the [^\n] means to discard the newline character
	scanf("%[^\n]s", name);
	// make sure name starts with a capital letter
	name[0] = toupper((unsigned char)name[0]);

	// when no arguments given
	if (argc < 2){
		// Task 1: display welcome
		char *greeting = welcome(hello, name);
		printf("%s\n", greeting);

		// Task 2: count characters
		int len = length(name);
		printf("%s is %d characters long.\n", name, len);

		// Task 3: reverse string
		char backwards[length(name)];
		reverse(name, backwards);
		printf("%s backwards is %s.\n", name, backwards);

		// Task 4: count vowels
		printf("%s contains %d vowels.\n", name, vowels(name));

		// Task 5: find which quarter of the alphabet
		printf("%s is in quartile #%d alphabetically.", name, quartile(name));
	}else{
		/******************************
		 *  USED BY GRADESCOPE TESTS  *
		 *****************************/
		if (!strcmp(argv[1], "-count")){
			printf("%d\n", length(name));
		}else if (!strcmp(argv[1], "-greeting")){
			printf("%s\n", welcome(hello, name));
		}else if (!strcmp(argv[1], "-reverse")){
			char backwards[length(name)];
			reverse(name, backwards);
			printf("%s\n", backwards);
		}else if (!strcmp(argv[1], "-vowel")){
			printf("%d\n", vowels(name));
		}else if (!strcmp(argv[1], "-quartile")){
			printf("%d\n", quartile(name));
		}else{
			// incorrect command, exit with error
			fprintf(stderr, "[error] Unknown command %s.\n", argv[1]);
			return 1;
		}
	}
    return 0;
}
