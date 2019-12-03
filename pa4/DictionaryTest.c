/* 
*  Connor Monson cmonson@ucsc.edu
*  pa5
*  DictionaryTest.c 
*  Tests Dictionary.h using Hash Tables
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"
#define MAX_LEN 180

int main(int argc, char* argv[]) {
   Dictionary T = newDictionary();
   char* R[] = {"one","two","three","four","five","six","seven"};
   char* S[] = {"a","b","c","d","e","f","g"};
   int i;

   for(i=0; i<7; i++) {
      insert(T, R[i], S[i]);
   }
   
   printDictionary(stdout, T);
}