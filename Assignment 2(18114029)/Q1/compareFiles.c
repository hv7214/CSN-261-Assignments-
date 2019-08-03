#include<stdio.h>
#include <stdlib.h> 
#include<string.h>

void read_file(char filename[], char *output) {

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
}

int main() {

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
}  