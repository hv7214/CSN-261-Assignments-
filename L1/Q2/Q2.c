#include <stdio.h>
#include <stdlib.h>

struct deque {
    int *data;
    int capacity;
    int length;
    int front;
};

void init_deque(struct deque* dq, int init_capacity) {

    dq->capacity = init_capacity;
    dq->length = 0;
    dq->front = 0;

    dq->data = (int*)malloc(sizeof(init_capacity * sizeof(int)));
}

void resize_dbl(struct deque* dq) {
    dq->capacity *=2;

    dq->data = (int*)realloc(dq->data, sizeof(dq->capacity * sizeof(int))); 
}

void resize_half(struct deque* dq) {
    dq->capacity /=2;

    dq->data = (int*)realloc(dq->data, sizeof(dq->capacity * sizeof(int))); 
}

void push_front(struct deque* dq, int x) {

    if(dq->capacity == dq->length) resize_dbl(dq);
    
    int back = dq->front + dq->length - 1;
    if(back < 0) back = 0;

    dq->length++;

    if(dq->length == 1) { dq->data[dq->front] = x; return; }
    
    for(int i = back+1; i >= 1; i--) {
        dq->data[i] = dq->data[i-1];
    }
    dq->data[dq->front] = x;
}

void push_back(struct deque* dq, int x) {
    if(dq->capacity == dq->length) resize_dbl(dq);
    
    int back = dq->front + dq->length - 1;
    if(back < 0) back = 0;

    dq->length++;

    dq->data[back+1] = x;
}

void pop_back(struct deque* dq) {

    if(dq->length == 0) {printf("%s", "Deque is empty!"); return;}
    
    int back = dq->front + dq->length - 1;

    dq->length--;

    dq->data[back] = 0;

    if(dq->length == dq->capacity/2) resize_half(dq);
}

void pop_front(struct deque* dq) {
    if(dq->length == 0) {printf("%s", "Deque is empty!"); return;}
    
    int back = dq->front + dq->length - 1;

    dq->length--;

    int x;
    for(int i = dq->front; i <= back-1; i++) {
        dq->data[i] = dq->data[i+1];
    }
    dq->data[back] = 0;

    if(dq->length == dq->capacity/2) resize_half(dq);
}

void print_dq(struct deque* dq) {

    for(int i = 0; i < dq->length; i++)
        printf("%d ", dq->data[i]);

    putchar('\n');    
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
                push_back(dq, num);
                break;
            }  
            case 2: {
                printf("%s\n", "Enter number: ");
                int num; scanf("%d", &num);
                push_front(dq, num);
                break;
            }
            case 3: {
                pop_back(dq);
                break;
            }  
            case 4: {
                pop_front(dq);
                break;
            }
            case 5: {
                print_dq(dq);    
                break;
            }
            case 6: {
                return 0;
            }
            default:
                printf("%s\n", "Wrong input! Try again.");
        }
    }
}