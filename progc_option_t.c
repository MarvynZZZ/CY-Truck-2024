#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode {
    char town[50];
    int totalTrips;
    int departTrips;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode *newNode(char *town) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    strcpy(node->town, town);
    node->totalTrips = 0;
    node->departTrips = 0;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getTrips(AVLNode *root, char *town, int isDepart) {
    if (root == NULL)
        return 0;

    int compare = strcmp(town, root->town);

    if (compare < 0)
        return getTrips(root->left, town, isDepart);
    else if (compare > 0)
        return getTrips(root->right, town, isDepart);
    else
        return isDepart ? root->departTrips : root->totalTrips;
}

AVLNode *insertNode(AVLNode *node, char *town, int isDepart) {
    if (node == NULL)
        return newNode(town);

    int compare = strcmp(town, node->town);

    if (compare < 0)
        node->left = insertNode(node->left, town, isDepart);
    else if (compare > 0)
        node->right = insertNode(node->right, town, isDepart);
    else {
        if (isDepart)
            node->departTrips++;
        node->totalTrips++;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1) {
        if (strcmp(town, node->left->town) < 0)
            return rightRotate(node);
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balance < -1) {
        if (strcmp(town, node->right->town) > 0)
            return leftRotate(node);
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

void printTop10Trips(AVLNode *root) {
    if (root != NULL) {
        printTop10Trips(root->right);
        printf("%s: Total Trips - %d, Depart Trips - %d\n", root->town, root->totalTrips, root->departTrips);
        printTop10Trips(root->left);
    }
}

int main() {
    FILE *file = fopen("trajets.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    char line[256];
    AVLNode *root = NULL;

    while (fgets(line, sizeof(line), file)) {
        char *routeID, *stepID, *townA, *townB, *distance, *driverName;
        routeID = strtok(line, ";");
        stepID = strtok(NULL, ";");
        townA = strtok(NULL, ";");
        townB = strtok(NULL, ";");
        distance = strtok(NULL, ";");
        driverName = strtok(NULL, ";");

        // Insert townA as the departure town
        root = insertNode(root, townA, 1);
        // Insert townB as part of the route
        root = insertNode(root, townB, 0);
    }

    fclose(file);

    printTop10Trips(root);

    return 0;
}
