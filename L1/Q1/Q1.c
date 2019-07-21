#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int unusedRollNo[100000]; int ptr = 0;    // queue for unused roll no
int G_Roll_no = 101;

struct Node {

    int Roll_No;
    char Name[100];
    char DOB[50];
    char address[200];
    int phn_no;
    struct Node *prev;
    struct Node *next;

};

struct Node *head = NULL;

void insert(int Roll_No, char Name[], char DOB[], char address[], int phn_no) {

    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    
    temp->Roll_No = Roll_No;
    strcpy(temp->Name, Name);
    strcpy(temp->DOB, DOB);
    strcpy(temp->address, address);
    temp->phn_no = phn_no;

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
}

struct Node* search( int Roll_No) {

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
}

void UnusedRollNo_insert(int Roll_No) {

    if(ptr == 9999) { printf("%s\n", "This Roll number will not be preserved as storage is full!"); return; }
    ptr++;
    unusedRollNo[ptr] = Roll_No; 
}

void Delete( int Roll_No) {

    struct Node* ptr = search(Roll_No);

    if(ptr == NULL) { printf("%s", "Roll Number not found\n"); return; }
    
    UnusedRollNo_insert(Roll_No); // pushing deleted roll number in queue

    struct Node *temp1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *temp2 = (struct Node*)malloc(sizeof(struct Node));
    
    temp1 = ptr->prev; 
    temp2 = ptr->next;
    temp1->next = temp2;
    temp2->prev = temp1;
    free(ptr);

    printf("%s", "Successfully Deleted!\n");
}

void Modify(int Roll_No, int field, char val[]) {

    struct Node* ptr = search(Roll_No);

    if (ptr == NULL) { printf("%s", "Roll number not found"); return; }
    
    if (field == 1) strcpy(ptr->Name, val);
    else if (field == 2) strcpy(ptr->DOB, val);
    else if (field == 3) strcpy(ptr->address, val);
    else if (field == 4) ptr->phn_no = atoi(val);
    else {printf("%s\n", "Wrong field!"); return;}

    printf("%s\n", "Successfully Updated!\n");
}

void swap(struct Node* p1, struct Node* p2) {

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

}
void Sort() {

    struct Node *temp1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node *temp2 = (struct Node*)malloc(sizeof(struct Node));
    if(head == NULL) printf("%s", "List length is zero, please insert some elements to sort it!\n");
    temp1 = head;

    int f1 = 1, f2 = 1;
    while(temp1 != head || f1) {
        f1 = 0;
        f2 = 1;
        int r1 = temp1->Roll_No;
        temp2 = temp1->next;
        
        while(temp2 != head || f2) {
            f2 = 0;
            int r2 = temp2->Roll_No;
            if(r1 > r2) swap(temp1, temp2);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    printf("%s", "Sorted!\n");
}

void printList() {

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
} 

int main() {
    // Main Menu loop
    while(1) {
     
        printf("%s", "-----------------MAIN MENU-----------------\n");
        printf("%s", "1. Insert from file(file should be in same folder)\n");
        printf("%s", "2. Modify\n");
        printf("%s", "3. Delete\n");
        printf("%s", "4. Sort\n");
        printf("%s", "5. Print\n");

        int option;
        scanf("%d", &option);

        switch(option) {
            case 1: {
                char Name[100], DOB[50], address[200];
                int phn_no;
                
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
                    // printf("%s %s %s %d\n", Name, DOB, address, phn_no);
                    if(ptr == 0) { 
                        insert(G_Roll_no, Name, DOB, address, phn_no);
                        G_Roll_no++;
                    }
                    else {
                        int rno = unusedRollNo[ptr];
                        unusedRollNo[ptr] = 0;
                        insert(rno , Name, DOB, address, phn_no);
                        ptr--;

                        Sort();
                    }
                    i++;
                }
                printf("%s", "Successfully Inserted!\n");
                break;
            }
            case 2 : {
                char val[100];
                int rno, field;

                printf("%s\n", "Enter the field which you want to change: ");
                printf("%s\n", "1. Name");
                printf("%s\n", "2. DOB");
                printf("%s\n", "3. Address");
                printf("%s\n", "4. Phone Number");
                scanf("%d", &field);

                printf("%s\n", "Enter Roll number: ");
                scanf("%d", &rno);
                
                printf("%s\n", "Enter new value: ");
                scanf("%s", val);

                Modify(rno, field, val);
                break;
            }
            case 3 : {
                int rno;
                printf("%s\n", "Enter Roll number: ");
                scanf("%d", &rno);
                Delete(rno);
                break;
            }
            case 4 : {
                Sort();
                break;
            }        
            case 5 : {
                printList();
                break;
            }
        }
    }            
	return 0;
}
