/*
 * Dictionary.hpp
 *
 *  Created on: Jul 13, 2014
 *      Author: Brandon
 */

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


   Dictionary(bool dummy){
      succesfull=false;  //used to instantiate an empty dictionary
   }
   Dictionary ( int maxWordLenght = UNRESTRICTED, string filename = "dictionary.txt"){
      succesfull = InflateDict(filename,maxWordLenght);
   }




   bool IsAWord ( string word ) {
      if ( wordMap.count( word ) > 0 )
         return true;
      else
         return false;
   }

   long int NumWords () {
      return wordMap.size();
   }

   /*void TestDictionary(){
    long int size = wordMap.size();
    cout << endl << endl << size << " words" << endl;

    string test[] = {"hello","goodbye","toodaloo", "6454klj", "thank you", "japan", "frost"};

    for(int i=0; i<7; i++){
    cout << test[i] << (IsAWord(test[i])? " is a word": " isn't a word" ) << endl;

    }
    getchar();
    }*/

};



#endif /* DICTIONARY_HPP_ */
