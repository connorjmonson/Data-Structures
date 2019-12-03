// Connor Monson 1461818 cmonson@ucsc.edu
// lab6 11/15/16
// List.java 
// Lab section: Wednesday 6-7:30pm 

// This is pretty much the same thing as linkedlist integerList.java just modified
// for the T and implimentation of ListInterface

@SuppressWarnings("overrides") //directions said place this befoer the class itself
public class List<T> implements ListInterface<T> {

   /* Node Class */
   private class Node {
      T item;
      Node next;

      Node (T x) {
         item = x;
         next = null;
      }
   }

   /* Class Fields */
   private Node head;
   private int numItems;

   /* Constructor */
   public List(){
      head = null;
      numItems = 0;
   }

 // private helper function -------------------------------------------------

   // find()
   // returns a reference to the Node at position index in this IntegerList
   private Node find(int index){
      Node N = head;
      for(int i=1; i<index; i++){
         N = N.next;
      }
      return N;
   }

 //--------------------------------------------------------------------------  
   /* ADT Operations */

   /* isEmpty
    pre: none
    post: returns true if this List is empty, false otherwisez*/
   public boolean isEmpty() {
      return (numItems == 0);
   }

   /* size
    pre: none
    post: returns the number of elements in this List*/
   public int size() {
      return numItems;
   }

   /* get
    pre: 1 <= index <= size()
    post: returns item at position index*/
   public T get(int index) throws ListIndexOutOfBoundsException {
      if (index < 1 || index > numItems) {
         throw new ListIndexOutOfBoundsException(index + " is not a valid index");
      }
      Node N = find(index);
      return N.item;
   }

   /* add
    inserts newItem in this List at position index
    pre: 1 <= index <= size()+1
    post: !isEmpty(), items to the right of newItem are renumbered*/
   public void add(int index, T newItem) throws ListIndexOutOfBoundsException {
      if (index < 1 || index > numItems+1) {
         throw new ListIndexOutOfBoundsException(index + " is not a valid index");
      }
      if (index == 1) {
         Node N = new Node(newItem);
         N.next = head;
         head = N;
      } else {
         Node A = find(index-1);
         Node B = A.next;
         A.next = new Node(newItem);
         A = A.next;
         A.next = B;

      }
      numItems++;
   }

   /* remove
    deletes item from position index
    pre: 1 <= index <= size() 
    post: items to the right of deleted item are renumbered*/
   public void remove(int index) throws ListIndexOutOfBoundsException {
      if (index < 1 || index > numItems) {
         throw new ListIndexOutOfBoundsException(index + " is not a valid index");
      }
      if (index == 1) {
         Node N = head;
         head = head.next;
         N.next = null;
      } else {
         Node A = find(index-1);
         Node B = A.next;
         A.next = B.next;
         B.next = null;
      }
      numItems--;
   }

   /* removeAll
    pre: none
    post: isEmpty()*/
   public void removeAll() {
      head = null;
      numItems = 0;
   }
   
 // toString() translation method
   /* toString() */ 
   //returns: string type 
   public String toString() {
      String str = ""; //initialize string 
      for (Node N = head; N != null; N = N.next) {
         str += N.item.toString() + " "; //add content to string 
      }
      return str; //return string type 
   }

   
    // equals()
   // pre: none
   // post: returns true if this IntegerList matches rhs, false otherwise
   // Overrides Object's equals() method
   @SuppressWarnings("unchecked") //place before the function definition
   public boolean equals(Object rhs) {
      boolean eq = false; //initializing 
      List<T> R = null;
      Node C = null;
      Node M = null;

      if (this.getClass() == rhs.getClass()) {
         R = (List<T>)rhs;
         eq = (this.numItems == R.numItems); //boolean expression
         C = this.head; // setting heads
         M = R.head; 
         while (eq && C != null) { 
            eq = (C.item == M.item); //boolean expression
            C = C.next; //pointing to the next in C and M
            M = M.next;
         }
      }
      return eq; //final answer boolean experession
   }
}