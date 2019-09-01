#include<iostream>
using namespace std;


int flag = 0;
bool is_attacked(int i, int j, int **board, int N){
	for (int pointer=0; pointer <N; pointer++) {
		if (board[i][pointer] == 1) return true;
	}

	for (int pointer=0; pointer <N; pointer++) {
		if (board[pointer][j] == 1) return true;
	}

	int p=i,q=j;

	if(p==N-1){
			p=N-q-1;
			q=0;
		}
	else if(q==N-1){
			q=N-p-1;
			p=0;
		}
	else{
		p=(p+1)%N;
		q=(q+1)%N;}

	while(p!=i && q!=j){
		if(board[p][q]==1) return true;
		if(p==N-1){
			p=N-q-1;
			q=0;
		}
		else if(q==N-1){
			q=N-p-1;
			p=0;
		}else{
		p=(p+1)%N;
		q=(q+1)%N;}
	}

	if(p==N-1 || q==0){
			p=p+q;
			q=p-q;
			p=p-q;
		}
	else{
		p=(p+1)%N;
		q=(q-1+N)%N;}

	while(p!=i && q!=j){
		if(board[p][q]==1) return true;
		if(p==N-1 || q==0){
			p=p+q;
			q=p-q;
			p=p-q;
		} else{
		p=(p+1)%N;
		q=(q-1+N)%N;}
	}

	return false;
}

void N_queen(int **board, int N, int number_of_queens, int next_i, int next_j){

	if(number_of_queens==0){
		flag++;
		cout<<"Solution "<<flag<<" is :"<<endl;
		for (int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
		cout<<endl;
	}

	for (int i=next_i; i<N; i++){
		for(int j= i==next_i?next_j:0; j<N; j++){
			if (is_attacked(i,j,board,N)){
			}
			else{
				board[i][j]=1;
				N_queen(board, N, number_of_queens-1, i, j);
				board[i][j]=0;
			}
		}
	}
}


int main()
{
	int n;
	cout<<"Enter n : ";
	cin>>n;
	cout<<"\n";
	int **board;
	board = new int *[n];
	for(int i = 0; i < n; i++)
	    board[i] = new int[n];

	N_queen(board, N, N, 0, 0);
	cout<<"Number of Solutions possible are : "<<flag<<endl<<endl;

	return 0;
}