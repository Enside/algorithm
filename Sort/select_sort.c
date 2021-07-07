#include <stdio.h>
#include <stdlib.h>

typedef struct link_list
{
    int data;
    struct link_list *next;
} LIST, *LIST_P, **LIST_PP;

void add_data(LIST_PP list_pp, int data)
{
    LIST_P new = (LIST_P)malloc(sizeof(LIST));
    new->data = data;
    new->next = NULL;
    if (!*list_pp)
    {
        *list_pp = new;
        return;
    }
    else
    {
        LIST_P list_base = *list_pp;
        while (list_base->next)
        {
            list_base = list_base->next;
        }
        list_base->next = new;
        return;
    }
}

void select_sort(LIST_P list_p)
{
    if (list_p)
    {
        LIST_P list_base = list_p;
        LIST_P list_point;
        LIST_P list_min;
        int data_min;
        while (list_base)
        {
            list_min = list_base;
            list_point = list_base->next;
            while (list_point)
            {
                if (list_point->data < list_min->data)
                {
                    list_min = list_point;
                }
                list_point = list_point->next;
            }
            data_min = list_min->data;
            list_min->data = list_base->data;
            list_base->data = data_min;
            list_base = list_base->next;
        }
    }
}

void print_list(LIST_P list_p)
{
    LIST_P temp = list_p;
    while (temp)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int main(int argc, char const *argv[])
{
    LIST_P list = NULL;
    int select;
    int num;
    while (1)
    {
        printf("\n1：添加数据\n2：排序数据\n3：打印数据\n4：退出程序\n请输入选项：");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            printf("输入要添加的数据：");
            scanf("%d", &num);
            add_data(&list, num);
            continue;
        case 2:
            select_sort(list);
            continue;
        case 3:
            print_list(list);
            continue;
        case 4:
            break;
        default:
            printf("输入错误请重新输入！");
            continue;
        }
        break;
    }
    return 0;
}
