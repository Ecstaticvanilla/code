#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack 
{
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
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

void push(struct Stack* stack, char item)
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

int precedence(char op) 
{
    switch(op) 
    {
        case '~': return 4;
        case '^': return 3;
        case '*': return 2;
        case '/': return 2;
        case '+': return 1;
        case '-': return 1;
        default: return 0;
    }
}

int isOperator(char ch) 
{
    return (ch == '~' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int main() 
{
    printf("Enter length of equation: ");
    int size;
    scanf("%i", &size);
    getchar(); 
    printf("Enter equation: ");
    char input[size + 1];
    scanf(" %[^\n]s", input);
    int i = size-1;
    struct Stack* stack = createStack(strlen(input));
    char output[strlen(input)];
    int output_pointer = 0;

    while(i >= 0) 
    {
        if (input[i] == ')') 
        {
            push(stack, input[i]);
        } 
        else if (input[i] == '(') 
        {
            while (!isEmpty(stack) && peek(stack) != ')') 
            {
                output[output_pointer] = pop(stack);
                output_pointer++;
            }
            pop(stack);
        } 
        else if (isOperator(input[i])) 
        {
            while (!isEmpty(stack) && precedence(peek(stack)) > precedence(input[i])) 
            {
                output[output_pointer] = pop(stack);
                output_pointer++;
            }
            push(stack, input[i]);
        } 
        else 
        {
            output[output_pointer] = input[i];
            output_pointer++;
        }
        i--;
    }
    while (!isEmpty(stack)) 
    {
        output[output_pointer] = pop(stack);
        output_pointer++;
    }
    output[output_pointer] = '\0';
    for (int i = 0; i < strlen(output); i++) 
        push(stack, output[i]);
    while (!isEmpty(stack)) 
        printf("%c", pop(stack));
    return 0;
}