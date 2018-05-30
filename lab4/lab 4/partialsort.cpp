// Zeyu Shen
//Student ID: 1672876
//Q = 0: Finding the top k items while the rest of the vector remains unsorted. e.g. Given a random vector, [9, 3, 6, 7, 8, 1, 2], and given k is 3, then you will have a vector that contains [1, 2, 3, 9, 7, 6, 8]. Note this example should not be used for testing but it is to show you what should happen. 

#include <vector>
#include <iostream>
using namespace std;

template <class Comparable>
void objectSwap( Comparable &lhs, Comparable &rhs )
{
  Comparable tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

template <class Comparable>
void choosePivot( vector<Comparable> &a, int first, int last )
{
  int middle = ( first + last ) / 2;
  objectSwap( a[first], a[middle] );
}

template <class Comparable>
void partition( vector<Comparable> &a, int first, int last, int &pivotIndex )
{
  // place the pivot in a[first]
  choosePivot( a, first, last );
  Comparable pivot = a[first];
  int lastS1 = first;
  int firstUnknown = first + 1;
  
  for ( ; firstUnknown <= last; ++firstUnknown )
  {
    if ( a[firstUnknown] < pivot )
    {
      ++lastS1;
      objectSwap( a[firstUnknown], a[lastS1] );
    }
    // else item from unknown belongs in S2
  }
  // decide a new pivot
  objectSwap( a[first], a[lastS1] );
  pivotIndex = lastS1;
}



template <class Comparable>
void quicksort( vector<Comparable> &a, int first, int last ) {
    int pivotIndex;
    
    if ( first < last ) {
        partition( a, first, last, pivotIndex );
        quicksort( a, first, pivotIndex - 1 );
        quicksort( a, pivotIndex + 1, last );
    }
}
template <class Comparable>
void partialsort( vector<Comparable> &a, int first, int last, int K)
{
    
    int pivotIndex;
    if (first>K)// when first is greater than topK, stop doing this recersive algorithm
    {
        return;
    }
    if ( first < last )
    {
        partition( a, first, last, pivotIndex );
        partialsort( a, first, pivotIndex - 1,K );
        partialsort( a, pivotIndex + 1, last,K );
    }
}

template <class Comparable>
void partialsort (vector<Comparable> &a,int K )
{
    partialsort( a, 0, a.size( ) - 1, K);
}




