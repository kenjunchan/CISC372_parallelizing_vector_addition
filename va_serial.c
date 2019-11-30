#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <string.h> 

#define VSIZE 10000000
#define TESTSIZE 10
#define LOWER -100
#define UPPER 100

void readAllFiles(int* arr1, int* arr2, int* arr3, int numOfValues);
void readFile(char* fileName, int* arr, int numOfValues);
void createAllFiles(int numOfValues, int upper, int lower);
void createFile(char* fileName, int numOfValues, int upper, int lower);

int main(int argc, char* argv[]){
    int vsize = VSIZE;
    int testsize = TESTSIZE;
    int lower = LOWER;
    int upper = UPPER;

    
    if(argc == 1){
    }
    else if(argc == 2){
        testsize = TESTSIZE;
        if(strcmp("max", strtok(argv[1], "\n"))){
            testsize = VSIZE;
        }
        else{
            testsize = atoi(argv[1]);
        }
    }
    
    printf("Beginning Vector Addition - Serial, for %d vectors...\n", testsize);

    clock_t begin = clock();
    srand(time(0));
    //createAllFiles(VSIZE, UPPER, LOWER);

    int myid, size;
    int i;
    int *X, *Y, *Z;
    int *results;
    X =  (int *) malloc (vsize*sizeof(int));
    Y =  (int *) malloc (vsize*sizeof(int));
    Z =  (int *) malloc (vsize*sizeof(int));
    results = (int *) malloc (testsize*sizeof(int));

    readAllFiles(X, Y, Z, testsize);
    
    int X_SUMMATION = 0;
    int Y_SUMMATION = 0;
    int Z_SUMMATION = 0;

    for(int i = 0; i < testsize; i++){
        X_SUMMATION = X_SUMMATION + X[i];
    }

    for(int i = 0; i < testsize; i++){
        Y_SUMMATION = Y_SUMMATION + Y[i];
    }

    for(int i = 0; i < testsize; i++){
        Z_SUMMATION = Z_SUMMATION + Z[i];
    }


    printf("Summation of X components: %d\nSummation of Y components: %d\nSummation of Z components: %d\n", X_SUMMATION, Y_SUMMATION, Z_SUMMATION);

    free(X);
    free(Y);
    free(Z);
    free(results);
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n");
    printf("Execution time in seconds: %f\n", time_spent);

    return 0;
}

void readAllFiles(int* arr1, int* arr2, int* arr3, int numOfValues){
    readFile("x.txt", arr1, numOfValues);
    readFile("y.txt", arr2, numOfValues);
    readFile("z.txt", arr3, numOfValues);
}

void readFile(char* fileName, int* arr, int numOfValues){
    FILE *fp;
    fp = fopen(fileName, "r");
    for(int i = 0; i < numOfValues; i++){
        fscanf(fp, "%d", &arr[i]);
        //printf("Reading from %s, value is : %d\n", fileName, arr[i]);
    }
    fclose(fp);    
}

void createAllFiles(int numOfValues, int upper, int lower){
    createFile("x.txt", numOfValues, upper, lower);
    createFile("y.txt", numOfValues, upper, lower);
    createFile("z.txt", numOfValues, upper, lower);
}

void createFile(char* fileName, int numOfValues, int upper, int lower){
    FILE *fp;
    fp = fopen(fileName, "w+");
    for(int i = 0; i < numOfValues; i++){
        fprintf(fp, "%d\n", rand() % (upper - lower + 1) + lower);
    }
    fclose(fp);
}