/**
* @file MAT.c
* @brief Medial axis transformation (MAT) 
*
* @author Harshit Verma
*
* @date 08/5/19
*/
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <stdbool.h> 
#include <string.h>
#include <time.h>

//! Quadtree node
struct node {
    int label;
    int bit;
    int level;
};

int N, n, **a, **msa, top = 0;
struct node quadtree[6000];
double TOTAL_TIME = 0;

/**
* This method will be used to get value of input array from input.txt file
* @author harshit Verma
* @date 08/5/2019
*/
void initialize_n() {
    __clock_t 	start_t, end_t;
	start_t = clock();

    FILE *fp = fopen("input.txt", "r");
    
    if(fp == NULL) {printf("No input.txt file found!\n"); return;}

    char c; int x = 0;
    while( (c = fgetc(fp)) != EOF) {
        if(c == ' ' || c == '\n') continue;
        x++;
    }

    n = sqrt(x);

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to read the array from input.txt file
* @author harshit Verma
* @date 08/5/2019
*/
void read_inputfile() {
    __clock_t 	start_t, end_t;
	start_t = clock();

    FILE *fp = fopen("input.txt", "r");
    
    if(fp == NULL) {printf("No input.txt file found!\n"); return;}

    char c; 
    int i = 1, j = 1;
    while( (c = fgetc(fp)) != EOF) {
        if(c == ' ' || c == '\n') continue;
        a[i][j] = c - '0';
        
        j++;
        if(j == n+1) { j = 1; i++;}
    }

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to normalize the array size to pow of 2.
* @param n the size of input array 
* @author harshit Verma
* @date 08/5/2019
*/
void Preprocess(int n) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    N = pow(2, ceil(log2(n)));

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to check if subarray has same bits 
* @author harshit Verma
* @date 08/5/2019
*/
bool same_bits(int x1, int y1, int x2, int y2) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    int bit = a[x1][y1];

    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++) 
            if(a[i][j] != bit) return false;

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;

    return true;
}

/**
* This method will be used to fill the maximal square array with node value
* @author harshit Verma
* @date 08/5/2019
*/
void fill_msa(int x1, int y1, int x2, int y2, int node) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            msa[i][j] = node;

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;        
}

/**
* This recursive method will be used to set the msa array with node values 
* @author harshit Verma
* @date 08/5/2019
*/
int MAT(int x1, int y1, int x2, int y2, int node, int level) {
     __clock_t 	start_t, end_t;
	start_t = clock();

    if(same_bits(x1, y1, x2, y2)) { 
        fill_msa(x1, y1, x2, y2, node);
        
        quadtree[top].label = node;
        quadtree[top].bit = a[x1][y1];
        quadtree[top].level = level;
        top++;

        return ++node;
    }

    node = MAT(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, node, level+1);
    node = MAT(x1, (y1 + y2) / 2 + 1, (x1 + x2) / 2, y2, node, level+1);
    node = MAT((x1 + x2) / 2 + 1, y1, x2, (y1 + y2) / 2, node, level+1);
    node = MAT((x1 + x2) / 2 + 1, (y1 + y2) / 2 + 1, x2, y2, node, level+1);

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
    
    return node;
}

int main() {
    
    initialize_n();

    Preprocess(n);

    a = (int **) malloc ((N+1) * sizeof(int*));
    for(int i = 0; i < N+1; i++)
        a[i] = (int *) malloc((N+1) * sizeof(int));

    msa = (int **) malloc ((N+1) * sizeof(int*));
    for(int i = 0; i < N+1; i++)
        msa[i] = (int *) malloc((N+1) * sizeof(int));

    read_inputfile();

    int x = MAT(1, 1, N, N, 1, 0);


    while(1) {
        
        printf("------- Medial axis transformation (MAT) -------\n");
        printf("1. Maximal square array\n");
        printf("2. Quadtree\n");
        printf("3. Exit\n");

        int option;
        scanf("%d", &option);

        switch(option) {
            
            case 1 : {
                
                putchar('\n');
                printf("Maximal square array :");
                putchar('\n');
                putchar('\n');
                for(int i = 1; i <= N; i++) {
                    for(int j = 1; j <= N; j++)
                        printf("%d ", msa[i][j]);
                    putchar('\n');
                }
                putchar('\n');
                break;
            }

            case 2 : {
                
                for(int i = 0; i < top; i++) {
                    printf("%d, %d, %d\n", quadtree[i].label, quadtree[i].bit, quadtree[i].level);
                }

                break;
            }

            case 3 : {
                printf("CPU Time : %f\n", TOTAL_TIME);      
                printf("Program terminating..\n");
                return 0;
            }
            default : {
                printf("Wrong choice!");
            }
        }    
    }
}