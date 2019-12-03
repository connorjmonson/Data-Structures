/* 
*  Connor Monson cmonson@ucsc.edu 1461818
*  this is lab4 called charType.c
*  fall 2016
*  This program classifies char's on each line of the input file into
*  alphabetic characters, numeric characters, punctuation and whitespace.
*  Then prints analysis of the inFile to the outFile.  
*/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define maxStrLength 100

void extract_chars(char* s, char* a, char* d, char* p, char* w);

int main(int argc, char* argv[]) {
   FILE* inFile;
   FILE* outFile;
   char* line; /* intializing all the char Arrays */
   char* word;
   char* number;
   char* punctuation;
   char* wspace;
   int lineNum = 1;
   
   if (argc != 3) {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   /* if input file is null, error */
   inFile = fopen(argv[1], "r");
   if (inFile == NULL) {
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   /* if output file is null, error */
   outFile = fopen(argv[2], "w");
   if (outFile == NULL) {
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   /* char arrays are allocated heap memory here */
   line			= calloc(maxStrLength + 1, sizeof(char));
   word			= calloc(maxStrLength + 1, sizeof(char));
   number		= calloc(maxStrLength + 1, sizeof(char));
   punctuation	= calloc(maxStrLength + 1, sizeof(char));
   wspace		= calloc(maxStrLength + 1, sizeof(char));
   
   assert (line != NULL && word != NULL && number != NULL && punctuation != NULL && wspace != NULL);
   
   /* reads input file and prints array in its character type */
   while (fgets(line, maxStrLength, inFile) != NULL) {
      extract_chars(line, word, number, punctuation, wspace); //sorts the character into arrays of its type
      fprintf(outFile, "line %d contains: \n", lineNum); 
      
      //word(s)
      if (strlen(word) > 1) {
         fprintf(outFile, "%d alphabetic characters: %s\n", (int)strlen(word), word);
      } 
      else {
         fprintf(outFile, "%d alphabetic characters: %s\n", (int)strlen(word), word);
      }
      
      //number(s)
      if (strlen(number) > 1) {
         fprintf(outFile, "%d numeric characters: %s\n", (int)strlen(number), number);
      } 
      else {
         fprintf(outFile, "%d numeric characters: %s\n", (int)strlen(number), number);
      }
      
      //punctuation(s)
      if (strlen(punctuation) > 1) {
         fprintf(outFile, "%d punctuation characters: %s\n", (int)strlen(punctuation), punctuation);
      } 
      else {
         fprintf(outFile, "%d punctuation characters: %s\n", (int)strlen(punctuation), punctuation);
      }
      
      //whitespace(s)
      if (strlen(wspace) > 1) {
         fprintf(outFile, "%d whitespace characters: %s\n", (int)strlen(wspace), wspace);
      } 
      else {
         fprintf(outFile, "%d whitespace characters: %s\n", (int)strlen(wspace), wspace);
      }
      
      lineNum++;  //increment line number
   }

   /* free allocated heap memory */
   free(line);
   free(word);
   free(number);
   free(punctuation);
   free(wspace);

   /* close the files */
   fclose(inFile);
   fclose(outFile);

   return EXIT_SUCCESS;

}

void extract_chars(char* s, char* a, char* d, char* p, char* w) {
   		
   int i=0, al=0, num=0, punc=0, wh=0; //initialize local vars
   while (s[i] != '\0' && i<maxStrLength) { //continue while not null and not max. length
   /* this just complicated things 
   	  if (isupper(int)s[i]){

   	  }	
   	  if (islower(int)s[i]){

   	  }	
   	*/
      if (isalpha((int)s[i])) { //alphabetical characters
	     a[al] = s[i];
		 al++;
	  } else if (isdigit((int)s[i])) { //number
		 d[num] = s[i];
         num++;
	  } else if (ispunct((int)s[i])) { //punctuation
	     p[punc] = s[i];
	     punc++;
	  } else { //white space
	     w[wh] = s[i];
	     wh++;
	  }
	  i++;
   }

   a[al] = '\0';
   d[num] = '\0';		//end of array has null character
   p[punc] = '\0';
   w[wh] = '\0';
   
}
