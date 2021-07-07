#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MERGE -1

typedef struct b_tree
{
    int amount;
    int data[2];
    int cur[2];
    struct b_tree *child[3];
    struct b_tree *parent;
} TREE, *TREE_P;

typedef struct data
{
    int data[MAX];
    int amount;
    TREE_P b_tree;
} DATA, *DATA_P;

TREE_P init_tree()
{
    TREE_P tree = (TREE_P)malloc(sizeof(TREE));
    tree->amount = 0;
    for (int i = 0; i < 3; i++)
    {
        tree->child[i] = NULL;
    }
    return tree;
}

DATA_P init_data()
{
    DATA_P data = (DATA_P)malloc(sizeof(DATA));
    data->amount = 0;
}

void insert_tree(TREE_P new, TREE_P target)
{
    if (target)
    {
        if (target->amount == 1)
        {
            if (new->data[0] < target->data[0])
            {
                target->data[1] = target->data[0];
                target->cur[1] = target->cur[0];
                target->data[0] = new->data[0];
                target->cur[0] = new->cur[0];
                if (new->child[0])
                {
                    target->child[2] = target->child[1];
                    target->child[0] = new->child[0];
                    new->child[0]->parent = target;
                    target->child[1] = new->child[1];
                    new->child[1]->parent = target;
                }
                target->amount++;
                return;
            }
            if (new->data[0] > target->data[0])
            {
                target->data[1] = new->data[0];
                target->cur[1] = new->cur[0];
                if (new->child[0])
                {
                    target->child[1] = new->child[0];
                    new->child[0]->parent = target;
                    target->child[2] = new->child[1];
                    new->child[1]->parent = target;
                }
                target->amount++;
                return;
            }
        }
        if (target->amount == 2)
        {
            if (new->data[0] < target->data[0])
            {
                TREE_P left = new;
                TREE_P right = init_tree();
                right->data[0] = target->data[1];
                right->cur[0] = target->cur[1];

                if (target->child[0])
                {
                    right->child[0] = target->child[1];
                    target->child[1]->parent = right;
                    right->child[1] = target->child[2];
                    target->child[2]->parent = right;
                }

                right->amount++;
                target->child[0] = left;
                left->parent = target;
                target->child[1] = right;
                right->parent = target;
                target->child[2] = NULL;
                target->amount--;

                insert_tree(target, target->parent);
                return;
            }
            if (new->data[0] > target->data[0] && new->data[0] < target->data[1])
            {
                TREE_P left = init_tree();
                left->data[0] = target->data[0];
                left->cur[0] = target->cur[0];
                left->amount++;

                TREE_P right = init_tree();
                right->data[0] = target->data[1];
                right->cur[0] = target->cur[1];
                right->amount++;

                if (target->child[0])
                {
                    left->child[0] = target->child[0];
                    target->child[0]->parent = left;
                    right->child[1] = target->child[2];
                    target->child[2]->parent = right;
                }
                if (new->child[0])
                {
                    left->child[1] = new->child[0];
                    new->child[0]->parent = left;
                    right->child[0] = new->child[1];
                    new->child[1]->parent = right;
                }

                target->data[0] = new->data[0];
                target->cur[0] = new->cur[0];
                target->child[0] = left;
                left->parent = target;
                target->child[1] = right;
                right->parent = target;
                target->child[2] = NULL;
                target->amount--;

                insert_tree(target, target->parent);
                return;
            }
            if (new->data[0] > target->data[1])
            {
                TREE_P left = init_tree();
                left->data[0] = target->data[0];
                left->cur[0] = target->cur[0];
                if (target->child[0])
                {
                    left->child[0] = target->child[0];
                    target->child[0]->parent = left;
                    left->child[1] = target->child[1];
                    target->child[1]->parent = left;
                }
                left->amount++;

                TREE_P right = new;

                target->data[0] = target->data[1];
                target->cur[0] = target->cur[1];
                target->child[0] = left;
                left->parent = target;
                target->child[1] = right;
                right->parent = target;
                target->child[2] = NULL;
                target->amount--;

                insert_tree(target, target->parent);
                return;
            }
        }
    }
}

