#include<stdio.h>
#include <stdlib.h> 
#include <math.h>
#include<string.h>

struct key{
    int a;
    int b;
    int n;
};

void read_file(char filename[], char *output) {

    FILE *fp = fopen(filename, "r");
    if(fp) {
        int  i = 0;
        char c;
        while( (c = fgetc(fp)) != EOF ) { 
            output[i] = c;
            i++;
        }
    } 
    else {
        printf("%s", "Failed to open the file!");
    }
}

void Transpose(struct key Key, char text[], char *encrypted_text) {
    
    int length = strlen(text), MAX = ceil((double)length / Key.n) * Key.n, index = 0;    
    char c;
    
    for(int i = length; i < MAX; i++) text[i] = '\0';
    
    for(int i = 1; i <= MAX; i++) {
        index = index % Key.n;
        int x = ((Key.a * index + Key.b) % Key.n) + ((i / Key.n) * Key.n);
        // printf("%d ", ((Key.a * index + Key.b) % Key.n) + (((i-1) / Key.n) * Key.n));
        c = text[x];
        
        encrypted_text[i] = c;
        printf("%c", c);        
        index++;
    }
        // printf("%s\n", encrypted_text);
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
    
    char text[6000], encrypted_text[6000], filename[100];

    strcpy(filename, argv[4]);
    read_file(filename, text);

    Transpose(Key, text, encrypted_text);

    printf("%s\n", encrypted_text);
}