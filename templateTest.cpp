#include <iostream>
#include <string>
#include "myFunctions.hpp"

using namespace std;


template <typename Type>
void show(Type element, Type set[], int numElements){
   cout << endl << "in the set:";
   Type sorted[numElements];
   for(int i=0; i<numElements; i++){
      cout << set[i] << ",";
      swansonUtil::InsertElement(set[i],sorted,numElements);
   }
   cout << "the element " << element
       << ((swansonUtil::Contains(element,set,numElements))? " exists" : " does not exist");

   cout << endl << "sorted this array is: ";
   for(int i=0; i<numElements; i++) cout << sorted[i] << ",";
   cout << endl;

}


int main(){
   int ints[] = {1,2,4,66,77,88,4}; //7
   float floats[] = {1.0,2,4.5,6.678,77.66,88.5,4.8}; // 7
   double doubles[] = {1.0,2,4.5,6.678,77.66,88.5,4.8}; // 7
   char chars[] = {'s','d','d','g','f'}; // 5
   string strings[] = {"hello", "goodbye", "love", "hate" }; // 4

   double testD = 6.678;

   show('h', chars, 5);
   show('d', chars, 5);
   show(ints[0],ints,7);
   show(floats[0], floats, 7);

   //show(testD, doubles, 7);

   //show(strings[3], strings, 4);

}
