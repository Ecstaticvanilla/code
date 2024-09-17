#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int capacity;
    int top;
    int *array;
}Stack;

Stack* createStack(int capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity*sizeof(int));
    return stack;
}

int isFull(Stack* stack)
{
    return stack->top == stack->capacity-1;
}
int isEmpty(Stack* stack)
{
    return stack->top == -1;
}
void push(Stack* stack, int data)
{
    if(isFull(stack))
        return;
    stack->array[++stack->top] = data;
}
int peek(Stack* stack)
{
    if(isEmpty(stack))
        return 404;
    return stack->array[stack->top];
}
int pop(Stack* stack)
{
    if(isEmpty(stack))
        return 404;
    return stack->array[stack->top--];
}
void main()
{
    int size;
    int size_stack = 0;
    printf("Enter Size of expression : ");
    scanf("%i", &size);
    char input[size];
    printf("Enter expression : \n");
    getchar();
    scanf("%[^\n]s", input);
    for(int i = 0 ; i < size ; i++)
    {
        if(input[i] == '(')
            size_stack++;
    }
    Stack* stack = createStack(size_stack);
    int brackets [size_stack][2];
    int bracket_numbers = 0;
    for(int i = 0 ; i < size ; i++)
    {
        if(input[i] == '(')
        {
            push(stack, i);
        }
        else if(input[i] == ')')
        {
            brackets[bracket_numbers][0] = pop(stack);
            brackets[bracket_numbers][1] = i;
            bracket_numbers++;
        }
        printf("Stack : ");
        for(int i = 0 ; i <= stack->top ; i++)
            printf(" %i", stack->array[i]);
        printf("\n");
    }
    if (!isEmpty(stack))
        printf("BRACKETS NOT COMPLETE\n");
    else
    {
        for(int i = 0 ; i < size_stack ; i++)
            printf("(%i , %i)\n", brackets[i][0], brackets[i][1]);
    }
}