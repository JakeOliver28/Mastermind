#include <stdio.h>
#include <string.h>
#include "header.h"

// Flushes Standard Input
void FlushStdin(){
   int ch;
   while (((ch = getchar()) != '\n') && (ch != EOF));
}

// Prompt for random number generator seed
int seedPrompt(int *seed){
   int scanResult;
   printf("Enter the seed for random number generation: ");
   while (1){
      scanResult = scanf("%d", seed);
      FlushStdin();
      if (scanResult == 1)
         break;
      printf("Seed must be an integer value, please try again\n");
      if (scanResult == EOF){
         printEOF();
         return EOF;
      }
      else{
         printf("Enter the seed for random number generation: ");
      }
   }
   return 0;
}

// Prompt for maximum letter for the game
int maxLetterPrompt(char *maxLetter){
   int scanResult;
   printf("Enter the maximum letter for the game (A-Z): ");
   while (1){
      scanResult = scanf(" %c", maxLetter);
      FlushStdin();
      if (!(scanResult == EOF || *maxLetter < 'A' || *maxLetter > 'Z' || scanResult == 0))
         return 0;
      printf("The letter must be an uppercase A-Z, please try again\n");
      if (scanResult == EOF){
         printEOF();
         return EOF;
      }
      else
         printf("Enter the maximum letter for the game (A-Z): ");
   }
}

// Prompt for the number of positions for the game
int numPosPrompt(int *numPositions){
   int scanResult;
   printf("Enter the number of positions for the game (1-8): ");
   while (1){
      scanResult = scanf("%d", numPositions);
      FlushStdin();
      if (scanResult == EOF){
         printf("The number of positions must be 1-8, please try again\n");
         printEOF();
         return EOF;
      }
      if (*numPositions < 1 || *numPositions > 8 || scanResult == 0){
         printf("The number of positions must be 1-8, please try again\n");
         printf("Enter the number of positions for the game (1-8): ");
      }
      else
         return 0;
   }
}

// Prompt for the number of guesses allowed
int numGuessPrompt(int *numGuesses){
   int scanResult;
   printf("Enter the number of guesses allowed for the game: ");
   while (1){
      scanResult = scanf("%d", numGuesses);
      FlushStdin();
      if (!(scanResult == EOF || *numGuesses < 1 || scanResult == 0))
         return 0;
      printf("The number guesses must be a ");
      printf("positive integer, please try again\n");
      if (scanResult == EOF){
         printEOF();
         return EOF;
      }
      else if (*numGuesses < 1 || scanResult == 0)
         printf("Enter the number of guesses allowed for the game: ");
   }
}

void printEOF(){
   fprintf(stderr, "Unexpected EOF\n");
}
