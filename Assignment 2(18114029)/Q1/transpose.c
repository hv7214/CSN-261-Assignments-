/**
* @file transpose.c
* @brief Encrypts the plaintext 
*
* @author Harshit Verma
*
* @date 08/5/19
*/
#include<stdio.h>
#include <stdlib.h> 
#include<string.h>
#include <time.h>

//! Encryption Key
struct key{
    int a;
    int b;
    int n;
};

int row = 0;
double TOTAL_TIME = 0;

/**
* This method will be used to read text from inputfile,txt
* @author Harshit Verma
* @date 08/5/2019
*/
void read_file(char filename[], char *output, struct key Key) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    FILE *fp = fopen(filename, "r");
    if(fp) {
        int  i = 0, j = 0;
        char c;
        while( (c = fgetc(fp)) != EOF ) { 
            *((output + i * Key.n) + j) = c;
            row = i+1;
            j++;
            if(j == Key.n) {i++; j = 0;}
        }

        fclose(fp);
    } 
    else {
        printf("%s", "Failed to open the file!");
    }

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to write the encrypted text to outputfile.txt 
* @author Harshit Verma
* @date 08/5/2019
*/
void write_file(char *encrypted_text, struct key Key) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    FILE *fp = fopen("outputfile.txt", "w");

    for(int i = 0; i < row; i++)
        for(int j = 0; j < Key.n; j++) {
            char c = *((encrypted_text + (i * Key.n)) + j);
            fputc(c, fp);
        }
        
    fclose(fp);

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}


/**
* This method will be used to encrypt the plaintext 
* @author Harshit Verma
* @date 08/5/2019
*/
void Transpose(struct key Key, char *text, char *encrypted_text) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    char c;
    
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < Key.n; j++) {
            *((encrypted_text + i * Key.n) + j) = *((text +  i * Key.n) + (Key.a * j + Key.b) % Key.n);
        }
    }
}

int main(int argc, char *argv[]) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    if(argc < 5) {
        printf("%s\n", "Not enough arguments");
        return 0;
    }

    struct key Key;
    Key.a = atoi(argv[1]);
    Key.b = atoi(argv[2]);
    Key.n = atoi(argv[3]);
    
    char text[6000][Key.n], encrypted_text[6000][Key.n], filename[100];
    memset(encrypted_text, '\0', sizeof(encrypted_text));
    
    strcpy(filename, argv[4]);

    read_file(filename, (char *)text, Key);

    Transpose(Key, (char *)text, (char *)encrypted_text);
    
    write_file((char *) encrypted_text, Key);

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;	

    printf("CPU Time : %f\n", TOTAL_TIME);
    return 0;
}
