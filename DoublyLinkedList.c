#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int data;
    struct node* next;
    struct node* prev;
};
struct node* head;
struct node* createnode(int data)
{
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void insertnode(struct node* newnode, int position)
{
    struct node* temp = head;
    if (position == 0)
    {
        newnode->next = temp;
        temp->prev = newnode;
        head = newnode;
        return;
    }
    for ( int i = 0 ; i < position - 1 ;i ++)
        temp = temp->next;
    if(temp->next != NULL)
    {
        newnode->next  = temp->next;
        temp->next->prev = newnode;
    }    
    temp->next = newnode;
    newnode->prev = temp;
}

void deletenode(int position)
{
    struct node* temp = head;
    if (position == 0)
    {
        temp->next->prev = NULL;
        head = temp->next; 
    }
    for ( int i = 0 ; i < position - 1 ;i ++)
        temp = temp->next;
    temp->next->prev = temp;
    temp->next = temp->next->next;
}
void main()
{
    int n, data;
    printf("Enter number of nodes : ");
    scanf("%i", &n);
    printf("Enter Data at node 1 : ");
    scanf("%i", &data);
    head = createnode(data);
    for(int i = 2 ;i <= n ; i++)
    {
        printf("Enter Data at node %i : ", i);
        scanf("%i", &data);   
        insertnode(createnode(data),i-1);
    }
    struct node* temp = head;
    printf("Linked List : ");
    while(temp!= NULL)
    {
        printf("%i ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}