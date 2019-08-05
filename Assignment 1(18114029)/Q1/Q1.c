/**
* @file Q1.c
* @brief Student management system
*
* @author Harshit Verma
*
* @date 07/24/19
*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

double TOTAL_TIME = 0;

//! queue for unused roll no
int unusedRollNo[100000]; 
int ptr = 0;     

//! Global Roll number
int G_Roll_no = 101;     

//! Student node
struct Node {

    int Roll_No;
    char Name[100];
    char DOB[50];
    char address[200];
    long long int phn_no;
    struct Node *prev;
    struct Node *next;

};

//! Head ptr of chain
struct Node *head = NULL;

//!Loader array, storing student details
struct Node Loader[13]; 

/**
* This method will be used to load data from csv file
* @author Harshit Verma
* @date 7/24/2019
*/
void Load_details() {
    __clock_t 	start_t, end_t;
	start_t = clock();

    char Name[100], DOB[50], address[200];
    long long int phn_no; int rno;

    char filename[31] = "StudentData2.csv";
    char buff[1024];

    FILE *fp = fopen(filename, "r");
    fgets(buff, sizeof(buff), fp); // to skip column names
    int i = 1;
    while(i <= 13) { 
        fgets(buff, sizeof(buff), fp);
        char *token = strtok(buff, ","); // Sr.no column val
        token = strtok(NULL, ",");
        strcpy(Name, token);
        token = strtok(NULL, ",");
        strcpy(DOB, token);
        token = strtok(NULL, ",");  
        strcpy(address, token);
        token = strtok(NULL, ",");
        phn_no = atoi(token);

        if(ptr == 0) { 
            rno = G_Roll_no;
            G_Roll_no++;
        }
        else {
            rno = unusedRollNo[ptr];
            unusedRollNo[ptr] = 0;
            ptr--;
        }

        strcpy(Loader[i-1].Name, Name);
        strcpy(Loader[i-1].address, address);
        strcpy(Loader[i-1].DOB, DOB);
        Loader[i-1].phn_no = phn_no;
        Loader[i-1].Roll_No = rno;
        
        i++;
    }

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

void swap(struct Node* p1, struct Node* p2) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    char n[50], d[10], a[100];int  p, r;
    strcpy(n, p1->Name);
    strcpy(a, p1->address);
    strcpy(d, p1->DOB);
    p = p1->phn_no;
    r = p1->Roll_No;

    strcpy(p1->Name, p2->Name);
    strcpy(p1->address, p2->address);
    strcpy(p1->DOB, p2->DOB);
    p1->phn_no = p2->phn_no;
    p1-> Roll_No = p2->Roll_No;

    strcpy(p2->Name, n);
    strcpy(p2->address, a);
    strcpy(p2->DOB, d);
    p2->phn_no = p;
    p2->Roll_No = r; 

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to sort student by names
* @author harshit Verma
* @date 7/24/2019
*/
void sort_a_z() {
    __clock_t 	start_t, end_t;
	start_t = clock();

    struct Node *temp1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *temp2 = (struct Node*)malloc(sizeof(struct Node));
    if(head == NULL) printf("%s", "List length is zero, please insert some elements to sort it!\n");
   
    temp1 = head;

    int flag = 1;
    while(temp1 != head || flag) {
        flag = 0;
        char n1[1024], n2[1024];

        strcpy(n1, temp1->Name);

        temp2 = temp1->next;
        
        while(temp2 != head) {
            strcpy(n2, temp2->Name);
            if(strcmp(n1, n2) > 0) { swap(temp1, temp2);  strcpy(n1, n2);}
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    printf("%s", "Sorted!\n");

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to insert data by row number
* @author harshit Verma
* @param row row number
* @date 7/24/2019
*/
void insert(int row) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    struct Node *temp = (struct Node*) malloc (sizeof(struct Node));
    
    
    if(ptr == 0) { temp->Roll_No = Loader[row-2].Roll_No; }
    else { temp->Roll_No = unusedRollNo[ptr]; ptr--;}

    strcpy(temp->Name, Loader[row-2].Name);
    strcpy(temp->DOB, Loader[row-2].DOB);
    strcpy(temp->address, Loader[row-2].address);
    temp->phn_no = Loader[row-2].phn_no;

    if(head == NULL) {
        temp->next = temp;
        temp->prev = temp;
        head = temp;
        return;
    }
    struct Node* last = head->prev;   
    head->prev = temp;
    temp->next = head;
    last->next = temp;
    temp->prev = last;
    
    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to search student by roll number
* @author harshit Verma
* @param Roll_no search by roll number
* @date 7/24/2019
*/
struct Node* search(int Roll_No) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    if(head == NULL) return NULL;

    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp = head;
    int f = 1;

    while(temp != head || f) {
        f = 0;
        int rno = temp->Roll_No;
        if(rno == Roll_No) return temp;
        temp = temp->next; 
    }
    return NULL;

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to insert deleted roll number in queue
* @param Roll_No Roll number to insert
* @author harshit Verma
* @date 7/24/2019
*/
void UnusedRollNo_insert(int Roll_No) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    if(ptr == 9999) { printf("%s\n", "This Roll number will not be preserved as storage is full!"); return; }
    ptr++;
    unusedRollNo[ptr] = Roll_No; 

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to delete student by roll number
* @param Roll_No Student's roll number
* @author harshit Verma
* @date 7/24/2019
*/
void Delete(int Roll_No) {
     __clock_t 	start_t, end_t;
	start_t = clock();

    struct Node* ptr = search(Roll_No);

    if(ptr == NULL) { printf("%s", "Roll Number not found\n"); return; }

    //! pushing deleted roll number in queue 
    UnusedRollNo_insert(Roll_No); 

    struct Node *temp1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *temp2 = (struct Node*)malloc(sizeof(struct Node));
    
    temp1 = ptr->prev; 
    temp2 = ptr->next;
    temp1->next = temp2;
    temp2->prev = temp1;
    if(ptr == head) head = temp2; 
    
    free(ptr);

    printf("%s", "Successfully Deleted!\n");

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to modify student's details by roll number
* @param Roll_No Student's roll number  
* @author harshit Verma
* @date 7/24/2019
*/
void Modify(int Roll_No) {
     __clock_t 	start_t, end_t;
	start_t = clock();

    char val[100];
    int field;

    printf("%s\n", "Enter the field which you want to change: ");
    printf("%s\n", "1. Name");
    printf("%s\n", "2. DOB");
    printf("%s\n", "3. Address");
    printf("%s\n", "4. Phone Number");
    scanf("%d", &field);
    
    printf("%s\n", "Enter new value: ");
    scanf("%s", val);
    struct Node* ptr = search(Roll_No);

    if (ptr == NULL) { printf("%s", "Roll number not found"); return; }
    
    if (field == 1) strcpy(ptr->Name, val);
    else if (field == 2) strcpy(ptr->DOB, val);
    else if (field == 3) strcpy(ptr->address, val);
    else if (field == 4) ptr->phn_no = atoi(val);
    else {printf("%s\n", "Wrong field!"); return;}

    printf("%s\n", "Successfully Updated!\n");

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to print student's details
* @param Roll_No Student's roll number to delete 
* @author harshit Verma
* @date 7/24/2019
*/
void printList() {
     __clock_t 	start_t, end_t;
	start_t = clock();

    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp = head;    
    int f = 1;
    while(temp != head || f) {
        f = 0;
        printf("%s\n", temp->Name);
        printf("%d\n", temp->Roll_No);
        printf("%s\n\n", temp->DOB);
        temp = temp->next;
    }

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
} 

int main() {
    
    Load_details();

    while(1) {
     
        printf("%s", "-----------------MAIN MENU-----------------\n");
        printf("%s", "1. Enter row number\n");
        printf("%s", "2. Modify\n");
        printf("%s", "3. Delete\n");
        printf("%s", "4. Sort\n");
        printf("%s", "5. Print\n");
        printf("%s", "6. Exit\n");

        int option;
        scanf("%d", &option);

        switch(option) {

            case 1: {
                int n;
                printf("Enter your row number : " );
                scanf("%d", &n);
                insert(n);
                break;
            }
            case 2 : {
                int n;
                printf("Enter Roll number : " );
                scanf("%d", &n);
                Modify(n);
                break;
            }
            case 3: {
                int n;
                printf("Enter Roll number : " );
                scanf("%d", &n);
                Delete(n);
                break;
            }
            case 4: {
                sort_a_z();
                break;
            }
            case 5: {
                printList();
                break;
            }
            case 6: {
                printf("CPU Time: ");
                printf("%f\n", TOTAL_TIME);
                return 0;
            }
        }
    }        
}
