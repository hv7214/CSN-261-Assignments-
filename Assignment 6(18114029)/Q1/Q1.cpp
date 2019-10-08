#include <iostream>
#include <chrono>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std ;

class Node{
    public:
    int v;
    Node* next = NULL;
    Node(int n)
    {
        v=n;
    }

};

void addEdge(Node**a  , int n , int v1 ,int v2)
{
    Node* n1 = new Node(v1);
    Node* n2 = new Node(v2);

    Node * temp = a[v1];
    if(temp==NULL)
    {   
        a[v1] = n2 ;
    }
    else
    {
        while(temp->next!=NULL)
        {   
             temp =temp->next;
        }
         temp->next = n2;
    }
    temp = a[v2];
    if (temp == NULL)
    {

         a[v2] = n1;
    }
     else
        {
            while (temp->next != NULL)
            {
            temp = temp->next;
            }
        temp->next = n1;
        }
}

void printAdjList(Node**a , int n)
{
    for (int i = 0; i < n; i++)
    {
        Node *temp = a[i];

        while (temp != NULL)
        {
            cout << i << "--" << temp->v << endl;
            temp = temp->next;
        }
    }
}

void DFS(int v , bool* f , Node**a,int n)
{
    f[v]=true;
    cout<<char(v+'A')<<" ";
    Node* temp = a[v];
    while(temp!=NULL)
    {   if(!f[temp->v])
        {DFS(temp->v,f,a,n);}
        temp = temp->next;
    }

}
void test_dfs(Node**a , int n,int*mark)
{
    bool f[n] ;
    for(int i = 0 ; i< n ; i++)
    {
        f[i] = false;
    }

    for(int i = 0 ; i< n ; i++)
    {   if(!mark[i])
        {
            continue;
        }
        if(!f[i])
        {
            DFS(i,f,a,n);
            cout<<endl;
        }
    }

}

class Queue{
    public:
    int front = 0;
    int rear = 0;
    int  q[1000];

    bool is_empty(){
        if(front==rear)
        {
            return true;
            
        }
        return false;
    }

    void push(int n)
    {
        q[rear]=n;
        rear++;
    }
    void pop()
    {
        front++;
    }   

};

void bfs(int v , bool* f , Node**a , int n,Queue* que)
{   
    f[v]=true;
    que->push(v);

    while(que->is_empty()!=true)
    {
        int v1 = que->q[que->front];
        cout<<char(v1+'A')<<" ";
        que->pop();

        Node *temp = a[v1];
        while (temp != NULL)
        {
            if (!f[temp->v])
            {
                f[temp->v] = true;
                que->push(temp->v);
            }
            temp = temp->next;
        }
    }
}

void try_bfs(Node**a ,int n ,int* mark)
{   Queue* q = new Queue();
    bool f[n];
    for (int i = 0; i < n; i++)
    {
        f[i] = false;
    }

    for (int i = 0; i < n; i++)
    {
        if(!mark[i])
        {
            continue;
        }
        if (!f[i])
        {
            bfs(i, f, a, n,q);
            cout <<endl;
        }
    }
}

bool cycle(int v, bool *f, Node **a, int n ,int p)
{
    f[v] = true;
    Node *temp = a[v];
    while (temp != NULL)
    {
        if (!f[temp->v])
        {
            if(cycle(temp->v, f, a,n,v)==true)
            {
                return true;
            }
        }

        else {
            if(temp->v!=p)
            {
                return true;
            }
        }
        temp = temp->next;
    }
    return false;
}
bool try_cycle(Node **a, int n ,int *mark)
{
    bool f[n];
    for (int i = 0; i < n; i++)
    {
        f[i] = false;
    }

    for (int i = 0; i < n; i++)
    {
        if(!mark[i])
        {
            continue;
        }

        if (!f[i])
        {
            bool b =cycle(i, f, a, n , -1);
            if(b)
            {
                return true;
            }
        }
    }

    return false;
}

