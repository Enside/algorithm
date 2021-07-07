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
        LIST_P temp_list = *list_pp;
        while (temp_list->next)
        {
            temp_list = temp_list->next;
        }
        temp_list->next = new;
        return;
    }
}

void bubble_sort(LIST_P list_p)
{
    if (list_p)
    {
        LIST_P temp_list = list_p;
        int temp_data;
        int count = 0;
        _Bool flag = 1;
        while (temp_list->next)
        {
            if (temp_list->next->data < temp_list->data)
            {
                temp_data = temp_list->data;
                temp_list->data = temp_list->next->data;
                temp_list->next->data = temp_data;
            }
            temp_list = temp_list->next;
            count++;
        }
        for (int i = count; i > 0 && flag; i--)
        {
            flag = 0;
            temp_list = list_p;
            for (int j = 0; j < i - 1; j++)
            {
                if (temp_list->next->data < temp_list->data)
                {
                    temp_data = temp_list->data;
                    temp_list->data = temp_list->next->data;
                    temp_list->next->data = temp_data;
                    flag = 1;
                }
                temp_list = temp_list->next;
            }
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
            bubble_sort(list);
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
