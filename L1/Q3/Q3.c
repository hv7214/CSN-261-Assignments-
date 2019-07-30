/**
* @file Q3.c
* @brief Image transformer
*
* @author Harshit Verma
*
* @date 07/24/19
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

double TOTAL_TIME = 0;

struct image IMG;

struct pixel{
	int R, G, B;
};

struct image{
	int n, m;
	struct pixel **Pixel;
};

/**
* This method will be used to write data in o/p file
* @author harshit Verma
* @date 7/24/2019
*/

double Write_red_dat() {
	__clock_t start_t, end_t;
	start_t = clock();	
	
	FILE *fp = fopen("Q3_Output/Q3_op_Red.dat", "w");
	if(fp == NULL) {printf("FILE NOT FOUND"); return 0;}

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) 
			fprintf(fp, "%d,", IMG.Pixel[i][j].R);
	
	fclose(fp);	

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to write data in o/p file
* @author harshit Verma
* @date 7/24/2019
*/
double Write_green_dat() {
	__clock_t start_t, end_t;
	start_t = clock();	

	FILE *fp = fopen("Q3_Output/Q3_op_Green.dat", "w");
	if(fp == NULL) {printf("FILE NOT FOUND"); return 0;}

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) 
			fprintf(fp, "%d,", IMG.Pixel[i][j].G);

	fclose(fp);	

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to write data in o/p file
* @author harshit Verma
* @date 7/24/2019
*/
double Write_blue_dat() {
	__clock_t start_t, end_t;
	start_t = clock();	

	FILE *fp = fopen("Q3_Output/Q3_op_Blue.dat", "w");
	if(fp == NULL) {printf("FILE NOT FOUND"); return 0;}

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) 
			fprintf(fp, "%d,", IMG.Pixel[i][j].B);

	fclose(fp);		

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to read data in o/p file
* @author harshit Verma
* @date 7/24/2019
*/
double Read_red() {
	__clock_t start_t, end_t;
	start_t = clock();

	FILE *fp = fopen("Q3_Input/Q3_ip_Red.dat", "r");
	if(fp == NULL) {printf("FILE NOT FOUND"); return 0;}

    char buff[12000], *token;
    int i = 0, j = 0, m = IMG.m, n = IMG.n;

    while(fgets(buff, 12000, fp) != NULL) {
    	token = strtok(buff, ",");
    	for(int k = 0; k < 6000; k++) {
    		if(token != NULL) { IMG.Pixel[i][j].R = atoi(token); j++;}

    		token = strtok(NULL, ",");
    		if(j == m) { j = 0; i++; }
    		if(i == n) break;
    	}
    }

	fclose(fp);

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to read data in o/p file
* @author harshit Verma
* @date 7/24/2019
*/
double Read_green() {
	__clock_t start_t, end_t;
	start_t = clock();
	
	FILE *fp = fopen("Q3_Input/Q3_ip_Green.dat", "r");
	if(fp == NULL) {printf("FILE NOT FOUND"); return 0;}

    char buff[12000], *token;
    int i = 0, j = 0, m = IMG.m, n = IMG.n;

    while(fgets(buff, 12000, fp) != NULL) {
    	token = strtok(buff, ",");
    	for(int k = 0; k < 6000; k++) {
    		if(token != NULL) { IMG.Pixel[i][j].G = atoi(token); j++;}

    		token = strtok(NULL, ",");
    		if(j == m) { j = 0; i++; }
    		if(i == n) break;
    	}
    }

	fclose(fp);
	
	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to read data in o/p file
* @author harshit Verma
* @date 7/24/2019
*/
double Read_blue() {
	__clock_t start_t, end_t;
	start_t = clock();

	FILE *fp = fopen("Q3_Input/Q3_ip_Blue.dat", "r");
	if(fp == NULL) {printf("FILE NOT FOUND"); return 0;}

    char buff[12000], *token;
    int i = 0, j = 0, m = IMG.m, n = IMG.n;

    while(fgets(buff, 12000, fp) != NULL) {
    	token = strtok(buff, ",");
    	for(int k = 0; k < 6000; k++) {
    		if(token != NULL) { IMG.Pixel[i][j].B = atoi(token); j++;}

    		token = strtok(NULL, ",");
    		if(j == m) { j = 0; i++; }
    		if(i == n) break;
    	}
    }
	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to remove green shade
* @author harshit Verma
* @date 7/24/2019
*/
double Remove_Green() {
	__clock_t start_t, end_t;
	start_t = clock();

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) {
			int R = IMG.Pixel[i][j].R;
			int *G = &IMG.Pixel[i][j].G;
			int B = IMG.Pixel[i][j].B;

			if(*G > R && *G > B) *G = 0;       // remove green shade
		}
	Write_green_dat();

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to remove red shade
* @author harshit Verma
* @date 7/24/2019
*/
double Remove_Red() {
	__clock_t start_t, end_t;
	start_t = clock();

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) {
			int *R = &IMG.Pixel[i][j].R;
			int G = IMG.Pixel[i][j].G;
			int B = IMG.Pixel[i][j].B;

			if(*R > G && *R > B) *R = 0;       // remove red shade
		}
	Write_red_dat();	

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to remove blue shade
* @author harshit Verma
* @date 7/24/2019
*/
double Remove_Blue() {
	__clock_t start_t, end_t;
	start_t = clock();

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) {
			int R = IMG.Pixel[i][j].R;
			int G = IMG.Pixel[i][j].G;
			int *B = &IMG.Pixel[i][j].B;

			if(*B > R && *B > G) *B = 0;       // remove blue shade
			
		}
	Write_blue_dat();	

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;
}

/**
* This method will be used to remove preserve green shade
* @author harshit Verma
* @date 7/24/2019
*/
double Preserve_Green() {
	__clock_t start_t, end_t;
	start_t = clock();

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) {
			int *R = &IMG.Pixel[i][j].R;
			int G = IMG.Pixel[i][j].G;
			int *B = &IMG.Pixel[i][j].B;

			if(G < *R && *R > *B) *R = 0;      // Red shade
			if(G < *B && *R < *B) *B = 0;      // Blue shade  
		}
	Write_green_dat();

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to remove preserve red shade
* @author harshit Verma
* @date 7/24/2019
*/
double Preserve_Red() {
	__clock_t start_t, end_t;
	start_t = clock();

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) {
			int R = IMG.Pixel[i][j].R;
			int *G = &IMG.Pixel[i][j].G;
			int *B = &IMG.Pixel[i][j].B;

			if(R < *G && *B < *G) *G = 0;
			if(R < *B && *G < *B) *B = 0;       
		}
	Write_red_dat();

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to remove preserve blue shade
* @author harshit Verma
* @date 7/24/2019
*/
double Preserve_Blue() {
	__clock_t start_t, end_t;
	start_t = clock();

	for(int i = 0; i < IMG.n; i++)
		for(int j = 0; j < IMG.m; j++) {
			int *R = &IMG.Pixel[i][j].R;
			int *G = &IMG.Pixel[i][j].G;
			int B = IMG.Pixel[i][j].B;

			if(B < *R && *G < *R) *R = 0;
			if(B < *G && *R < *G) *G = 0;       
		}
	Write_blue_dat();		

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to print pixel value
* @author harshit Verma
* @date 7/24/2019
*/
double Pixel_Value(int x, int y) {
	__clock_t start_t, end_t;
	start_t = clock();

	x--; y--; 
	int R = IMG.Pixel[x][y].R;
	int G = IMG.Pixel[x][y].G;
	int B = IMG.Pixel[x][y].B;

	printf("%d %d %d\n", R, G, B);

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to print color component array
* @author harshit Verma
* @param color which color component to print
* @date 7/24/2019
*/
double print_component(char color[]) {
	__clock_t start_t, end_t;
	start_t = clock();

	if(color[0] == 'R') {
		for(int i = 0; i < IMG.n; i++)
			for(int j = 0; j < IMG.m; j++) {
				printf("%d ", IMG.Pixel[i][j].R);
			}
	}
	
	else if(color[0] == 'G') {
		for(int i = 0; i < IMG.n; i++)
			for(int j = 0; j < IMG.m; j++) {
				printf("%d ", IMG.Pixel[i][j].G);
			}
	}

	else if(color[0] == 'B') {
		for(int i = 0; i < IMG.n; i++)
			for(int j = 0; j < IMG.m; j++) {
				printf("%d ", IMG.Pixel[i][j].B);
			}
	}

	else {
		printf("Wrong color component!!");
	}

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

/**
* This method will be used to initialize image
* @author harshit Verma
* @param color which color component to print
* @date 7/24/2019
*/
double init_image(int n, int m) {
	__clock_t start_t, end_t;
	start_t = clock();

	IMG.n = n;
	IMG.m = m;

	IMG.Pixel = (struct pixel **)malloc( n * sizeof(struct pixel *));
	for(int i = 0; i < n; i++) {
		IMG.Pixel[i] = (struct pixel*)malloc(m * sizeof(struct pixel));
	}
	Read_red(IMG);
	Read_green(IMG);
	Read_blue(IMG);

	Write_blue_dat();
	Write_green_dat();
	Write_red_dat();

	end_t = clock();

	return (double)(end_t - start_t) / CLOCKS_PER_SEC;	
}

int main() {
	
	int n = 953, m = 1268;
    init_image(n, m);

	while(1) {

		printf("-----------MAIN MENU-----------\n");
		printf("%s", "1. Remove red shades\n");
        printf("%s", "2. Remove green shades\n");
        printf("%s", "3. Remove blue shades\n");
        printf("%s", "4. Preserve red\n");
        printf("%s", "5. Preserve green\n");
        printf("%s", "6. Preserve blue\n");
		printf("%s", "7. Pixel Value\n");
		printf("%s", "8. Print color component values\n");
		printf("%s", "9. Exit\n");

        int option;
        scanf("%d", &option);

		switch(option) {
			
			case 1 : {
				TOTAL_TIME += Remove_Red();
				printf("Done successfully.\n");
				break;
			}
			case 2 : {
				TOTAL_TIME += Remove_Green();
				printf("Done successfully.\n");
				break;
			}
			case 3 : {
				TOTAL_TIME += Remove_Blue();
				printf("Done successfully.\n");
				break;
			}
			case 4 : {
				TOTAL_TIME += Preserve_Red();
				printf("Done successfully.\n");
				break;
			}
			case 5 : {
				TOTAL_TIME += Preserve_Green();
				printf("Done successfully.\n");
				break;
			}
			case 6 : {
				TOTAL_TIME += Preserve_Blue();
				printf("Done successfully.\n");
				break;
			}
			case 7 : {
				int x, y;
				scanf("%d %d", &x, &y);
				TOTAL_TIME += Pixel_Value(x, y);
				printf("Done successfully.\n");
				break;
			}
			case 8 : {
				printf("Which component you want to print:\n");
				printf("R / G / B\n");
				
				char color[1];
				scanf("%s", color);
				TOTAL_TIME += print_component(color);

				break;
			}
			case 9 :
				printf("CPU Time: ");
				printf("%f", TOTAL_TIME);
				return 0;
				break;
		
			default:
				printf("Wrong input!\n");
		}

	}

	printf("%f", TOTAL_TIME);

    return 0;
}