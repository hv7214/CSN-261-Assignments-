/**
* @file Q1.cpp
* @brief BST/Red-Black-Tree/AVL 
*
* @author Harshit Verma
*
* @date 08/17/19
*/

#include<bits/stdc++.h>
using namespace std;

/**
* This class will be used for Binary Search Tree Node
* @author harshit Verma
* @date 08/17/2019
*/
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

/**
* This class will be used for Red Black Tree Node
* @author harshit Verma
* @date 08/17/2019
*/
class RBTnode {
    public :
        int data; 
        int color; 
        int balancefactor;
        int h;
        RBTnode *left, *right, *par; 
    
        RBTnode(int data) 
        { 
        this->data = data; 
        left = right = par = NULL; 
        this->color = 1; 
        }   
};

/**
* This class will be used for Binary search tree
* @author harshit Verma
* @date 08/17/2019
*/
class BST {

    public:
        BSTnode *root;

        //!Consructor
        BST() {
            root = NULL;
        }

        /**
        * This funtion will be used to insert node in bst
        * @author harshit Verma
        * @date 08/17/2019
        */
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

        /**
        * This funtion will be used for inorder printing of tree
        * @author harshit Verma
        * @date 08/17/2019
        */
        void inorderprint(BSTnode *root) {

            if(root == NULL) return;

            inorderprint(root->left);
            cout << root->data << " ";
            inorderprint(root->right);    
        }

        /**
        * This funtion will be used for Level wise identation printing of tree
        * @author harshit Verma
        * @date 08/17/2019
        */
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

/*
* This class will be used for Red Black Tree
* @author harshit Verma
* @date 08/17/2019
*/ 
class RedBlackTree{

    public:
        RBTnode *root;

        //!Constuctor
        RedBlackTree() {
            root = NULL;
        }

        /*
        * This function will be used for BST insert for red black tree
        * @author harshit Verma
        * @date 08/17/2019
        */ 
        RBTnode* BSTinsert(RBTnode *root, RBTnode* temp) {

            if (root == NULL) 
            return temp; 
        
            if (temp->data <= root->data) 
            { 
                root->left  = BSTinsert(root->left, temp); 
                root->left->par = root; 
            } 
            else if (temp->data > root->data) 
            { 
                root->right = BSTinsert(root->right, temp); 
                root->right->par = root; 
            } 
        
            return root; 
        };

        /*
        * This function is used to calculate balance factor of nodes after every insertion
        * @author harshit Verma
        * @date 08/17/2019
        */
        void calcbalancefactor(RBTnode *root) {
            
            if(root == NULL) return; 

            calcbalancefactor(root->left);
            calcbalancefactor(root->right);

            int lh = (root->left != NULL ? root->left->h : 0);
            int rh = (root->right != NULL ? root->right->h : 0);
            root->h = max(lh, rh) + 1;
            root->balancefactor = abs(lh - rh);
        };

        /*
        * This function used in balancing the tree by rotation of tree around a node in right direction
        * @author harshit Verma
        * @date 08/17/2019
        */
        void rotateRight(RBTnode *&root, RBTnode *&temp) 
        { 
            RBTnode *temp_left = temp->left; 
        
            temp->left = temp_left->right; 
        
            if (temp->left != NULL) 
                temp->left->par = temp; 
        
            temp_left->par = temp->par; 
        
            if (temp->par == NULL) 
                root = temp_left; 
        
            else if (temp == temp->par->left) 
                temp->par->left = temp_left; 
        
            else
                temp->par->right = temp_left; 
        
            temp_left->right = temp; 
            temp->par = temp_left; 
        };
        
        /*
        * This function used in balancing the tree by rotation of tree around a node in left direction
        * @author harshit Verma
        * @date 08/17/2019
        */
        void rotateLeft(RBTnode *&root, RBTnode *&temp) 
        { 
            RBTnode *temp_right = temp->right; 
        
            temp->right = temp_right->left; 
        
            if (temp->right != NULL) 
                temp->right->par = temp; 
        
            temp_right->par = temp->par; 
        
            if (temp->par == NULL) 
                root = temp_right; 
        
            else if (temp == temp->par->left) 
                temp->par->left = temp_right; 
        
            else
                temp->par->right = temp_right; 
        
            temp_right->left = temp; 
            temp->par = temp_right; 
        };

