#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int *data;
    int amount;
} LIST, *LIST_P, **LIST_PP;

void add_data(LIST_P list_p, int data)
{
    list_p->data[list_p->amount] = data;
    list_p->amount++;
}

void merging(LIST_P list1, LIST_P list2)
{
    // printf("Merging\n");
    int temp[20];
    int i = 0, j = 0, k = 0;
    // for (int x = 0; x < list1->amount; x++)
    // {
    //     printf("//list1->data[%d]=%d\n", x, list1->data[x]);
    // }
    // for (int x = 0; x < list2->amount; x++)
    // {
    //     printf("//list2->data[%d]=%d\n", x, list2->data[x]);
    // }
    while (i < list1->amount && j < list2->amount)
    {
        if (list1->data[i] < list2->data[j])
        {
            temp[k++] = list1->data[i++];
            // printf("//list1->data[i] < list2->data[j]\n//temp[%d]=list1->data[%d]\n", k - 1, i - 1);
        }
        else
        {
            temp[k++] = list2->data[j++];
            // printf("//list1->data[i] < list2->data[j]\n//temp[%d]=list2->data[%d]\n", k - 1, j - 1);
        }
    }

    while (i < list1->amount)
    {
        temp[k++] =list1->data[i++];
    }
    while (j < list2->amount)
    {
        temp[k++] = list2->data[j++];
    }
    for (int m = 0; m < list1->amount + list2->amount; m++)
    {
        list1->data[m] = temp[m];
        // printf("//tmep[%d]=%d\n", m, temp[m]);
    }
}

void merge_sort(LIST_P list_p)
{
    if (list_p->amount > 1)
    {
        LIST_P list1 = (LIST_P)malloc(sizeof(LIST_P));
        list1->data = list_p->data;
        list1->amount = list_p->amount / 2;
        LIST_P list2 = (LIST_P)malloc(sizeof(LIST_P));
        list2->data = list_p->data + list1->amount;
        list2->amount = list_p->amount - list1->amount;

        merge_sort(list1);
        merge_sort(list2);
        merging(list1, list2);
    }
}

void print_list(LIST_P list_p)
{
    for (int i = 0; i < list_p->amount; i++)
    {
        printf("%d\n", list_p->data[i]);
    }
}

int main(int argc, char const *argv[])
{
    LIST_P list = (LIST_P)malloc(sizeof(LIST));
    list->amount = 0;
    list->data = (int *)malloc(sizeof(int) * 20);
    int select;
    int num;

    while (1)
    {
        printf("\n1:ADD\n2:SORT\n3:PRINT\n4:QUIT\nSELECT:");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            printf("INPUT:");
            scanf("%d", &num);
            add_data(list, num);
            continue;
        case 2:
            merge_sort(list);
            continue;
        case 3:
            print_list(list);
            continue;
        case 4:
            break;
        default:
            printf("ERROR!");
            continue;
        }
        break;
    }
    return 0;
}
