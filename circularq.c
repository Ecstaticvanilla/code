#include <stdio.h>
#include <stdlib.h>

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
    return queue->front == (queue->rear + 1) % queue->capacity || queue->front == -1;
}

int isFull(struct Queue* queue) 
{
    return (queue->rear + 1) % queue->capacity == queue->front;
}

void enqueue(struct Queue* queue, int petrol, int distance) {
    if (isFull(queue)) 
    {
        printf("Queue is full\n");
        return;
    }
    if(isEmpty(queue))
        queue->front = 0;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->petrol[queue->rear] = petrol;
    queue->distance[queue->rear] = distance;
}

int canCompleteTour(struct Queue* queue, int front, int n) 
{
    int petrol = 0, distance = 0;
    int count = 0;
    int i = front;
    
    while (count < n) 
    {
        petrol += queue->petrol[i];
        distance += queue->distance[i];
        if (petrol < distance)
            return 0; 
        i = (i + 1) % queue->capacity;
        count++;
    }
    return 1; 
}

void findTours(struct Queue* queue, int n) 
{
    int totalPetrol = 0, totalDistance = 0;
    for (int i = 0; i < n; i++) 
    {
        totalPetrol += queue->petrol[i];
        totalDistance += queue->distance[i];
    }
    if (totalPetrol < totalDistance) 
    {
        printf("No possible tour\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (canCompleteTour(queue, i, n)) 
        {
            printf("Tour starting at pump %d\n", i + 1);
        }
    }
}

void main() 
{
    printf("Enter the number of petrol pumps: ");
    int n;
    scanf("%d", &n);
    struct Queue* queue = createQueue(n);
    for (int i = 0; i < n; i++) 
    {
        int petrol, distance;
        printf("Enter petrol available and distance to next pump for pump %d: ", i + 1);
        scanf("%d %d", &petrol, &distance);
        enqueue(queue, petrol, distance);
    }
    findTours(queue, n);
}
