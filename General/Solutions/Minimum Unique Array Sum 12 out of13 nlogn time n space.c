/*
 * Complete the 'getMinimumUniqueSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int getMinimumUniqueSum(int arr_count, int* arr) {
 qsort(arr,arr_count,sizeof(int),compare);
 // after the array is sorted we can easily detect duplicates and move forward from there.
// we solve this problem by using slow pointer and fast pointer after sorting the array for detecting duplicates.
 // Time Complexity (NlogN) Space Complexity (N) (Aux Array)
 // 9/13 cases pass need to check if there is better solution 
 // had a memory leak fixed it by adding 1 more int to the array but this is still not good at all so now 12/13 passed
int *aux = (int*)calloc(arr_count+1,sizeof(int));
//int aux[arr_count];
int max=INT_MIN;
int c=1;
int i=0,j=1,k=0,f=0;

while(j<=arr_count-1) {
    while(arr[i]==arr[j]) {
        c++,j++;
        if(j==arr_count-1) break;
    } 
    if(c>1) {
        if(arr[i]>max) {
         while(k<c) aux[f] = arr[i]+k,k++,f++;
        }
        else {
            while(k<c) aux[f] = max+k,k++,f++;
        }
        max = aux[f-1]+1;
        k=0;
        c=1;
        i=j,j++;
    }
     if (c==1 && arr[i]<=max && arr[i]!=arr[j]) {
        aux[f++] = max;
        max++;
        i++,j++;
    }
    else if(arr[i]!=arr[j]) {
        aux[f]=arr[i];
        aux[f+1]=arr[j];
        max=arr[j]+1;
       i+=2,j+=2,f+=2;
    }

}
aux[i]=max;
max =0;
for (i=0;i<arr_count;i++) {
    max+=aux[i];
}
return max;
}