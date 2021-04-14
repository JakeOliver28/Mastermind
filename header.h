#ifndef HEADER_H
#define HEADER_H

typedef struct{
   int numPos, maxGuess, curGuess;
   char maxLet, answer[9], guess[9];
} Board;

void FlushStdin();
int seedPrompt(int *seed);
int maxLetterPrompt(char *maxLetter);
int numPosPrompt(int *numPositions);
int numGuessPrompt(int *numGuesses);
Board generateBoard(int seed, char maxLtr, int numPos, int numGuess);
int promptGuess(Board *brd, int *value);
int checkExactGuesses(Board brd);
int checkInexactGuesses(Board brd);
int existsInexactMatch(int numPos, char guess, char *answer);
void runTheGame(Board *brd, int *gameOver, int value);
int showGuesses(Board brd);
void printEOF();
int miniPrompt(int *x, int *y);

#define TRUE 1
#define FALSE 0
#define CORRECT 1
#define INCORRECT 0

#endif
