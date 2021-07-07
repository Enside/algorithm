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

void quick_sort_main(LIST_PP list_pp, LIST_PP array, int left, int right)
{
    LIST_P temp;
    int pivot = array[left]->data;
    int low = left;
    int high = right;

    while (low <= high)
    {
        while (array[low]->data < pivot)
        {
            low++;
        }
        while (array[high]->data > pivot)
        {
            high--;
        }
        if (low == high) //防止array[low]==array[high]==pivot死循环
        {
            low++;
            high--;
            break;
        }
        if (low < high)
        {
            temp = array[low];
            array[low] = array[high];
            array[high] = temp;

            if (low > 0)
            {
                array[low - 1]->next = array[low];
            }
            else
            {
                *list_pp = array[low];
            }
            array[low]->next = array[low + 1];
            if (high > 0)
            {
                array[high - 1]->next = array[high];
            }
            else
            {
                *list_pp = array[high];
            }
            array[high]->next = array[high + 1];
            low++;
            high--;
        }
    }
    if (high > left)
    {
        quick_sort_main(list_pp, array, left, high);
    }
    if (low < right)
    {
        quick_sort_main(list_pp, array, low, right);
    }
}

void quick_sort(LIST_PP list_pp)
{
    if (*list_pp)
    {
        LIST_P temp = *list_pp;
        LIST_P array[64];
        int count = 0;
        while (temp)
        {
            array[count] = temp;
            count++;
            temp = temp->next;
        }
        array[count] = NULL;
        quick_sort_main(list_pp, array, 0, count - 1);
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
            quick_sort(&list);
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
