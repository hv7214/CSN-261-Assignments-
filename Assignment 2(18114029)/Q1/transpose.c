#include<stdio.h>
#include <stdlib.h> 
#include <math.h>
#include<string.h>

struct key{
    int a;
    int b;
    int n;
};

int row = 0;

void read_file(char filename[], char *output, struct key Key) {

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
}

void write_file(char *encrypted_text, struct key Key) {
 
    FILE *fp = fopen("outputfile.txt", "w");

    for(int i = 0; i < row; i++)
        for(int j = 0; j < Key.n; j++) {
            char c = *((encrypted_text + (i * Key.n)) + j);
            fputc(c, fp);
        }
        
    fclose(fp);
}

void Transpose(struct key Key, char *text, char *encrypted_text) {
    
    char c;
    
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < Key.n; j++) {
            *((encrypted_text + i * Key.n) + j) = *((text +  i * Key.n) + (Key.a * j + Key.b) % Key.n);
        }
    }
}

int main(int argc, char *argv[]) {

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
}
