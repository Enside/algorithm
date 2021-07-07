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

void shell_sort(LIST_PP list_pp)
{
    if (*list_pp)
    {
        LIST_P list_array[64];
        int count = 0;
        LIST_P temp = *list_pp;
        while (temp)
        {
            list_array[count] = temp;
            count++;
            temp = temp->next;
        }
        list_array[count] = NULL;
        int increment = count;
        while (increment > 1)
        {
            increment = increment / 3 + 1;
            for (int i = 0; i < count - increment; i++)
            {
                if (list_array[i]->data > list_array[i + increment]->data)
                {
                    temp = list_array[i];
                    list_array[i] = list_array[i + increment];
                    list_array[i + increment] = temp;

                    if (i > 0)
                    {
                        list_array[i - 1]->next = list_array[i];
                    }
                    else
                    {
                        *list_pp = list_array[i];
                    }
                    list_array[i]->next = list_array[i + 1];
                    list_array[i + increment - 1]->next = list_array[i + increment];
                    list_array[i + increment]->next = list_array[i + increment + 1];
                }
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
            shell_sort(&list);
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
