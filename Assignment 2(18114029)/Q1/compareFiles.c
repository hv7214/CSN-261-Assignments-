/**
* @file compareFiles.c
* @brief Compare the plaintext and decrypted text 
*
* @author Harshit Verma
*
* @date 08/5/19
*/

#include<stdio.h>
#include <stdlib.h> 
#include<string.h>
#include <time.h>

double TOTAL_TIME = 0;

/**
* This method will be used to decrypted text and plaintext from their respective files
* @author Harshit Verma
* @date 08/5/2019
*/
void read_file(char filename[], char *output) {
    __clock_t 	start_t, end_t;
	start_t = clock();

    FILE *fp = fopen(filename, "r");
    if(fp) {
        int i = 0;
        char c;
        while( (c = fgetc(fp)) != EOF) {
            if(i >= 1024) {printf("Buffer overflow!\n"); return;}
            if((int)c != 127) { output[i] = c; i++;}
        }
        
        fclose(fp);
    } 
    else {
        printf("%s", "Failed to open the file!\n");
    }

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

int main() {
    __clock_t 	start_t, end_t;
	start_t = clock();

    char filename1[] = "inputfile.txt";
    char filename2[] = "decryptedOutputfile.txt";

    char plaintext[1024], decryptedtext[1024];

    read_file(filename1, plaintext);
    read_file(filename2, decryptedtext);

    if(!strcmp(plaintext, decryptedtext))
        printf("Matched!\n"); 
    else 
        printf("Not matched!\n");

    printf("Plaintext : %s\n", plaintext);        
    printf("Decrypted text : %s\n", decryptedtext);

    end_t = clock();
    TOTAL_TIME += (double)(end_t - start_t) / CLOCKS_PER_SEC;

    printf("CPU Time : %f\n", TOTAL_TIME);      

    return 0;  
}  