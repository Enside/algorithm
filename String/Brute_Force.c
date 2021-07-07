#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int brute_force(char *main, char *sub)
{
    int main_len = strlen(main);
    int sub_len = strlen(sub);
    int main_cur = 0;
    int sub_cur = 0;
    int match_count = 0;
    int move_count = 0;

    while (main_cur < main_len)
    {
        match_count++;
        if (main[main_cur] == sub[sub_cur])
        {
            if (sub_cur == sub_len - 1) //当遍历到子串中最后一个元素，表明已经找到匹配段
            {
                printf("总共经历%d次匹配，%d次移位！\n", match_count, move_count);
                printf("在主字符串中找到子字符串，起始于%d，结束于%d！\n", main_cur - sub_cur, main_cur);
                return main_cur - sub_cur;
            }
            main_cur++;
            sub_cur++;
        }
        else
        {
            if (main_len - main_cur == sub_len - sub_cur)
            {
                printf("检测到不匹配：sub=%d,main=%d\n", sub_cur, main_cur);
                printf("总共经历%d次匹配，%d次移位！\n", match_count, move_count);
                printf("在主字符串中未找到子字符串！\n");
                return -1;
            }
            printf("检测到不匹配：sub=%d,main=%d\n", sub_cur, main_cur);
            main_cur = main_cur - sub_cur + 1;
            sub_cur = 0;
            move_count += 2;
        }
    }
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
    brute_force(main, sub);
    return 0;
}
