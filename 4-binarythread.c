#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int isThreaded; 
} TreeNode;


TreeNode* CreateNewNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->isThreaded = 0; 
    return node;
}


TreeNode* InsertIntoBST(TreeNode* root, int data) {
    if (root == NULL) {
        return CreateNewNode(data);
    }
    if (data < root->data) {
        root->left = InsertIntoBST(root->left, data);
    }
    else if (data > root->data) {
        root->right = InsertIntoBST(root->right, data);
    }
    return root;
}


void BinaryTreeInOrder(TreeNode* root) {
    if (root == NULL) return;
    BinaryTreeInOrder(root->left);
    printf("%d ", root->data);
    BinaryTreeInOrder(root->right);
}

TreeNode* GenerateBinaryTree(int inputData[]) {
    TreeNode* root = NULL;
    for (int i = 0; inputData[i] != '\0'; i++) {
        root = InsertIntoBST(root, inputData[i]);
    }
    return root;
}

void ConvertToThreaded(TreeNode* root, TreeNode** prev) {
    if (root == NULL) return;

    
    ConvertToThreaded(root->left, prev);

    
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = 1;  
    }

    
    *prev = root;

    
    ConvertToThreaded(root->right, prev);
}


TreeNode* GenerateThreadTree(int inputData[]) {
    TreeNode* root = GenerateBinaryTree(inputData);  
    TreeNode* prev = NULL;
    ConvertToThreaded(root, &prev);  
    return root;
}


void ThreadTreeInOrder(TreeNode* root) {
    TreeNode* curr = root;
    while (curr != NULL) {
        
        while (curr->left != NULL) {
            curr = curr->left;
        }

        printf("%d ", curr->data);

        
        while (curr->isThreaded) {
            curr = curr->right;
            printf("%d ", curr->data);
        }

        curr = curr->right;
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11, '\0' }; 

    
    TreeNode* root = GenerateBinaryTree(inputData);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root); 
    printf("\n");

    
    TreeNode* troot = GenerateThreadTree(inputData);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot); 
    printf("\n");

    
    free(root);
    free(troot);

    return 0;
}
