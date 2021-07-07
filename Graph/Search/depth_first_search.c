#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define INFINITY 65565

typedef struct adjacency_matrix
{
    int amount;
    int vertex[MAX];
    short matrix[MAX][MAX];
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
                printf("Link V%d to V%d(Y/N):", i, j);
                select = getchar();
                getchar();
                if (select == 'Y')
                {
                    matrix->matrix[i][j] = 1;
                }
                else if (select == 'N')
                {
                    matrix->matrix[i][j] == INFINITY;
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

void depth_first_search(MATRIX_P matrix, int start)
{
    static int visited[MAX] = {0};
    visited[start] = 1;
    int flag = 0;
    for (int i = 0; i < matrix->amount; i++)
    {
        if (matrix->matrix[start][i] != 0)
        {
            flag = 1;
            printf("<%d,%d>\n", start, i);
            if (visited[i] == 0)
            {
                depth_first_search(matrix, i);
            }
        }
    }
    if (flag == 0)
    {
        printf("(%d)\n", start);
    }
    for (int i = 0; i < matrix->amount; i++)
    {
        if (visited[i] == 0)
        {
            depth_first_search(matrix, i);
        }
    }
    return;
}

int main(int argc, char const *argv[])
{
    MATRIX_P matrix = creat_matrix();
    printf("Adjacency_Matrix:\n");
    print_matrix(matrix);
    printf("Depth_First_Search:\n");
    depth_first_search(matrix, 0);
    return 0;
}
