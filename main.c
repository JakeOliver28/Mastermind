#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[]){
   int seed, numPos, numGuess, gameOver, invalidGuess;
   char maxLtr;
   Board brd;
   invalidGuess = FALSE;

   // Return error if more than 2 arguments without "-show" as an argument
   if (argc >= 2 && (strcmp(argv[1], "-show") || argc != 2)){
      fprintf(stderr, "Usage: mastermind [-show]\n");
      return EXIT_FAILURE;
   }

   // Prompt user for input and store values in their respective variables
   if (seedPrompt(&seed) == EOF)
      return EXIT_FAILURE;
   else if (maxLetterPrompt(&maxLtr) == EOF)
      return EXIT_FAILURE;
   else if (numPosPrompt(&numPos) == EOF)
      return EXIT_FAILURE;
   else if (numGuessPrompt(&numGuess) == EOF)
      return EXIT_FAILURE;


   // Randomly generate the board with proper constraints
   brd = generateBoard(seed, maxLtr, numPos, numGuess);

   // Print the correct board if "-show" was an argument
   if (argc == 2)
      printf("Initialized Game Board: %s\n", brd.answer);
   printf("\n");

   // Run the game
   runTheGame(&brd, &gameOver, invalidGuess);

   // If answer was guessed on or before the last possible guess
   if (!gameOver)
      printf("\nWow, you won in %d guesses - well done!\n", brd.curGuess);

   return 0;
}
