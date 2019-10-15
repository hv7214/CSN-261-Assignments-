#include<bits/stdc++.h>
using namespace std;

struct Edge{
    char source;
    char dest;
    int weight;
};

vector<Edge> input, output;
map<char, char> parent;
int V = 0;
int totalWeight = 0;

bool compare( Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

void readCSV() {
    
    string filename = "Q2.csv";
    fstream file(filename);

    string line;
    if(file.is_open()) {
        while(getline(file, line)) {
            Edge e ;
            e.source  = line[0];
            e.dest    = line[2];
            e.weight  = stoi(line.substr(4, line.length()-1));
            input.push_back(e);  
        }
    }

    sort(input.begin(), input.end(), compare);
}

void writeOutputFile() {

    string filename = "output.dot";
    fstream file(filename, ios::out | ios::trunc);

    file << "graph G{\n";
    
    for(auto e : output) {
        string line = "    " + string(1, e.source) + "--" + string(1, e.dest) + "[label=" + to_string(e.weight) + "];\n";
        file << line;

        totalWeight += e.weight;
    }

    file << "}";

    file.close();
}

void getVertices() {

    set<int> v;
    for(auto e : input) {
        v.insert(e.dest);
        v.insert(e.source);
    }

    V = v.size();
}

char findParent(char v) {
    if (parent[v] == v) 
        return v;
    return findParent(parent[v]);    
}

void kruskal() {

    for(char i = 'A'; i < 'A' + V; i++) {
        parent[i] = i;
    }

    int i = 0;
    while(i != input.size()) {
        Edge currentedge = input[i];

        char p1 = findParent(currentedge.source);
        char p2 = findParent(currentedge.dest);
      
        if (p1 != p2) {
            output.push_back(currentedge);
            parent[p1] = p2;
        }
        i++;
    }    
}

int main() {
    
    readCSV();
    
    getVertices();

    kruskal();

    writeOutputFile(); 
    for(auto e : input) {
        cout << e.source << " " << e.dest << " " << e.weight << "\n";  
    }

    cout <<"Total Weight :" <<  totalWeight << "\n";

    system("dot -Tps ./output.dot -o q2.pdf");
}