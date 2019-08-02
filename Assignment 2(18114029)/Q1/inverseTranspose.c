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

int main() {

}