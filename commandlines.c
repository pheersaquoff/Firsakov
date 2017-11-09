#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wait.h>

enum { maxLetters = 500, maxWords = 100, maxLength = 50};

void Split(char* string, char* delimiters, char*** tokensPtr, int* tokensCountPtr) {
        int tokensCount = *tokensCountPtr;
	char ** tokens = *tokensPtr;
	tokens[tokensCount] = (char*) calloc (maxLength, sizeof (char));
        tokens[tokensCount] = strtok (string, delimiters);
	while (tokens[tokensCount] != NULL) {
		tokensCount++;
		tokens[tokensCount] = (char*) calloc (maxLength, sizeof(char));
		tokens[tokensCount] = strtok (NULL, delimiters);
	}
	*tokensCountPtr = tokensCount;	
	for (int i = 0; i < tokensCount; i++) 
		free(tokens[tokensCount]);
}
	
int  main () {
	FILE* f = fopen ("comms.txt", "r");
	fseek (f, 0, SEEK_END);
        int size = ftell(f);
        fseek (f, 0, SEEK_SET);
        char * buf = (char*) calloc(size, sizeof (char));
	fread (buf, 1, size, f);
	char** lines = (char**) calloc(size, sizeof(char));
	int linesCount = 0;
	Split (buf, "\n", &lines, &linesCount); 
	int i;
	pid_t pid = 0;
	int wholeTime = 0;
	for (i = 1; i < linesCount; i++) {
		char** words = (char**) calloc(maxWords, sizeof(char));
		int wordsCount = 0;
		Split(lines[i], " ", &words, &wordsCount);
		int time = atoi(words[wordsCount - 1]);
		if (time > wholeTime) wholeTime = time;
		words[wordsCount - 1] = NULL;
		pid = fork();
		if (pid == 0) {
			sleep(time);
			execvp(words[0], words);
			exit(-1);
		}
		if (pid == -1) {
			printf("Error\n");
			exit(-1);
		}
	sleep(wholeTime+1);
	free(words);
	}
	free(buf);
}
