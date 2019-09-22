#include<bits/stdc++.h>
using namespace std;

int n1, n2;
map<int, int> eq1, eq2, addition, multiply;

void input() {

    cout << "1st expression:" << "\n";
    cout << "Number of terms: ";
    cin >> n1;
    for(int i = 1; i <= n1; i++) {
        int c, p;
        cin >> c >> p;
        eq1[p] = c;
    }

    cout << "2nd expression:" << "\n";
    cout << "Number of terms: ";
    cin >> n2;
    for(int i = 1; i <= n2; i++) {
        int c, p;
        cin >> c >> p;
        eq2[p] = c;
    }
}

void add() {
    
    for(auto t : eq1) {
        int p = t.first;
        int c = t.second;
        addition[p] = c; 
    }
    for(auto t : eq2) {
        int p = t.first;
        int c = t.second;
        addition[p] += c; 
    }
}

void mul() {

     for(auto t1 : eq1) {
        int p1 = t1.first;
        int c1 = t1.second; 
        for(auto t2 : eq2) {
            int p2 = t2.first;
            int c2 = t2.second;
            multiply[p1+p2] += c1*c2;
        }
    }
}

int main() {

    input();
    add();
    mul();

    int opt;

    while(1) {

        cout << "Main Menu" << "\n";
        cout << "1. Add" << "\n";
        cout << "2. Multiply" << "\n";
        cout << "3. Exit" << "\n";
        cin >> opt;

        switch(opt) {
            
            case 1: {
                for(auto t : addition) {
                    int p = t.first;
                    int c = t.second;
                    cout << c << " " << p << "\n";
                }
                break;
            }
            
            case 2: {
                for(auto t : multiply) {
                    int p = t.first;
                    int c = t.second;
                    cout << c << " " << p << "\n";
                }
                break;
            }

            case 3: {
                return 0;
            }
            default: {
                cout << "Wrong option";
            }
        }
    }

}

