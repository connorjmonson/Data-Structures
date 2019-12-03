/* 
*  Connor Monson cmonson@ucsc.edu
*  pa5
*  Dictionary.c 
*  Implements Dictionary.h using Hash Tables
*/  

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"
#define MAX_LEN 180

const int tableSize=101;

// Hash Functions

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
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

//Node
typedef NodeObj* Node;

//newNode() constructor for the Node type
Node newNode(char*k, char* v){
   Node M = malloc(sizeof(NodeObj));
   assert(M!=NULL);
   M->key = k;
   M->value = v;
   M->next = NULL;
   return(M);
}

//freeNode() destructor for the Node type
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
}

//DictionaryObj
typedef struct DictionaryObj {
   List table;
   int itemCount;
} DictionaryObj;

//Private helper functions-----------------------

//findKey()
//returns a reference to the NodeObj containing its respective key
//returns null if no such Node exists
Node findKey(Node H, char* targetKey) {
   while (H!=NULL) {
      if (strcmp(H->key, targetKey)==0) {
         break;
      } 
      H = H->next;
   } return H;
}

//deleteAll
void deleteAll(Node M) {
   if (M!=NULL) {
      deleteAll(M->next);
      freeNode(&M);
   }
}

//Public functions-------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void) {
   Dictionary T = malloc(sizeof(DictionaryObj));
   assert(T!=NULL);
   T->table = calloc(tableSize, sizeof(ListObj));
   T->itemCount = 0;
   return T;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* fD) {
   if (fD!=NULL && *fD!=NULL){
      if (!isEmpty(*fD)) makeEmpty(*fD);
      free(*fD);
      *fD = NULL;
   }
}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary T){
   if(T==NULL){
      fprintf(stderr, "DICTIONARY ERROR: calling isEmpty() on invalid Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(T->itemCount==0);
}

// size()
// returns the number of (key, value) pairs in T
// pre: none
int size(Dictionary T){
   return T->itemCount;
}

// lookup()
// returns the value v such that (k, v) is in T, or returns NULL if no
// such value v exists.
// pre: none
char* lookup(Dictionary T, char* k){
   int tableIndex;
   Node M;
   List P;
   tableIndex = hash(k);
   P = &T->table[tableIndex];
   M = findKey(P->head, k);
   if(M==NULL) {
      return NULL;
   } else {
      return M->value;
   }
}

// insert()
// inserts new (key,value) pair into T
// pre: lookup(T, k)==NULL
void insert(Dictionary T, char* k, char* v){
   Node M;
   List P;
   int tableIndex;
   tableIndex = hash(k);
   M = newNode(k,v);
   P = &T->table[tableIndex];
   if(findKey(P->head,k)!=NULL) {
      fprintf(stderr, "DICTIONARY ERROR: calling insert() on an existing key\n");
      exit(EXIT_FAILURE);
   }
   M->next = P->head;
   P->head = M;
   M = NULL;
   T->itemCount++;
}

// delete()
// deletes pair with the key k
// pre: lookup(T, k)!=NULL
void delete(Dictionary T, char* k) {
   if (T==NULL) {
      fprintf(stderr, "DICTIONARY ERROR: calling delete() on an invalid Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   Node M;
   List P;
   int tableIndex;
   tableIndex = hash(k);
   P = &T->table[tableIndex];
   if (findKey(P->head, k)==P->head) {
      M = P->head;
      P->head = P->head->next;
      M->next = NULL;
   } else {
      M = findKey(P->head,k);
      Node prev = P->head;
      Node temp = P->head->next;
      while (temp != M) {
         temp = temp->next;
         prev = prev->next;
      }
      prev->next = M->next;
      M->next = NULL;
   }
   T->itemCount--;
   freeNode(&M);
}

// makeEmpty()
// re-sets T to the empty state.
// pre: none
void makeEmpty(Dictionary T) {
   List P;
   if (T==NULL) {
      fprintf(stderr, "DICTIONARY ERROR: calling makeEmpty() on an invalid Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if (T->itemCount==0) {
      fprintf(stderr, "DICTIONARY ERROR: calling makeEmpty() on an empty Dictionary\n");
      exit(EXIT_FAILURE);
   }
   for (int i=0; i<tableSize; i++) {
      P = &T->table[i];
      deleteAll(P->head);
   }
   T->table = NULL;
   T->itemCount = 0;
}

// printDictionary()
// pre: none
// prints a text representation of T to the file pointed to by out
void printDictionary(FILE* out, Dictionary T) {
   if (T==NULL) {
      fprintf(stderr, "DICTIONARY ERROR: calling printDictionary() on an invalid Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   Node M;
   List P;
   for (int i=0; i<tableSize; i++) {
      P = &T->table[i];
      M = P->head;
      while (M!=NULL) {
         fprintf(out, "%s %s\n", M->key, M->value);
         M = M->next;
      }
   }
}