void add_data(DATA_P data, int num)
{
    if (data->amount == 0)
    {
        data->b_tree = init_tree();
        data->b_tree->parent = NULL;
        data->b_tree->data[0] = num;
        data->b_tree->cur[0] = 0;
        data->b_tree->amount++;
    }
    else
    {
        TREE_P new = init_tree();
        new->data[0] = num;
        new->cur[0] = data->amount;
        new->amount++;

        TREE_P next = data->b_tree;
        TREE_P temp;

        while (next)
        {
            if (next->amount == 1)
            {
                if (num < next->data[0])
                {
                    temp = next;
                    next = next->child[0];
                    continue;
                }
                else if (num > next->data[0])
                {
                    temp = next;
                    next = next->child[1];
                    continue;
                }
                else
                {
                    printf("已有相同的数据！\n");
                    return;
                }
            }
            if (next->amount == 2)
            {
                if (num < next->data[0])
                {
                    temp = next;
                    next = next->child[0];
                    continue;
                }
                else if (num > next->data[0] && num < next->data[1])
                {
                    temp = next;
                    next = next->child[1];
                    continue;
                }
                else if (num > next->data[1])
                {
                    temp = next;
                    next = next->child[2];
                    continue;
                }
                else
                {
                    printf("已有相同的数据！\n");
                    return;
                }
            }
        }
        insert_tree(new, temp);
    }
    data->data[data->amount] = num;
    data->amount++;
}

