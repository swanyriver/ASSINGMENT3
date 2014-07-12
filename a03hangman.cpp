/***********************************************************
 * Author: Brandon Swanson
 * Date Created: 06-30-2014
 * Last Modification Date: 07-11-2014
 * Filename: hangman.cpp
 *
 * Overview: A word guessing game version 2
 *
 * Input: A secret word, letter guesses
 *
 * Output: correctly guessed letters
 *
 ***********************************************************/

#include "myFunctions.hpp"
#include "hangmanStrings.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>

using namespace std;

struct Guess {
   bool succesful;
   string errorMsg;
   char guessLetter;
   bool correct;
   int occurences;
};

//reset variables for each game
void InitializeVars ();

//get a word from player one
string PlayerOnePickWord ();

//get a guess letter or word from player two
Guess PlayerTwoGuess ();

//analyze guess made
void ProcessGuess ( Guess &nextGuess );

//output correct letters to player
void Display ();
void Display ( string message , bool gameLost = false );

//check if word has been guessed
bool PlayerHasWon ();

//refresh terminal screen
void (*ClearScreen) ();
//somewhat obscure secret word input
void HackClearScreen();

//map alpha character onto array from 0-25
inline int at ( char inCh ) {
   return inCh - 'a';
}

const int MAX_WORD_LENGTH = 12;
const int LENGTH_OF_ALPHABET = 26;
const string SIMPLE = "-s";

string SecretWord;
int maxGuesses;
bool LettersInSecretWord[LENGTH_OF_ALPHABET];
bool GuessesMade[LENGTH_OF_ALPHABET];
int numGuessesMade;

