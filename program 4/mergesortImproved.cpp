#include <vector>
#include <math.h> // may need to use pow( )
#include <iostream>
using namespace std;
///////////////////////////////////////merge/////////////////////////////////////////////
// copy form usual mergesort
template<class Comparable>
void merge(vector<Comparable> &a, vector<Comparable> &b, int first,
           int mid, int last) {
    
    int first1 = first;
    int last1 = mid;      // the left array[first1..last1]
    int first2 = mid + 1;
    int last2 = last;     // the right array[first2..last2]
    
    int index = first1;
    // choosing the smaller, sorting
    for (; first1 <= last1 && first2 <= last2; index++) {
        if (a[first1] < a[first2])
            b[index] = a[first1++];
        else
            b[index] = a[first2++];
    } // end for loop
    // exhausting left array
    for (; first1 <= last1; ++first1, ++index)
        b[index] = a[first1];
    
    // exhausting right array
    for (; first2 <= last2; ++first2, ++index)
        b[index] = a[first2];
}

////////////////////////////////mergesortImproved//////////////////////////////
// sorts an array passed in the parameter

template<class Comparable>
void mergesortImproved(vector<Comparable> &a)
{
    int size = a.size();
    vector<Comparable> b(size);  //temporary array.
    // implement a nonrecursive mergesort only using vectors a and b
    int width; // the width of each pairs to be merge in the array
    bool sorted = false; // to determine if the merge array is in
    // the original param
    
    for (width = 1; width < size; width *= 2) { // width is segment size
        // pairs up the array by width
        for (int first = 0; first < size; first += width * 2) {
            // merge parameters loc
            int left = first;
            int middle = first + width - 1;
            int right = min(first + (width * 2 - 1), size - 1);
            if(middle > size)
                middle = left + (size % left) / 2;
            if (!sorted)  // copying and merging array to the temp
                merge(a, b, left, middle, right);
            else
                // call merge to copying and merging array
                merge(b, a, left, middle, right);
        }
        // alternating between unsorted and temp array each iteration
        if (sorted)
            sorted = false;
        else
            sorted = true;
    }
    
    // copy b array back into a
    if (sorted == true)
    {
        for (int index = 0; index <= a.size(); ++index) // write them back to original
            a[index] = b[index];
    }
}

