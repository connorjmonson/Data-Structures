/* 
*  Connor Monson cmonson@ucsc.edu 1461818
*  this is lab5 essencially doing pa3 in c
*  fall 2016
*  DictionaryTest.c 
*  Tests Dictionary.h using Hash Tables
*/

#include<stdio.h> //include everything
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h" //test Dictionary.h using Hash Tables
#define MAX_LEN 180 //set max length

int main(int argc, char* argv[]) {
   Dictionary T = newDictionary(); //initilize
   char* c;
   char* m;
   char* R[] = {"one","two","three","four","five","six","seven"}; //char arrays
   char* S[] = {"a","b","c","d","e","f","g"};
   int i; //initilize for loop

   for(i=0; i<7; i++) { //loop to insert()
      insert(T, R[i], S[i]);
   }
   
   printDictionary(stdout, T);

   for(i=0; i<7; i++){
      c = R[i];
      m = lookup(T, c);
      printf("key=\"%s\" %s\"%s\"\n", c, (m==NULL?"not found ":"value="), m);
   }

   delete(T, "one");
   printDictionary(stdout, T);

   printf("%s\n", (isEmpty(T)?"true":"false"));
   printf("%d\n", size(T));
   makeEmpty(T);
   printf("%s\n", (isEmpty(T)?"true":"false"));
   freeDictionary(&T);

   return(EXIT_SUCCESS);
}