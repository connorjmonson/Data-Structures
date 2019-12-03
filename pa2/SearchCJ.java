//Connor Monson 10/12/16
// cmonson@ucsc.edu 1461818
// Search.java
// This program takes command line arguments giving target word in a target file to be searched.


import java.io.*;
import java.util.Scanner;

class Search{

   public static void main(String[] args) throws IOException {
      int f = 0; //initialize ints
      int t = 0;
      int location = 0; //initialize variables 
      int[] line; //make an int array
      String[] file1; //make a string array 

      //Prints message and exits program if less than 2 arguments are provided
      if(args.length < 2) {
         System.out.println("Usage: Search file target1 [target2 ..]");
         System.exit(1);
      }
      //Count the number of lines in a file
      Scanner in = new Scanner(new File(args[0]));

      while( in.hasNextLine() ) {
         in.nextLine();
         f++;
      }
      file1 = new String[f];
      line = new int[f];
      Scanner in1 = new Scanner(new File(args[0]));

      while( in1.hasNextLine() ) {
         file1[t] = in1.nextLine();
         line[t] = t;
         t++;
      }
      mergeSort(file1, line, 0, f-1);  //calls for the mergeSort
 // so first, read in the file, then mergeSort so that the file is in order, then do binary search to look for the possitional element in the file 
      //calls for the binarySearch 
      for(t=1; t<args.length; t++) {
         location = binarySearch(file1, 0, f-1, args[t]);
         if( !(binarySearch(file1, 0, f-1, args[t]) == -1) ) {
            location = line[location]+1;
            System.out.println(args[t]+" found on line "+ location);
         } else {
            System.out.println(args[t]+ " not found");
         }
      }
   }

   public static void mergeSort(String[] word, int[] lineNumber, int p, int r) { //use recursion on mergeSort and also use a helper function called merge
      int mid;
      if(p < r) {
         mid = (p+r)/2;
         mergeSort(word, lineNumber, p, mid); //first half 
         mergeSort(word, lineNumber, mid + 1, r); //second half 
         merge(word, lineNumber, p, mid, r); //actually doing the work 
      }
   }

   public static void merge(String[] w, int[] lN, int x, int y, int z) { //doesnt return anything; helper function for mergeSort 
     //this function allows us to pass in more variables
      int h1 = y - x + 1;
      int h2 = z - y;
      
      String[] L = new String[h1]; //initializing Array of strings 
      String[] R = new String[h2];
      
      int[] Left = new int[h1]; //initializing Array of ints 
      int[] Right = new int[h2];
     
      int c; //initilizing ints
      int j;
      int m;

      for(c=0; c<h1; c++) {
         L[c] = w[x+c];
         Left[c] = lN[x+c];
      }
      
      for(j=0; j<h2; j++) {
         R[j] = w[y+j+1];
         Right[j] = lN[y+j+1];
      }
      
      c = 0; j = 0;
      for(m=x; m<=z; m++) {
         if( c<h1 && j<h2 ) {
            if( L[c].compareTo(R[j])<0 ) {
               w[m] = L[c];
               lN[m] = Left[c];
               c++;
            } else {
               w[m] = R[j];
               lN[m] = Right[j];
               j++;
            }
         } else if( c<h1 ) {
            w[j] = L[c];
            lN[j] = Left[c];
            c++;
         } else {
            w[m] = R[j];
            lN[m] = Right[j];
            j++;
         }
      }
   }

   public static int binarySearch(String[] file, int c, int j, String target){
      int mid; // local int to keep track of the midpoint 
      if(c > j) {
         return -1;
      }
      else {
        mid = (c+j)/2;
         if(target.compareTo(file[mid])==0) {
            return mid;
         } 
         else if(target.compareTo(file[mid])<0) {
            return binarySearch(file, c, mid-1, target);
         } 
//         else if (target.compareTo(file[mid])>0){
//            return binarySearch(file, mid+1, j, target); //not quite sure why this wasnt working...
//   
//         }
         else{
            return binarySearch(file, mid + 1, j, target);
         }
      }
   }   
}