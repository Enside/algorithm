#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StackEmpty -1
#define StackSize 32

typedef struct Stack
{
    char text[StackSize];
    int top;
    int size;
} STACK, *STACK_P;

STACK_P init_stack(void);
void input_stack(STACK_P);
int pop_stack(STACK_P);
void match_stack(STACK_P);

STACK_P init_stack(void)
{
    STACK_P stack = (STACK_P)malloc(sizeof(STACK));
    stack->top = 0;
    stack->size = StackSize;
    return stack;
}

void input_stack(STACK_P stack)
{
    printf("请输入一段文字：");
    scanf("%s", stack->text);
    int length = strlen(stack->text);
    stack->top = length - 1;
}

int pop_stack(STACK_P stack)
{
    if (stack->top != -1)
    {
        char output;
        output = stack->text[stack->top];
        stack->top--;
        return output;
    }
    else
    {
        return StackEmpty;
    }
}

void match_stack(STACK_P stack)
{
    char temp;
    int result[4] = {0, 0, 0, 0};
    char bracket[4][3] = {"()", "[]", "{}", "<>"};
    while ((temp = pop_stack(stack)) != StackEmpty)
    {
        switch (temp)
        {
        case '(':
            result[0]++;
            continue;
        case '[':
            result[1]++;
            continue;
        case '{':
            result[2]++;
            continue;
        case '<':
            result[3]++;
            continue;
        case ')':
            result[0]++;
            continue;
        case ']':
            result[1]++;
            continue;
        case '}':
            result[2]++;
            continue;
        case '>':
            result[3]++;
            continue;
        default:
            continue;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (result[i] % 2 == 0 && result[i] != 0)
        {
            printf("%s匹配！\n", bracket[i]);
        }
        else if (result[i] != 0)
        {
            printf("%s不匹配！\n", bracket[i]);
        }
        else
        {
            printf("未检测到%s！\n", bracket[i]);
        }
    }
}

int main(int argc, char const *argv[])
{
    STACK_P stack = init_stack();
    input_stack(stack);
    match_stack(stack);
    return 0;
}
