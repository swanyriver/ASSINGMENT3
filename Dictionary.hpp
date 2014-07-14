/***********************************************************
* Author: Brandon Swanson
* Date Created: 07-13-2014
* Last Modification Date: 07-13-2014
* Filename: Dictionary.hpp
*
* Overview: Create a searchable map of words
*
* Input: a file with alpha only, lower case, return character separated words
*
* Output: a dictionary object that can be polled for number of words contained
* and if a single string element exists in the dictionary
*
***********************************************************/



#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include <iostream>  //might be extraneous
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Dictionary {
private:

   map<string, long int> wordMap;

   /**************************************************************
    *
    * * Entry: a file with only alpha, lower case, return character separated
    *          words
    *
    * * Exit: an inflated map
    *
    *
    * * Purpose:  read all words from a file,
    *             excluding ones greater than max length
    *
    * ***************************************************************/
   bool InflateDict(string filename, int MaxWordLength){
      //open dict file
      fstream instream;
      string nextWord;
      long int mapValue = 0;

      //open dictionary file
      instream.open( filename.c_str() );

      if ( instream.fail() ) {
         return false;
      }

      while ( !instream.eof() ) {
         getline( instream , nextWord ); // Retrieve next word
         if(MaxWordLength == UNRESTRICTED || nextWord.size()<=MaxWordLength){
            wordMap[nextWord] = mapValue;//add it to a map
            mapValue++;
         }
      }
      //words added  //close file
      instream.close();
      return true;

   }

public:
   bool succesfull;
   static const int UNRESTRICTED = -1;


   ///constructors
   Dictionary(bool dummy){
      succesfull=false;  //used to instantiate an empty dictionary
   }
   Dictionary ( int maxWordLenght = UNRESTRICTED, string filename = "dictionary.txt"){
      succesfull = InflateDict(filename,maxWordLenght);
   }

   /**************************************************************
    *
    * * Entry:an inflated map
    *
    *
    * * Exit:true if map contains 1 or more of element, false otherwise
    *
    *
    * * Purpose: determine if passed in word is a word in dictionary
    *
    *
    * ***************************************************************/
   bool IsAWord ( string word ) {
      if ( wordMap.count( word ) > 0 )
         return true;
      else
         return false;
   }

   //returns number of words
   long int NumWords () {
      return wordMap.size();
   }

};



#endif /* DICTIONARY_HPP_ */
