#ifndef MYFUNCTIONS_H_
#define MYFUNCTIONS_H_

#include <list>
#include <string>
#include <climits>
#include <cfloat>

using namespace std;

/******************************************************************************
 * SWANSON STRING
 * static bool IsALetter ( char character );
 *
 *    purpose: determines if a char is a letter
 *
 *    entry: none
 *
 *    exit: true if char is [a-z] or [A-Z]
 *
 * static bool IsANumber ( char character );
 *
 *    purpose: determines if a char is a number
 *
 *    entry: none
 *
 *    exit: true if char is [0-9]
 *
 * static bool AllNumbers ( string numberString );
 *
 *    purpose: determines if a string represents a whole number, using IsANumber
 *
 *    entry: none
 *
 *    exit: true if all chars in string are [0-9]
 *
 * static bool AllNumbersFloat ( string numberString );
 *
 *    purpose: determines if a string represents a float point number
 *
 *    entry: non void string
 *
 *    exit: true if all chars are numeric and contains 0 or 1 '.'
 *
 * static bool AllLetters ( string letterString );
 *
 *    purpose: determines if a string is comprised of only letters
 *             using IsALetter
 *
 *    entry: non void string
 *
 *    exit: true if all chars are [a-z] or [A-Z]
 *
 * static bool AllLetters ( string letterString , char permitedChars[] ,
 *        int arraySize );
 *
 *    purpose: determines if a string is comprised of only letters and the
 *             characters in permitedChars
 *
 *    entry: non void string
 *
 *    exit: true if the string is alpha chars or the permitedChars
 *
 * static void SeperateWords ( string myString , list<string>& seperateWords );
 *
 *    purpose: create a list of individual words using anything other than
 *             alpha as a separation token
 *
 *    entry: non void string, empty list seperateWords
 *
 *    exit: seperateWords will contain strings of only alpha characters
 *
 * static string LowerCase ( string caseString );
 *
 *    purpose: convert all letters in string to lower case
 *
 *    entry: non void string
 *
 *    exit: string with any alpha chars between [a-z]
 *
 * static string UpperCase ( string caseString );
 *
 *    purpose: convert all letters in string to upper case
 *
 *    entry: non void string
 *
 *    exit: string with any alpha chars between [A-Z]
 *****************************************************************************/

class swansonString {
public:

   static bool IsALetter ( char character );
   static bool IsANumber ( char character );
   static bool AllNumbers ( string numberString );
   static bool AllNumbersFloat ( string numberString );
   static bool AllLetters ( string letterString );
   static bool AllLetters ( string letterString , char permitedChars[] ,
         int arraySize );

   static void SeperateWords ( string myString , list<string>& seperateWords );
   static string LowerCase ( string caseString );
   static string UpperCase ( string caseString );
};

/******************************************************************************
 * SWANSON INPUT
 *
 * static string GetString ( string prompt );
 *
 *    purpose: receive a string including spaces from the user
 *
 *    entry: a string to be used to clarify desired input to user
 *
 *    exit: a string of user input
 *
 * static string GetOneWord ( string prompt );
 *
 *    purpose: receive a string excluding spaces from the user
 *
 *    entry: a string to be used to clarify desired input to user
 *
 *    exit: a string of user input including no spaces
 *
 * static int/long/double/float Get* ( string prompt );
 *
 *    purpose: receive a value from the user, screen for alpha input
 *             and overflow
 *
 *    entry: a string to be used to clarify desired input to user
 *
 *    exit: a value between TYPE_MIN and TYPE_MAX
 *
 * static int/long/double/float ( string prompt , int rangeMin , int rangeMax );
 *
 *    purpose: receive a value from the user, screen for alpha input
 *             and overflow, restrict input to specific range
 *
 *    entry: a string to be used to clarify desired input to user
 *
 *    exit: a value between rangeMin and rangeMax
 *
 * static bool yesNo ( string prompt );
 *
 *    purpose: get an affirmative or negative answer from the user
 *
 *    entry: a string to be used to clarify desired input to user
 *
 *    exit: true if entered 'y' or 'yes' in upper or lower case
 *          flase if entered 'n' or 'no' in upper or lower case
 *
 ******************************************************************************/

