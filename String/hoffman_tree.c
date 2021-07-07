#include <stdio.h>
#include <stdlib.h>

typedef struct hoffman_tree
{
    char word;
    int weight;
    struct hoffman_tree *next;
    struct hoffman_tree *l_child;
    struct hoffman_tree *r_child;
} HOFFMAN_TREE, *HOFFMAN_TREE_P;

typedef struct encode
{
    int amount;
    char **code;
    char *word;
} ENCODE, *ENCODE_P;

typedef struct bit
{
    int zero : 1;
    int one : 1;
} BIT, *BIT_P;

HOFFMAN_TREE_P sort_data(char *text, int length)
{
    int amount = 0;
    HOFFMAN_TREE_P hoffman_tree = NULL;
    HOFFMAN_TREE_P current = NULL;
    HOFFMAN_TREE_P temp = NULL;
    HOFFMAN_TREE_P pre = NULL;

    for (int i = 0; i < length; i++)
    {
        current = hoffman_tree;
        pre = NULL;
        for (int j = 0; j <= amount; j++)
        {
            if (!current)
            {
                temp = hoffman_tree;
                hoffman_tree = (HOFFMAN_TREE_P)malloc(sizeof(HOFFMAN_TREE));
                hoffman_tree->word = text[i];
                hoffman_tree->weight = 1;
                hoffman_tree->next = temp;
                hoffman_tree->l_child = NULL;
                hoffman_tree->r_child = NULL;
                amount++;
                break;
            }
            if (current->word == text[i])
            {
                current->weight++;
                while (current->next && current->next->weight < current->weight)
                {
                    if (pre)
                    {
                        pre->next = current->next;
                        pre = pre->next;
                        current->next = pre->next;
                        pre->next = current;
                    }
                    else
                    {
                        hoffman_tree = current->next;
                        current->next = hoffman_tree->next;
                        hoffman_tree->next = current;
                        pre = hoffman_tree;
                    }
                }
                break;
            }
            pre = current;
            current = current->next;
        }
    }

    return hoffman_tree;
}

HOFFMAN_TREE_P build_hoffman_tree(HOFFMAN_TREE_P hoffman_tree)
{
    HOFFMAN_TREE_P head = hoffman_tree;
    HOFFMAN_TREE_P temp = NULL;
    HOFFMAN_TREE_P pre = NULL;

    while (head)
    {
        temp = head;
        head = head->next;

        if (head)
        {
            hoffman_tree = (HOFFMAN_TREE_P)malloc(sizeof(HOFFMAN_TREE));
            hoffman_tree->word = '\0';
            hoffman_tree->l_child = temp;
            hoffman_tree->r_child = head;
            hoffman_tree->weight = hoffman_tree->l_child->weight + hoffman_tree->r_child->weight;
            head = head->next;
            hoffman_tree->l_child->next = hoffman_tree;
            hoffman_tree->r_child->next = hoffman_tree;

            if (head)
            {
                if (hoffman_tree->weight <= head->weight)
                {
                    hoffman_tree->next = head;
                    head = hoffman_tree;
                }
                else
                {
                    temp = head;
                    while (temp && temp->weight < hoffman_tree->weight)
                    {
                        pre = temp;
                        temp = temp->next;
                    }
                    pre->next = hoffman_tree;
                    hoffman_tree->next = temp;
                }
            }
        }
    }

    return hoffman_tree;
}

void getcode(HOFFMAN_TREE_P hoffman_tree, char *path, ENCODE_P encode, int level)
{
    if (hoffman_tree->l_child)
    {
        char *code = (char *)malloc(sizeof(char) * level + 2);
        for (int i = 0; i < level; i++)
        {
            code[i] = path[i];
        }
        code[level] = '0';
        code[level + 1] = '\0';
        getcode(hoffman_tree->l_child, code, encode, level + 1);
    }
    if (hoffman_tree->r_child)
    {
        char *code = (char *)malloc(sizeof(char) * level + 2);
        for (int i = 0; i < level; i++)
        {
            code[i] = path[i];
        }
        code[level] = '1';
        code[level + 1] = '\0';
        getcode(hoffman_tree->r_child, code, encode, level + 1);
    }
    if (hoffman_tree->word != '\0')
    {
        encode->code = (char **)realloc(encode->code, sizeof(char *) * (encode->amount + 1));
        encode->word = (char *)realloc(encode->word, sizeof(char) * (encode->amount + 1));
        encode->code[encode->amount] = path;
        encode->word[encode->amount] = hoffman_tree->word;
        encode->amount++;
        return;
    }
}

ENCODE_P encode(char *text)
{
    int text_length = 0;
    while (text[text_length] != '\0')
    {
        text_length++;
    }

    HOFFMAN_TREE_P hoffman_tree = build_hoffman_tree(sort_data(text, text_length));
    ENCODE_P encode = (ENCODE_P)malloc(sizeof(ENCODE));
    encode->amount = 0;
    char *code = NULL;
    getcode(hoffman_tree, code, encode, 0);

    for (int i = 0; i < encode->amount; i++)
    {
        printf("%c:%s\n", encode->word[i], encode->code[i]);
    }
}

int main(int argc, char const *argv[])
{
    char text[256];
    printf("plz input:");
    scanf("%[^\n]", text);
    encode(text);
    return 0;
}
