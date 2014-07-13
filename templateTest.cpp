#include <iostream>
#include <string>
#include "myFunctions.hpp"

using namespace std;


template <typename Type>
void show(Type element, Type set[], int numElements){
   cout << endl << "in the set:";
   for(int i=0; i<numElements; i++){
      cout << set[i] << ",";
      //swansonUtil::InsertElement(set[i],sorted,numElements);
   }
   cout << "the element " << element
       << ((swansonUtil::Contains(element,set,numElements))? " exists" : " does not exist");



}


int main(){
   int ints[] = {1,2,4,66,77,88,4}; //7
   float floats[] = {1.0,2,4.5,6.678,77.66,88.5,4.8}; // 7
   double doubles[] = {1.0,2,4.5,6.678,77.66,88.5,4.8}; // 7
   char chars[] = {'s','d','d','g','f'}; // 5
   string strings[] = {"hello", "goodbye", "love", "hate" }; // 4

   double testD = 6.678;
   int sorted[7];
   float sortedf[7];
   double sortedd[7];
   char sortedc[5];

   show('h', chars, 5);
   for(int i=0;i<5;i++) swansonUtil::InsertElement(chars[i],sortedc,i);
   cout << endl << "sorted this array is: ";
   for(int i=0; i<5; i++) cout << sortedc[i] << ",";
   cout << endl;
   //show('d', chars, 5,sortedc);
   show(ints[0],ints,7);
   for(int i=0;i<7;i++) swansonUtil::InsertElement(ints[i],sorted,i);
   cout << endl << "sorted this array is: ";
   for(int i=0; i<7; i++) cout << sorted[i] << ",";
   cout << endl;


   show(floats[0], floats, 7);
   for(int i=0;i<7;i++) swansonUtil::InsertElement(floats[i],sortedf,i);
   cout << endl << "sorted this array is: ";
   for(int i=0; i<7; i++) cout << sortedf[i] << ",";
   cout << endl;


   show(testD, doubles, 7);
   for(int i=0;i<7;i++) swansonUtil::InsertElement(doubles[i],sortedd,i);
   cout << endl << "sorted this array is: ";
   for(int i=0; i<7; i++) cout << sortedd[i] << ",";
   cout << endl;

   //show(strings[3], strings, 4);

}
