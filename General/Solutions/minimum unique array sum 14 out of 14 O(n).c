#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
/*
 * Complete the 'getMinimumUniqueSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
int series_sum(int start, int count_times) {
    //double ser = (double)((double)start + 1 + ((double)start + count_times - 1)) / 2;
    //ser *= ((double)count_times - 1);
    int ret_val = start + ((double)(start + 1 + (start + count_times -1 )) / 2 * (count_times - 1));
    // 3 + 4 + 4 /2 *2
    //int ret_val = start + (int)ser;
// 2 2 2 2 creates series of 2 3 4 5 where we do the calculation like this 2 + 3 + 4 + 5 instead of calculating using for loop we     //could use a math trick here
// series from 3 to 5 can be calculated (3+5)/2 * count_times -1 ,where count_times is 4 so we calculate series of 3-5 and add 2 to
// it, we get 2+3+4+5 in constant time.
    return ret_val;
}
// The Algorithm: in case the number is single(no dups) we just add that number to the sum, in case it is a dup then we create a
// series ranging from that number and series continues by the amount of dups of that number, so number 2 and 4 dups will create a
// series of 2,3,4,5, now what happends if we see a new single number that now was used back in the series of number 2 ?
// we give it the value of the last element in the series we created +1 and we add it to the sum, if it is not a single number
// then we create a series that starts from te last element from the last series + 1 and series will be from that number and its range
// will be relative to the number of duplicates, by this idea we can achieve the smallest array sum by making all elements unique.
// another algorithm will be using sorting, i also solved that by using sorting and using aux array, althrough using hash is better.
int getMinimumUniqueSum(int arr_count, int* arr) {
    // Time Complexity (N) Space complexity (1) - only constant space used for hash_table.

    int* hash = (int*)calloc(3000, sizeof(int)); // 0 place is 1 2999 is 3000 so index -1
    int i = 0, sum = 0, max = INT_MIN;
    for (i = 0; i < arr_count; i++) {
        hash[arr[i] - 1]++; // range of numbers is 1 to 3000 so -1
    }

    for (i = 0; i < 3000; i++) {
        if (hash[i] == 1) {
            // if its only a single number than just add it to the sum.
            // what if we used that number in previous series calculation? we will have to increment it, we have to keep track of last series number(max).
            if ((i + 1) > max) {
                sum += i + 1; // just add that number, its i+1 because numbers range from 1 to 2999 and our index is 0 - 3000
                max = i + 1; // update max value
            }
            else {
                sum += max + 1; // using max because the number was a part from last series
                max += 1; // we cant use that number again so we increment it by 1.
            }
        }
        else if (hash[i] > 1) {
            if ((i+1) > max) {
                sum += series_sum(i + 1, hash[i]); // function will calculate the new series sum in constant time, we add it to sum.
                max = i + hash[i]; // we update max value with the last element in that series.
            }
            else {
                // here we deal with duplicate scenario where the dup number was a part from a past series.
                sum += series_sum(max + 1, hash[i]); // we give the beginning element the maximum achieved so far and create series
                max = max + hash[i]; // we update the max value with the last element created in that series
            }
        }
    }
    return sum;
}
//int arr[4] = { 2,2,4,5 };
int main() {
    //int arr[10] = {2,2,2,2,4,4,12,12,12,12};
    //int arr[5] = { 4,2,2,4,5 };
    //int arr[3] = { 1,2,3};
    //int arr[4] = { 2,2,4,5 };
    //int arr[9] = { 2,2,2,2,4,12,12,12,12 };
    //int arr[20] = { 493 ,504 ,710 ,710 ,710 ,879 ,1250 ,1328 ,1441 ,1613, 1613 ,1613 ,1659 ,1730, 1730 ,1808, 1841, 2043 ,2043, 2545 };
    //int arr[10] = { 1,2,3,20,22,23,24,20,20,3}; // bug 143 expected:145
    //int arr[14] = {3000,3000,3000,3000,10,10,10,5,1000,1000,2,3,4,5};
    int arr[10] = { 80,81,82,1,2,3,3,3,1,2 }; // bug expected 271 returns 274
    // all bugs fixed! 14/14 works
    printf("%d",getMinimumUniqueSum(sizeof(arr)/sizeof(arr[0]), arr));
    return 0;
}