int  short_bfs(int v, bool *f, Node **a, int n, Queue *que)
{   int d[n];
    for(int i = 0 ; i<n ; i++)
    {
        d[i] = 0;
    }
    d[v] = 0;
    f[v] = true;
    que->push(v);

    while (que->is_empty() != true)
    {
        int v1 = que->q[que->front];
        que->pop();

        Node *temp = a[v1];
        while (temp != NULL)
        {
            if (!f[temp->v])
            {
                f[temp->v] = true;
                d[temp->v] = d[v1]+1;
                que->push(temp->v);
            }
            temp = temp->next;
        }
    }

    int max = -1;

    for(int i = 0 ;i<n;i++)
    {
        if(i!=v)
        {
            if(d[i]>max)
            {
                max = d[i];
            }
        }
    }

    return max;
}

int  short_try_bfs(Node **a, int n , int* mark)
{
    Queue *q = new Queue();
    bool f[n];
    int max = -1;

    for (int i = 0; i < n; i++)
    {   
        if(!mark[i])
        {
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            f[i] = false;
        }
        int x =short_bfs(i, f, a, n, q);
        if(x>max)
        {
            max=x;
        }
        
    }
    return max;
}

int main()
{
   
        Node **a = new Node *[26];
        for (int i = 0; i < 26; i++)
        {
            a[i] = NULL;
        }

        int f[26];
        for(int i = 0 ; i<26 ; i++)
        {
            f[i] = 0;
        }

        ifstream fin;
        fin.open("./Q1.input.txt", ios::in);

        string line;
        int count = 0;
        while (getline(fin, line))
        {
            int k = line.length();
            int src = line[0] - 'A';
            if (!f[src])
            {
                f[src]++;
            }

            int i = 1;
            while (!(line[i] >= 'A' && line[i] <= 'Z'))
            {
                i++;
            }
            int des = line[i] - 'A';
            if (!f[des])
            { 
                f[des]++;
            }

            while (!(line[i] >= '0' && line[i] <= '9'))
            {
                i++;
            }

            string s = "";
            for (int j = i; i < k; j++)
            {
                if (!(line[j] >= '0' && line[j] <= '9'))
                {
                    break;
                }
                s += line[j];
            }

            addEdge(a, 26, src, des);
        }

        fin.close();

        while (1)
        {
            cout << "Choose any one of the options :" << endl;
            cout << "1: Insert Edge" << endl;
            cout << "2: Print BFS Traversal" << endl;
            cout << "3: Print DFS Traversal" << endl;
            cout << "4: Cycle finding in Graph" << endl;
            cout << "5: Calculate Diameter of Graph" << endl;
            cout << "6: Exit" << endl;

            int x;
            cin >> x;

            switch (x)
            {
            case 1:

           {   
               char v1,v2;
               cout<<"Enter vertex 1:"<<endl;
               cin>>v1;
               cout << "Enter vertex 2;:" << endl;
               cin>>v2;
               addEdge(a,26,v1-'A',v2-'A');
               cout<<"Edge entered successfully"<<endl;
               break;
            }

           case 2:
           {    cout<<"BFS:"; 
               try_bfs(a,26,f);
                break;
           }

           case 3:
           {   cout<<"DFS: ";
               test_dfs(a,26,f);
               break;
           }

           case 4:
           {    bool b = try_cycle(a,26,f);
            if(b)
            {
                cout<<"YES"<<endl;
            }
            else
            {
                cout<<"NO"<<endl;
            }
            
               break;
           }

           case 5:
           {    cout<<"Diameter of graph : "<<short_try_bfs(a,26,f)<<endl;
               break;
           }

           case 6:
           {   cout<<"program terminating!....)"<<endl;
               return (0);
               break;
           }

           default:
           {
               cout<<"Try again, wrong input"<<endl;
           }
    }

}
}