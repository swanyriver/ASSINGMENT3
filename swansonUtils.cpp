/***********************************************************
 * Author: Brandon Swanson
 * Date Created: 06-29-2014
 * Last Modification Date: 07-03-2014
 * Filename: swansonUtils.cpp
 *
 * Overview: A collections of array and random number utility functions
 ***********************************************************/

#include "myFunctions.hpp"
#include <cstdlib>
#include <ctime>

/******************************************************************************
 *    purpose: determins if the array values of size range contains the item var
 *             for types: bool, int, long, double, float, char, string
 *
 *    entry: an array of size range
 *
 *    exit: true if the array values[] has at least one instance of var
******************************************************************************/
bool swansonUtil::Contains ( long int var , long int values[] , int range ) {
   for ( int i = 0 ; i < range ; i++ ) {
      if ( values[i] == var )
         return true;
   }
   return false;
}
bool swansonUtil::Contains ( int var , int values[] , int range ) {
   for ( int i = 0 ; i < range ; i++ ) {
      if ( values[i] == var )
         return true;
   }
   return false;
}
bool swansonUtil::Contains ( double var , double values[] , int range ) {
   for ( int i = 0 ; i < range ; i++ ) {
      if ( values[i] == var )
         return true;
   }
   return false;
}
bool swansonUtil::Contains ( float var , float values[] , int range ) {
   for ( int i = 0 ; i < range ; i++ ) {
      if ( values[i] == var )
         return true;
   }
   return false;
}

bool swansonUtil::Contains ( bool var , bool values[] , int range ) {
   for ( int i = 0 ; i < range ; i++ ) {
      if ( values[i] == var )
         return true;
   }
   return false;
}

bool swansonUtil::Contains ( string var , string values[] , int range ) {
   for ( int i = 0 ; i < range ; i++ ) {
      if ( values[i] == var )
         return true;
   }
   return false;
}

bool swansonUtil::Contains ( char var , char values[] , int range ) {
   for ( int i = 0 ; i < range ; i++ ) {
      if ( values[i] == var )
         return true;
   }
   return false;
}

/******************************************************************************
 *    purpose: seeds the random number generator creating non repeatable output
 *
 *    entry: none
 *
 *    exit: rand() is seeded with time()
******************************************************************************/
void swansonUtil::SeedRandom () {
   srand( time( NULL ) );
}

/******************************************************************************
 *    purpose:produce a random number
 *
 *    entry: none
 *
 *    exit: random int in range [0,max]
******************************************************************************/
int swansonUtil::GetRandomInRange ( int max ) {
   return GetRandomInRange( 0 , max );
}

/******************************************************************************
 *    purpose:produce a random number
 *
 *    entry: none
 *
 *    exit: random int in range [min,max]
******************************************************************************/
int swansonUtil::GetRandomInRange ( int min , int max ) {

   int random;
   int range = max - min + 1;
   if ( range == 1 )
      return min;
   random = (rand() % range) + min;
   return random;
}

/******************************************************************************
 *    purpose: to insert an element into an array preserving sorted order
 *
 *    entry: sorted array
 *
 *    exit: a sorted array with additional element val
******************************************************************************/
void swansonUtil::InsertElement ( int val , int sortArray[] , int numHolding ) {
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

/******************************************************************************
 *    purpose: produce an amount (numGeneratedValues) of numbers across a given
 *             range avoiding duplicate values
 *
 *    entry: empty array
 *
 *    exit: a sorted array of non repeated random values
******************************************************************************/
void swansonUtil::GetMappedRandomInts ( int valuesOut[] , int rangeBegining ,
      int rangeEnd , const int numGenerateValues ) {

   int nextSelection;
   list<int> selectionsList;

   //first value doesnt need special consideration
   valuesOut[0] = swansonUtil::GetRandomInRange( rangeBegining , rangeEnd );
   rangeEnd--;

   for ( int i = 1 ; i < numGenerateValues ; ++i ) {
      nextSelection = swansonUtil::GetRandomInRange( rangeBegining , rangeEnd );
      rangeEnd--;
      selectionsList.clear();
      for ( int j = 0 ; j < i ; j++ ) {
         selectionsList.push_back( valuesOut[j] );
      }
      do {
         int increment = 0;
         while ( !selectionsList.empty()
               && selectionsList.front() <= nextSelection ) {
            increment++;
            selectionsList.pop_front();
         }
         nextSelection += increment;
      } while ( !selectionsList.empty()
            && selectionsList.front() <= nextSelection );
      swansonUtil::InsertElement( nextSelection , valuesOut , i );
   }

}

