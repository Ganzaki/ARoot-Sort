# AROOT SORT

Time : 25th September 2019 12:14 IST(Indian Standard Time)


ARoot Sort is a highly optimised merge sort which performes two different kinds of merge sort based on degree of sortedness of input after subarray reversing.
It is a stable sort and outperforms std::sort that implements introsort by a small margin.




## ALGORITHM


### ARootSort (a[] , n):


    1. array_iterator_1 = 0;
    2. array_iterator_2 = start + 1;
    //It is not proved to be optimal, just intuitively taken
    3. optimal_near_sorted_parameter = (log(end-start)/log(2));
    4. number_of_decreasing_subarray = 0;
    5. for iterator = start + 1 to end  
            while (array_iterator_2 < end) && 
                   (array[array_iterator_2 - 1] > array[array_iterator_2]) do
                array_iterator_2++;
            if array_iterator_2 - array_iterator_1 > 1 then
                arrayReverse(array ,array_iterator_1, array_iterator_2);
                number_of_decreasing_subarray++;
            array_iterator_1 = array_iterator_2;
    6. if number_of_decreasing_subarray <= optimal_near_sorted_parameter then
            ARootMergeV1(array, start, end);
    7. else
            ARootMergeV2(array, start, end);



### ARootMergerV1 (a[] , p , q):


    1. merge_iterator_start = start;
    2. merge_iterator_middle = start;
    3. merge_iterator_end = start + 1;
    4. isMerge = false;
    5. number_of_sorted_subarray = 0;
    6. while true do
            while  (merge_iterator_end < end) && 
                   (array[merge_iterator_end] >= array[merge_iterator_end - 1]) do
                merge_iterator_end++;
            if isMerge then
                Merge(array, merge_iterator_start, 
                      merge_iterator_middle, 
                      merge_iterator_end);
                merge_iterator_start = merge_iterator_end;
                merge_iterator_end++;
                isMerge = false;
            else
                isMerge = true;
                merge_iterator_middle = merge_iterator_end;
                merge_iterator_end++;
                number_of_sorted_subarray++;
                if merge_iterator_middle >= end then
                    if number_of_sorted_subarray < 2 then 
                        return;
                    else 
                        number_of_sorted_subarray = 0;
                        merge_iterator_start = start;
                        merge_iterator_middle = start;
                        merge_iterator_end = start + 1;
                        isMerge = false;




### ARootMergerV2 (a[] , p , q):


    1. merge_iterator_start = 0;
    2. merge_iterator_middle = 0;
    3. merge_iterator_end = 0;
    4. step_counter = 1;
    5. list sorted_subarray_end_points;
    6. sorted_subarray_end_points.add(0);
    7. for iterator = start + 1 to end
            while (iterator < end) && (array[iterator] >= array[iterator - 1]) do
                iterator++;
            sorted_subarray_end_points.add(iterator);
    8. if sorted_subarray_end_points[sorted_subarray_end_points.size() - 1] != end then
            sorted_subarray_end_points.add(end);
    9. number_of_sorted_subarray = (int)sorted_subarray_end_points.size() - 1;
    10. while true do
            merge_iterator_start = 0;
            merge_iterator_middle = merge_iterator_start + step_counter;
            merge_iterator_end = minimim(merge_iterator_middle + step_counter, 
                                          number_of_sorted_subarray);
            if merge_iterator_middle >= number_of_sorted_subarray then
                return
            while merge_iterator_middle < number_of_sorted_subarray do
                Merge(array, sorted_subarray_end_points[merge_iterator_start], 
                      sorted_subarray_end_points[merge_iterator_middle], 
                      sorted_subarray_end_points[merge_iterator_end]);
                merge_iterator_start = merge_iterator_end;
                merge_iterator_middle = merge_iterator_start + step_counter;
                merge_iterator_end = minimum(merge_iterator_middle + step_counter, 
                                              number_of_sorted_subarray);
            step_counter = step_counter * 2


### Merge (a[] , p , q , r) :


    1. first_array_size = middle - start;
    2. temp_array[first_array_size];
    3. for iterator = 0 to first_array_size
        temp_array[iterator] = array[start + iterator];
    4. temp_array_iterator = 0;
    5. second_array_iterator = middle;
    6. array_iterator = start;
    7. while  (temp_array_iterator < first_array_size) && 
           (second_array_iterator < end) do
            if  temp_array[temp_array_iterator] <= array[second_array_iterator] then
                array[array_iterator] = temp_array[temp_array_iterator];
                array_iterator++;
                temp_array_iterator++;
            else
                array[array_iterator] = array[second_array_iterator];
                array_iterator++;
                second_array_iterator++;
    8. while temp_array_iterator < first_array_size do
            array[array_iterator] = temp_array[temp_array_iterator];
            array_iterator++;
            temp_array_iterator++;





## EXECUTION STEP TO CHECK WITH CUSTOM INPUT


```bash
git clone https://github.com/Ganzaki/ARoot-Sort.git
cd ARoot-Sort
g++ ./ARootSort/main.cpp
./a.out
```



## TESTS

1. 100 test cases 10^3 elements in each

```bash
std::sort : 0.0139650000 sec
std::stable_sort : 0.0146700000 sec
ARootSort : 0.0134540000 sec
```


2. 100 test cases 10^4 elements in each

```bash
std::sort : 0.1437870000 sec
std::stable_sort : 0.1484690000 sec
ARootSort : 0.1353240000 sec
```


3. 100 test cases 10^5 elements in each

```bash
std::sort : 1.7315120000 sec
std::stable_sort : 1.8135910000 sec
ARootSort : 1.6314080000 sec
```



4. 100 test cases 10^6 elements in each

```bash
std::sort : 19.8574830000 sec
std::stable_sort : 21.5276450000 sec
ARootSort : 18.8334520000 sec
```



5. 10 test cases 10^7 elements in each

```bash
std::sort : 24.4440440000 sec
std::stable_sort : 25.3892670000 sec
ARootSort : 22.1385360000 sec
```



6. 1 test cases 10^8 elements

```bash
std::sort : 27.8200120000 sec
std::stable_sort : 29.2600900000 sec
ARootSort : 25.6958740000 sec
```



7. 1 test cases 10^8 elements where elements are mostly sorted

```bash
std::sort : 40.2773120000 sec
std::stable_sort : 10.8091520000 sec
ARootSort : 1.5766540000 sec
```





## NOTE 
1. optimal_near_sorted_parameter = ln(n)/ln(2) might not be the optimal value, ln(n)/ln(2) is intuitively taken

2. To be fair with all sorting method compared above,
        All of them are run on same machine, 
        Best of three time_taken is considered
        

3. File test_case3.txt, test_case4.txt, test_case5.txt, test_case6.txt and test_case7.txt are not included as all these file size sum up to be more than 3GB

4. Root in the name for the above optimised sorting algorithm doesn't convey or tell anything about the sort.




## TODO

- [ ] Program to sort different data types.




### Last Updated

Time : 03rd October 2019 20:04 IST(Indian Standard Time)

