#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std ;

class Node;

class S{
    public:
    Node* s[10000];
    int size =0;
    S ()
    {
        for(int i = 0 ; i<10000;i++)
        {
            s[i]=NULL;
        }
    }

    int t = -1;

    void push(Node* x)
    {
        t++;
        s[t] = x;
        size++;
    }

    Node*  pop()
    {
        Node* dummy = s[t];
        t--;
        size--;
        return dummy;
    }

    bool is_empty()
    {
        if(t==-1)
        {
            return true;
        }
        return false;
    }

};

class Node
{
public:
    int k;
    bool is_root =true;
    int degree =0;
    Node(int x)
    {
        k = x;
    }
    S *children = new S();
};

void heap_init(S* root)
{
 
    if(root->size<=1)
    {
        return;
    }
    bool f = true;
    while(f)
    {
        if(root->s[root->t]->degree!=root->s[root->t-1]->degree)
        {
            f = false;
        }
        else if (root->s[root->t]->k <= root->s[root->t - 1]->k)
        {
            root->s[root->t]->children->push(root->s[root->t - 1]);
            root->s[root->t]->degree++;
            Node *dummy1 = root->pop();
            Node *dummy2 = root->pop();
            root->push(dummy1);
            dummy1->is_root=true;
        }
        else
        {
            root->s[root->t - 1]->children->push(root->s[root->t]);
            root->s[root->t - 1]->degree++;
            Node *dummy1 = root->pop();
            dummy1->is_root=false;
                }

        if (root->size <= 1)
        {
            return;
        }
    }
}

void output_binomialHeap(Node*node,string s,ofstream&out)
{
    cout<<node->k<<" ";
    string space = "";
    while(!node->children->is_empty())
    {
        Node * dummy2 = node->children->pop();
        s = space + to_string(node->k) + "--" + to_string(dummy2->k) + ";";
        out << s << endl;
        output_binomialHeap(dummy2,s,out);
    }

    if(node->children->is_empty()&&node->is_root)
    {
        s = space + to_string(node->k)+";";
        out<<s<<endl;
    }

}

int n;
S* root = new S();


void gen_output() {
    int l = root->size;
    ofstream out;
    out.open("./output.dot");
    string s;
    s = "graph {";
    out << s << endl;
    cout<<"Order :    Heap elements"<<endl;
    for(int i =0 ;i<l ; i++)
    {
        Node * dummy = root->pop();
        
        cout<<dummy->degree<<"             ";
        output_binomialHeap(dummy,s,out);
        cout<<endl;
    }
    
    s = "}";
    out << s << endl;
    system("dot -Tps ./output.dot -o q2.pdf");
}

int main()
{
    cin>>n;

    int a[n];

    for(int i =0 ; i< n ;i++) {
        int x;
        cin>>x;
        Node* node = new Node(x);
        root->push(node);
        heap_init(root);

    }
  
    gen_output();
}