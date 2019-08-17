#include<bits/stdc++.h>
using namespace std;

template<class t>
class Node{

    public:
        Node<t>* next;
        t data;

        Node(t x) {
            next = NULL;
            data = x;
        }
};

template<class t>
class LinkedList {

    public:
        Node<t> *head;
        Node<t> *tail;
        int length;

        LinkedList() {
            head = NULL;
            tail = NULL;
            length = 0;
        } 

        void insert(t x) {

            Node<t>* temp = new Node<t>(x);

            if(head == NULL) {
                head = temp;
                tail = temp;
            } else {
                tail->next = temp;
                tail =temp;
            }

            length++;
        };   

        t getelement(int j) {
            int index = 0;
            Node<t>* temp = head;

            while(temp->next != NULL) {
                if(index == j) {
                    return temp->data;
                }
                index++;
                temp = temp->next;
            }
            return tail->data;
        }

        void setelement(int j, t x) {
            int index = 0;
            Node<t>* temp = head;

            while(temp->next != NULL) {
                if(index == j) {
                    temp->data = x;
                    break;
                }
                index++;
                temp = temp->next;
            }

            tail->data = x;
        }

        void printlist() {
            Node<t>* temp = head;
            while(temp->next != NULL) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << temp->data << "\n";
        }
};

void init(LinkedList<int> *a, int n, LinkedList<int> b, LinkedList<pair<int, int>>* pre_ans) {

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            a[i].insert(0);
        }

    a[0].setelement(0, b.getelement(0));
    for(int j = 1; j < n; j++) {
        a[0].setelement(j, a[0].getelement(j-1) ^ b.getelement(j));    
        if(a[0].getelement(j) == 0) {
                (*pre_ans).insert(make_pair(1, j+1));
            }
    }
}

int main() {
    
    int n;
    cin >> n;

    LinkedList<int> list;
    LinkedList<pair<int, int>> pre_ans;

    for(int i = 0; i < n; i++) {
        int data; cin >> data;
        list.insert(data);
    }    

    LinkedList<int> dp[n];
    //!Initializing dp 2d linkedlist array
    init(dp, n, list, &pre_ans);        
    
    for(int i = 1; i < n; i++)
        for(int j = i; j < n; j++) {
            dp[i].setelement(j, dp[0].getelement(i-1) ^ dp[0].getelement(j));
            
            // cout << dp[i].getelement(j) << " ";
            if(dp[i].getelement(j) == 0) {
                pre_ans.insert(make_pair(i+1, j+1));
            }
        }

    for(int i = 0; i < pre_ans.length; i++) {
        
        auto p = pre_ans.getelement(i);
        int I = p.first, K = p.second;

        for(int J = I+1; J <= K; J++) 
            cout << "(" << I << "," << J << "," << K << ")" << "\n";
    }    
    
    return 0;
}