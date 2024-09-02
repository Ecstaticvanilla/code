#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int data;
    struct node* next;
};
struct node* head;
struct node* createnode(int data)
{
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = data;
    n->next = NULL;
    return n;
}

int insert(struct node* newnode)
{
    struct node* temp = head;
    if(temp->data >= newnode->data)
    {
        newnode->next = temp;
        head = newnode;
        return 0;
    }
    while(temp->next != NULL)
    {
        if(temp->next->data >= newnode->data)
        {
            newnode->next = temp->next;
            temp->next = newnode;
            return 0;
        }
        temp = temp->next;
    }
    temp->next = newnode;
    return 0;   
}

void duplicate()
{
    struct node* temp = head;
    while(temp->next != NULL)
    {
        if(temp->data == temp->next->data)
        {
            temp->next = temp->next->next;
            continue;
        }
        temp = temp->next;
    }
}
void main()
{
    int data,num;
    // printf("Enter number of nodes : ");
    // scanf("%i", &num);
    num = 4;
    printf("Enter data for node 1 : ");
    scanf("%i", &data);
    head = createnode(data);
    for ( int i = 2; i <=num; i++)
    {
        printf("Enter data for node %i : ", i);
        scanf("%i", &data);
        struct node*n = createnode(data);
        insert(n);
    }
    duplicate();
    struct node* traverse = head;
    while(traverse != NULL)
    {
        printf("%i\n",traverse->data);
        traverse = traverse->next;
    }
}