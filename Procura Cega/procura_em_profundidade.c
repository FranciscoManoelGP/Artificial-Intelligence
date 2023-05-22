#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 8
#define STACK_SIZE 100

typedef struct
{
    int items[STACK_SIZE];
    int top;
} Stack;

Stack __stack__()
{
    Stack stack;
    stack.top = -1;

    return stack;
}

// push and test
bool stack_is_full(Stack *stack)
{
    return (stack->top >= STACK_SIZE - 1);
}

void push_and_test(Stack *stack, int item, int *stack_overflow)
{
    *stack_overflow = stack_is_full(stack);
    if (!*stack_overflow)
        stack->items[++stack->top] = item;
}

// pop and test
bool stack_is_empty(Stack *stack)
{
    return stack->top < 0;
}

int pop_and_test(Stack *stack, int *stack_underflow)
{
    *stack_underflow = stack_is_empty(stack);
    if (!*stack_underflow)
        return stack->items[stack->top--];
    return -1;
}

bool search_deep(Stack *stack, int D[N][N], int start, int goal)
{
    int stack_overflow, stack_underflow;
    bool visited[N] = {false};

    push_and_test(stack, start, &stack_overflow);

    while (!stack_is_empty(stack))
    {
        int state = pop_and_test(stack, &stack_underflow);

        visited[state] = true;
        for (int i = 0; i < N; i++)
        {
            if (D[state][i] == 1 && !visited[i])
            {
                printf("%d | %d\n", state, i);
                if (state == goal)
                {
                    return true;
                }
                push_and_test(stack, i, &stack_overflow);
            }
        }
    }
    return false;
}

int main()
{
    int D[N][N] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};

    Stack stack = __stack__(&stack);

    int start = 0, goal = 100;

    if (search_deep(&stack, D, start, goal))
    {
        printf("Goal\n");
    }
    else
    {
        printf("Not found\n");
    }

    return 0;
}