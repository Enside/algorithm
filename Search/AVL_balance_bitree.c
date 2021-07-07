#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct balance_bitree
{
    int data;
    int cur;
    int factor;
    struct balance_bitree *high_child;
    struct balance_bitree *low_child;
    struct balance_bitree *parent;
} TREE, *TREE_P;

typedef struct data
{
    int data[MAX];
    int amount;
    TREE_P balance_bitree;
} DATA, *DATA_P;

DATA_P init_data()
{
    DATA_P data = (DATA_P)malloc(sizeof(DATA));
    return data;
}

int calculate_factor(TREE_P tree)
{
    if (!tree)
    {
        return 0;
    }
    else
    {
        int low = calculate_factor(tree->low_child);
        int high = calculate_factor(tree->high_child);
        tree->factor = low - high;
        if (low >= high)
        {
            return low + 1;
        }
        else
        {
            return high + 1;
        }
    }
}

void revise_tree(TREE_P tree, DATA_P data)
{
    if (tree)
    {
        TREE_P temp, new, parent;
        if (tree->factor >= 2)
        {
            switch (tree->low_child->factor)
            {
            case 1:
                parent = tree->parent;
                temp = tree->low_child->high_child;
                new = tree->low_child;
                new->high_child = tree;
                tree->parent = new;
                tree->low_child = temp;
                if (temp)
                {
                    temp->parent = new;
                }
                break;
            case 0:
                parent = tree->parent;
                new = tree->low_child->high_child;
                temp = tree->low_child;
                temp->high_child = NULL;
                tree->low_child = NULL;
                new->low_child = temp;
                temp->parent = new;
                new->high_child = tree;
                tree->parent = new;
                break;
            case -1:
                parent = tree->parent;
                new = tree->low_child->high_child;
                temp = tree->low_child;
                tree->low_child = new->high_child;
                if (new->high_child)
                {
                    new->high_child->parent = tree;
                }
                temp->high_child = new->low_child;
                if (new->low_child)
                {
                    new->low_child->parent = temp;
                }
                new->low_child = temp;
                temp->parent = new;
                new->high_child = tree;
                tree->parent = new;
                break;
            default:
                revise_tree(tree->low_child, data);
                return;
            }
            if (parent)
            {
                parent->low_child = new;
                new->parent = parent;
            }
            else
            {
                data->balance_bitree = new;
                new->parent = NULL;
            }
            return;
        }
        else if (tree->factor <= -2)
        {
            switch (tree->high_child->factor)
            {
            case -1:
                parent = tree->parent;
                temp = tree->high_child->low_child;
                new = tree->high_child;
                new->low_child = tree;
                tree->parent = new;
                tree->high_child = temp;
                if (temp)
                {
                    temp->parent = new;
                }
                break;
            case 0:
                parent = tree->parent;
                new = tree->high_child->low_child;
                temp = tree->high_child;
                temp->low_child = NULL;
                tree->high_child = NULL;
                new->high_child = temp;
                temp->parent = new;
                new->low_child = tree;
                tree->parent = new;
                break;
            case 1:
                parent = tree->parent;
                new = tree->high_child->low_child;
                temp = tree->high_child;
                tree->high_child = new->low_child;
                if (new->low_child)
                {
                    new->low_child->parent = tree;
                }
                temp->low_child = new->high_child;
                if (new->high_child)
                {
                    new->high_child->parent = temp;
                }
                new->low_child = tree;
                tree->parent = new;
                new->high_child = temp;
                temp->parent = new;
                break;
            default:
                revise_tree(tree->high_child, data);
                return;
            }
            if (parent)
            {
                parent->high_child = new;
                new->parent = parent;
            }
            else
            {
                data->balance_bitree = new;
                new->parent = NULL;
            }
            return;
        }
        else
        {
            revise_tree(tree->low_child, data);
            revise_tree(tree->high_child, data);
        }
    }
}

