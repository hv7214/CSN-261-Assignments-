
#include <limits.h> 
#include <stdlib.h> 
#include <string.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

struct ALnode { 
	int dest; 

	
	int weight; 
	
	
	
struct ALnode* next; 
}; 




struct AL { 


	struct ALnode* head;
}; 

struct G { 
	int V; 

	struct AL* a; 
}; 

struct ALnode* newALnode(int dest, int weight) 
{ 
	struct ALnode* nn = (struct ALnode*)malloc(sizeof(struct ALnode)); 
	nn->dest = dest; 
	
	nn->weight = weight; 
	nn->next = NULL; 

	return nn; 
} 

struct G* createG(int V) 
{ 
	struct G* G = (struct G*)malloc(sizeof(struct G)); 
	G->V = V; 

	G->a = (struct AL*)malloc(V * sizeof(struct AL)); 

	for (int i = 0; i < V; ++i) 

		G->a[i].head = NULL; 

	return G; 
} 

void addEdge(struct G* G, int src, int dest, int weight) 
{ 

	struct ALnode* nn = newALnode(dest, weight); 
	nn->next = G->a[src].head; 

	G->a[src].head = nn; 

	nn = newALnode(src, weight); 
	nn->next = G->a[dest].head; 

	G->a[dest].head = nn; 
} 

struct FibonacciHeapNode { 
	int v; 

	int key; 
}; 

struct FibonacciHeap { 
	int size;

	int capacity;

	int* pos;


	struct FibonacciHeapNode** a; 
}; 

struct FibonacciHeapNode* newFibonacciHeapNode(int v, int key) 
{ 
	struct FibonacciHeapNode* FibonacciHeapNode = (struct FibonacciHeapNode*)malloc(sizeof(struct FibonacciHeapNode)); 
	FibonacciHeapNode->v = v; 
	FibonacciHeapNode->key = key; 
	return FibonacciHeapNode; 
} 

struct FibonacciHeap* createFibonacciHeap(int capacity) 
{ 
	struct FibonacciHeap* FibonacciHeap = (struct FibonacciHeap*)malloc(sizeof(struct FibonacciHeap)); 
	
	FibonacciHeap->pos = (int*)malloc(capacity * sizeof(int)); 
	FibonacciHeap->size = 0; 
	FibonacciHeap->capacity = capacity; 

	FibonacciHeap->a = (struct FibonacciHeapNode** )malloc(capacity * sizeof(struct FibonacciHeapNode)); 
	return FibonacciHeap; 
} 

void swapFibonacciHeapNode(struct FibonacciHeapNode** a, struct FibonacciHeapNode** b) 
{ 
	struct FibonacciHeapNode* t = *a; 
	*a = *b; 
	*b = t; 

} 

void FibonacciHeapify(struct FibonacciHeap* FibonacciHeap, int idx) 
{ 
	int smallest, left, right; 
	smallest = idx; 
	left = 2 * idx + 1; 
	right = 2 * idx + 2; 

	if (left < FibonacciHeap->size && FibonacciHeap->a[left]->key < FibonacciHeap->a[smallest]->key) 
		smallest = left; 

	if (right < FibonacciHeap->size && FibonacciHeap->a[right]->key < FibonacciHeap->a[smallest]->key) 
		smallest = right; 

	if (smallest != idx) { 
		FibonacciHeapNode* smallestNode = FibonacciHeap->a[smallest]; 
		FibonacciHeapNode* idxNode = FibonacciHeap->a[idx]; 

		FibonacciHeap->pos[smallestNode->v] = idx; 
		FibonacciHeap->pos[idxNode->v] = smallest; 

		swapFibonacciHeapNode(&FibonacciHeap->a[smallest], &FibonacciHeap->a[idx]); 

		FibonacciHeapify(FibonacciHeap, smallest); 
	} 
} 

int isEmpty(struct FibonacciHeap* FibonacciHeap) 
{ 
	return FibonacciHeap->size == 0; 
} 

struct FibonacciHeapNode* extractMin(struct FibonacciHeap* FibonacciHeap) 
{ 
	if (isEmpty(FibonacciHeap)) 
		return NULL; 

	struct FibonacciHeapNode* root = FibonacciHeap->a[0]; 

	struct FibonacciHeapNode* lastNode = FibonacciHeap->a[FibonacciHeap->size - 1]; 
	FibonacciHeap->a[0] = lastNode; 

