/*
* * * * * * * * * * * * * * * * * * *
*       Author : Ganzaki            *
*                                   *
*       language : c++              *
*                                   *
* * * * * * * * * * * * * * * * * * *
*/
#include "ARootSort.hpp"


void ksb::arrayReverse(int *array, int start, int end)
{
    int middle = start + (end - start)/2;
    int temp = start + end -1;
    for (int iterator = start; iterator < middle; ++iterator)
        std::swap(array[iterator], array[temp-iterator]);
}


void ksb::Merge(int *array, int start, int middle, int end)
{
    int first_array_size = middle - start;

    int temp_array[first_array_size];

    for (int iterator = 0; iterator < first_array_size; ++iterator) 
        temp_array[iterator] = array[start + iterator];

    int temp_array_iterator = 0;
    int second_array_iterator = middle;
    int array_iterator = start;

    while ( (temp_array_iterator < first_array_size) && 
           (second_array_iterator < end) )
    {

        if ( temp_array[temp_array_iterator] <= array[second_array_iterator])
        {
            array[array_iterator] = temp_array[temp_array_iterator];

            array_iterator++;
            temp_array_iterator++;

        }

        else
        {
            array[array_iterator] = array[second_array_iterator];

            array_iterator++;
            second_array_iterator++;
        }
    
    }
    while (temp_array_iterator < first_array_size)
    {
        array[array_iterator] = temp_array[temp_array_iterator];

        array_iterator++;
        temp_array_iterator++;
    }
}



void ksb::ARootMergeV1(int *array, int start, int end)
{
    int merge_iterator_start = start;
    int merge_iterator_middle = start;
    int merge_iterator_end = start + 1;

    bool isMerge = false;

    int number_of_sorted_subarray = 0;

    while (true)
    {
        while ( (merge_iterator_end < end) && 
               (array[merge_iterator_end] >= array[merge_iterator_end - 1]) )

            merge_iterator_end++;

        if (isMerge)
        {

            Merge(array, merge_iterator_start, 
                  merge_iterator_middle, 
                  merge_iterator_end);

            merge_iterator_start = merge_iterator_end;
            merge_iterator_end++;

            isMerge = false;

        }
        else
        {

            isMerge = true;

            merge_iterator_middle = merge_iterator_end;
            merge_iterator_end++;

            number_of_sorted_subarray++;

            if (merge_iterator_middle >= end)
            {
                if (number_of_sorted_subarray < 2) 
                    break;

                else 
                {
                    number_of_sorted_subarray = 0;

                    merge_iterator_start = start;
                    merge_iterator_middle = start;
                    merge_iterator_end = start + 1;

                    isMerge = false;
                }
            }
        }
    }
}



void ksb::ARootMergeV2(int *array, int start, int end)
{
    
    int merge_iterator_start = 0;
    int merge_iterator_middle = 0;
    int merge_iterator_end = 0;

    int step_counter = 1;

    std::vector<int> sorted_subarray_end_points;

    sorted_subarray_end_points.push_back(0);

    for (int iterator = start + 1; iterator < end; ++iterator) 
    {
        while( (iterator < end) && (array[iterator] >= array[iterator - 1]) )
            iterator++;

        sorted_subarray_end_points.push_back(iterator);
    }

    if (sorted_subarray_end_points[sorted_subarray_end_points.size() - 1] != end) 
        sorted_subarray_end_points.push_back(end);

    int number_of_sorted_subarray = (int)sorted_subarray_end_points.size() - 1;

    while (true)
    {
        merge_iterator_start = 0;
        merge_iterator_middle = merge_iterator_start + step_counter;
        merge_iterator_end = std::min(merge_iterator_middle + step_counter, 
                                      number_of_sorted_subarray);

        if (merge_iterator_middle >= number_of_sorted_subarray) 
            break;

        while (merge_iterator_middle < number_of_sorted_subarray)
        {

            Merge(array, sorted_subarray_end_points[merge_iterator_start], 
                  sorted_subarray_end_points[merge_iterator_middle], 
                  sorted_subarray_end_points[merge_iterator_end]);

            merge_iterator_start = merge_iterator_end;
            merge_iterator_middle = merge_iterator_start + step_counter;
            merge_iterator_end = std::min(merge_iterator_middle + step_counter, 
                                          number_of_sorted_subarray);

        }

        step_counter = step_counter * 2;

    }
}



void ksb::ARootSort(int *array, int start, int end)
{

    int array_iterator_1 = 0;
    int array_iterator_2 = start + 1;


    //It is not proved to be optimal, just intuitively taken

    int optimal_near_sorted_parameter = (int)(log(end-start)/log(2));

    int number_of_decreasing_subarray = 0;


    for (int iterator = start + 1; iterator < end; ++iterator) 
    {

        while ( (array_iterator_2 < end) && 
               (array[array_iterator_2 - 1] > array[array_iterator_2]) )

            array_iterator_2++;

        if (array_iterator_2 - array_iterator_1 > 1)
        {
            arrayReverse(array ,array_iterator_1, array_iterator_2);

            number_of_decreasing_subarray++;
        }

        array_iterator_1 = array_iterator_2;

    }

    if (number_of_decreasing_subarray <= optimal_near_sorted_parameter)
        ARootMergeV1(array, start, end);
    else
        ARootMergeV2(array, start, end);
}

