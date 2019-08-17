#include<bits/stdc++.h>
using namespace std;

class BSTnode {

    public :
        BSTnode *left;
        BSTnode *right;
        int data;
        int balancefactor;
        int h;

        BSTnode(int root_val) {
            balancefactor = 0;
            data = root_val;
            left = NULL;
            right = NULL;
            h = 1;
        }    
};

class RBTnode {
    public :
        int data; 
        int color; 
        int balancefactor;
        int h;
        RBTnode *left, *right, *parent; 
    
        RBTnode(int data) 
        { 
        this->data = data; 
        left = right = parent = NULL; 
        this->color = 1; 
        }   
};

class BST {

    public:
        BSTnode *root;

        BST() {
            root = NULL;
        }

        BSTnode* insert(BSTnode *root, int x) {
            
            if(root == NULL) {
                BSTnode *temp = new BSTnode(x);
                return temp;
            }
            if(x >= root->data) {
                root->right = insert(root->right, x); 
                if(root->left != NULL) { 
                    root->h = max(root->left->h, root->right->h) + 1;
                    root->balancefactor = abs(root->left->h - root->right->h);
                } else {
                    root->h = root->right->h + 1;
                    root->balancefactor = root->right->h;
                }
            }
            else {
                root->left = insert(root->left, x);
                if(root->right != NULL) { 
                    root->h = max(root->left->h, root->right->h) + 1;
                    root->balancefactor = abs(root->left->h - root->right->h);
                } else {
                    root->h = root->left->h;
                    root->balancefactor = root->left->h;
                }
            }
            return root;     
        };

        void inorderprint(BSTnode *root) {

            if(root == NULL) return;

            inorderprint(root->left);
            cout << root->data << " ";
            inorderprint(root->right);    
        }

        void levelorderprint(BSTnode *root, int spaces) {
            
            if(root == NULL) return;

            for(int i = 1; i <= spaces; i++) cout << " ";

            cout << root->data;

            if(root->balancefactor != 0)
                cout << "[" << root->balancefactor << "]";
            cout << "\n";    
            levelorderprint(root->left, spaces+1);
            levelorderprint(root->right, spaces+1);
        } 
};

class RedBlackTree{

    public:
        RBTnode *root;
        RedBlackTree() {
            root = NULL;
        }

        RBTnode* BSTinsert(RBTnode *root, RBTnode* temp) {

            if (root == NULL) 
            return temp; 
        
            if (temp->data <= root->data) 
            { 
                root->left  = BSTinsert(root->left, temp); 
                root->left->parent = root; 
            } 
            else if (temp->data > root->data) 
            { 
                root->right = BSTinsert(root->right, temp); 
                root->right->parent = root; 
            } 
        
            return root; 
        };

        void calcbalancefactor(RBTnode *root) {
            
            if(root == NULL) return; 

            calcbalancefactor(root->left);
            calcbalancefactor(root->right);

            int lh = (root->left != NULL ? root->left->h : 0);
            int rh = (root->right != NULL ? root->right->h : 0);
            root->h = max(lh, rh) + 1;
            root->balancefactor = abs(lh - rh);
        };

        void rotateRight(RBTnode *&root, RBTnode *&pt) 
        { 
            RBTnode *pt_left = pt->left; 
        
            pt->left = pt_left->right; 
        
            if (pt->left != NULL) 
                pt->left->parent = pt; 
        
            pt_left->parent = pt->parent; 
        
            if (pt->parent == NULL) 
                root = pt_left; 
        
            else if (pt == pt->parent->left) 
                pt->parent->left = pt_left; 
        
            else
                pt->parent->right = pt_left; 
        
            pt_left->right = pt; 
            pt->parent = pt_left; 
        };
        
        void rotateLeft(RBTnode *&root, RBTnode *&pt) 
        { 
            RBTnode *pt_right = pt->right; 
        
            pt->right = pt_right->left; 
        
            if (pt->right != NULL) 
                pt->right->parent = pt; 
        
            pt_right->parent = pt->parent; 
        
            if (pt->parent == NULL) 
                root = pt_right; 
        
            else if (pt == pt->parent->left) 
                pt->parent->left = pt_right; 
        
            else
                pt->parent->right = pt_right; 
        
            pt_right->left = pt; 
            pt->parent = pt_right; 
        };