        /*
        * This function is used to fix any voilations of rules of Red Black Tree
        * @author harshit Verma
        * @date 08/17/2019
        */
        void fix(RBTnode *&root, RBTnode* &temp) {

                RBTnode *par_temp = NULL; 
                RBTnode *grand_par_temp = NULL; 
  
                while ((temp != root) && (temp->color != 0) && 
                    (temp->par->color == 1)) 
                { 
            
                    par_temp = temp->par; 
                    grand_par_temp = temp->par->par; 
            
                    if (par_temp == grand_par_temp->left) 
                    { 
            
                        RBTnode *unc_temp = grand_par_temp->right; 
            
                        if (unc_temp != NULL && unc_temp->color == 1) 
                        { 
                            grand_par_temp->color = 1; 
                            par_temp->color = 0; 
                            unc_temp->color = 0; 
                            temp = grand_par_temp; 
                        } 
            
                        else { 
                            if (temp == par_temp->right) 
                            { 
                                rotateLeft(root, par_temp); 
                                temp = par_temp; 
                                par_temp = temp->par; 
                            } 
            
                            rotateRight(root, grand_par_temp); 
                            swap(par_temp->color, grand_par_temp->color); 
                            temp = par_temp; 
                        } 
                    } 

                    else
                    { 
                        RBTnode *unc_temp = grand_par_temp->left; 
            
                        if ((unc_temp != NULL) && (unc_temp->color == 1)) 
                        { 
                            grand_par_temp->color = 1; 
                            par_temp->color = 0; 
                            unc_temp->color = 0; 
                            temp = grand_par_temp; 
                        } 
                        else
                        { 
                            if (temp == par_temp->left) 
                            { 
                                rotateRight(root, par_temp); 
                                temp = par_temp; 
                                par_temp = temp->par; 
                            } 
            
                            rotateLeft(root, grand_par_temp); 
                            swap(par_temp->color, grand_par_temp->color); 
                            temp = par_temp; 
                        } 
                    } 
                } 
                             root->color = 0; 
                        
        };

        /*
        * This function is used to insert node in RBT
        * @author harshit Verma
        * @date 08/17/2019
        */
        void insert(const int &data) 
            { 
                RBTnode *temp = new RBTnode(data); 
            
                root = BSTinsert(root, temp); 
            
                fix(root, temp); 

                calcbalancefactor(root);
            }; 
        
        /*
        * This function is used to inorder print of RBT
        * @author harshit Verma
        * @date 08/17/2019
        */
        void inorderprint(RBTnode *root) 
        { 
            if (root == NULL) 
                return; 
        
            inorderprint(root->left); 
            cout << root->data  << " "; 
            inorderprint(root->right); 
        };    

        /*
        * This function is used to level wise identation print of RBT
        * @author harshit Verma
        * @date 08/17/2019
        */
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

/*
* template function to print all paths to leaf in a tree
* @author harshit Verma
* @date 08/17/2019
*/
template<class t>
void PrintAllPaths(t *root) {

    if(root == NULL) return;

    gotoleaf(root, {});
    PrintAllPaths(root->left);
    PrintAllPaths(root->right);
}

/*
* Helper functio for PrintAllPaths function
* @author harshit Verma
* @date 08/17/2019
*/
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

/*
* Helper function for BSTtoAVL
* @author harshit Verma
* @date 08/17/2019
*/
void Makearr(BSTnode *root) {

    if(root == NULL) return;
    
    Makearr(root->left);
    v.push_back(root->data);
    Makearr(root->right);
}

/*
* Helper function for avlgen
* @author harshit Verma
* @date 08/17/2019
*/
BSTnode* avlgen(BSTnode*root, int start, int mid, int end) {

    if(start > end) return NULL;

    root = new BSTnode(v[mid]);
    root->h = mid - start + 1;
    
    root->left = avlgen(root->left, start, (start + mid - 1) / 2, mid-1);
    root->right = avlgen(root->right, mid+1, (mid + 1 + end) / 2, end);

    root->balancefactor = abs( ((root->left != NULL) ? root->left->h : 0) - ((root->right != NULL) ? root->right->h : 0) );    
    return root;
}

/*
* This function is used to convert to BST to AVL
* @author harshit Verma
* @date 08/17/2019
*/
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

        int otempion; cin >> otempion;

        switch(otempion) {

            case 1: {

                cout << "1. Red-Black-Tree" << "\n";
                cout << "2. BST" << "\n";

                int subotempion; cin >> subotempion;
                
                cout << "Enter data" << "\n";
                int x; cin >> x;

                switch(subotempion) {
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

                int subotempion; cin >> subotempion;

                switch(subotempion) {
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

                int subotempion; cin >> subotempion;

                switch(subotempion) {

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

                int subotempion; cin >> subotempion;

                switch(subotempion) {
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