/* 
*  Connor Monson cmonson@ucsc.edu 1461818
*  this is lab5 essencially doing pa3 in c
*  fall 2016
*  Dictionary.c 
*  Implements Dictionary.h using Hash Tables
*/  

#include<stdio.h> //include everything
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h" //test .h file using Hash tables
#define MAX_LEN 180

const int tableSize=101;

// Hash Functions
//basically same format as pa3 just in c

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits-1);
   if ( shift == 0 )
      return value;
   return (value << shift) | (value >> (sizeInBits -shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
   unsigned int result = 0xBAE86554;
   while (*input) { 
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}
   
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
   return pre_hash(key)%tableSize;
}

// -------------------------------------------------------------------------------

//NodeObj
typedef struct NodeObj {
   char* key; //initilize 
   char* value;
   struct NodeObj* next;
} NodeObj;

//Node
typedef NodeObj* Node;

//newNode() the Node type constructor
Node newNode(char*k, char* v){
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = k;
   N->value = v;
   N->next = NULL;
   return(N);
   //started confusing myself when I made the constructor Node N and other different names 
   //so I stuck with node N (even for local variables )
}

//freeNode() the Node type destructor
void freeNode(Node* fN) {
   if (fN!=NULL && *fN!=NULL) {
      free(*fN);
      *fN = NULL;
   }
}

//ListObj
typedef struct ListObj {
   Node head;
} ListObj;

//List
typedef ListObj* List; 

//newList() constructor for the Node type
List newList(void) {
   List P = malloc(sizeof(ListObj));
   assert(P!=NULL);
   P->head = NULL;
   return P;
   //started confusing myself when I made the constructor List P and other Lists list L 
   //so Im going with List L for local variables 
}

//DictionaryObj
typedef struct DictionaryObj {
   List table;
   int itemCount;
} DictionaryObj;

// -------------------------------------------------------------------------------

//Private helper functions-----------------------

//findKey()
//returns a reference to the NodeObj containing its respective key
//returns null if no such Node exists
Node findKey(Node H, char* targetKey) {
   while (H!=NULL) { 
      if (strcmp(H->key, targetKey)==0) { //searching through H to find targetKey
         break;
      } 
      H = H->next;
   } return H; //returns respective key or null 
}

//deleteAll does exactly what you think, deletes everything
void deleteAll(Node N) {
   if (N!=NULL) {
      deleteAll(N->next); //recursive call to until base of freeNode()
      freeNode(&N);
   }
}

//Public functions-------------------------------

// newDictionary()
// constructor for the Dictionary type!
Dictionary newDictionary(void) {
   Dictionary T = malloc(sizeof(DictionaryObj)); //setting everything up for Dictionary Consntructor
   assert(T!=NULL);
   T->table = calloc(tableSize, sizeof(ListObj));
   T->itemCount = 0;
   return T; 
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* fD) { //no return on this function call
   if (fD!=NULL && *fD!=NULL){ 
      if (!isEmpty(*fD)) makeEmpty(*fD);
      free(*fD);
      *fD = NULL;
   }
}

//ADT operations-------------------------------


// isEmpty()
// pre: takes in none
// post: returns true if this IntgerList is empty, false otherwise
int isEmpty(Dictionary T){
   if(T==NULL){
      fprintf(stderr, "DICTIONARY ERROR: calling isEmpty() on invalid Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(T->itemCount==0);
}

// size()
// pre: takes in none
// post: returns the number of elements in this IntegerList
int size(Dictionary T){
   return T->itemCount;
}

// lookup()
// pre: takes in T and char 
// returns the value v such that (k, v) is in T, or returns NULL if no
// such value v exists.
char* lookup(Dictionary T, char* k){
   int tableIndex; //initilize variables
   Node N;
   List P;
   tableIndex = hash(k);
   P = &T->table[tableIndex];
   N = findKey(P->head, k); //call to findkey
   if(N==NULL) {
      return NULL; //returns null if findkey returned null
   } else {
      return N->value; //returns value 
   }
}

// insert() is like add
   // add()
   // inserts newItem into this IntegerList at position index
   // pre: 1 <= index <= size()+1 and takes in two strings 
   // post: !isEmpty(), items to the right of newItem are renumbered
// pre: lookup(T, k)==NULL and takes in Dictionary and 2 chars
// inserts new (key,value) pair into T
void insert(Dictionary T, char* k, char* v){
   Node N; //initilize to use 
   List P;
   int tableIndex;
   tableIndex = hash(k);
   N = newNode(k,v);
   P = &T->table[tableIndex];
   if(findKey(P->head,k)!=NULL) {
      fprintf(stderr, "DICTIONARY ERROR: calling insert() on an existing key\n");
      exit(EXIT_FAILURE);
   }
   N->next = P->head;
   P->head = N;
   N = NULL;
   T->itemCount++;
}

// delete()is like remove
   // remove()
   // deletes item at position index from this IntegerList
   // pre: 1 <= index <= size() and takes in string
   // post: items to the right of deleted item are renumbered
// pre: lookup(T, k)!=NULL and takes in Dictionary and 1 char
// deletes pair with the key k
void delete(Dictionary T, char* k) {
   if (T==NULL) { //base case test 
      fprintf(stderr, "DICTIONARY ERROR: calling delete() on an invalid Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   Node N; //initilize 
   List P;
   int tableIndex;
   tableIndex = hash(k);
   P = &T->table[tableIndex];
   if (findKey(P->head, k)==P->head) { //finds what we want to remove and removes
      N = P->head;
      P->head = P->head->next;
      N->next = NULL;
   } else {
      N = findKey(P->head,k);
      Node prev = P->head;
      Node temp = P->head->next;
      while (temp != N) { //moves everything
         temp = temp->next;
         prev = prev->next;
      }
      prev->next = N->next; 
      N->next = NULL; //concludes the delete
   }
   T->itemCount--; //account for what happend to variable
   freeNode(&N);
}

// makeEmpty() is like removeAll
   // removeAll()
   // pre: takes in none
   // post: isEmpty()
// pre: takes in Dictionary
// re-sets T to the empty state. making it completely empty 
void makeEmpty(Dictionary T) {
   List P; //intialize
   if (T==NULL) { // check if T is empty
      fprintf(stderr, "DICTIONARY ERROR: calling makeEmpty() on an invalid Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if (T->itemCount==0) { //both these if's I think get the same result, just not going to chance it
      fprintf(stderr, "DICTIONARY ERROR: calling makeEmpty() on an empty Dictionary\n");
      exit(EXIT_FAILURE);
   }
   for (int i=0; i<tableSize; i++) { //loop for removal 
      P = &T->table[i];
      deleteAll(P->head);
   }
   T->table = NULL; //setting the values
   T->itemCount = 0;
}

// printDictionary()
// pre: none
// prints a text representation of T to the file pointed to by out
void printDictionary(FILE* out, Dictionary T) {
   Node N; //initialize 
   if (T==NULL) { //if T is nothing, exit, otherwise...
      fprintf(stderr, "DICTIONARY ERROR: calling printDictionary() on an invalid Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   List P;
   //realizing I should have had implimented the node in the Dictionary rather
   //then having it in the List. I should have just implimented Node in Dictionary
   //and totally negated list. I would have to change all my code but I have run out of time
   //having another object is screwing this up. 
   /*
   int i = 0;
   while (i<tableSize){
      P=&T->table[i];
      for(N=P->head; N!=NULL; N=N->next){
            fprintf(out, "%s %s\n", N->key, N->value);
            i++;
      } */
   //List P;
   /*
   for(int i=0; i<tableSize; i++){
      P = &T->table[i];
      for(N=T->head; N!=NULL; N=N->next){
         fprintf(out, "%s %s\n", N->key, N->value); //segmentation fault? 
         N = N->next;
      }
   } */
      
   for (int i=0; i<tableSize; i++) { //impliment for loop with imbedded while for everything not null for Node
      P = &T->table[i];
      N = P->head;
      while (N!=NULL) {
         fprintf(out, "%s %s\n", N->key, N->value); //think this is the part that mixes up my order
         N = N->next;  //everything else I try screws it up printing more or makes printDictionary not work
      }
   } 
   //free(P);
   //P = NULL;
}