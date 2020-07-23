// Complete the rotLeft function below.

// Please store the size of the integer array to be returned in result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;
//
int* rotLeft(int a_count, int* a, int d, int* result_count) {
    *result_count=a_count;
    if(d==a_count || d>a_count && a_count%d==0 || d==0) return a;
    else if(d>a_count && a_count%d!=0) {
        d%=a_count;
    }
    if(a_count==2) {
        int t1;
        t1=a[a_count-2],a[a_count-2]=a[a_count-1],a[a_count-1]=t1;
    }
        while(d) {
    int i=a_count,t1,t2;

    t1=a[i-2],a[i-2]=a[i-1];
    for(i=a_count-3;i>=0;i--) {
        t2=a[i];
        a[i]=t1;
        t1=t2;
    }
    a[a_count-1]=t1;
    d--;
    }
    return a;
}