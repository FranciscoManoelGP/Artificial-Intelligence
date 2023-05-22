#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 8
#define QUEUE_SIZE 100

typedef struct
{
    int items[QUEUE_SIZE];
    int front, rear, num_items;
} CircularQueue;

CircularQueue __circular_queue__()
{
    CircularQueue cqueue;

    cqueue.front = 0;
    cqueue.rear = -1;
    cqueue.num_items = 0;

    return cqueue;
}

bool queue_is_full(CircularQueue *cqueue)
{
    return cqueue->num_items == QUEUE_SIZE;
}

void insert_and_test(CircularQueue *cqueue, int item, int *queue_overflow)
{
    *queue_overflow = queue_is_full(cqueue);
    if (!*queue_overflow)
    {
        cqueue->rear = (cqueue->rear + 1) % QUEUE_SIZE;
        cqueue->items[cqueue->rear] = item;
        cqueue->num_items++;
    }
}

bool queue_is_empty(CircularQueue *cqueue)
{
    return cqueue->num_items == 0;
}

int delete_and_test(CircularQueue *cqueue, int *queue_underflow)
{
    int old_front = cqueue->front;

    *queue_underflow = queue_is_empty(cqueue);
    if (!*queue_underflow)
    {
        cqueue->front = (cqueue->front + 1) % QUEUE_SIZE;
        cqueue->num_items--;
        return cqueue->items[old_front];
    }
    return -1;
}

bool search_hange(CircularQueue *open_queue, int D[8][8], int start, int goal)
{
    int queue_overflow, queue_underflow;
    bool visited[N] = {false};

    insert_and_test(open_queue, start, &queue_overflow);

    while (!queue_is_empty(open_queue))
    {
        int state = delete_and_test(open_queue, &queue_underflow);

        for (int i = 0; i < N; i++)
        {
            if (D[state][i] == 1 && !visited[i])
            {
                visited[i] = true;
                printf("%d | %d\n", state, i);
                if (i == goal)
                {
                    return true;
                }

                insert_and_test(open_queue, i, &queue_overflow);
            }
        }
    }
    return false;
}

int main()
{
    int D[8][8] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0}};

    CircularQueue open_queue = __circular_queue__();

    int start = 0, goal = 7;

    if (search_hange(&open_queue, D, start, goal))
    {
        printf("Goal");
    }
    else
    {
        printf("Not found\n");
    }

    return 0;
}