#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Elemtype char
#define Stacksize 10

typedef struct Stack
{
    Elemtype *base;
    Elemtype *top;
    int size;
} STACK, *STACK_P;

STACK_P init_stack(void);
void push_stack(STACK_P, Elemtype *);
void pop_stack(STACK_P, Elemtype *);
void print_stack(STACK_P);
int calculator(STACK_P);
int power(int, int);

STACK_P init_stack(void)
{
    STACK_P stack = (STACK_P)malloc(sizeof(STACK));
    stack->base = (Elemtype *)malloc(sizeof(Elemtype) * Stacksize);
    stack->top = stack->base;
    stack->size = Stacksize;

    return stack;
}

void push_stack(STACK_P stack, Elemtype *x)
{
    if (stack->top - stack->base == stack->size)
    {
        stack->base = (Elemtype *)realloc(stack->base, (stack->size + Stacksize) * sizeof(Elemtype));
        stack->top = stack->base + stack->size;
        stack->size += Stacksize;
    }
    *stack->top = *x;
    stack->top++;
}

void pop_stack(STACK_P stack, Elemtype *x)
{
    if (stack->top == stack->base)
    {
        printf("栈已空！\n");
    }
    else
    {
        *x = *--(stack->top);
        printf("%d已弹出！\n", *x);
    }
}

int calculator(STACK_P stack)
{
    char input[32];
    char output;
    int result=0;
    printf("请输入一个二进制数：");
    scanf("%s", input);
    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        push_stack(stack, &input[i]);
    }
    for (int i = 0; i < length; i++)
    {
        pop_stack(stack, &output);
        result += power(2,i)*(output-48);
    }
    return result;
}

int power(int x,int y)
{
    int product=1;
    for (int i = 0; i < y;i++)
    {
        product *= x;
    }
    return product;
}

int main(int argc, char const *argv[])
{
    STACK_P stack = init_stack();
    printf("结果是：%d\n", calculator(stack));
    return 0;
}
