#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define INFINITY 65535

typedef struct adjacency_matrix
{
    int amount;
    int vertex[MAX];
    int matrix[MAX][MAX];
} MATRIX, *MATRIX_P;

MATRIX_P creat_matrix()
{
    char select;
    MATRIX_P matrix = NULL;
    while (1)
    {
        printf("Add a Vertex(Y/N):");
        select = getchar();
        getchar();
        if (select == 'Y')
        {
            if (!matrix)
            {
                matrix = (MATRIX_P)malloc(sizeof(MATRIX));
                matrix->amount = 0;
            }
            matrix->vertex[matrix->amount] = matrix->amount;
            printf("Vertex V%d Added In.\n", matrix->amount);
            matrix->amount++;
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
    if (matrix)
    {
        for (int i = 0; i < matrix->amount; i++)
        {
            for (int j = 0; j < matrix->amount; j++)
            {
                if (j > i)
                {
                    printf("Link V%d to V%d(Y/N):", i, j);
                    select = getchar();
                    getchar();
                    if (select == 'Y')
                    {
                        printf("Input Weight:");
                        scanf("%d", &matrix->matrix[i][j]);
                        getchar();
                    }
                    else if (select == 'N')
                    {
                        matrix->matrix[i][j] = INFINITY;
                    }
                    else
                    {
                        printf("Error Input!\n");
                        j--;
                    }
                }
                else
                {
                    if (j == i)
                    {
                        matrix->matrix[i][j] = 0;
                    }
                    else
                    {
                        matrix->matrix[i][j] = matrix->matrix[j][i];
                    }
                }
            }
        }
    }
    else
    {
        return NULL;
    }
    return matrix;
}

void print_matrix(MATRIX_P matrix)
{
    if (matrix)
    {
        for (int i = 0; i < matrix->amount; i++)
        {
            for (int j = 0; j < matrix->amount; j++)
            {
                if (matrix->matrix[i][j] == INFINITY)
                {
                    printf("%-3c", '#');
                }
                else
                {
                    printf("%-3d", matrix->matrix[i][j]);
                }
            }
            putchar('\n');
        }
    }
}

void dijkstra(MATRIX_P matrix, int origin)
{
    int distance[MAX];
    int min = INFINITY;
    int min_vertex = origin;
    int found_count = 1;
    int fount_vertex[MAX];
    int path[MAX][MAX];
    path[origin][0] = origin;

    for (int i = 0; i < MAX; i++)
    {
        distance[i] = INFINITY;
    }
    distance[origin] = 0;

    while (found_count < matrix->amount)
    {
        min = INFINITY;
        for (int i = 0; i < matrix->amount; i++)
        {
            if (fount_vertex[i] != 1 && distance[i] < min)
            {
                min = distance[i];
                min_vertex = i;
            }
        }
        fount_vertex[min_vertex] = 1;
        for (int i = 0; i < matrix->amount; i++)
        {
            if (i != min_vertex)
            {
                if (min + matrix->matrix[min_vertex][i] < distance[i])
                {
                    distance[i] = min + matrix->matrix[min_vertex][i];
                    for (int j = 0; j < matrix->amount; j++)
                    {
                        path[i][j] = path[min_vertex][j];
                        if (path[min_vertex][j] == min_vertex)
                        {
                            path[i][j + 1] = i;
                            break;
                        }
                    }
                }
            }
        }

        found_count++;
        // Debug:
        // printf("min:%d,min_vertex:%d\n", min, min_vertex);
        // for (int i = 0; i < matrix->amount; i++)
        // {
        //     printf("%d:%d\n", i, distance[i]);
        // }
        // putchar('\n');
    }

    for (int i = 0; i < matrix->amount; i++)
    {
        printf("V%d to V%d:", origin, i);
        for (int j = 0; j < matrix->amount; j++)
        {
            printf("%-3d", path[i][j]);
            if (path[i][j] == i)
            {
                break;
            }
        }
        putchar('\n');
    }
}

int main(int argc, char const *argv[])
{
    MATRIX_P matrix = creat_matrix();
    printf("Adjacency_Matrix:\n");
    print_matrix(matrix);
    printf("Shortest_Path:\n");
    dijkstra(matrix, 0);
    return 0;
}
