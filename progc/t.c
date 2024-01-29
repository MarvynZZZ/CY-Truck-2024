#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------*/
// STRUCTURES USED IN THE PROGRAM
// Structure representing a step in a route
typedef struct Step {
    char town[50];
    int isDeparture;
} Step;

// Structure representing a route 
typedef struct Route {
    Step* step;
    int stepNumber;
} Route;

// Structure representing a town with the total of number route and departures
typedef struct Town {
    char name[50];
    int totalRoute;
    int departures;
} Town;

// Structure representing an AVL node
typedef struct Node {
    Town town;
    struct Node* left;
    struct Node* right;
    int height;
} Node;


/*-----------------------------------------------*/
// MAIN FUNCTIONS FOR THE PROGRAM
// Utility function to create a new AVL tree node
Node* newNode(char* name, int totalRoute, int departures){
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->town.name, name);
  
    node->town.totalRoute = totalRoute;
    node->town.departures = departures;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
  
    return node;
}


// Utility function to get the height of a node
int height(Node* node){
    if(node != NULL){
      return node->height;
    }
    else {
      return 0;
    }
}


// Utility function to get the maximum of two integers
int max(int a, int b){
   if(a > b){
     return a;
   }
   else {
     return b;
   } 
}


// Rotation functions to move nodes in the AVL :
// Utility function to do a simple left rotation
Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;

    // Do the rotations :
    x->left = y;
    y->right = T2;

    // Updating the heights : 
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}


// Utility function to do a simple right rotation
Node* rotateRight(Node* x) {
    Node* y = x->left;
    Node* T2 = y->right;

    // Do the rotation : 
    y->right = x;
    x->left = T2;

    // Updating the heights : 
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


// Utility function to get the balance of a node 
int getBalance(Node* node) {
    if(node != NULL){
      return height(node->left) - height(node->right);
    }
    else {
      return 0;
    }
}


// Function to insert a node in the AVL 
Node* insert(Node* root, char* name, int totalRoute, int departures){
  
    // Normal insertion for an ABR :
    if(root == NULL){
        return newNode(name, totalRoute, departures);
    }
    int compareResult = strcmp(name, root->town.name);

    if(compareResult < 0){
        root->left = insert(root->left, name, totalRoute, departures);
    }
    else if (compareResult > 0){
        root->right = insert(root->right, name, totalRoute, departures);
    }
  
    // Updating the node's heights :
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node to check balance :
    int balance = getBalance(root);

    // Case of imbalance on the left :
    if(balance > 1){
        if(compareResult < 0){
            return rotateRight(root);
        }
        else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }


    // Case of imbalance on the right :
    if(balance < -1){
        if(compareResult > 0){
            return rotateLeft(root);
        }
        else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    // The AVL Tree is balanced
    return root;
}


// Utility function to free the AVL's memory 
void freeTree(Node* root) {
    if(root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}


// MAIN FUNCTION TO BROWSE THE TREE AND GET THE DATA 
void traverseAndProcess(Node* root) {
    if(root != NULL){
        // Sort the data and keep the 10 most visited town : 

        /* code pour récupérer les 10 villes les plus traversé */

        // Browse the rest of the AVL : 
        traverseAndProcess(root->left);
        traverseAndProcess(root->right);
    }
}


