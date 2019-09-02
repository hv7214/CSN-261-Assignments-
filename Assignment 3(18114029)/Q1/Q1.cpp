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
                    root->h = root->left->h + 1;
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
                RBTnode *gr_par_temp = NULL; 
  
                while ((temp != root) && (temp->color != 0) && 
                    (temp->par->color == 1)) 
                { 
            
                    par_temp = temp->par; 
                    gr_par_temp = temp->par->par; 
            
                    if (par_temp == gr_par_temp->left) 
                    { 
            
                        RBTnode *unc_temp = gr_par_temp->right; 
            
                        if (unc_temp != NULL && unc_temp->color == 1) 
                        { 
                            gr_par_temp->color = 1; 
                            par_temp->color = 0; 
                            unc_temp->color = 0; 
                            temp = gr_par_temp; 
                        } 
            
                        else { 
                            if (temp == par_temp->right) 
                            { 
                                rotateLeft(root, par_temp); 
                                temp = par_temp; 
                                par_temp = temp->par; 
                            } 
            
                            rotateRight(root, gr_par_temp); 
                            swap(par_temp->color, gr_par_temp->color); 
                            temp = par_temp; 
                        } 
                    } 

                    else
                    { 
                        RBTnode *unc_temp = gr_par_temp->left; 
            
                        if ((unc_temp != NULL) && (unc_temp->color == 1)) 
                        { 
                            gr_par_temp->color = 1; 
                            par_temp->color = 0; 
                            unc_temp->color = 0; 
                            temp = gr_par_temp; 
                        } 
                        else
                        { 
                            if (temp == par_temp->left) 
                            { 
                                rotateRight(root, par_temp); 
                                temp = par_temp; 
                                par_temp = temp->par; 
                            } 
            
                            rotateLeft(root, gr_par_temp); 
                            swap(par_temp->color, gr_par_temp->color); 
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
* Helper function for PrintAllPaths function
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

/**
 * @brief This method returns maximum of two numbers
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  
  
/**
 * @brief This method returns height of any node in AVL Tree
 * 
 * @param avlNode 
 * @return int 
 */
int height(BSTnode *avlNode)  {  
    if (avlNode == NULL)  
        return 0;  
    return avlNode->h;  
} 

/**
 * @brief This method returns the balance factor of particular node
 * 
 * @param avlNode 
 * @return int 
 */
int getBalance(BSTnode *avlNode)  {  
    if (avlNode == NULL)  
        return 0;  
    return height(avlNode->left) - height(avlNode->right);  
}  

/**
 * @brief This method performs the right rotation of nodes to make AVL Tree
 * 
 * @param avlNode 
 * @return AVL* 
 */
BSTnode *rightRotate(BSTnode *avlNode)  
{  
    BSTnode *avlNodeLeft = avlNode->left;  
    BSTnode *node = avlNodeLeft->right;  
  
    avlNodeLeft->right = avlNode;  
    avlNode->left = node;  
  
    avlNode->h = max(height(avlNode->left), 
                    height(avlNode->right)) + 1;  
    avlNodeLeft->h = max(height(avlNodeLeft->left), 
                    height(avlNodeLeft->right)) + 1;  
  
    return avlNodeLeft;  
}  

/**
 * @brief This method performs the left rotation of nodes to make AVL Tree
 * 
 * @param avlNode 
 * @return AVL* 
 */
BSTnode *leftRotate(BSTnode *avlNode)  
{  
    BSTnode *avlNodeRight = avlNode->right;  
    BSTnode *node = avlNodeRight->left;  

    avlNodeRight->left = avlNode;  
    avlNode->right = node;  

    avlNode->h = max(height(avlNode->left),     
                    height(avlNode->right)) + 1;  
    avlNodeRight->h = max(height(avlNodeRight->left),  
                    height(avlNodeRight->right)) + 1;  

    return avlNodeRight;  
}

/**
 * @brief This method inserts a node in AVL Tree
 * 
 * @param avlNode 
 * @param data 
 * @return AVL* 
 */
BSTnode* insert(BSTnode* avlNode, int data)  
{  
    if (avlNode == NULL) {
      BSTnode* node = new BSTnode(data); 
	    node->left = NULL; 
	    node->right = NULL; 
	    node->h = 1;
      return node;
    }

	if (data < avlNode->data) 
		avlNode->left = insert(avlNode->left, data); 
	else if (data > avlNode->data) 
		avlNode->right = insert(avlNode->right, data); 
	else
		return avlNode; 

	avlNode->h = 1 + max(height(avlNode->left), 
						height(avlNode->right)); 

	int balance = getBalance(avlNode); 

	if (balance > 1 && data < avlNode->left->data) 
		return rightRotate(avlNode); 

	if (balance < -1 && data > avlNode->right->data) 
		return leftRotate(avlNode); 

	if (balance > 1 && data > avlNode->left->data) 
	{ 
		avlNode->left = leftRotate(avlNode->left); 
		return rightRotate(avlNode); 
	} 

	if (balance < -1 && data < avlNode->right->data) 
	{ 
		avlNode->right = rightRotate(avlNode->right); 
		return leftRotate(avlNode); 
	} 

	return avlNode;  
}

vector<int> arrBST;

/**
 * @brief This method stores the BST Tree in a vector
 * 
 * @param bstNode 
 * @return vector<int> 
 */
vector<int> getBST(BSTnode* bstNode){
  if(bstNode != NULL){
    getBST(bstNode->left);
    arrBST.push_back(bstNode->data);
    getBST(bstNode->right);
  }
  return arrBST;
}

/**
 * @brief This method prints the AVL Tree with proper indentation
 * 
 * @param avlNode 
 * @param space 
 */
void printAVLTree(BSTnode* avlNode, int space){
  if(avlNode != NULL){
    for(int i=0;i<space;i++){
      cout<<"      ";
    }
    int balance = getBalance(avlNode);
    if(avlNode->left == 0 && avlNode->right == 0){
      cout<<avlNode->data<<endl;
    }else{
      cout<<avlNode->data<<"["<<abs(balance)<<"]"<<endl;
    }
    printAVLTree(avlNode->left, space+1);
    printAVLTree(avlNode->right, space+1);
  }
}

int main() {
    
    RedBlackTree rbt;
    BST bst;
    BST avl;
    vector<int> BSTTree;

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
                
                BSTTree.clear();
                BSTTree = getBST(bst.root);

                for(int i=0;i<BSTTree.size();i++){
                  avl.root = insert(avl.root, BSTTree[i]);
                }
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
                        printAVLTree(avl.root, 0);
                        // avl.levelorderprint(avl.root, 0);
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