#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Randomly generate game board with given constraints
Board generateBoard(int seed, char maxLet, int numPos, int numGuess){
   int i;
   Board brd;
   // Seed the random number generator
   srand((unsigned)seed);

   // Generate the board
   for (i = 0; i < numPos; i++)
      brd.answer[i] = rand()%(maxLet-64) + 65;
   brd.answer[i] = '\0';
   brd.maxLet = maxLet;
   brd.numPos = numPos;
   brd.maxGuess = numGuess;
   brd.curGuess = 1;
   return brd;
}

// Function that runs main gameplay.
// Iterates through each turn until correct guess happens or max guesses is reached.
void runTheGame(Board *brd, int *gameOver, int invalidGuess){
   int continueGame = TRUE;
   while (continueGame != FALSE){
      continueGame = promptGuess(brd, &invalidGuess);
      // If guess is correct
      if (continueGame == FALSE)
        break;
      // If guess is valid and incorrect
      if (invalidGuess == FALSE){
         // Show exact & inexact guesses
         *gameOver = showGuesses(*brd);
         // End game if max amount of guesses has been reached
         if (*gameOver == TRUE)
            break;
         // Increment current guess number
         brd->curGuess = brd->curGuess + 1;
      }
      // Reset invalidGuess variable
      else
         invalidGuess = FALSE;
   }
}

// Prompt a guess and check if it's correct
int promptGuess(Board *brd, int *invalidGuess){
   int i;
   char guess[9];
   printf("Enter guess %d: ", brd->curGuess);
   // Iterate through the characters in the guess
   for (i = 0; i < brd->numPos; i++){
      scanf(" %c", &(guess[i]));

      // Exit if EOF is found
      if (feof(stdin))
        exit(0);
      // If character is not valid, print statement & exit function
      if (guess[i] < 'A' || guess[i] > brd->maxLet){
         printf("Invalid guess, please try again\n\n");
         FlushStdin();
         *invalidGuess = 1;
         return 1;
      }
   }

   guess[i] = '\0';
   FlushStdin();

   // Update the current guess & check if it's correct
   strcpy(brd->guess, guess);
   if (strcmp(brd->guess, brd->answer) != 0)
      return CORRECT;
   else
      return INCORRECT;
}

// Check the amount of exact guesses on a given turn
int checkExactGuesses(Board brd){
   int i;
   int count = 0;
   // Iterate through each board position and compare
   for (i = 0; i < brd.numPos; i++){
      if (brd.guess[i] == brd.answer[i])
         count++;
   }
   return count;
}

// Check the amount of inexact guesses on a given turn
int checkInexactGuesses(Board brd){
   int i, count;
   char guess[9], answer[9];
   count = 0;
   // Create string copies of the board and the current guess
   strcpy(guess, brd.guess);
   strcpy(answer, brd.answer);

   // Clear the exact guesses
   for (i = 0; i < brd.numPos; i++){
      if (guess[i] == answer[i]){
         guess[i] = ' ';
         answer[i] = ' ';
      }
   }
   // Check the remaining spots
   for (i = 0; i < brd.numPos; i++){
      count += existsInexactMatch(brd.numPos, guess[i], answer);
   }
   return count;
}

// Check for a single inexact match
int existsInexactMatch(int numPos, char guess, char *answer){
   int i;
   for (i = 0; i < numPos; i++){
      // If a non-blank space matches, clear matching space and return TRUE
      if (guess == answer[i] && answer[i] != ' '){
         answer[i] = ' ';
         return TRUE;
      }
   }
   return FALSE;
}

// Prints an update for user after each guess.
// Prints final message if user is out of guesses.
int showGuesses(Board brd){
   printf("Nope, %d exact guesses and ", checkExactGuesses(brd));
   printf("%d inexact guesses\n\n", checkInexactGuesses(brd));

   // Print final message if max guesses has been reached
   if (brd.maxGuess <= brd.curGuess){
      printf("Game over, you ran out of guesses. Better luck next time!\n");
      return 1;
   }
   else
      return 0;
}
