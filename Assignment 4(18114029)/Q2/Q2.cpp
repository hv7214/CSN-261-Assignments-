/**
* @file Q2.cpp
* @brief NQueens problem 
*
* @author Harshit Verma
*
* @date 08/31/19
*/

#include <bits/stdc++.h>
using namespace std;


int combination = 0;
int **chessboard;

/**
* This function will be used to check for any conflicting positions, helper function of nqueen
* @author harshit Verma
* @date 08/31/2019
*/
bool checkforattack(int i, int j, int **chessboard, int n){

	for (int x = 0; x < n; x++) {
		if (chessboard[i][x] == 1) return true;
	}

	for (int x = 0; x < n; x++) {
		if (chessboard[x][j] == 1) return true;
	}

	int l = i, r = j;

	if(l == n-1){
			l = n - r - 1;
			r = 0;
	}

	else if(r == n - 1){
			r = n - l- 1;
			l = 0;
	}

	else {
		l = (l + 1 ) % n;
		r = (r + 1) % n;
    }

	while(l != i && r != j) {

		if(chessboard[l][r]==1) return true;
		if(l == n-1){
			l = n - r -1;
			r = 0;
		}
		else if(r == n-1){
			r = n - l- 1;
			l = 0;
		}else{
		l = (l + 1 ) % n;
		r = (r + 1 ) % n;}
	}

	if(l == n-1 || r == 0){
			l = l+r;
			r = l-r;
			l = l-r;
	}

	else {
		l = (l + 1) % n;
		r = (r - 1 + n) % n;
    }

	while(l != i && r != j) {

		if(chessboard[l][r] == 1) return true;

		if(l == n-1 || r == 0){
			l = l + r;
			r = l - r;
			l = l - r;
		} 
        else {
            l = ( l + 1 ) % n;
            r = ( r - 1 + n ) % n;
        }
	}

	return false;
}

/**
* This function will be used to find all possible combination of chessboard
* @author harshit Verma
* @date 08/31/2019
*/
void nQueen(int n, int nq, int ni, int nj){

	if(nq == 0){
		combination++;
		cout << "Combination " << combination << " is :" << "\n";

		for (int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << chessboard[i][j] << " ";
		    }

		    cout << "\n";
	    }

		cout << "\n";
	}

	for (int i = ni; i < n; i++){
		for(int j = (i==ni ? nj:0); j<n; j++){
			if (!checkforattack(i,j,chessboard,n)){
		
				chessboard[i][j]=1;
				nQueen(n, nq-1, i, j);
				chessboard[i][j]=0;
			}
		}
	}
}

int main()
{
	int n;
	cout << "Enter n : ";
    cin >> n;

	cout << "\n";

    //!Initializing the board
	chessboard = new int *[n];
	for(int i = 0; i < n; i++)
	    chessboard[i] = new int[n];

	nQueen(n, n, 0, 0);
	cout<<"Total number of combinations are : " << combination << "\n\n";

	return 0;
}