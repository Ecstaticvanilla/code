#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack 
{
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    return stack->array[stack->top--];
}

int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    return stack->array[stack->top];
}

void main() 
{
    int t, n;
    printf("Enter number of test cases: ");
    scanf("%d", &t);
    while (t--) 
    {
        printf("Enter number of towers: ");
        scanf("%d", &n);
        int heights[n];
        struct Stack* stack = createStack(n);
        printf("Enter heights of the towers: ");
        for (int j = 0; j < n; j++) 
            scanf("%d", &heights[j]);
        int range[n];
        for (int j = 0; j < n; j++) 
            range[j] = 1;
        for (int j = 0; j < n; j++) 
        {
            while (!isEmpty(stack) && heights[peek(stack)] <= heights[j]) 
                pop(stack);
            if (!isEmpty(stack)) 
                range[j] = j - peek(stack);
            else
                range[j] = j + 1;
            push(stack, j);
        }
        printf("Range: ");
        for (int j = 0; j < n; j++)
            printf("%d ", range[j]);
        printf("\n");
    }
}