void add_data(DATA_P data, int num)
{
    TREE_P temp, pre, change;

    data->data[data->amount] = num;

    if (data->amount == 0)
    {
        data->balance_bitree = (TREE_P)malloc(sizeof(TREE));
        data->balance_bitree->high_child = NULL;
        data->balance_bitree->low_child = NULL;
        data->balance_bitree->data = num;
        data->balance_bitree->cur = data->amount;
        data->balance_bitree->parent = NULL;
    }
    else
    {
        temp = data->balance_bitree;
        while (temp)
        {
            while (temp)
            {
                if (num > temp->data)
                {
                    pre = temp;
                    temp = temp->high_child;
                }
                else
                {
                    break;
                }
            }
            while (temp)
            {
                if (num < temp->data)
                {
                    pre = temp;
                    temp = temp->low_child;
                }
                else
                {
                    break;
                }
            }
            if (temp && num == temp->data)
            {
                printf("已有相同的数据！\n");
                return;
            }
        }
        temp = (TREE_P)malloc(sizeof(TREE));
        temp->data = num;
        temp->cur = data->amount;
        temp->high_child = NULL;
        temp->low_child = NULL;
        temp->parent = pre;
        if (num > pre->data)
        {
            pre->high_child = temp;
        }
        if (num < pre->data)
        {
            pre->low_child = temp;
        }
        calculate_factor(data->balance_bitree);
        revise_tree(data->balance_bitree, data);
        calculate_factor(data->balance_bitree);
    }
    data->amount++;
}

void del_data(DATA_P data, int num)
{
    TREE_P pre, temp, next, end;
    temp = data->balance_bitree;
    while (temp && temp->data != num)
    {
        while (temp)
        {
            if (num > temp->data)
            {
                pre = temp;
                temp = temp->high_child;
            }
            else
            {
                break;
            }
        }
        while (temp)
        {
            if (num < temp->data)
            {
                pre = temp;
                temp = temp->low_child;
            }
            else
            {
                break;
            }
        }
    }
    if (temp)
    {
        //修改树中的数据
        if (temp == data->balance_bitree)
        {
            if (temp->low_child)
            {
                data->balance_bitree = temp->low_child;
                next = temp->low_child;
                while (next->high_child)
                {
                    next = next->high_child;
                }
                next->high_child = temp->high_child;
            }
            else if (temp->high_child)
            {
                data->balance_bitree = temp->high_child;
            }
            else
            {
                data->balance_bitree = NULL;
            }
        }
        else
        {
            if (pre->high_child == temp)
            {
                if (temp->low_child)
                {
                    pre->high_child = temp->low_child;
                    next = temp->low_child;
                    while (next->high_child)
                    {
                        next = next->high_child;
                    }
                    next->high_child = temp->high_child;
                }
                else
                {
                    pre->high_child = temp->high_child;
                }
            }
            if (pre->low_child == temp)
            {
                if (temp->high_child)
                {
                    pre->low_child = temp->high_child;
                    next = temp->high_child;
                    while (next->low_child)
                    {
                        next = next->low_child;
                    }
                    next->low_child = temp->low_child;
                }
                else
                {
                    pre->low_child = temp->low_child;
                }
            }
        }
        calculate_factor(data->balance_bitree);
        revise_tree(data->balance_bitree, data);
        calculate_factor(data->balance_bitree);
        //修改表中的数据
        if (temp->cur != data->amount - 1)
        {
            end = data->balance_bitree;
            while (end->data != data->data[data->amount - 1])
            {
                while (end->high_child)
                {
                    if (data->data[data->amount - 1] > end->data)
                    {
                        end = end->high_child;
                    }
                    else
                    {
                        break;
                    }
                }
                while (end->low_child)
                {
                    if (data->data[data->amount - 1] < end->data)
                    {
                        end = end->low_child;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            end->cur = temp->cur;
            data->data[temp->cur] = data->data[data->amount - 1];
        }
        data->amount--;
        free(temp);
    }
    else
    {
        printf("没找到相关数据！\n");
        return;
    }
}

void traverse_bitree(TREE_P tree, int level)
{
    if (tree)
    {
        traverse_bitree(tree->low_child, level + 1);
        printf("%-2d:cur %-2d,level %-2d,factor %-2d\n", tree->data, tree->cur, level, tree->factor);
        traverse_bitree(tree->high_child, level + 1);
    }
}

int main(int argc, char const *argv[])
{
    int select;
    int num;
    DATA_P data = init_data();
    while (1)
    {
        printf("\n1：添加数据\n2：删除数据\n3：全部数据\n4：退出程序\n请输入选项：");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            printf("输入要添加的数据：");
            scanf("%d", &num);
            add_data(data, num);
            continue;
        case 2:
            printf("输入要删除的数据：");
            scanf("%d", &num);
            del_data(data, num);
            continue;
        case 3:
            traverse_bitree(data->balance_bitree, 1);
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
