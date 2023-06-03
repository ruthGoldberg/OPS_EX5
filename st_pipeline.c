#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "st_pipeline.h"

int seed, N;
pActiveObject obj1, obj2, obj3, obj4;

int main(int argc, char *argv[]) {
    switch (argc) {
        case 2:
            seed = getSeed();
            N = atoi(argv[1]);
            break;

        case 3:
            seed = atoi(argv[2]);
            N = atoi(argv[1]);
            break;

        default:
            printf("usage: ./st_pipline N <SEED>\n");
    }
    srand(seed);


    obj4 = CreateActiveObject(AO4, NULL, N);
    obj3 = CreateActiveObject(AO3, obj4, N);
    obj2 = CreateActiveObject(AO2, obj3, N);
    obj1 = CreateActiveObject(AO1, obj2, N);

    while (1) {
        sleep(1);
        if (!obj1->N && !obj2->N && !obj3->N && !obj4->N) {
            stop(obj1);
            stop(obj2);
            stop(obj3);
            stop(obj4);
            break;
        }
    }
    return 0;
}

int getSeed() {
    return time(NULL);
}

int getRandNum() {
    return rand() % 900000 + 100000;
}

int AO1(void *data) {
    usleep(1000);
    return getRandNum();
}

int AO2(void *data) {
    int number = (int) data;
    printf("%d\n", number);
    if (isPrime(number))
        printf("true\n");
    else printf("false\n");
    number += 11;
    return number;
}

int AO3(void *data) {
    int number = (int) data;
    printf("%d\n", number);
    if (isPrime(number))
        printf("true\n");
    else printf("false\n");
    number -= 13;
    return number;
}

int AO4(void *data) {
    int number = (int) data;
    printf("%d\n", number);
    number += 2;
    printf("%d\n", number);
    return 0;
}

float my_sqrt(int num) {
    float sqt = num / 2;
    float temp = 0;
    while (sqt != temp) {
        temp = sqt;
        sqt = (num / temp + temp) / 2;
    }
    return sqt;
}

int isPrime(int num) {
    if (num == 0)
        return 0;
    int sqrt = my_sqrt(num);
    for (int i = 2; i <= sqrt; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
