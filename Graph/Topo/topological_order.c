#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct list_edge
{
    int edge[2];
    struct list_edge *in_next;
    struct list_edge *out_next;
} EDGE, *EDGE_P;

typedef struct adjacency_list
{
    int amount;
    int vertex[MAX];
    EDGE_P in_list[MAX];
    EDGE_P out_list[MAX];
} LIST, *LIST_P;

LIST_P creat_list()
{
    char select;
    LIST_P list = NULL;
    while (1)
    {
        printf("Add a Vertex(Y/N):");
        select = getchar();
        getchar();
        if (select == 'Y')
        {
            if (!list)
            {
                list = (LIST_P)malloc(sizeof(LIST));
            }
            list->vertex[list->amount] = list->amount;
            printf("Vertex V%d Added In.\n", list->amount);
            list->amount++;
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
    if (list)
    {
        EDGE_P new, in_pre[list->amount], out_pre;
        for (int i = 0; i < list->amount; i++)
        {
            for (int j = 0; j < list->amount; j++)
            {
                printf("Link V%d to V%d(Y/N):", i, j);
                select = getchar();
                getchar();
                if (select == 'Y')
                {
                    new = (EDGE_P)malloc(sizeof(EDGE));
                    new->edge[0] = i;
                    new->edge[1] = j;
                    new->out_next = NULL;
                    new->in_next = NULL;
                    if (!list->out_list[i])
                    {
                        list->out_list[i] = new;
                    }
                    else
                    {
                        out_pre->out_next = new;
                    }
                    if (!list->in_list[j])
                    {
                        list->in_list[j] = new;
                    }
                    else
                    {
                        in_pre[j]->in_next = new;
                    }
                    out_pre = new;
                    in_pre[j] = new;
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
        }
    }
    else
    {
        return NULL;
    }
    return list;
}

void print_list(LIST_P list)
{
    EDGE_P temp;
    printf("OutDegree:\n");
    for (int i = 0; i < list->amount; i++)
    {
        printf("V%d:", i);
        if (temp = list->out_list[i])
        {
            while (temp != NULL)
            {
                printf("<%d,%d> ", temp->edge[0], temp->edge[1]);
                temp = temp->out_next;
            }
        }
        else
        {
            printf("NULL");
        }
        putchar('\n');
    }
    printf("InDegree:\n");
    for (int i = 0; i < list->amount; i++)
    {
        printf("V%d:", i);
        if (temp = list->in_list[i])
        {
            while (temp != NULL)
            {
                printf("<%d,%d> ", temp->edge[0], temp->edge[1]);
                temp = temp->in_next;
            }
        }
        else
        {
            printf("NULL");
        }
        putchar('\n');
    }
}

int *topological_order(LIST_P list)
{
    int in_degree[MAX] = {0};
    int visited[MAX] = {0};
    int count_current = 0;
    int count_previous = 0;
    int *topo=(int *)malloc(sizeof(int)*list->amount);
    EDGE_P temp;
    for (int i = 0; i < list->amount; i++)
    {
        temp = list->in_list[i];
        while (temp != NULL)
        {
            in_degree[i]++;
            temp = temp->in_next;
        }
    }
    while (1)
    {
        for (int i = 0; i < list->amount; i++)
        {
            if (in_degree[i] == 0 && visited[i] == 0)
            {
                printf("%d\n", i);
                temp = list->out_list[i];
                while (temp != NULL)
                {
                    in_degree[temp->edge[1]]--;
                    temp = temp->out_next;
                }
                visited[i] = 1;
                topo[count_current]=i;
                count_current++;
            }
        }
        if (count_previous == count_current)
        {
            printf("Exsiting Loop!\n");
            return NULL;
        }
        else
        {
            if (count_current == list->amount)
            {
                return NULL;
            }
            else
            {
                count_previous = count_current;
            }
        }
    }
    return topo;
}

int main(int argc, char const *argv[])
{
    LIST_P list = creat_list();
    printf("Adjacency_List:\n");
    print_list(list);
    printf("Topological_Order:\n");
    topological_order(list);
    return 0;
}
