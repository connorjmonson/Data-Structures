// Connor Monson 1461818 cmonson@ucsc.edu
// lab6 11/15/16
// ListTest.java 
// Lab section: Wednesday 6-7:30pm 
// This is pretty much the same thing as ListClient.java just modified my version 

public class ListTest {
   public static void main(String[] args) {
      List<String> A = new List<String>(); //following the same initializations as ListClient.jav
      List<String> B = new List<String>();
      List<List<String>> C = new List<List<String>>();
      int i, j, k;
      //doing tests
      A.add(1, "a"); 
      A.add(2, "b");
      A.add(3, "c");
      
      B.add(1, "c");
      B.add(2, "d");
      B.add(3, "c");
      
      C.add(1, A);
      C.add(2, B);
      

      System.out.println("A: "+A);
      System.out.println("B: "+B);
      System.out.println("C: "+C);
      
      System.out.println("A.equals(A) is "+A.equals(A));
      System.out.println("A.equals(B) is "+A.equals(B));
      System.out.println("A.equals(C) is "+A.equals(C));
      
      System.out.println("B.equals(A) is "+B.equals(A));
      System.out.println("B.equals(B) is "+B.equals(B));
      System.out.println("B.equals(C) is "+B.equals(C));
      
      
      System.out.println("A.size() is "+A.size());
      System.out.println("B.size() is "+B.size());
      System.out.println("C.size() is "+C.size());

      A.remove(1);
      B.remove(3);
      

      System.out.println("A.size() is "+A.size());
      System.out.println("B.size() is "+B.size());
      System.out.println("B.get(1) is "+B.get(1));
      System.out.println("C: "+C);
      System.out.println();
      try{
         System.out.println(A.get(123));
      }catch(ListIndexOutOfBoundsException e){
         System.out.println("Caught Exception: ");
         System.out.println(e);
         System.out.println("Continuing without interuption");
      }
      System.out.println();
      System.out.println("A.get(2) is "+A.get(1));
      System.out.println("A.get(2) is "+A.get(2));
      
      System.out.println("C.get(1) is "+C.get(1));
      
      
      System.out.println("B.get(2) is "+B.get(1));
      System.out.println("B.get(2) is "+B.get(2));
      
   }
}