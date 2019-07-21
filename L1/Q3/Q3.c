#include<stdio.h>
#include <stdlib.h>

int main() {
    int n = 953; int m = 1268;
    int r[n][m]; 
    int y = 0;
    FILE *input = fopen("Q3_ip_Red.dat", "r");
    char c;

    int i = 0; int j = 0;
    while ((c = getc(input)) != EOF) {
        if(c != ',' && c != ' ' && c!= '-') {
            int x = c - '0';
            // j++;
            // if(j == n) { j = 0; i++;}
            // r[i][j] = x;
            printf("%c", c);
            y++;
        }
    }
    fclose(input);
    return 0;
}