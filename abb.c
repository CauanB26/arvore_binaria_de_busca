#include <stdio.h>
#include <stdlib.h>

struct Node {
  int key;
  struct Node *left;
  struct Node *right;
};
typedef struct Node Node;

Node *createNode(int key);
void insertNode(Node *root, int key);
void printTree(Node *root);
void removeNode(Node *root, int key);

int main(void) {

  Node *root = createNode(10);

  insertNode(root, 3);
  insertNode(root, 7);
  insertNode(root, 8);
  insertNode(root, 11);
  insertNode(root, 14);
  insertNode(root, 17);

  // I know isn't the best way to print a tree, but it is the most
  // understandable way to do it (because im doing this to study)

  printf("Root: %d\n", root->key);
  printf("left subtree: ");
  printTree(root->left);
  printf("\n");
  printf("right subtree: ");
  printTree(root->right);
  printf("\n");

  printf("Tree before removing some nodes\n");
  removeNode(root, 7);
  printf("Root: %d\n", root->key);
  printf("left subtree: ");
  printTree(root->left);
  printf("\n");
  printf("right subtree: ");
  printTree(root->right);
  printf("\n");

  return 0;
}

Node *createNode(int key) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (newNode == NULL) {
    printf("Error: Memory allocation failed\n");
    exit(1);
  }
  newNode->key = key;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

void insertNode(Node *root, int key) {
  if (key < root->key) {
    if (root->left == NULL) {
      root->left = createNode(key);
    } else {

      insertNode(root->left, key);
    }
  } else if (key > root->key) {

    if (root->right == NULL) {
      root->right = createNode(key);
    } else {

      insertNode(root->right, key);
    }
  }
}

void printTree(Node *root) {
  if (root != NULL) {
    printTree(root->left);
    printf("%d ", root->key);
    printTree(root->right);
  }
}

void removeNode(Node *root, int key) {
  if (root == NULL) {
    return;
  }
  if (key < root->key) {
    removeNode(root->left, key);
  } else if (key > root->key) {
    removeNode(root->right, key);
  } else {
    // If the key is equal to the root's key, then we need to remove the root.
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    }
    // If the root has no children, then we can simply delete it.
    else if (root->left == NULL) {
      Node *temp = root;
      root = root->right;
      free(temp);
    } else if (root->right == NULL) {
      Node *temp = root;
      root = root->left;
      free(temp);
    }
    // If the root has two children, then we need to find the smallest node in the right subtree and replace the root with that node.
    else {
      Node *temp = root->right;
      while (temp->left != NULL) {
        temp = temp->left;
      }
      root->key = temp->key;
      removeNode(root->right, temp->key);
    }
  }
}

