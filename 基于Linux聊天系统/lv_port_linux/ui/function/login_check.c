#include "../ui.h"

//检查用户是否已注册的函数
int Check_Usr(const char *buf, const char *usr) 
{
    char *line = NULL;
    char temp_usr[128] = {0};

    //逐行解析
    line = strtok((char *)buf, "\n");  //按照下划线区分结点
    while (line != NULL)  //line为指向下一个结点的指针
    {  
        if (sscanf(line, "usr:%s ", temp_usr) == 1) {
            if (strcmp(temp_usr, usr) == 0) {
                return 1; //用户已存在
            }
        }
        line = strtok(NULL, "\n");
    }
    return 0; //用户未注册
}

//判断数据是否为空或全为空格
int is_empty_or_whitespace(const char *str) 
{
    if (str == NULL || *str == '\0') 
    {
        return 1;  // 空字符串或 NULL
    }

    while (*str) 
    {
        if (!isspace((unsigned char)*str)) 
        {
            return 0;  // 存在非空格字符
        }
        str++;
    }

}