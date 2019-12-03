// Connor Monson cmonson@ucsc.edu 1461818
// this is pa3 
// fall 2016
// DictionaryTest.java

public class DictionaryTest {

   public static void main(String[] args) {
     //testing shtuff
      Dictionary D = new Dictionary();
         System.out.println(D.isEmpty());
         D.insert("1","f");
         System.out.println(D.isEmpty());
         D.insert("5","h");
         System.out.println(D.size());
         D.insert("3","a");
         System.out.println("*********");
         System.out.println(D.size());
         System.out.println("*********");
      
         D.insert("8","c");
         D.insert("2","e");
         D.insert("9","3");
      
         System.out.println(D);
         System.out.println(D.size());
         D.delete("3");
         System.out.println(D.size());
         System.out.println(D);
         System.out.println(D.lookup("5"));
      
         //throws DuplicateKeyException ???
         //throws KeyNotFoundException ???
         //why does it? 
         D.makeEmpty();
         System.out.println(D.size() + " " + D.isEmpty());
   }
}