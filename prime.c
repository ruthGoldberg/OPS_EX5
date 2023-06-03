#include <stdio.h>

float my_sqrt(int num){
    float sqt=num/2;
    float temp=0;
    while(sqt!=temp){
        temp=sqt;
        sqt=(num/temp+temp)/2;
    }
    return sqt;
}

int isPrime(int num ){
    if (num == 0)
        return 0;
    int sqrt= my_sqrt(num);
    for(int i = 2 ; i<=sqrt ; i++){
        if (num % i == 0)
            return 0;
    }
    return 1;
}