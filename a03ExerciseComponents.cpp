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
#include <cmath>
#include "myFunctions.hpp"
#include "menu.hpp"
#include "ExerciseComponentStrings.hpp"

using namespace std;

void RandomByRefrence (); //problem 1
void CompareStrings (); //problem 2
void SortThreeNumbers (); //problem 3
void ShowFib (); //problem 4
void BowlingPins (); //problem 5
void ShowInterest (); //problem 6

int main ( int argc , char* argv[] ) {

   swansonUtil::SeedRandom();

   Menu myMenu( MENU_TITLE );
   myMenu.addItem( RandomByRefrence , RNDM_TITLE , RNDM_INTRO , RNDM_RPT );
   myMenu.addItem( CompareStrings , STR_TITLE , STR_INTRO , STR_RPT );
   myMenu.addItem( SortThreeNumbers , SRT_TITLE , SRT_INTRO , SRT_RPT );
   myMenu.addItem( ShowFib , FIB_TITLE , FIB_INTRO , FIB_RPT );
   myMenu.addItem( BowlingPins , PIN_TITLE , PIN_INTRO , PIN_RPT );
   myMenu.addItem( ShowInterest , INT_TITLE , INT_INTRO , INT_RPT );

   myMenu.runFromCommandLine( argc , argv );

   cout << MAIN_INTRO;

   myMenu.showMenu();

   return 0;
}

////////////////////////////////////////
//////problem 6/////////////////////////
////////////////////////////////////////

float GetInterst ( float principal , float interest , int years ) {
   if ( years > 0 ) {
      return GetInterst( principal , interest , --years ) * (1 + interest);
   } else {
      return principal;
   }
}

void ShowInterest () {
   float recursiveBalance, formulaBalance;
   float principal = swansonInput::GetFloat( "What is the initial amount:" ,
         1 );
   float interestRate = swansonInput::GetFloat(
         "What is the interest rate (as a percentage):" , 0 ) / 100;
   int years = swansonInput::GetInt(
         "How many years will it collect interest:" , 1 );

   recursiveBalance = GetInterst( principal , interestRate , years ) + 1;

   formulaBalance = principal * pow( (1 + interestRate) , years );

   cout << "the recursively calculated amount is:" << recursiveBalance << endl;

   if(swansonUtil::IsEqual(recursiveBalance,formulaBalance)){
      cout << "this is the same as the formula calculation balance of:"
            << formulaBalance;
   }else{
      cout << "this is different from the formula calculation balance of:"
            << formulaBalance;
   }

}

////////////////////////////////////////
//////problem 5/////////////////////////
////////////////////////////////////////
int HowManyBowlingPins ( int row ) {
   if ( row == 1 )
      return 1;
   else {
      return row + HowManyBowlingPins( row - 1 );
   }
}

void BowlingPins () {
   int numRows = swansonInput::GetInt( "how many rows of bowling pins:" , 1 );
   int numPins = HowManyBowlingPins( numRows );
   cout << "there would be " << numPins << ((numPins > 1) ? " pins" : "pin");
}

////////////////////////////////////////
//////problem 4/////////////////////////
////////////////////////////////////////
unsigned long int GetFibonacci ( int n ) {
   if ( n == 0 || n == 1 )
      return 1;
   else {
      return GetFibonacci( n - 1 ) + GetFibonacci( n - 2 );
   }
}

void ShowFib () {

   int place = swansonInput::GetInt(
         "What number in the sequence do you want to know:" , 0 , 40 );
   cout << "That number is:" << GetFibonacci( place );

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
      numbers[index] = swansonInput::GetInt(
            "what is the " + numericalPrompts[index] + " number:" );
   }

   //sort them
   SortNumbers( numbers[0] , numbers[1] , numbers[2] );

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
