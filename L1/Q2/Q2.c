/**
* @file Q2.c
* @brief Dynamic deque
*
* @author Harshit Verma
*
* @date 07/24/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double TOTAL_TIME = 0;

struct deque {
    int *data;
    int capacity;
    int length;
    int front;
};

/**
* This method will be used to initiate the deque
* @param dq deque
* @param init capacity Initial Capacity
* @author harshit Verma
* @date 7/24/2019
*/
double init_deque(struct deque* dq, int init_capacity) {
    __clock_t start_t, end_t;
	start_t = clock();

    dq->capacity = init_capacity;
    dq->length = 0;
    dq->front = 0;

    dq->data = (int*)malloc(sizeof(init_capacity * sizeof(int)));   

    end_t = clock();
    return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to increase the size of deque to double
* @param dq deque
* @author harshit Verma
* @date 7/24/2019
*/
double resize_dbl(struct deque* dq) {
    __clock_t start_t, end_t;
	start_t = clock();

    dq->capacity *=2;

    dq->data = (int*)realloc(dq->data, sizeof(dq->capacity * sizeof(int))); 

    end_t = clock();
    return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to decrease the size of deque by half
* @param dq deque
* @author harshit Verma
* @date 7/24/2019
*/
double resize_half(struct deque* dq) {
    __clock_t start_t, end_t;
	start_t = clock();

    dq->capacity /=2;

    dq->data = (int*)realloc(dq->data, sizeof(dq->capacity * sizeof(int))); 

    end_t = clock();
    return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to push data to front
* @param dq deque
* @param x value to be pushed
* @author harshit Verma
* @date 7/24/2019end_t = clock();
*/
double push_front(struct deque* dq, int x) {
    __clock_t start_t, end_t;
	start_t = clock();

    if(dq->capacity == dq->length) resize_dbl(dq);
    
    int back = dq->front + dq->length - 1;
    if(back < 0) back = 0;

    dq->length++;

    if(dq->length == 1) { dq->data[dq->front] = x; return 0; }
    
    for(int i = back+1; i >= 1; i--) {
        dq->data[i] = dq->data[i-1];
    }
    dq->data[dq->front] = x;

    end_t = clock();
    return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to push data at back
* @param dq deque
* @param x value to be pushed
* @author harshit Verma
* @date 7/24/2019
*/
double push_back(struct deque* dq, int x) {
    __clock_t start_t, end_t;
	start_t = clock();

    if(dq->capacity == dq->length) resize_dbl(dq);
    
    int back = dq->front + dq->length - 1;
    if(back < 0) back = 0;

    if(dq->length == 0) dq->data[back] = x;
    else dq->data[back+1] = x;

    dq->length++;

    end_t = clock();
    return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to pop data from back
* @param dq deque
* @author harshit Verma
* @date 7/24/2019
*/
double pop_back(struct deque* dq) {
    __clock_t start_t, end_t;
	start_t = clock();

    if(dq->length == 0) {printf("%s", "Deque is empty!"); return 0;}
    
    int back = dq->front + dq->length - 1;

    dq->length--;

    dq->data[back] = 0;

    if(dq->length == dq->capacity/2) resize_half(dq);

    end_t = clock();
    return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to pop data from front
* @param dq deque
* @author harshit Verma
* @date 7/24/2019
*/
double pop_front(struct deque* dq) {
    __clock_t start_t, end_t;
	start_t = clock();

    if(dq->length == 0) {printf("%s", "Deque is empty!"); return 0;}
    
    int back = dq->front + dq->length - 1;

    dq->length--;

    int x;
    for(int i = dq->front; i <= back-1; i++) {
        dq->data[i] = dq->data[i+1];
    }
    dq->data[back] = 0;

    if(dq->length == dq->capacity/2) resize_half(dq);

    end_t = clock();
    return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to print deque
* @param dq deque
* @author harshit Verma
* @date 7/24/2019
*/
double print_dq(struct deque* dq) {
    __clock_t start_t, end_t;
	start_t = clock();

    for(int i = 0; i < dq->length; i++)
        printf("%d ", dq->data[i]);

    putchar('\n');    

    end_t = clock();
    return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

int main(void) {

    struct deque* dq = (struct deque*)malloc(sizeof(struct deque));
    init_deque(dq, 1);
    
    while(1) { 
        printf("%s\n", "-----------------MAIN-MENU-----------------");
        printf("%s\n", "1. Push back");
        printf("%s\n", "2. Push front");
        printf("%s\n", "3. Pop back");
        printf("%s\n", "4. Pop front");
        printf("%s\n", "5. Print");
        printf("%s\n", "6. Exit");

        int option; 
        scanf("%d", &option);

        switch(option) {
            case 1: {
                printf("%s\n", "Enter number: ");
                int num; scanf("%d", &num);
                TOTAL_TIME += push_back(dq, num);
                break;
            }  
            case 2: {
                printf("%s\n", "Enter number: ");
                int num; scanf("%d", &num);
                TOTAL_TIME += push_front(dq, num);
                break;
            }
            case 3: {
                TOTAL_TIME += pop_back(dq);
                break;
            }  
            case 4: {
                TOTAL_TIME += pop_front(dq);
                break;
            }
            case 5: {
                TOTAL_TIME += print_dq(dq);    
                break;
            }
            case 6: {
                printf("%f", TOTAL_TIME);
                return 0;
            }
            default:
                printf("%s\n", "Wrong input! Try again.");
        }
    }

}