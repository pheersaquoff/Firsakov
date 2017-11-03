#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum { maxLetters = 500, maxWords = 100, maxLength = 50};

void Split(char* string, char* delimiters, char*** tokensPtr, int* tokensCountPtr) {
        int tokensCount = *tokensCountPtr;
	char ** tokens = *tokensPtr;
	tokens[tokensCount] = (char*) calloc (maxLength, sizeof (char));
        tokens[tokensCount] = strtok (string, delimiters);
	while (tokens[tokensCount] != NULL) {
		printf("%d: %s\n", (tokensCount + 1), tokens[tokensCount]);
		tokensCount++;
		tokens[tokensCount] = strtok (NULL, delimiters);
	}	
}

int main () {
        char string [maxLetters]    = "";
        char delimiters [maxLength] = "";
        char ** tokens;
        int tokensCount = 0;
        tokens = (char**) calloc (maxWords, sizeof(char*));
        printf ("Enter the string: ");
	fgets (string, maxLetters, stdin);
	printf ("Enter the delimiter: ");
        fgets (delimiters, maxLength, stdin);
        Split (string, delimiters, &tokens, &tokensCount);   
        free(tokens);
}

