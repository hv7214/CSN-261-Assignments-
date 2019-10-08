/**
* @file Q3.cpp
* @brief Subarray problem 
*
* @author Harshit Verma
*
* @date 08/31/19
*/

#include<bits/stdc++.h>

using namespace std;

//!Global variables
int n, k, S = 0, l, r, ans=0;
unordered_map<int, int> unmap;

int main() {
	
    cin >> n >> k;
    int a[n];
	
    for (int i = 0; i < n; i++){

		cin >> a[i];
		S += a[i];
		unmap[S] = i;
	}

	S = 0;

	for(int i = 0; i < n; i++){

		if(!(unmap.find(S + k) == unmap.end())){

			if((unmap[S + k] - i + 1) > ans){
				ans = unmap[S + k]-i+1;
				l = i;
				r = unmap[S + k];
			}
		}
		S += a[i];
	}

	if(ans != 0)
		cout <<"Length of longest subarray: " << ans << "\nIndex: "<< l <<" - "<< r << "\n";
	else
		cout << "Not Found"<< "\n";
		
	return 0;
}