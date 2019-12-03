/* 
*  Connor Monson
*  cmonson@ucsc.edu
*  1461818
*  10/19/16
*  File Reverse.c 
*  Reads input file and prints each word backwards on a separate line
*  of the output file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stringReverse(char* s) { 
   /* actually stringReverse method call 
   *  that does the same as in java, just now in c :)
   *  void because it doesnt return
   */
   
   int a = 0; /* initializing local variable a,b, c first, like I should */
   int b = 0;
   int c = strlen(s) - 1;
   
   while(a < c) {
      b = s[a]; 
      s[a] = s[c];
      s[c] = b;
      a++; /*incriment front (A) by 1 while decreasing back (c) by one*/
      c--;
   }
}

int main(int argc, char* argv[]) {
   
   FILE* in; /* file handle for input */ 
   FILE* out; /* file handle for output */ /*ERROR */
   char word[256]; /* char array to store words from input file */

   /* check command line for correct number of arguments */

   if( argc != 3 ) {
      printf ("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   
   /* open input file for reading */
   in = fopen(argv[1], "r");
   if( in==NULL ) {
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }
   
   /* open output file for writing */
   out = fopen(argv[2], "w"); /* ERROR */
   if( out==NULL ) {
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }
   
   /* read words from input file, print on separate lines to output file */
   while(fscanf(in, " %s", word) != EOF) {
      stringReverse(word);
      fprintf(out, "%s\n", word);
   }

   /* close input and output files */
   fclose(in);
   fclose(out);
   
   return(EXIT_SUCCESS);
}