	FibonacciHeap->pos[root->v] = FibonacciHeap->size - 1; 
	FibonacciHeap->pos[lastNode->v] = 0; 

	--FibonacciHeap->size; 
	FibonacciHeapify(FibonacciHeap, 0); 

	return root; 
} 

void decreaseKey(struct FibonacciHeap* FibonacciHeap, int v, int key) 
{ 
	int i = FibonacciHeap->pos[v]; 

	FibonacciHeap->a[i]->key = key; 

	while (i && FibonacciHeap->a[i]->key < FibonacciHeap->a[(i - 1) / 2]->key) { 

		FibonacciHeap->pos[FibonacciHeap->a[i]->v] = (i - 1) / 2; 
		FibonacciHeap->pos[FibonacciHeap->a[(i - 1) / 2]->v] = i; 
		swapFibonacciHeapNode(&FibonacciHeap->a[i], &FibonacciHeap->a[(i - 1) / 2]); 

		i = (i - 1) / 2; 
	} 
} 

bool isInFibonacciHeap(struct FibonacciHeap* FibonacciHeap, int v) 
{ 
	if (FibonacciHeap->pos[v] < FibonacciHeap->size) 
		return true; 

	return false; 
} 

void printArr(int node[], int weight[], int n) 
{ 

	cout << "Node1 Node2 Weight"<< endl;
	FILE *fp;

    if((fp = fopen("output.gv", "w")) != NULL){
        fprintf(fp, "G G {\n");



		for (int i = 1; i < n; ++i){

			char start = (char) (node[i]+65);
			char end = (char) (i+65);

			if(node[i] > i){
				cout<<end<<" "<<start<<" "<<weight[i]<<endl;
			}else{
				cout<<start<<" "<<end<<" "<<weight[i]<<endl;
			}

			fprintf(fp, "\t%c -- %c [label=\"%d\"]\n", start, end, weight[i]);

		}

		fprintf(fp, "}\n");
    	fclose(fp);
	}else{

		printf("\nfopen() failed\n");
	}
} 

void primfibo(struct G* G) 
{ 
	int V = G->V;
	int parent[V];
	int key[V];

	struct FibonacciHeap* FibonacciHeap = createFibonacciHeap(V); 

	for (int v = 1; v < V; ++v) { 
		parent[v] = -1; 

		key[v] = INT_MAX; 
		FibonacciHeap->a[v] = newFibonacciHeapNode(v, key[v]); 
		FibonacciHeap->pos[v] = v; 
	} 



	key[0] = 0; 
	FibonacciHeap->a[0] = newFibonacciHeapNode(0, key[0]); 
	FibonacciHeap->pos[0] = 0; 

	FibonacciHeap->size = V; 

	while (!isEmpty(FibonacciHeap)) { 

		struct FibonacciHeapNode* FibonacciHeapNode = extractMin(FibonacciHeap); 
		int u = FibonacciHeapNode->v;

		struct ALnode* pCrawl = G->a[u].head; 
		while (pCrawl != NULL) { 
			int v = pCrawl->dest; 

			if (isInFibonacciHeap(FibonacciHeap, v) && pCrawl->weight < key[v]) { 
				key[v] = pCrawl->weight; 
				parent[v] = u; 
				decreaseKey(FibonacciHeap, v, key[v]); 
			} 
			pCrawl = pCrawl->next; 
		} 
	} 

	printArr(parent, key, V); 
} 

int main() { 

	int V = 6; 
	struct G* G = createG(V); 

    ifstream fin; 
	fin.open("Q3.csv"); 
	string line,s;
	vector<string> words;
    getline(fin, line);
	string max="";

	cout<<"Node1 Node2 Weight"<<endl;
    while (fin) {
        vector<string> words;
        stringstream ss(line); 
        string tok;
        while(getline(ss, tok, ',')) {
            words.push_back(tok);
        }
  		s = words[0]+words[1];
  		max = (max>s)?max:(words[0]>words[1]?words[0]:words[1]);
  		
		cout<<words[0]<<" "<<words[1]<<" "<<stoi(words[2])<<endl;
        int start = (int) words[0][0] - 65;
        int end = (int) words[1][0] - 65;
        int weight = stoi(words[2]);

        addEdge(G, start, end, weight);

		getline(fin, line);
    } 

	primfibo(G); 

	return 0; 
}