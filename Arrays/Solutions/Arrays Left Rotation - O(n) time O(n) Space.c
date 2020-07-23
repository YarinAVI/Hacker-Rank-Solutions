int* rotLeft(int a_count, int* a, int d) {
    if(d==a_count || d>a_count && a_count%d==0 || d==0) return a;
    else if(d>a_count && a_count%d!=0) {
        d%=a_count;
    }
    int t1;
    if(a_count==2) {
        t1=a[a_count-2],a[a_count-2]=a[a_count-1],a[a_count-1]=t1;
        return a;
    }
    int *res= (int*)malloc(a_count*sizeof(int));
    int i=a_count-1,k;

    for(;i>=0;i--) {

    if(i-d>=0) k=i-d;
    else k=a_count-(d-i);
    res[k]=a[i];
    }
    return res;
}