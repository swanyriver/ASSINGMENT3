/***********************************************************
 * Author: Brandon Swanson
 * Date Created: 07-08-2014
 * Last Modification Date: 07-08-2014
 * Filename: a03ExerciseComponents.cpp
 *
 * Overview: demonstrate the exercise components from week 3
 *
 * Input:
 *
 * Output:
 *
 ***********************************************************/

#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <climits>
#include "myFunctions.hpp"
#include "menu.hpp"
#include "ExerciseComponentStrings.hpp"

using namespace std;

void RandomByRefrence (); //problem 1
void CompareStrings (); //problem 2
void SortThreeNumbers (); //problem 3

int main ( int argc , char* argv[] ) {
   Menu myMenu( MENU_TITLE );
   myMenu.addItem( RandomByRefrence , RNDM_TITLE , RNDM_INTRO , RNDM_RPT );
   myMenu.addItem( CompareStrings , STR_TITLE , STR_INTRO , STR_RPT );
   myMenu.addItem( SortThreeNumbers , SRT_TITLE , SRT_INTRO , SRT_RPT );

   myMenu.runFromCommandLine( argc , argv );

   myMenu.showMenu();

   return 0;
}
////////////////////////////////////////
//////problem 3/////////////////////////
////////////////////////////////////////

void SortNumbers ( int &numberA , int &numberB , int &numberC ) {

   list<int> sortedNumbers;

   //add first number indiscriminantly
   sortedNumbers.push_back( numberA );

   //add next number to back or front
   if ( numberB < numberA )
      sortedNumbers.push_front( numberB );
   else
      sortedNumbers.push_back( numberB );

   //add next number to back, front or middle
   if ( numberC < sortedNumbers.front() )
      sortedNumbers.push_front( numberC );
   else if ( numberC > sortedNumbers.back() )
      sortedNumbers.push_back( numberC );
   else { //put numberC in middle
      int temp = sortedNumbers.back();
      sortedNumbers.pop_back();
      sortedNumbers.push_back( numberC );
      sortedNumbers.push_back( temp );
   }

   //assign values in order
   numberA = sortedNumbers.front();
   sortedNumbers.pop_front();
   numberB = sortedNumbers.front();
   sortedNumbers.pop_front();
   numberC = sortedNumbers.front();
   sortedNumbers.pop_front();
}

void SortThreeNumbers () {
   const int AMOUNT_OF_NUMBERS = 3;
   int numbers[3];
   string numericalPrompts[] = { "first", "second", "third" };

   //get the three numbers
   for ( int index = 0 ; index < AMOUNT_OF_NUMBERS ; index++ ) {
      numbers[index]=swansonInput::GetInt(
            "what is the " + numericalPrompts[index] + " number:" );
   }

   //sort them
   SortNumbers(numbers[0],numbers[1],numbers[2]);

   //output sorted numbers
   cout << "the numbers in order are:";
   for ( int index = 0 ; index < AMOUNT_OF_NUMBERS ; index++ ) {
      cout << " " << numbers[index];
   }

}

////////////////////////////////////////
//////problem 2/////////////////////////
////////////////////////////////////////

bool compare ( string &stringOne , string &stringTwo );

void CompareStrings () {
   string stringInOne, stringInTwo;

   stringInOne = swansonInput::GetString( "Give me a string:" );
   stringInTwo = swansonInput::GetString( "Ok, now give me another:" );

   if ( compare( stringInOne , stringInTwo ) ) {
      cout << endl << "these strings are the same";
   } else {
      cout << endl << "these strings are different";
   }
}

bool compare ( string &stringOne , string &stringTwo ) {
   if ( stringOne.size() != stringTwo.size() ) {
      return false;
   } else {
      for ( int i = 0 ; i < stringOne.size() ; i++ ) {
         if ( stringOne.at( i ) != stringTwo.at( i ) ) {
            return false;
         }
      }
   }
   return true;
}

////////////////////////////////////////
//////problem 1/////////////////////////
////////////////////////////////////////

/******************************************************************************
 *    purpose:produce a random number
 *
 *    entry: none
 *
 *    exit: random int in range [min,max]
 ******************************************************************************/
void rand_int ( const int &min , const int &max , int &val ) {

   int range = max - min + 1;
   if ( range == 1 )
      val = min;
   val = (rand() % range) + min;

}
void RandomByRefrence () {
   int min, max;
   int myRandom;

   cout << endl << "Tell me a range and I will give you a random number!";
   min = swansonInput::GetInt( "What is the lowest number allowed:" );
   max = swansonInput::GetInt( "What is the highest number allowed:" , min ,
   INT_MAX );

   rand_int( min , max , myRandom );

   cout << endl << "The random number generated is:" << myRandom;
}
