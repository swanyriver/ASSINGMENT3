#ifndef HANGMANSTRINGS_H_
#define HANGMANSTRINGS_H_

#include <string>
using std::string;

#define GOODBYE_STR "Thank you for playing"
#define PLAY_AGAIN_STR 	"would you like to play again"
#define ENTER_WORD_STR 	"Tell me what the secret word will be:"
#define MAX_GUESSES_STR 	"How many guesses do you want the other player to have:"
//#define GUESS_INSTR_STR "\nEnter a letter to guess at the letters contained in the secret word \nOr enter a word if you think you know the answer"
//#define NUM_GUESSES "guesses remaining:"
//#define NUM_GUESSES_SINGULAR "guess remaining:"
#define GUESS_PROMPT "Enter Your Guess:"
#define ENTERED_BEFORE "You have entered this guess already"
#define NO_STR "something went wrong"
#define LONG_STR "Please keep it to one letter at a time"
#define NOT_ALPHA "That was not a letter"
//#define GUESS_CHECK "Do you want to guess that the word is: "
#define STILL_WRONG "No thats not it, keep trying"
#define STRING_HINT "Here is what we have discovered about the word so far:"
#define TOO_LONG "The secret word cannot be that long"
#define YOU_WIN "\nCONGRADULATIONS YOU WIN!!!!"
#define YOU_LOSE "\nYou ran out of guesses without guessing the Secret Word\nBetter luck next time"
//#define MISSING "\nYou were missing "
//#define LETTER "this letter: "
//#define LETTER_PLURAL "these letters: "
#define WORD_REVEAL "\nFrom the Secret Word: "

//special display

#define LINE_SEPERATE "***************************************************************************"
#define SECRET_WORD_LABEL "*    SECRET WORD    * "
#define GUESS_MADE_LABEL "*   GUESSES MADE    * "
#define LETTERS_LABEL "* LETTERS AVAILABLE * "
#define GUESS_REMAINING_LABEL "* GUESSES REMAINING * "

#endif /* HANGMANSTRINGS_H_ */

/*
****|****|****|****|****|****|****|****|****|****|****|****|****|****|****| 75 WIDE
***************************************************************************
***************************************************************************
*    SECRET WORD    * - - - - - - - - - - - - - - -                       *
***************************************************************************
* LETTERS AVAILABLE * A B C D E F G H I J K L M N O P Q R S T U V W X Y Z *
***************************************************************************
*   GUESSES MADE    *                                                     *
***************************************************************************
* GUESSES REMAINING * ? ? ? ? ?                                           *
***************************************************************************
****         msg here                           ***************************
***************************************************************************
***************************************************************************
What is your guess:
 */
