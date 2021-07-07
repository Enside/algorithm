#include <stdio.h>
#include <stdlib.h>

#define COUNT 10

typedef struct josephus
{
    int member;
    int code;
    struct josephus *next;
} LIST, *LIST_P, **LIST_PP;

void add_person(LIST_PP, int);
void init_person(LIST_PP);
void killer(LIST_PP);

void add_person(LIST_PP rear, int num)
{
    LIST_P new;
    new = (LIST_P)malloc(sizeof(LIST));
    new->member = num;
    srand(num);
    new->code = (rand() % 5) + 1;

    if (*rear == NULL)
    {
        new->next = new;
        *rear = new;
    }
    else
    {
        new->next = (*rear)->next;
        (*rear)->next = new;
        *rear = new;
    }
}

void init_person(LIST_PP rear)
{
    for (int i = 1; i <= COUNT; i++)
    {
        add_person(rear, i);
    }
}

void killer(LIST_PP rear)
{
    LIST_P temp = (*rear);       //存储被删除元素的前一个元素，初始为最后一个元素
    int code = temp->next->code; //存储被删除元素的code,初始为第一个元素的code
    
/////////////////////起始元素不删除自己//////////////////////////////////
    printf("起始元素是：%d\n", temp->next->member);
    printf("本轮密码是：%d\n", code);
    for (int i = code; i > 0; i--)
    {
        temp = temp->next;
    }
    printf("被删除的是：%d\n", temp->next->member); 
    temp->next = temp->next->next;
//////////////////////////////////////////////////////////////////////
    while (temp->next->next != temp)
    {
        printf("本轮密码是：%d\n", code);
        for (int i = code; i > 1; i--)
        {
            temp = temp->next;
        }
        printf("被删除的是：%d\n", temp->next->member); //打印被删除的号码
        code = temp->next->code;//存储被删除元素的code
        temp->next = temp->next->next;//删除元素
    }
    putchar('\n');
    printf("%d\n", temp->member);
    printf("%d\n", temp->next->member);
}

int main(int argc, char const *argv[])
{
    LIST_P Josephus = NULL;
    init_person(&Josephus);
    killer(&Josephus);
    return 0;
}