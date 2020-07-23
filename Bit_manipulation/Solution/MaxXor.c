#include <stdlib.h>
#include <stdio.h>
#include <limits.h>




int maxXor(int lo, int hi, int k) {
    int a=lo,b=hi;
    int temp = INT_MIN;
    for(b=hi;b>lo;b--) {
    for(a=lo;a<b;a++) {
        if( (a^b) > temp && (a^b)<k) {
            temp = a^b;
        }
        else if ((a^b)==k) return a^b;
    }
    }
    return temp;
}




int main () {

    printf("%d",maxXor(10,13,50));
}