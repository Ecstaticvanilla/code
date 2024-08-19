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

int isOperator(char c)
{
    return (c == '+' ||c=='-' || c=='*'||c=='/' || c == '~' ||c == '^' );
}



void main()
{
    printf("Enter length of equation: ");
    int size;
    scanf("%i", &size);
    getchar(); 
    printf("Enter equation: ");
    char input[size];
    scanf("%[^\n]s" , input);
    struct Stack* stack = createStack(size);
    int i = 0;
    while(input[i] != '\0')
    {
        int a,b,c;
        if(isOperator(input[i]))
        {
            a = 0;
            b = 0;
            c = 0;
            if(input[i] == '~')
                c = -(pop(stack));
            else
            {
                a = (pop(stack));
                b = (pop(stack));
                if(input[i] == '+')
                    c = b+a;            
                else if(input[i] == '-')
                    c = b-a;            
                else if(input[i] == '*')
                    c = b*a;            
                else if(input[i] == '/')
                    c = b/a;            
                else if(input[i] == '^')
                {
                    c = 1;
                    for(int i = 0 ; i < a ; i++)
                        c *= b;
                }
            }   
            push(stack,(c));        
        }
        else
            push(stack,input[i] - '0');
        printf("Stack : ");
        for(int j = stack->top ;j >=0; j--)
            printf("%i ",stack->array[j]);
        printf("\n");
        i++;
    }
    printf("Answer is : %i\n",pop(stack));
}