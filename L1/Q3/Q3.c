#include<stdio.h>
#include <stdlib.h>

int main() {
    int n = 953; int m = 1268;
    int r[n][m]; 
    FILE *input = fopen("Q3_ip_Red.dat", "r");

    char buff[2500000];
    fgets(buff, 2500000, input);
    printf("%s", buff);
    fclose(input);
    return 0;
}