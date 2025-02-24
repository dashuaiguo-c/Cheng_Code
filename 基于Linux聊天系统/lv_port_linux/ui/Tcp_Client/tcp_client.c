#include "tcp_client.h"

//客户端初始化
P_Cli Client_Init(char * ser_ip,int ser_port_num)
{
    P_Cli p_cli=(P_Cli)malloc(sizeof(Cli));  //申请堆空间
    if(NULL==p_cli)
    {
        perror("申请空间失败");
        return NULL;
    }

    // strcpy(p_cli->name,user_name);  //保存用户名   
    memset(p_cli->chat_data,0,sizeof(p_cli->chat_data));//清空私聊聊天数据
    memset(p_cli->chat_data_plus,0,sizeof(p_cli->chat_data_plus));//清空群聊聊天数据
    pthread_mutex_init(&p_cli->mutxe,NULL);  //初始化锁
    p_cli->run=1;//初始化判断聊天循环是否继续 0：正在聊天 1：没有在聊天
     
    //创建套接字
    p_cli->socket = socket(AF_INET,SOCK_STREAM,0);  
    if(p_cli->socket == -1)
    {
        perror("socket ...");
        return NULL;
    }  

    //连接服务器
    struct sockaddr_in ser_inf;
    memset(&ser_inf,0,sizeof(ser_inf));
    ser_inf.sin_family        = AF_INET;
    ser_inf.sin_port          = htons(ser_port_num);
    ser_inf.sin_addr.s_addr   = inet_addr(ser_ip);
    if(connect(p_cli->socket,(struct sockaddr *)&ser_inf,sizeof(ser_inf)) == -1) 
    {
        perror("connect ...");
        return NULL;
    }
    return p_cli;
}