int remove_tree(TREE_P target, int flag)
{
    if (flag == MERGE)
    {
        printf("--------合并节点--------\n");
    }
    else
    {
        printf("--------删除节点--------\n");
    }

    if (!target->child[0] || flag == MERGE)
    {
        if (target->amount == 2 && flag != MERGE)
        {
            printf("叶子三节点,直接删除...\n");
            if (flag == 0)
            {
                target->data[0] = target->data[1];
                target->cur[0] = target->cur[1];
            }
            target->amount--;
            return 1;
        }

        if (!target->parent && flag != MERGE)
        {
            printf("只有叶子二节点,产生空树...\n");
            return 0;
        }
        if (!target->parent && flag == MERGE)
        {
            printf("已合并到根节点,减少层数...\n");
            return 1;
        }

        TREE_P parent = target->parent;
        if (parent->amount == 2)
        {
            printf("父节点为三节点...\n");
            if (parent->child[0] == target)
            {
                printf("处理左叶子节点...\n");
                if (parent->child[1]->amount == 1)
                {
                    printf("兄弟节点为二节点...\n");
                    parent->child[1]->data[1] = parent->child[1]->data[0];
                    parent->child[1]->cur[1] = parent->child[1]->cur[0];
                    parent->child[1]->data[0] = parent->data[0];
                    parent->child[1]->cur[0] = parent->cur[0];
                    parent->child[1]->child[2] = parent->child[1]->child[1];
                    parent->child[1]->child[1] = parent->child[1]->child[0];
                    parent->child[1]->amount++;

                    if (flag != MERGE)
                    {
                        parent->child[1]->child[0] = NULL;
                    }
                    if (flag == MERGE)
                    {
                        parent->child[1]->child[0] = target;
                        target->parent = parent->child[1];
                    }

                    parent->data[0] = parent->data[1];
                    parent->cur[0] = parent->cur[1];
                    parent->child[0] = parent->child[1];
                    parent->child[1] = parent->child[2];
                    parent->child[2] = NULL;
                    parent->amount--;
                    return 1;
                }
                if (parent->child[1]->amount == 2)
                {
                    printf("兄弟节点为三节点...\n");
                    TREE_P new = init_tree();
                    new->data[0] = parent->data[0];
                    new->cur[0] = parent->cur[0];
                    new->amount++;
                    parent->child[0] = new;
                    new->parent = parent;

                    if (flag != MERGE)
                    {
                        new->child[0] = NULL;
                        new->child[1] = NULL;
                    }
                    if (flag == MERGE)
                    {
                        new->child[0] = target;
                        target->parent = new;
                        new->child[1] = parent->child[1]->child[0];
                        parent->child[1]->child[0]->parent = new;
                    }

                    parent->data[0] = parent->child[1]->data[0];
                    parent->cur[0] = parent->child[1]->cur[0];
                    parent->child[1]->data[0] = parent->child[1]->data[1];
                    parent->child[1]->cur[0] = parent->child[1]->cur[1];
                    parent->child[1]->child[0] = parent->child[1]->child[1];
                    parent->child[1]->child[1] = parent->child[1]->child[2];
                    parent->child[1]->child[2] = NULL;
                    parent->child[1]->amount--;
                    return 1;
                }
            }
            if (parent->child[1] == target)
            {
                printf("处理中叶子节点...\n");
                if (parent->child[2]->amount == 1)
                {
                    printf("兄弟节点为二节点...\n");
                    parent->child[2]->data[1] = parent->child[2]->data[0];
                    parent->child[2]->cur[1] = parent->child[2]->cur[0];
                    parent->child[2]->data[0] = parent->data[1];
                    parent->child[2]->cur[0] = parent->cur[1];
                    parent->child[2]->child[2] = parent->child[2]->child[1];
                    parent->child[2]->child[1] = parent->child[2]->child[0];
                    parent->child[2]->amount++;

                    if (flag != MERGE)
                    {
                        parent->child[2]->child[0] = NULL;
                    }
                    if (flag == MERGE)
                    {
                        parent->child[2]->child[0] = target;
                        target->parent = parent->child[2];
                    }

                    parent->child[1] = parent->child[2];
                    parent->child[2] = NULL;
                    parent->amount--;
                    return 1;
                }
                if (parent->child[2]->amount == 2)
                {
                    printf("兄弟节点为三节点...\n");
                    TREE_P new = init_tree();
                    new->data[0] = parent->data[1];
                    new->cur[0] = parent->cur[1];
                    new->amount++;
                    parent->child[1] = new;
                    new->parent = parent;

                    if (flag != MERGE)
                    {
                        new->child[0] = NULL;
                        new->child[1] = NULL;
                    }
                    if (flag == MERGE)
                    {
                        new->child[0] = target;
                        target->parent = new;
                        new->child[1] = parent->child[2]->child[0];
                        parent->child[2]->child[0]->parent = new;
                    }

                    parent->data[1] = parent->child[2]->data[0];
                    parent->cur[1] = parent->child[2]->cur[0];
                    parent->child[2]->data[0] = parent->child[2]->data[1];
                    parent->child[2]->cur[0] = parent->child[2]->cur[1];
                    parent->child[2]->child[0] = parent->child[2]->child[1];
                    parent->child[2]->child[1] = parent->child[2]->child[2];
                    parent->child[2]->child[2] = NULL;
                    parent->child[2]->amount--;
                    return 1;
                }
            }
            if (parent->child[2] == target)
            {
                printf("处理右叶子节点...\n");
                if (parent->child[1]->amount == 1)
                {
                    printf("兄弟节点为二节点...\n");
                    parent->child[1]->data[1] = parent->data[1];
                    parent->child[1]->cur[1] = parent->cur[1];
                    parent->child[1]->amount++;

                    if (flag != MERGE)
                    {
                        parent->child[1]->child[2] = NULL;
                    }
                    if (flag == MERGE)
                    {
                        parent->child[1]->child[2] = target;
                        target->parent = parent->child[1];
                    }

                    parent->child[2] = NULL;
                    parent->amount--;
                    return 1;
                }
                if (parent->child[1]->amount == 2)
                {
                    printf("兄弟节点为三节点...\n");
                    TREE_P new = init_tree();
                    new->data[0] = parent->data[1];
                    new->cur[0] = parent->cur[1];
                    new->amount++;
                    parent->child[2] = new;
                    new->parent = parent;

                    if (flag != MERGE)
                    {
                        new->child[1] = NULL;
                        new->child[0] = NULL;
                    }
                    if (flag == MERGE)
                    {
                        new->child[1] = target;
                        target->parent = new;
                        new->child[0] = parent->child[1]->child[2];
                        parent->child[1]->child[2]->parent = new;
                    }

                    parent->data[1] = parent->child[1]->data[1];
                    parent->cur[1] = parent->child[1]->cur[1];
                    parent->child[1]->child[2] = NULL;
                    parent->child[1]->amount--;
                    return 1;
                }
            }
        }
        if (parent->amount == 1)
        {
            printf("父节点为二节点...\n");
            if (parent->child[0] == target)
            {
                printf("处理左叶子节点...\n");
                if (parent->child[1]->amount == 1)
                {
                    printf("兄弟节点为二节点...\n");
                    TREE_P temp = parent->child[1];
                    parent->data[1] = parent->child[1]->data[0];
                    parent->cur[1] = parent->child[1]->cur[0];
                    parent->amount++;

                    if (flag != MERGE)
                    {
                        parent->child[0] = NULL;
                        parent->child[1] = NULL;
                        free(target);
                        free(temp);
                    }
                    if (flag == MERGE)
                    {
                        parent->child[2] = temp->child[1];
                        parent->child[2]->parent = parent;
                        parent->child[1] = temp->child[0];
                        parent->child[1]->parent = parent;
                        free(temp);
                    }
                    remove_tree(parent, MERGE);
                    return 1;
                }
                if (parent->child[1]->amount == 2)
                {
                    printf("兄弟节点为三节点...\n");
                    TREE_P new = init_tree();
                    new->data[0] = parent->data[0];
                    new->cur[0] = parent->cur[0];
                    new->amount++;
                    parent->child[0] = new;
                    new->parent = parent;

                    if (flag != MERGE)
                    {
                        new->child[0] = NULL;
                        new->child[1] = NULL;
                    }
                    if (flag == MERGE)
                    {
                        new->child[0] = target;
                        target->parent = new;
                        new->child[1] = parent->child[1]->child[0];
                        parent->child[1]->child[0]->parent = new;
                    }

                    parent->data[0] = parent->child[1]->data[0];
                    parent->cur[0] = parent->child[1]->cur[0];
                    parent->child[1]->data[0] = parent->child[1]->data[1];
                    parent->child[1]->cur[0] = parent->child[1]->cur[1];
                    parent->child[1]->child[0] = parent->child[1]->child[1];
                    parent->child[1]->child[1] = parent->child[1]->child[2];
                    parent->child[1]->child[2] = NULL;
                    parent->child[1]->amount--;
                    return 1;
                }
            }
            if (parent->child[1] == target)
            {
                printf("处理右叶子节点...\n");
                if (parent->child[0]->amount == 1)
                {
                    printf("兄弟节点为二节点...\n");
                    TREE_P temp = parent->child[0];
                    parent->data[1] = parent->data[0];
                    parent->cur[1] = parent->cur[0];
                    parent->data[0] = parent->child[0]->data[0];
                    parent->cur[0] = parent->child[0]->cur[0];
                    parent->amount++;

                    if (flag != MERGE)
                    {
                        parent->child[0] = NULL;
                        parent->child[1] = NULL;
                        free(target);
                        free(temp);
                    }
                    if (flag == MERGE)
                    {
                        parent->child[2] = parent->child[1];
                        parent->child[1] = temp->child[1];
                        parent->child[1]->parent = parent;
                        parent->child[0] = temp->child[0];
                        parent->child[0]->parent = parent;
                        free(temp);
                    }

                    remove_tree(parent, MERGE);
                    return 1;
                }
                if (parent->child[0]->amount == 2)
                {
                    printf("兄弟节点为三节点...\n");
                    TREE_P new = init_tree();
                    new->data[0] = parent->data[0];
                    new->cur[0] = parent->cur[0];
                    new->amount++;
                    parent->child[1] = new;
                    new->parent = parent;

                    if (flag != MERGE)
                    {
                        new->child[0] = NULL;
                        new->child[1] = NULL;
                    }
                    if (flag == MERGE)
                    {
                        new->child[0] = parent->child[0]->child[2];
                        parent->child[0]->child[2]->parent = new;
                        new->child[1] = target;
                        target->parent = new;
                    }

                    parent->data[0] = parent->child[0]->data[1];
                    parent->cur[0] = parent->child[0]->cur[1];
                    parent->child[0]->child[2] = NULL;
                    parent->child[0]->amount--;
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("非叶子节点，向后寻找...\n");
        TREE_P temp;
        if (target->amount == 1)
        {
            temp = target->child[1];
        }
        if (target->amount == 2)
        {
            if (flag == 0)
            {
                temp = target->child[1];
            }
            if (flag == 1)
            {
                temp = target->child[2];
            }
        }
        while (temp->child[0])
        {
            temp = temp->child[0];
        }
        target->data[flag] = temp->data[0];
        target->cur[flag] = temp->cur[0];
        remove_tree(temp, 0);
        return 1;
    }
}

void del_data(DATA_P data, int num)
{
    TREE_P temp = data->b_tree;
    int flag = 0;
    while (temp)
    {
        if (temp->amount == 1)
        {
            if (num < temp->data[0])
            {
                temp = temp->child[0];
                continue;
            }
            else if (num > temp->data[0])
            {
                temp = temp->child[1];
                continue;
            }
            else
            {
                flag = 0;
                break;
            }
        }
        if (temp->amount == 2)
        {
            if (num < temp->data[0])
            {
                temp = temp->child[0];
                continue;
            }
            else if (num > temp->data[0] && num < temp->data[1])
            {
                temp = temp->child[1];
                continue;
            }
            else if (num > temp->data[1])
            {
                temp = temp->child[2];
                continue;
            }
            else
            {
                if (num == temp->data[0])
                {
                    flag = 0;
                    break;
                }
                if (num == temp->data[1])
                {
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (temp)
    {
        TREE_P end = data->b_tree;
        int flag_end = 0;
        while (end)
        {
            if (end->amount == 1)
            {
                if (data->data[data->amount - 1] < end->data[0])
                {
                    end = end->child[0];
                    continue;
                }
                else if (data->data[data->amount - 1] > end->data[0])
                {
                    end = end->child[1];
                    continue;
                }
                else
                {
                    flag_end = 0;
                    break;
                }
            }
            if (end->amount == 2)
            {
                if (data->data[data->amount - 1] < end->data[0])
                {
                    end = end->child[0];
                    continue;
                }
                else if (data->data[data->amount - 1] > end->data[0] && data->data[data->amount - 1] < end->data[1])
                {
                    end = end->child[1];
                    continue;
                }
                else if (data->data[data->amount - 1] > end->data[1])
                {
                    end = end->child[2];
                    continue;
                }
                else
                {
                    if (data->data[data->amount - 1] == end->data[0])
                    {
                        flag_end = 0;
                        break;
                    }
                    if (data->data[data->amount - 1] == end->data[1])
                    {
                        flag_end = 1;
                        break;
                    }
                }
            }
        }
        end->cur[flag_end] = temp->cur[flag];
        data->data[temp->cur[flag]] = data->data[data->amount - 1];
        data->amount--;
        if (remove_tree(temp, flag))
        {
            return;
        }
        else
        {
            data->b_tree = NULL;
            return;
        }
    }
    else
    {
        printf("没有找到相关数据！\n");
        return;
    }
}

void traverse_b_tree(TREE_P tree, int level)
{
    if (tree)
    {
        traverse_b_tree(tree->child[0], level + 1);
        for (int i = 0; i < tree->amount; i++)
        {
            printf("数据:%-2d,坐标:%-2d,层级:%-2d\n", tree->data[i], tree->cur[i], level);
            traverse_b_tree(tree->child[i + 1], level + 1);
        }
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
            traverse_b_tree(data->b_tree, 1);
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
