#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n, k;
    unordered_map<int, int> unmap;
    int S = 0;
	
    cin >> n >> k;
    int a[n];
	
    for (int i = 0; i < n; i++){

		cin >> a[i];
		S += a[i];
		unmap[S] = i;
	}

	int l, r, ans=0;
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