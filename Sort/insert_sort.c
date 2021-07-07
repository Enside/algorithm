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

void insert_sort(LIST_PP list_pp)
{
    if (*list_pp)
    {
        LIST_P temp_list = *list_pp;
        LIST_P pre, current, next;
        int temp_data;
        while (temp_list->next)
        {
            if (temp_list->next->data < temp_list->data)
            {
                pre = NULL;
                next = *list_pp;
                current = temp_list->next;
                temp_list->next = temp_list->next->next;
                while (current->data > next->data)
                {
                    pre = next;
                    next = next->next;
                }
                if (pre)
                {
                    pre->next = current;
                    current->next = next;
                }
                else
                {
                    current->next = next;
                    *list_pp = current;
                }
            }
            else
            {
                temp_list = temp_list->next;
            }
        }
    }
}

void print_list(LIST_P list_p)
{
    LIST_P temp_list = list_p;
    while (temp_list)
    {
        printf("%d\n", temp_list->data);
        temp_list = temp_list->next;
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
            insert_sort(&list);
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
