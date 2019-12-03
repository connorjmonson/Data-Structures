// Connor Monson cmonson@ucsc.edu (:

import java.io.*;
import java.util.Scanner;
public class FileReverse{
  
  public static void main(String[] args) throws IOException{
    
    int lineNumber = 0; // check number of command line arguments is at least 2
    if(args.length < 2){ 
      System.out.println("Usage: FileCopy <input file> <output file>");
      System.exit(1); 
    } 

// open files     
    Scanner in = new Scanner(new File(args[0]));
    PrintWriter out = new PrintWriter(new FileWriter(args[1])); 
    
// read lines from in, extract and print tokens from each line 
    while( in.hasNextLine() ){ 
      lineNumber++; 

// trim leading and trailing spaces, then add one trailing space so
// split works on blank lines 
      String line = in.nextLine().trim() + " "; 
// split line around white space 
      String[] token = line.split("\\s+"); 
// print out tokens
      int n = token.length; 
       
      for(int i=0; i<n; i++){ 
        //out.println(" "+token[i]); //not used for this
        out.println(stringReverse(token[i],token[i].length())); //calling the stringReverse
        
      } 
    } 
// close files 
    in.close(); 
    out.close(); 
  } 
  
  // recursively reverses the first n characters of s
 public static String stringReverse(String s, int n){ //must return a string
   
   //same concept as reverseArray1 but with strings
//            static void reverseArray1(int[] X, int n, int[] Y){
//                //int c = -1; //use recursion for everything
//                if(n>0){
//                  Y[n-1]= X[X.length - n]; //using X[c+1] gets the X[0] but is having problems 
//                  System.out.print(X[n-1] + " "); // print nth element from left
//                  reverseArray1(X, n-1,Y);
//                } //works
//            }
   
            //utilize charAt(0 and substring() for this
  if (n>0){ 
    //substring(1) gives you the char at index 1 all the way to the end of string s 
    //charAt(0) gives you the first character in the string; I add it to the end so it reverses order putting the first
    // character in the last position
   return (stringReverse(s.substring(1), n-1) + s.charAt(0)); //has to return a string type; recursive call of stringReverse and adding the
   //the first character to the end 
  }
  return ""; //has to return a string type
 } 
}
