/**
* @file inverseTranspose.c
* @brief Decrypts the encrypted text
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
* This method will be used to encypted text from outputfile.txt file
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
* This method will be used to write decrypted text to decryptedOutputfile.txt
* @author Harshit Verma
* @date 08/5/2019
*/
void write_file(char *decrypted_text, struct key Key) {
    __clock_t 	start_t, end_t;
	start_t = clock();
    
    FILE *fp = fopen("decryptedOutputfile.txt", "w");

    for(int i = 0; i < row; i++)
        for(int j = 0; j < Key.n; j++) {
            char c = *((decrypted_text + (i * Key.n)) + j);
            fputc(c, fp);
        }
        
    fclose(fp);

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

void generate_decryption_key(struct key *decryption_key, struct key encryption_key) {

    int a = encryption_key.a;
    int b = encryption_key.b;
    int n = encryption_key.n;

    int *_a = &decryption_key->a;
    int *_b = &decryption_key->b;
    int *_n = &decryption_key->n;

    *_a = 0;
    *_b = 0;
    *_n = 5;

    //! Generating a for decryption key 
    while((a * (*_a)) % n != 1) *_a = *_a + 1;
    
    //! Generating b for decryption key
    while((*_a * b + *_b) % n != 0) *_b = *_b + 1;
}

/**
* This method will be used to decrypt the encrypted text
* @author Harshit Verma
* @date 08/5/2019
*/
void decrypt(char *encrypted_text, char *decrypted_text, struct key Key) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    int index;
    for(int i = 0; i < row; i++)
        for(int j = 0; j < Key.n; j++) {
            index = (Key.a * j + Key.b) % Key.n;
            *(decrypted_text + i * Key.n + j) = *(encrypted_text + i * Key.n + index);
        }

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;    
}

int main(int argc, char *argv[]) {
    __clock_t 	start_t, end_t;
	start_t = clock();
    
    if(argc < 5) {
        printf("%s\n", "Not enough arguments");
        return 0;
    }

    struct key Key, Decryption_key;

    Key.a = atoi(argv[1]);
    Key.b = atoi(argv[2]);
    Key.n = atoi(argv[3]);

    char encrypted_text[6000][Key.n], decrypted_text[6000][Key.n], filename[100];

    strcpy(filename, argv[4]);

    read_file(filename, (char *)encrypted_text, Key);

    generate_decryption_key( &Decryption_key, Key);

    decrypt((char *)encrypted_text, (char *)decrypted_text, Decryption_key);
    
    write_file((char *)decrypted_text, Key);
     
    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;	

    printf("CPU Time : %f\n", TOTAL_TIME);      

    return 0;  
}