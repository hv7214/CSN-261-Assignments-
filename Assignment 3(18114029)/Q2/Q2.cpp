/**
* @file Q2.cpp
* @brief XOR-DP problem 
*
* @author Harshit Verma
*
* @date 08/17/19
*/

#include<bits/stdc++.h>
using namespace std;

/**
* This class is used as node of Linked List
* @author harshit Verma
* @date 08/17/2019
*/
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

/**
* This class is used as Linked List
* @author harshit Verma
* @date 08/17/2019
*/
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

        /**
        * This funtion will be used to insert node in linked list
        * @author harshit Verma
        * @date 08/17/2019
        */
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
        
        /**
        * This funtion will be used to get element at jth index
        * @author harshit Verma
        * @date 08/17/2019
        */
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

        /**
        * This funtion will be used to set data at jth index 
        * @author harshit Verma
        * @date 08/17/2019
        */
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

        /**
        * This funtion will be used to print linked list
        * @author harshit Verma
        * @date 08/17/2019
        */
        void printlist() {
            Node<t>* temp = head;
            while(temp->next != NULL) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << temp->data << "\n";
        }
};

/**
* This funtion will be used to initialize the dp linked list
* @author harshit Verma
* @date 08/17/2019
*/
void init(LinkedList<LinkedList<int>> *a, int n, LinkedList<int> b, LinkedList<pair<int, int>>* pre_ans) {

    for(int i = 0; i < n; i++) {
        LinkedList<int> temp;
        for(int j = 0; j < n; j++) {
            temp.insert(0);
        }
        (*a).insert(temp);
    }
    (*a).getelement(0).setelement(0, b.getelement(0));
    for(int j = 1; j < n; j++) {
        (*a).getelement(0).setelement(j, (*a).getelement(0).getelement(j-1) ^ b.getelement(j));    
        if((*a).getelement(0).getelement(j) == 0) {
                (*pre_ans).insert(make_pair(1, j+1));
            }
    }
}

int main() {
    
    int n;
    cin >> n;

    LinkedList<int> list;
    LinkedList<pair<int, int>> pre_ans;
    LinkedList<pair<int, pair<int, int>>> ans;

    for(int i = 0; i < n; i++) {
        int data; cin >> data;
        list.insert(data);
    }    

    LinkedList<LinkedList<int>> dp;
    //!Initializing dp 2d linkedlist array
    init(&dp, n, list, &pre_ans);        
    
    for(int i = 1; i < n; i++)
        for(int j = i; j < n; j++) {
            dp.getelement(i).setelement(j, dp.getelement(0).getelement(i-1) ^ dp.getelement(0).getelement(j));
            
            if(dp.getelement(i).getelement(j) == 0) {
                pre_ans.insert(make_pair(i+1, j+1));
            }
        }

    for(int i = 0; i < pre_ans.length; i++) {
        
        auto p = pre_ans.getelement(i);
        int I = p.first, K = p.second;

        for(int J = I+1; J <= K; J++) {
            ans.insert(make_pair(I, make_pair(J, K)));
        }
    }

    cout << ans.length << "\n";     

    for(int i = 0; i < ans.length; i++) {

        auto p = ans.getelement(i);
        int I = p.first;
        int J = p.second.first;
        int K = p.second.second;

        cout << "(" << I << "," << J << "," << K << ")" << "\n";
    }
    return 0;
}