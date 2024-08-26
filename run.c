#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue 
{
    int front, rear;
    unsigned capacity;
    int* petrol;
    int* distance;
};

struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->petrol = (int*)malloc(queue->capacity * sizeof(int));
    queue->distance = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isEmpty(struct Queue* queue)
{
    return (queue->front == queue->rear)||(queue->front == -1);
}

int isFull(struct Queue* queue)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
{
    return  ((queue->rear+1)%queue->capacity == queue->front);
}

void enqueue(struct Queue* queue, int petrol, int distance)
{
    if (isFull(queue))
    {
        printf("Queue is full");
        return;
    }
    else if(isEmpty(queue))
        queue->front = 0;
    else
    {
        queue->rear++;
        queue->petrol[queue->rear%queue->capacity] = petrol;
        queue->distance[queue->rear%queue->capacity] = distance;
    }
}

// int dequeuePetrol(struct Queue* queue)
// {
//     if (isEmpty(queue))
//         return 0;
//     return queue->petrol[queue->front++%queue->capacity];
// }
// int dequeueDistance(struct Queue* queue)
// {
//     if (isEmpty(queue))
//         return 0;
//     return queue->distance[queue->front++%queue->capacity];
// }
int main() 
{
    printf("Enter how many petrol pumps are present :-");
    int n;
    scanf("%d" ,&n);
    struct Queue* q = createQueue(n);
    int petrol[n];
    int distance[n];
    for (int i = 0 ; i < n+1 ;i++)
    {
        printf("Enter petrol available and queue capacity :- ");
        scanf("%i", &petrol[i]), 
        scanf("%i", &distance[i]);
        enqueue(q,petrol[i],distance[i]);
    }
    printf("Petrol : ");
    for (int i = q->front ; i <= q->rear ;i++%q->capacity)
        printf("%i ",q->petrol[i]);
    printf("\nDistance : ");
    for (int i = q->front ; i <= q->rear ;i++%q->capacity)
        printf("%i ", q->distance[i]);
    printf("\n");
    int difference[n];
    for (int i =  0; i < n ;i++)
        difference[i] = q->petrol[i] - q->distance[i];
    int cumulative = 0;
    int index;
    for (int i =  0; i < n ;i++)
    {
        cumulative = 0;
        for(int i = q->front; i < q->rear+1%n;i++%n)
        {
            cumulative += q->petrol[i] - q->distance[i];
            if(cumulative < 0)
                continue;
        }
        index = q->front;
    }
    for (int i = index ; i < index -1  ;i++%n)
        printf("%i" , i);
    return 0;
}