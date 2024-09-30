#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode
{
    int value;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

treeNode* createTreeNode(int data)
{
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->value = data;
    return newNode;
}

void insertNode(treeNode* root,int data)
{
    if(root == NULL)
        root = createTreeNode(data);
    else if(root->value > data)
    {
        if(root->left == NULL)
            root->left = createTreeNode(data);
        else
            insertNode(root->left, data);
    }    
    else if(root->value < data)
    {
        if(root->right == NULL)
            root->right = createTreeNode(data);
        else
            insertNode(root->right, data);
    }
}

void inorderTraversal(treeNode* root)
{
    if(root != NULL)
    {
        inorderTraversal(root->left);
        printf("%i " ,root->value);
        inorderTraversal(root->right);
    }
}

treeNode* generateTree(int inorder[], int preorder[] , int length)
{
    if (length == 0)
        return NULL;
    if (length == 1)
    {
        treeNode* root = createTreeNode(preorder[0]);
        printf("Create Node : %i\n", root->value);
        return root;
    }   
    if(length > 2)
    {
        treeNode* root = createTreeNode(preorder[0]);
        printf("Create Node : %i\n", root->value);
        int root_position;
        for(int i =0; i< length; i++)
        {
            if (inorder[i] == preorder[0])
            {
                root_position = i;
                break;
            }
        }
        int leftlength = root_position;
        int rightlength= length - root_position -1;
        int leftsubtree[leftlength];
        int rightsubtree[rightlength];
        for (int i = 0; i < root_position; i++)
            leftsubtree[i] = inorder[i];
        for (int i = root_position+1,j = 0; i < length; i++,j++)
            rightsubtree[j] = inorder[i];
        int leftpreorder[leftlength];
        int rightpreorder[rightlength];
        int k = 1;
        for (int j = 0; j < leftlength;j++,k++)
            leftpreorder[j] = preorder[k];
        for (int j = 0; j < rightlength;j++,k++)
            rightpreorder[j] = preorder[k];    
        root->left = generateTree(leftsubtree,leftpreorder,leftlength);
        root->right = generateTree(rightsubtree,rightpreorder,rightlength);
        return root;
    }
}
void main()
{
    int size;
    printf("Enter Number of elements : ");
    scanf("%i", &size);
    int inorder[size];
    int preorder[size];
    printf("Enter Inorder : ");
    for(int i = 0 ;i < size ;i++)
        scanf("%i", &inorder[i]);    
    printf("Enter PreOrder : ");
    for(int i = 0 ;i < size ;i++)
        scanf("%i", &preorder[i]);    
    treeNode* root = generateTree(inorder,preorder,size);
    inorderTraversal(root);
    printf("\n");
}