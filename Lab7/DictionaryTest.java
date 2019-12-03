// Connor Monson cmonson@ucsc.edu
// lab7 
// DictionaryTest.java

public class DictionaryTest {

   public static void main(String[] args) {
   
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
      
         //D.delete("1");
         System.out.println(D);
         System.out.println(D.size());
         D.delete("3");
         System.out.println(D.size());
         System.out.println(D);
         System.out.println(D.lookup("5"));
      
         //D.insert("1", "f"); //throws DuplicateKeyException
         //D.delete("10"); //throws KeyNotFoundException
         D.makeEmpty();
         System.out.println(D.size() + " " + D.isEmpty());
   }
}