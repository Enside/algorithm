#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 5
#define ELEM_TYPE int

typedef struct Hash_Table
{
    ELEM_TYPE **elem;
    int table_size;
    int count;
} HASH, *HASH_P;

HASH_P init_hash()
{
    HASH_P hash = (HASH_P)malloc(sizeof(HASH));
    hash->table_size = TABLE_SIZE;
    hash->count = 0;
    hash->elem = (ELEM_TYPE **)malloc(sizeof(ELEM_TYPE *) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash->elem[i] = NULL;
    }
    return hash;
}

int hash_key(HASH_P hash, ELEM_TYPE value)
{
    return value % hash->table_size;
}

int add_data(HASH_P hash, ELEM_TYPE *value)
{
    if (hash->count < hash->table_size)
    {
        int key = hash_key(hash, *value);
        for (int i = 0; i < hash->table_size && hash->elem[key]; i++)
        {
            key = hash_key(hash, (*value) + i);
        }
        hash->elem[key] = value;
        hash->count++;
        return 1;
    }
    else
    {
        return 0;
    }
}

int del_data(HASH_P hash, ELEM_TYPE data)
{
    int key;
    for (int i = 0; i < hash->table_size; i++)
    {
        key = hash_key(hash, data + i);
        if (*hash->elem[key] == data)
        {
            free(hash->elem[key]);
            hash->elem[key] = NULL;
            hash->count--;
            return 1;
        }
    }
    return 0;
}

ELEM_TYPE *search_data(HASH_P hash, ELEM_TYPE data)
{
    int key;
    for (int i = 0; i < hash->table_size; i++)
    {
        key = hash_key(hash, data + i);
        if (hash->elem[key] && *hash->elem[key] == data)
        {
            return hash->elem[key];
        }
    }
    return NULL;
}

void print_all(HASH_P hash)
{
    for (int i = 0; i < hash->table_size; i++)
    {
        if (hash->elem[i])
        {
            printf("数据：%d\n地址：%p\n", *hash->elem[i], hash->elem[i]);
        }
    }
}

int main(int argc, char const *argv[])
{
    HASH_P hash = init_hash();
    ELEM_TYPE *value;
    ELEM_TYPE data;
    int select;
    while (1)
    {
        printf("\n1：添加数据\n2：删除数据\n3：查找数据\n4：全部数据\n5：退出程序\n请输入选项：");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            value = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE));
            printf("输入要添加的数据：");
            scanf("%d", value);
            if (!add_data(hash, value))
            {
                printf("哈希表已满！\n");
            }
            continue;
        case 2:
            printf("输入要删除的数据：");
            scanf("%d", &data);
            if (!del_data(hash, data))
            {
                printf("没有此数据！\n");
            }
            continue;
        case 3:
            printf("输入要查找的数据：");
            scanf("%d", &data);
            if (value = search_data(hash, data))
            {
                printf("数据：%d\n地址：%p\n", data, value);
            }
            else
            {
                printf("没有查找到此数据！\n");
            }
            continue;
        case 4:
            print_all(hash);
            continue;
        case 5:
            break;
        default:
            printf("输入错误请重新输入！");
            continue;
        }
        break;
    }
    return 0;
}