class swansonInput {
public:
   static string GetString ( string prompt );
   static string GetOneWord ( string prompt );

   static int GetInt ( string prompt );
   static int GetInt ( string prompt , int rangeMin , int rangeMax = INT_MAX );
   static long int GetLong ( string prompt );
   static long int GetLong ( string prompt , long int rangeMin ,
         long int rangeMax = LONG_MAX );

   static float GetFloat ( string prompt );
   static float GetFloat ( string prompt , float rangeMin , float rangeMax =
   FLT_MAX );
   static double GetDouble ( string prompt );
   static double GetDouble ( string prompt , double rangeMin , double rangeMax =
   DBL_MAX );

   static bool yesNo ( string prompt );
};

/******************************************************************************
 * SWANSON UTIL
 * static bool Contains ( var , values[] , range );
 *
 *    purpose: determins if the array values of size range contains the item var
 *             for types: bool, int, long, double, float, char, string
 *
 *    entry: an array of size range
 *
 *    exit: true if the array values[] has at least one instance of var
 *
 * static void SeedRandom ();
 *
 *    purpose: seeds the random number generator creating non repeatable output
 *
 *    entry: none
 *
 *    exit: rand() is seeded with time()
 *
 * static int GetRandomInRange ( int max );
 *
 *    purpose:produce a random number
 *
 *    entry: none
 *
 *    exit: random int in range [0,max]
 *
 * static int GetRandomInRange ( int min , int max );
 *
 *    purpose:produce a random number
 *
 *    entry: none
 *
 *    exit: random int in range [min,max]
 *
 * static void InsertElement ( int val , int sortArray[] , int numHolding );
 *
 *    purpose: to insert an element into an array preserving sorted order
 *
 *    entry: sorted array
 *
 *    exit: a sorted array with additional element val
 *
 * static void GetMappedRandomInts ( int valuesOut[] , int rangeBegining ,
 *    int rangeEnd , const int numGenerateValues );
 *
 *    purpose: produce an amount (numGeneratedValues) of numbers across a given
 *             range avoiding duplicate values
 *
 *    entry: empty array
 *
 *    exit: a sorted array of non repeated random values
 *
 * static bool IsEqual(float/double value1, float/double value2);
 *    Entry:2 float/double values
 *
 *    Exit: true if two values are within defined epsilon of each other, false
 *          otherwise
 *
 *    Purpose: to compare the "equality" of imperiously stored floating point
 *             numbers
 *
 * static void ClearScreen();
 *    Entry: running on unix based system
 *
 *    Exit: A cleared screen
 *
 *    Purpose: Clear screen for a refresh
 *
 ******************************************************************************/

class swansonUtil {
public:

   static void SeedRandom ();
   static int GetRandomInRange ( int max );
   static int GetRandomInRange ( int min , int max );
   static void GetMappedRandomInts ( int valuesOut[] , int rangeBegining ,
         int rangeEnd , const int numGenerateValues );
   static bool IsEqual ( float value1 , float value2 );
   static bool IsEqual ( double value1 , double value2 );
   static void ClearScreen ();

   //contains template method must be declared in class
   template<typename Type>
   static bool Contains ( Type var , Type values[] , int range ) {
      for ( int i = 0 ; i < range ; i++ ) {
         if ( values[i] == var )
            return true;
      }
      return false;
   }
   static bool Contains ( float var , float values[] , int range );
   static bool Contains ( double var , double values[] , int range );

   //insert template method must be declared in class
   //to-do, why not doubles and chars
   template<typename TypeIns>
   static void InsertElement ( TypeIns val , TypeIns sortArray[] ,
         int numHolding ) {
      int i = 0;
      for ( ; i < numHolding ; i++ ) {
         if ( val < sortArray[i] ) {
            for ( int j = numHolding ; j > i ; j-- ) {
               sortArray[j] = sortArray[j - 1];
            }
            break;
         }
      }
      sortArray[i] = val;
   }

};

#endif /* MYFUNCTIONS_H_ */
