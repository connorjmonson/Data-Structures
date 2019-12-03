//-----------------------------------------------------------------------------
// Connor Monson cmonson@ucsc.edu 1461818
// this is pa3 
//  fall 2016
// Dictionary.java
// Linked List implementation of the Dictionary ADT
//-----------------------------------------------------------------------------


public class Dictionary implements DictionaryInterface{

  // private inner Node class
  private class Node {
     String key;
     String value;
     Node next;

     Node(String key, String value){
        this.key = key; //initializing variables
        this.value = value;
        next = null;
     }
  }


  // Fields for the IntegerList class
  private Node head;     // reference to first Node in List
  private int numItems;  // number of items in this Dictionary

  // Dictionary()
  // constructor for the Dictionary class
  public Dictionary(){
     head = null; 
     numItems = 0;
  }


  // private helper function -------------------------------------------------

  // find()
  // returns a reference to the Node at position index in this Dictionary
  private Node findKey(String key){
     Node N = head;
     for( ; N != null; N = N.next){ //while node is not empty (null)
       if(N.key == key){
         return N; //if found return N

       }
     }

     return null; //if not return null


  }



  // ADT operations ----------------------------------------------------------

  // isEmpty()
  // pre: takes in none
  // post: returns true if this IntgerList is empty, false otherwise
  public boolean isEmpty(){
     return(numItems == 0); //will return true or false 
  }

  // size()
  // pre: takes in none
  // post: returns the number of elements in this IntegerList
  public int size() {
     return numItems; //elements
  }

  // get()
  // pre: 1 <= index <= size() and take in string
  // post: returns item at position index in this IntegerList
  public String lookup(String key){

     Node N = findKey(key);

     if(N == null){
       return null; //return null
     }else{
       return N.value; //return string value of the node
     }

  }

  // add()
  // inserts newItem into this IntegerList at position index
  // pre: 1 <= index <= size()+1 and takes in two strings 
  // post: !isEmpty(), items to the right of newItem are renumbered
  public void insert(String key, String value) 
     throws DuplicateKeyException{

     if( lookup(key)!=null ){ 
        throw new DuplicateKeyException(
           "Dictionary Error: Cannot insert duplicate keys: " + key);
     }

     if(numItems == 0){
       Node N = new Node(key, value); //inserts new 
       head = N;
       N = null;
       numItems++;
     }else{
       Node F = head;
       for(int i = 1; i < numItems; i++){  //move everything
         F = F.next;
       }
       Node C = new Node(key, value); //insert
       F.next = C;
       C = null;
       numItems++;
     }
  }

  // remove()
  // deletes item at position index from this IntegerList
  // pre: 1 <= index <= size() and takes in string
  // post: items to the right of deleted item are renumbered
  public void delete(String key)
     throws KeyNotFoundException{
     if( key.length()<1 || key.length()>numItems ){
        throw new KeyNotFoundException(
           "Dictionary Error: cannot delete non-existent key: " + key);
     }
     Node F = findKey(key);
     Node N = head;
     if(head.next == F.next){ //delete 
       head = head.next;
       F = null;
       numItems--;
     }else{
//       for( ; N.next != P; N = N.next){ //no need for a for loop for delete()
//       }
       N.next = F.next; 
       F.next = null;
       numItems--;
     }
  }


  // removeAll()
  // pre: takes in none
  // post: isEmpty()
  public void makeEmpty(){
     head = null;
     numItems = 0;
  }

  // toString()
  // pre: takes in none
  // post:  prints current state to stdout
  // Overrides Object's toString() method
  public String toString(){
     StringBuffer sb = new StringBuffer();
     Node N = head;

     for( ; N!=null; N=N.next){
        sb.append(N.key).append(" ").append(N.value).append("\n");
     }
     return new String(sb);
  }


}