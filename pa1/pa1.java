class Recursion{  

  public static void main(String[] args){
    int[] A = {1,-2,3,-4,5,-6};
    //int[] A = {-1, 2, 6, 12, 9, 2, -5, -2, 8, 5, 7};
    int[] B = new int[A.length]; 
    int[] C = new int[A.length];
//MININUM TEST
    int minIndex = minArrayIndex(A, 0, A.length-1); 
//MAXIMUM TEST
    int maxIndex = maxArrayIndex(A, 0, A.length-1); 
    
//    for(int x: A){
//    System.out.print(x+" "); 
//    System.out.println(); 
//    }
    
    System.out.println( "minIndex = " + minIndex ); 
    System.out.println( "maxIndex = " + maxIndex ); 

// ARRAY 1 TEST
    
    reverseArray1(A, A.length, B);
    System.out.println();
//    for(int x: B){
//    System.out.print(x+" "); 
//    //System.out.println(); 
//    }

// ARRAY 2 TEST
    reverseArray2(A, A.length, C);
    System.out.println();
//    for(int x: C){
//    System.out.print(x+" ");
//    //System.out.println();
//    }

// ARRAY 3 TEST
    //reverseArray3(A, 0, A.length-1);
    reverseArray3(A, 1, A.length-2); 
    for(int x: A){
      System.out.print(x+" ");
    }
//    System.out.println(); 
  }
  
  static void reverseArray1(int[] X, int n, int[] Y){
    //int c = -1; //use recursion for everything
    if(n>0){
      Y[n-1]= X[X.length - n]; //using X[c+1] gets the X[0] but is having problems 
      System.out.print(X[n-1] + " "); // print nth element from left
      reverseArray1(X, n-1,Y);
    } //works
     
  }
  
  static void reverseArray2(int[] X, int n, int[] Y){ //same thing as Array1 just reversing the Y[]=X[] part i think
    if(n>0){
      Y[X.length - n]= X[n-1];
      System.out.print(Y[X.length - n] + " "); // print nth element from left
      reverseArray1(X, n-1,Y);
    }
  } //works
  
  static void reverseArray3(int[] X, int i, int j){
   
   int c;
   if(i<j){
     c=X[i]; //not c= i; that was my mistake!
     X[i]= X[j];
     X[j]= c; // make it equal c not X[c]
     reverseArray3(X,i+1,j-1);
   }
  } //works now
  
  static int maxArrayIndex(int[] X, int p, int r){ //finding the index of the biggest in the array
    int maxL; //greatest on left side part
    int maxR; //greatest on right side part
    int half; //half way int 
    if(p==r){ //this is the base case (:
      return max(X, p, r);
    }
    else{
      half = (p+r)/2; //cut in half 
      maxL = maxArrayIndex(X, p, half); //max on left half
      maxR = maxArrayIndex(X,half+1,r); //max on right half
      return max(X, maxL, maxR);
    }
  } //works
  
  static int max(int[] X, int p, int r){ //compare
    int indexGreatest;
    if(X[p] >= X[r]){
      indexGreatest = p;
    }
    else{
      indexGreatest = r;
    }
    
    return indexGreatest;
  } //works
//  
  static int minArrayIndex(int[] X, int p, int r){ //same thing as max but change >= to <= and that should work I think
    int minL; //greatest on left
    int minR; //greatest on right
    int half; //half way int
    if(p==r){ //this is the base case (:
      return min(X, p, r);
    }
    else{
      half = (p+r)/2;
      minL = minArrayIndex(X, p, half); //min on left
      minR = minArrayIndex(X,half+1,r); //min on right
      return min(X, minL, minR);
    }
  } //works
  
  static int min(int[] X, int p, int r){ //compare
    int indexSmallest;
    if(X[p] <= X[r]){ //changed from >= to <= to get min 
      indexSmallest = p;
    }
    else{
      indexSmallest = r;
    }
    
    return indexSmallest;
  } //works
}