        void fix(RBTnode *&root, RBTnode* &temp) {

                RBTnode *parent_pt = NULL; 
                RBTnode *grand_parent_pt = NULL; 
  
                while ((temp != root) && (temp->color != 0) && 
                    (temp->parent->color == 1)) 
                { 
            
                    parent_pt = temp->parent; 
                    grand_parent_pt = temp->parent->parent; 
            
                    if (parent_pt == grand_parent_pt->left) 
                    { 
            
                        RBTnode *uncle_pt = grand_parent_pt->right; 
            
                        if (uncle_pt != NULL && uncle_pt->color == 1) 
                        { 
                            grand_parent_pt->color = 1; 
                            parent_pt->color = 0; 
                            uncle_pt->color = 0; 
                            temp = grand_parent_pt; 
                        } 
            
                        else { 
                            if (temp == parent_pt->right) 
                            { 
                                rotateLeft(root, parent_pt); 
                                temp = parent_pt; 
                                parent_pt = temp->parent; 
                            } 
            
                            rotateRight(root, grand_parent_pt); 
                            swap(parent_pt->color, grand_parent_pt->color); 
                            temp = parent_pt; 
                        } 
                    } 

                    else
                    { 
                        RBTnode *uncle_pt = grand_parent_pt->left; 
            
                        if ((uncle_pt != NULL) && (uncle_pt->color == 1)) 
                        { 
                            grand_parent_pt->color = 1; 
                            parent_pt->color = 0; 
                            uncle_pt->color = 0; 
                            temp = grand_parent_pt; 
                        } 
                        else
                        { 
                            if (temp == parent_pt->left) 
                            { 
                                rotateRight(root, parent_pt); 
                                temp = parent_pt; 
                                parent_pt = temp->parent; 
                            } 
            
                            rotateLeft(root, grand_parent_pt); 
                            swap(parent_pt->color, grand_parent_pt->color); 
                            temp = parent_pt; 
                        } 
                    } 
                } 
                             root->color = 0; 
                        
        };

        void insert(const int &data) 
            { 
                RBTnode *pt = new RBTnode(data); 
            
                root = BSTinsert(root, pt); 
            
                fix(root, pt); 

                calcbalancefactor(root);
            }; 

        void inorderprint(RBTnode *root) 
        { 
            if (root == NULL) 
                return; 
        
            inorderprint(root->left); 
            cout << root->data  << " "; 
            inorderprint(root->right); 
        };    

        void levelorderprint(RBTnode *root, int spaces) {
            
            if(root == NULL) return;

            for(int i = 1; i <= spaces; i++) cout << " ";

            cout << root->data;

            if(root->balancefactor != 0)
                cout << "[" << root->balancefactor << "]";
            cout << (root->color == 0 ? "[BLACK]" : "[RED]");    
            cout << "\n";    
            levelorderprint(root->left, spaces+1);
            levelorderprint(root->right, spaces+1);
        }; 
};

template<class t>
void PrintAllPaths(t *root) {

    if(root == NULL) return;

    gotoleaf(root, {});
    PrintAllPaths(root->left);
    PrintAllPaths(root->right);
}

template<class t> 
void gotoleaf(t *root, vector<int> v) {

    if(root == NULL) return;

    if(root->right == NULL && root->left == NULL) {
        v.push_back(root->data);
        for(int i = 0; i < v.size(); i++) {
            if(i == v.size()-1) cout << v[i] << "\n";
            else cout << v[i] << "-->";
        }
        return;
    }

    v.push_back(root->data);
    
    gotoleaf(root->left, v);
    gotoleaf(root->right, v);    
}

vector<int> v;
void Makearr(BSTnode *root) {

    if(root == NULL) return;
    
    Makearr(root->left);
    v.push_back(root->data);
    Makearr(root->right);
}

BSTnode* avlgen(BSTnode*root, int start, int mid, int end) {

    if(start > end) return NULL;

    root = new BSTnode(v[mid]);
    root->h = mid - start + 1;
    
    root->left = avlgen(root->left, start, (start + mid - 1) / 2, mid-1);
    root->right = avlgen(root->right, mid+1, (mid + 1 + end) / 2, end);

    root->balancefactor = abs( ((root->left != NULL) ? root->left->h : 0) - ((root->right != NULL) ? root->right->h : 0) );    
    return root;
}

