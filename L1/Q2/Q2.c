#include <stdio.h>
#include <stdlib.h>

int *deque, *l ,*r;
int capacity = 1, length = 0;

bool is_full() {
    return length == capacity;
}

void push_front(int x) {
    if(is_full()) expand_size();
    
    if(l == r && capacity == 1) {
        length++;
        l = x;
        return;
    }
    int *temp = (int*)malloc(capacity * sizeof(int));
    memcpy(temp, deque, malloc(capacity * sizeof(int)));
    free(deque);
    deque = (int*)malloc(capacity * sizeof(int));
    deque = x;
    
}
void push_back(int x) {

}
int main(void) {
    deque = (int*)malloc(capacity * sizeof(int));
    *l = deque, *r = deque;
}