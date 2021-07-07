#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define INFINITY 65535

typedef struct edgeset_array
{
    int vertex_amount;
    int edge_amount;
    int vertex[MAX];
    int edge[MAX * (MAX - 1) / 2][2];
    int weight[MAX * (MAX - 1) / 2];
} ARRAY, *ARRAY_P;

typedef struct Tree
{
    int vertex;
    int child_count;
    struct Tree *child[MAX];
} TREE, *TREE_P;

void sort_array(ARRAY_P array, int first, int last)
{
    int temp_weight;
    int temp_edge[2];
    int pivot = array->weight[(first + last) / 2];
    int low = first;
    int high = last;

    while (low <= high)
    {
        while (array->weight[low] < pivot)
        {
            low++;
        }
        while (array->weight[high] > pivot)
        {
            high--;
        }
        if (low <= high)
        {
            temp_weight = array->weight[low];
            array->weight[low] = array->weight[high];
            array->weight[high] = temp_weight;
            temp_edge[0] = array->edge[low][0];
            temp_edge[1] = array->edge[low][1];
            array->edge[low][0] = array->edge[high][0];
            array->edge[low][1] = array->edge[high][1];
            array->edge[high][0] = temp_edge[0];
            array->edge[high][1] = temp_edge[1];
            low++;
            high--;
        }
    }
    if (high > first)
    {
        sort_array(array, first, high);
    }
    if (low < last)
    {
        sort_array(array, low, last);
    }
}

ARRAY_P creat_array()
{
    char select;
    ARRAY_P array = NULL;
    while (1)
    {
        printf("Add a Vertex(Y/N):");
        select = getchar();
        getchar();
        if (select == 'Y')
        {
            if (!array)
            {
                array = (ARRAY_P)malloc(sizeof(ARRAY));
                array->vertex_amount = 0;
                array->edge_amount = 0;
            }
            array->vertex[array->vertex_amount] = array->vertex_amount;
            printf("Vertex V%d Added In.\n", array->vertex_amount);
            array->vertex_amount++;
        }
        else if (select == 'N')
        {
            break;
        }
        else
        {
            printf("Error Input!\n");
        }
    }
    if (array)
    {
        for (int i = 0; i < array->vertex_amount; i++)
        {
            for (int j = 0; j < array->vertex_amount; j++)
            {
                if (j > i)
                {
                    printf("Link V%d to V%d(Y/N):", i, j);
                    select = getchar();
                    getchar();
                    if (select == 'Y')
                    {
                        printf("Input Weight:");
                        scanf("%d", &array->weight[array->edge_amount]);
                        getchar();
                        array->edge[array->edge_amount][0] = i;
                        array->edge[array->edge_amount][1] = j;
                        array->edge_amount++;
                    }
                    else if (select == 'N')
                    {
                        continue;
                    }
                    else
                    {
                        printf("Error Input!\n");
                        j--;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
    else
    {
        return NULL;
    }
    sort_array(array, 0, array->edge_amount - 1);
    return array;
}

void print_array(ARRAY_P array)
{
    if (array)
    {
        for (int i = 0; i < array->edge_amount; i++)
        {
            printf("(%d,%d)->%d\n", array->edge[i][0], array->edge[i][1], array->weight[i]);
        }
    }
}

void kruskal(ARRAY_P array)
{
    if (array)
    {
        int linked[MAX];
        linked[0] = array->edge[0][0];
        int linked_amount = 1;
        int linked_flag_0 = 0;
        int linked_flag_1 = 0;
        while (linked_amount < array->vertex_amount)
        {
            for (int i = 0; i < array->edge_amount; i++)
            {
                linked_flag_0 = 0;
                linked_flag_1 = 0;
                for (int j = 0; j < linked_amount; j++)
                {
                    if (array->edge[i][0] == linked[j])
                    {
                        linked_flag_0 = 1;
                    }
                    if (array->edge[i][1] == linked[j])
                    {
                        linked_flag_1 = 1;
                    }
                }
                if (linked_flag_0 == 1 && linked_flag_1 != 1)
                {
                    printf("(%d,%d)->%d\n", array->edge[i][0], array->edge[i][1], array->weight[i]);
                    linked[linked_amount] = array->edge[i][1];
                    linked_amount++;
                }
                if (linked_flag_0 != 1 && linked_flag_1 == 1)
                {
                    printf("(%d,%d)->%d\n", array->edge[i][0], array->edge[i][1], array->weight[i]);
                    linked[linked_amount] = array->edge[i][0];
                    linked_amount++;
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    ARRAY_P array = creat_array();
    printf("Adjacency_Matrix:\n");
    print_array(array);
    printf("Min_Span_Tree:\n");
    kruskal(array);
    return 0;
}