int main (int argc , char* argv[]) {

   //check for simple mode
   bool simple = false;
   for(int i=0;i<argc;i++){
      if(strcmp(SIMPLE.c_str(),argv[i])==0) simple = true;
   }
   if(simple) ClearScreen = HackClearScreen; //run simple
   else ClearScreen=swansonUtil::ClearScreen; //call system clear
   ///finished with command line arguments////////////////////////

   string message;
   Guess nextGuess;

   //todo   make an intro

   do { //restart game
      ClearScreen();
      InitializeVars();
      message = "";

      do { // make guesses

         do {
            Display( message );
            nextGuess = PlayerTwoGuess();
            message = nextGuess.errorMsg;

         } while ( !nextGuess.succesful );


         ProcessGuess( nextGuess );

         if ( !PlayerHasWon() ) {
            if ( nextGuess.correct ){
               message = GOOD_JOB;
               if(nextGuess.occurences>1){ //display how many occurrences
                  ostringstream numToString;
                  numToString << nextGuess.occurences; //convert int to string
                  message+= " " + numToString.str() + " times";
               }
            }
            else
               message = STILL_WRONG;
         }

      } while ( numGuessesMade < maxGuesses && !PlayerHasWon() );

      if ( PlayerHasWon() ) {
         Display( YOU_WIN );
      } else {

         Display( YOU_LOSE , true );
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

   //fill arrays with false  for repeat games
   for ( int index = 0 ; index < LENGTH_OF_ALPHABET ; ++index ) {
      LettersInSecretWord[index] = false;
      GuessesMade[index] = false;
   }

   for ( int i = 0 ; i < SecretWord.size() ; i++ ) { //set lettersInSecretWord[]
      LettersInSecretWord[at( SecretWord.at( i ) )] = true;
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
/*void ClearScreen () {
   char randChar;
    for ( int i = 0 ; i < CLEAR_SCREEN_CHAR_NUM ; i++ ) {
    randChar = swansonUtil::GetRandomInRange( 'A' , 'Z' );
    cout << randChar;
    }

    cout << endl << endl;

   //system( "clear && printf '\e[3J'" );

}*/

/**************************************************************
 *
 * Entry: none
 *
 * Exit: a string of all letters no spaces
 *
 * Purpose: to get a guess from player 2
 *
 * ***************************************************************/
Guess PlayerTwoGuess () {

   Guess playerTwoGuess;
   playerTwoGuess.succesful = false;

   char guessLetter;
   string guessInputString;

   guessInputString = swansonInput::GetString( GUESS_PROMPT );

   //check that it is a string
   if ( guessInputString.empty() ) {
      playerTwoGuess.errorMsg = NO_STR;
      return playerTwoGuess;
   }
   //check if more than one char
   if ( guessInputString.length() > 1 ) {
      playerTwoGuess.errorMsg = LONG_STR;
      return playerTwoGuess;
   }
   guessLetter = guessInputString.at( 0 );
   //check if a letter
   if ( !swansonString::IsALetter( guessLetter ) ) {
      playerTwoGuess.errorMsg = NOT_ALPHA;
      return playerTwoGuess;
   }
   //check if a already been guessed
   if ( GuessesMade[at( guessLetter )] ) {
      playerTwoGuess.errorMsg = ENTERED_BEFORE;
      return playerTwoGuess;
   }

   //else, no errors, return guess
   playerTwoGuess.succesful = true;
   playerTwoGuess.guessLetter = guessLetter;
   return playerTwoGuess;

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
void ProcessGuess ( Guess &nextGuess ) {

   //add guess to guesses made
   GuessesMade[at( nextGuess.guessLetter )] = true;

   //check if correct and count
   if ( !LettersInSecretWord[at( nextGuess.guessLetter )] ) {
      numGuessesMade++;
      nextGuess.correct = false;
   } else{
      nextGuess.correct = true;
      nextGuess.occurences=0;
      for (int pos = 0; pos < SecretWord.length(); pos++) {
         if(SecretWord.at(pos) == nextGuess.guessLetter)
            nextGuess.occurences++;
      }
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
bool PlayerHasWon () {
   bool hasWon = true;
   for ( int i = 0 ; i < SecretWord.size() ; i++ ) {
      char letter = SecretWord.at( i );
      if ( !GuessesMade[at( letter )] )
         hasWon = false;
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
void Display () {
   Display( "" );
}
void Display ( string message , bool gameLost ) {

   const int WIDTH_DISPLAY = 75;

   string secretWordLine, lettersLine, guessesLine, guessRemainingLine;
   string lettersRemainingLine, wordRevealLine;
   string messageLine;

   //build secret word string
   secretWordLine = SECRET_WORD_LABEL;
   for ( int index = 0 ; index < SecretWord.length() ; index++ ) {
      char letter = SecretWord.at( index );
      if ( GuessesMade[at( letter )] ) {
         secretWordLine.push_back( letter );
         secretWordLine += " ";
      } else
         secretWordLine += "- ";
   }
   secretWordLine.append( WIDTH_DISPLAY - secretWordLine.length() - 1 , ' ' );
   secretWordLine += "*";

   //build letters available & guesses made string
   lettersLine = LETTERS_LABEL;
   guessesLine = GUESS_MADE_LABEL;
   for ( char currentChar = 'a' ; currentChar <= 'z' ; currentChar++ ) {
      //for each letter place a letter or empty space, acording to guesses
      if ( GuessesMade[at( currentChar )] ) {
         guessesLine.push_back( currentChar );
         guessesLine += " ";
         lettersLine += "  ";
      } else {
         lettersLine.push_back( currentChar );
         lettersLine += " ";
         guessesLine += "  ";
      }
   }
   guessesLine += "*";
   lettersLine += "*";

   //build guesses remaining string
   guessRemainingLine = GUESS_REMAINING_LABEL;
   int guessesRemaining = maxGuesses - numGuessesMade;
   for ( int i = 0 ; i < guessesRemaining ; i++ ) {
      guessRemainingLine += "? ";
   }
   guessRemainingLine.append
   ( WIDTH_DISPLAY - guessRemainingLine.length() - 1 , ' ' );
   guessRemainingLine += "*";

   //build message line
   messageLine = LINE_SEPERATE;
   if ( !message.empty() ) {
      message = "  " + message + "  ";
      int pos = WIDTH_DISPLAY / 2.0 - message.length() / 2.0;
      messageLine.replace( pos , message.size() , message );
   }

   ///special end of game display
   if ( gameLost ) {
      //build letters remaining line
      lettersRemainingLine = LETTERS_UNREAVEALED_LABEL;
      for ( int index = 0 ; index < SecretWord.length() ; index++ ) {
         char letter = SecretWord.at( index );
         if ( !GuessesMade[at( letter )] ) {
            lettersRemainingLine.push_back( letter );
            lettersRemainingLine += " ";
         } else
            lettersRemainingLine += "- ";
      }
      lettersRemainingLine.append
      ( WIDTH_DISPLAY - lettersRemainingLine.length() - 1 ,' ' );
      lettersRemainingLine += "*";


      //build secret word reveal line
      wordRevealLine = REVEAL_WORD_LABEL;
      wordRevealLine += SecretWord;
      wordRevealLine.append
      ( WIDTH_DISPLAY - wordRevealLine.length() - 1 ,' ' );
      wordRevealLine += "*";

      //swap lines for output
      lettersLine = lettersRemainingLine;
      guessRemainingLine = wordRevealLine;

   }

   //output display
   ClearScreen();
   cout << LINE_SEPERATE << endl;
   cout << LINE_SEPERATE << endl;
   cout << secretWordLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << lettersLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << guessesLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << guessRemainingLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << messageLine << endl;
   cout << LINE_SEPERATE << endl;


}

void HackClearScreen(){
   string clearScrn ="";
   clearScrn.append(100,'\n');
   std::cout << clearScrn;
}
