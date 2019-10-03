/*
* * * * * * * * * * * * * * * * * * *
*       Author : Ganzaki            *
*                                   *
*       language : c++              *
*                                   *
* * * * * * * * * * * * * * * * * * *
*/

#include <bits/stdc++.h>

namespace ksb
{
    
    //arrayReverse is used to reverse array element from index start to end
    
    void arrayReverse(int *array, int start, int end);

    //To merger array[start to middle] and array[middle to end] in ascending order
    
    void Merge(int *array, int start, int middle, int end);

    //Merger version 1 is used to sort array which are mostly sorted
    
    void ARootMergeV1(int *array, int start, int end);
    
    //Merger version 2 is used to sort array which are less started
    
    void ARootMergeV2(int *array, int start, int end);

    //Function that reverses large enough decreasingly sorted subarray and
    //decides if array has to go through version 1 or 2 of merger
    
    void ARootSort(int *array, int start, int end);
}



