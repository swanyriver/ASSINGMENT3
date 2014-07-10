/***********************************************************
 * Author: Brandon Swanson
 * Date Created: 06-30-2014
 * Last Modification Date: 06-30-2014
 * Filename: hangman.cpp
 *
 * Overview: A word guessing game
 *
 * Input: A secret word, letter guesses
 *
 * Output: correctly guess letters
 *
 ***********************************************************/

#include "myFunctions.hpp"
#include "hangmanStrings.h"
#include <iostream>
#include <string>

using namespace std;

//reset variables for each game
void InitializeVars ();

//get a word from player one
string PlayerOnePickWord ();

//get a guess letter or word from player two
string PlayerTwoGuess ();

//analyze guess made
void ProcessGuess ( string guessString );

//output correct letters to player
void PrintResults ();

//somewhat obscure secret word input
void ClearScreen ();

const int MAX_WORD_LENGTH = 12;
const int LENGTH_OF_ALPHABET = 26;
const int CLEAR_SCREEN_CHAR_NUM = 6000 * 5;

string SecretWord;
int maxGuesses;
char lettersRevealed[LENGTH_OF_ALPHABET];
char lettersInSecretWord[LENGTH_OF_ALPHABET];
string guessesMade[LENGTH_OF_ALPHABET];
int numLettersRevealed;
int numGuessesMade;
int numLettersInWord; //distinct letters

int main () {

   do { //restart game
      InitializeVars();

      ClearScreen();

      do { // make guesses
         string guessString = PlayerTwoGuess();
         guessesMade[numGuessesMade] = guessString;
         numGuessesMade++;

         ProcessGuess( guessString );

         if ( !(guessString == SecretWord
               || numLettersRevealed == numLettersInWord) ) {
            PrintResults();
         }

         /////debug string////////
         /*cout << numGuessesMade << " " << MAX_GUESSES
          << "  " << numLettersRevealed << "/" << numLettersInWord
          << " " << SecretWord << "  " << guessesMade[numGuessesMade-1]
          << endl;*/
         ///////debug string
      } while ( numGuessesMade < maxGuesses
            && numLettersRevealed < numLettersInWord
            && guessesMade[numGuessesMade - 1] != SecretWord );

      if ( guessesMade[numGuessesMade - 1] == SecretWord
            || numLettersRevealed == numLettersInWord ) {
         cout << YOU_WIN;
      } else {
         cout << MISSING <<
         (((numLettersInWord - numLettersRevealed) > 1) ?
         LETTER_PLURAL :
                                                          LETTER);
         for ( int i = 0 ; i < numLettersInWord ; i++ ) {
            if ( !swansonUtil::Contains( lettersInSecretWord[i] ,
                  lettersRevealed , numLettersRevealed ) )
               cout << lettersInSecretWord[i] << " ";
         }

         cout << WORD_REVEAL << SecretWord;

         cout << YOU_LOSE;
      }

   } while ( swansonInput::yesNo( PLAY_AGAIN_STR ) );

   cout << endl << GOODBYE_STR << endl;

   return 0;
}

/**************************************************************
 *
 * Entry: none
 *
 * Exit: counter values reset to 0, a secret word, number of guesses allowd
 *       letters in word counted and array filled
 *
 * Purpose: to reset the data structure for the playing of a new game
 *
 * ***************************************************************/

void InitializeVars () {
   SecretWord = PlayerOnePickWord();

   maxGuesses = swansonInput::GetInt( MAX_GUESSES_STR , 1 ,
         LENGTH_OF_ALPHABET );

   numLettersRevealed = 0;
   numGuessesMade = 0;
   numLettersInWord = 0;

   numLettersRevealed = 0;
   for ( int i = 0 ; i < SecretWord.size() ; i++ ) { //set lettersInSecretWord[]
      if ( !swansonUtil::Contains( SecretWord.at( i ) , lettersInSecretWord ,
            numLettersInWord ) ) {
         lettersInSecretWord[numLettersInWord] = SecretWord.at( i );
         numLettersInWord++;
      }
   }

}

/**************************************************************
 *
 * Entry:none
 *
 * Exit:a string of all alpha chars no spaces
 *
 * Purpose: to get the word to be used for the guessing game from player 1
 *
 * ***************************************************************/
string PlayerOnePickWord () {

   string secretString;
   secretString = swansonInput::GetOneWord( ENTER_WORD_STR );

   while ( secretString.size() > MAX_WORD_LENGTH ) {
      cout << endl << TOO_LONG;
      secretString = swansonInput::GetOneWord( ENTER_WORD_STR );
   }

   secretString = swansonString::LowerCase( secretString );
   return secretString;
}

/**************************************************************
 *
 * Entry: none
 *
 * Exit: a series of random letters sent to output stream
 *
 * Purpose: obscure the entered secret word
 *
 * ***************************************************************/
void ClearScreen () {
   /*char randChar;
   for ( int i = 0 ; i < CLEAR_SCREEN_CHAR_NUM ; i++ ) {
      randChar = swansonUtil::GetRandomInRange( 'A' , 'Z' );
      cout << randChar;
   }

   cout << endl << endl;*/

   system("clear");
}

/**************************************************************
 *
 * Entry: none
 *
 * Exit: a string of all letters no spaces
 *
 * Purpose: to get a guess from player 2
 *
 * ***************************************************************/
string PlayerTwoGuess () {
   string guessString;
   bool retry;

   int guessesRemaining = maxGuesses - numGuessesMade;

   cout << GUESS_INSTR_STR;
   cout << endl << ((guessesRemaining > 1) ? NUM_GUESSES : NUM_GUESSES_SINGULAR)
         << guessesRemaining;

   do {
      retry = false;
      do {
         if ( retry )
            cout << ENTERED_BEFORE;
         guessString = swansonInput::GetOneWord( GUESS_PROMPT );
         guessString = swansonString::LowerCase( guessString );
         retry = true;
      } while ( swansonUtil::Contains( guessString , guessesMade ,
            numGuessesMade ) );
   } while ( guessString.size() > 1
         && !swansonInput::yesNo( GUESS_CHECK + guessString + "\n" ) );

   return guessString;

}

/**************************************************************
 *
 * Entry: a single character
 *
 * Exit: if letter is in word its added to lettersRevealed
 *       and numLettersRevealed incremented
 *
 * Purpose: determine successful guesses
 *
 * ***************************************************************/
void ProcessGuess ( string guessString ) {

   if ( guessString.size() == 1 ) {
      //check character
      if ( swansonUtil::Contains( guessString.at( 0 ) , lettersInSecretWord ,
            numLettersInWord ) ) {
         lettersRevealed[numLettersRevealed] = guessString.at( 0 );
         numLettersRevealed++;
      }
   }

}

/**************************************************************
 *
 * Entry: none
 *
 * Exit: outputs the letters reveled in the secret word and guesses remaining
 *
 * Purpose: inform player 2 of his status in the game
 *
 * ***************************************************************/
void PrintResults () {
   cout << endl << STILL_WRONG << endl << STRING_HINT << endl;
   for ( int i = 0 ; i < SecretWord.size() ; i++ ) {
      cout << " ";
      char cursorChar = SecretWord.at( i );
      if ( swansonUtil::Contains( cursorChar , lettersRevealed ,
            numLettersRevealed ) ) {
         cout << cursorChar;
      } else
         cout << "-";
   }
}
