#include <stdio.h>
#include <stdlib.h>

#define COUNT 41

typedef struct josephus
{
    int member;
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
    LIST_P temp = *rear;//被删除的元素的前一个元素

    for (int i = COUNT; i > 2; i--)
    {
        temp = temp->next->next;
        printf("%d\n", temp->next->member);
        temp->next = temp->next->next;
    }
    putchar("\n");
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