BSTnode* BSTtoAVL(BSTnode *bstroot, BSTnode *avlroot) {

    Makearr(bstroot);

    avlroot = avlgen(avlroot, 0, (v.size() / 2) - 1, v.size() - 1);

    return avlroot;
}

int main() {
    
    RedBlackTree rbt;
    BST bst;
    BST avl;

    cout << "Welcome!\n";

    while(1) {

        cout << "---------------------MAIN MENU---------------------" << "\n\n";
        cout << "1. Insert node in BST/Red-Black-Tree" << "\n";
        cout << "2. Create AVL tree from the inorder traversal of the BST" << "\n";
        cout << "3. Inorder traversal of BST/AVL/Red-Black-Tree" << "\n";
        cout << "4. Display all the paths in the BST/AVL/Red-Black-Tree" << "\n";
        cout << "5. Level-wise indentation print of BST/AVL/Red-Black-Tree" << "\n"; 
        cout << "6. Exit" << "\n\n";

        int option; cin >> option;

        switch(option) {

            case 1: {

                cout << "1. Red-Black-Tree" << "\n";
                cout << "2. BST" << "\n";

                int suboption; cin >> suboption;
                
                cout << "Enter data" << "\n";
                int x; cin >> x;

                switch(suboption) {
                    case 1 : 
                        rbt.insert(x);
                        break;
                    case 2:
                        bst.root = bst.insert(bst.root, x);
                        break;
                    default:
                        cout << "Wrong input\n";        
                }
                break;
            }

            case 2: {
                v.clear();
                avl.root = NULL;
                avl.root = BSTtoAVL(bst.root, avl.root);
                cout << "Done successfully!" << "\n";
                break;
            }

            case 3: {
                
                cout << "1. Red-Black-Tree" << "\n";
                cout << "2. BST" << "\n";
                cout << "3. AVL" << "\n";

                int suboption; cin >> suboption;

                switch(suboption) {
                    case 1:
                        cout << "Inorder:";
                        rbt.inorderprint(rbt.root);
                        cout << "\n";
                        break;

                    case 2:
                        cout << "Inorder:";
                        bst.inorderprint(bst.root);
                        cout << "\n";
                        break;

                    case 3:
                        cout << "Inorder:";
                        avl.inorderprint(avl.root);
                        break;

                    default:
                        cout << "Wrong input!";            
                }    
                break;
            }

            case 4: {
                cout << "1. Red-Black-Tree" << "\n";
                cout << "2. BST" << "\n";
                cout << "3. AVL" << "\n";

                int suboption; cin >> suboption;

                switch(suboption) {

                    case 1:
                        cout << "Paths to leaf:" << "\n";
                        PrintAllPaths<RBTnode>(rbt.root);
                        break;
                    case 2:
                        cout << "Paths to leaf:" << "\n";
                        PrintAllPaths<BSTnode>(bst.root);
                        break;
                    case 3:
                        cout << "Paths to leaf:" << "\n";
                        PrintAllPaths<BSTnode>(avl.root);
                        break;
                    default:
                        cout << "Wrong input!" << "\n";   
                }

                break;
            }

            case 5: {
                cout << "1. Red-Black-Tree" << "\n";
                cout << "2. BST" << "\n";
                cout << "3. AVL" << "\n";

                int suboption; cin >> suboption;

                switch(suboption) {
                    case 1:
                        cout << "Level-indentation print:" << "\n";
                        rbt.levelorderprint(rbt.root, 0);
                        break;

                    case 2:
                        cout << "Level-indentation print:" << "\n";
                        bst.levelorderprint(bst.root, 0);
                        break;

                    case 3:
                        cout << "Level-indentation print:" << "\n";
                        avl.levelorderprint(avl.root, 0);
                        break;

                    default:
                        cout << "Wrong input!";            
                }    
                break;
            }

            case 6: {
                cout << "Program terminating. Have a good day! :D" << "\n";
                return 0;                
            }

            default:
                cout << "Wrong input!" << "\n";
        }
    } 

    return 0;
}