#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int KMP(char *main, char *sub)
{
    int main_len = strlen(main);
    int sub_len = strlen(sub);
    int *next = (int *)malloc(sizeof(int) * sub_len);
    int main_cur = 0;
    int sub_cur = 0;
    int next_cur = 0;
    int next_val = 0;
    int match_count = 0;
    int move_count = 0;
    //求next表中的值
    while (next_cur < sub_len)
    {
        for (int i = next_cur - 1; i >= -1; i--)
        /*next_cur为当前所要求的next的元素的下标*/
        {
            next_val = 0;
            for (int j = i; j > 0; j--)
            {
                if (sub[i - j] == sub[next_cur - j])
                //0,1,2,3           1,2,3,4
                //0,1,2             2,3,4
                //0,1               3,4
                //0                 4
                {
                    next_val++;
                }
            }
            if (i == -1)
            {
                next[next_cur] = -1;
                break;
            }
            if (sub[next_cur] == sub[next_val])
            {
                continue;
            }
            if (next_val == i)
            {
                next[next_cur] = next_val;
                break;
            }
        }
        next_cur++;
    }
    //依次打印next中的值
    printf("-------------------------\n");
    for (int i = 0; i < sub_len; i++)
    {
        printf("next[%d]=%d\n", i, next[i]);
    }
    printf("-------------------------\n");
    //开始进行匹配
    while (main_cur < main_len)
    {
        match_count++;
        if (main[main_cur] == sub[sub_cur])
        {
            if (sub_cur == sub_len - 1) //当遍历到子串中最后一个元素，表明已经找到匹配段
            {
                printf("-------------------------\n");
                printf("总共经历%d次匹配，%d次移位！\n", match_count, move_count);
                printf("在主字符串中找到子字符串，起始于%d，结束于%d！\n", main_cur - sub_cur, main_cur);
                printf("-------------------------\n");
                return main_cur - sub_cur;
            }
            main_cur++;
            sub_cur++;
        }
        else
        {
            if (main_len - main_cur == sub_len - sub_cur)
            {
                break;
            }
            if (next[sub_cur] == -1)
            {
                printf("检测到不匹配：sub=%d,main=%d\n", sub_cur, main_cur);
                main_cur++;
                sub_cur = 0;
                move_count++;
            }
            else
            {
                printf("检测到不匹配：sub=%d,main=%d\n", sub_cur, main_cur);
                sub_cur = next[sub_cur];
                move_count++;
            }
            if (main_len - main_cur < sub_len - sub_cur)
            {
                break;
            }
        }
    }
    printf("-------------------------\n");
    printf("检测到不匹配：sub=%d,main=%d\n", sub_cur, main_cur);
    printf("总共经历%d次匹配，%d次移位！\n", match_count, move_count);
    printf("在主字符串中未找到子字符串！\n");
    printf("-------------------------\n");
    return -1;
}

int main(int argc, char const *argv[])
{
    char main[1024];
    char sub[128];
    printf("请输入主字符串：");
    scanf("%[^\n]", main);
    getchar();
    printf("请输入子字符串：");
    scanf("%[^\n]", sub);
    KMP(main, sub);
    return 0;
}
