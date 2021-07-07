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
        LIST_P list_temp = *list_pp;
        while (list_temp->next)
        {
            list_temp = list_temp->next;
        }
        list_temp->next = new;
        return;
    }
}

void adjust_heap(LIST_PP heap, int i, int count)
{
    LIST_P temp;
    if (i * 2 + 1 <= count && heap[i]->data < heap[i * 2 + 1]->data)
    {
        temp = heap[i];
        heap[i] = heap[i * 2 + 1];
        heap[i * 2 + 1] = temp;
        if (i > 0)
        {
            heap[i - 1]->next = heap[i];
        }
        heap[i]->next = heap[i + 1];
        heap[i * 2]->next = heap[i * 2 + 1];
        heap[i * 2 + 1]->next = heap[i * 2 + 2];
        adjust_heap(heap, i * 2 + 1, count);
    }
    if (i * 2 + 2 <= count && heap[i]->data < heap[i * 2 + 2]->data)
    {
        temp = heap[i];
        heap[i] = heap[i * 2 + 2];
        heap[i * 2 + 2] = temp;
        if (i > 0)
        {
            heap[i - 1]->next = heap[i];
        }
        heap[i]->next = heap[i + 1];
        heap[i * 2 + 1]->next = heap[i * 2 + 2];
        heap[i * 2 + 2]->next = heap[i * 2 + 3];
        adjust_heap(heap, i * 2 + 2, count);
    }
}

void heap_sort(LIST_PP list_pp)
{
    if (*list_pp)
    {
        LIST_P heap[128];
        LIST_P temp = *list_pp;
        int count = 0;
        while (temp)
        {
            heap[count++] = temp;
            temp = temp->next;
        }
        heap[count] = NULL;
        for (int i = count - 1; i > 0; i--)
        {
            for (int j = (i - 1) / 2; j >= 0; j--)
            {
                adjust_heap(heap, j, i);
            }
            temp = heap[i];
            heap[i] = heap[0];
            heap[0] = temp;
            heap[0]->next = heap[1];
            heap[i - 1]->next = heap[i];
            heap[i]->next = heap[i + 1];
        }
        *list_pp = heap[0];
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
            heap_sort(&list);
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
