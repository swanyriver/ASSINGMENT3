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
char PlayerTwoGuess ();

//analyze guess made
void ProcessGuess ( char guessLetter );

//output correct letters to player
void PrintResults ();

bool PlayerHasWon();

//somewhat obscure secret word input
void ClearScreen ();

const int MAX_WORD_LENGTH = 12;
const int LENGTH_OF_ALPHABET = 26;
const int CLEAR_SCREEN_CHAR_NUM = 6000 * 5;

string SecretWord;
int maxGuesses;

/*
char lettersRevealed[LENGTH_OF_ALPHABET];
char lettersInSecretWord[LENGTH_OF_ALPHABET];
string guessesMade[LENGTH_OF_ALPHABET];
int numLettersRevealed;
int numGuessesMade;
int numLettersInWord; //distinct letters
*/
//bool bLetersRevealed[LENGTH_OF_ALPHABET];
bool bLettersInSecretWord[LENGTH_OF_ALPHABET];
bool bGuessesMade[LENGTH_OF_ALPHABET];
int numGuessesMade;

inline int at(char inCh){ return inCh -'a'; }

int main () {

   do { //restart game
      InitializeVars();

      ClearScreen();

      do { // make guesses
         char guessLetter = PlayerTwoGuess();


         ProcessGuess( guessLetter );

         if ( !PlayerHasWon()) {
            PrintResults();
         }

         /////debug string////////
         /*cout << numGuessesMade << " " << MAX_GUESSES
          << "  " << numLettersRevealed << "/" << numLettersInWord
          << " " << SecretWord << "  " << guessesMade[numGuessesMade-1]
          << endl;*/
         ///////debug string
      } while ( numGuessesMade < maxGuesses && !PlayerHasWon());

      if ( PlayerHasWon() ) {
         cout << YOU_WIN;
      } else {
         //todo fix this
         /*cout << MISSING <<
         (((numLettersInWord - numLettersRevealed) > 1) ?
         LETTER_PLURAL :
                                                          LETTER);
         for ( int i = 0 ; i < numLettersInWord ; i++ ) {
            if ( !swansonUtil::Contains( lettersInSecretWord[i] ,
                  lettersRevealed , numLettersRevealed ) )
               cout << lettersInSecretWord[i] << " ";
         }*/

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

   numGuessesMade = 0;

   //todo fill arrays with false

   for ( int i = 0 ; i < SecretWord.size() ; i++ ) { //set lettersInSecretWord[]
      bLettersInSecretWord[at(SecretWord.at(i))] = true;
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

   system( "clear && printf '\e[3J'" );
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
char PlayerTwoGuess () {
   char guessLetter;
   bool retry;

   int guessesRemaining = maxGuesses - numGuessesMade;

   //TODO move to display
   cout << GUESS_INSTR_STR;
   cout << endl << ((guessesRemaining > 1) ? NUM_GUESSES : NUM_GUESSES_SINGULAR)
         << guessesRemaining;

   guessLetter = swansonInput::GetString(GUESS_PROMPT).at(0);

   /*do {
      retry = false;
      do {
         if ( retry )
            cout << ENTERED_BEFORE;
         //guessString = swansonInput::GetOneWord( GUESS_PROMPT );
         guessCh = swansonString::LowerCase( string(guessCh) );
         retry = true;
      } while (bGuessesMade[at(guessCH)] );
   } while ( guessString.size() > 1
         && !swansonInput::yesNo( GUESS_CHECK + guessString + "\n" ) );*/


   /*cout << "what is your guess:";
   guessLetter = getchar();*/
   //guessLetter = swansonString::LowerCase( guessLetter + "").at(0);

   return guessLetter;

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
void ProcessGuess ( char guessLetter ) {

   bGuessesMade[at(guessLetter)] = true;
   if ( !bLettersInSecretWord[at(guessLetter)] ) {
      numGuessesMade++;
   }



}

/**************************************************************
 *
 * Entry: none
 *
 *
 * Exit: true if all letters in secret word are guessed
 *
 *
 * Purpose: determine if the game has ended by guessing all letters
 *
 *
 * ***************************************************************/
bool PlayerHasWon(){
   bool hasWon = true;
   for ( int i = 0 ; i < SecretWord.size() ; i++ ) {
      char letter = SecretWord.at(i);
      if (!bGuessesMade[at(letter)] ) hasWon = false;
   }
   return hasWon;
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
      if ( bGuessesMade[at(cursorChar)]) {
         cout << cursorChar;
      } else
         cout << "-";
   }
}
