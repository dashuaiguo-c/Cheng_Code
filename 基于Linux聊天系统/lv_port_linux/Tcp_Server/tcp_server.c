#include "tcp_server.h"

P_SI Tcp_Server_Init(int prot_num)
{
    P_SI p_si = (P_SI)malloc(sizeof(SI));
    if(p_si == (P_SI)NULL)
    {
        perror("malloc ...");
        return (P_SI)-1;
    }
    memset(p_si,0,sizeof(SI));

    if((p_si->client_list_head = Create_Client_Node()) == (client_link)-1)
    {
        printf("创建在线客户链表头结点失败！\n");
        return (P_SI)-1;
    }
    if(pthread_mutex_init(&p_si->mutex,NULL) != 0) //动态初始化，这个互斥锁变量类似malloc不想要的时候需要pthread_mutex_destory
    {
        perror("pthread_mutex_init ...");
        return (P_SI)-1;
    }
    if((p_si->ser_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket ...");
        return (P_SI)-1;
    }

    struct sockaddr_in ser_inf;
    memset(&ser_inf,0,sizeof(ser_inf));

    ser_inf.sin_family       = AF_INET;
    ser_inf.sin_port         = htons(prot_num);//小端（主机字节序）的8888转成大端（网络字节序）// hsot to net short
    ser_inf.sin_addr.s_addr  = htonl(INADDR_ANY)  ;//表示所有网卡的IP          

    if(bind(p_si->ser_fd,(struct sockaddr *)&ser_inf,sizeof(ser_inf)) == -1)
    {
        perror("bind ...");
        return (P_SI)-1;
    }

    if(listen(p_si->ser_fd,20) == -1)
    {
        perror("listen ...");
        return (P_SI)-1;
    }
    return p_si;
}

client_link Create_Client_Node()
{
    client_link new_node = (client_link)malloc(sizeof(client_node));
    if(new_node == (client_link)NULL)
    {
        perror("malloc ...");
        return (client_link)-1;
    }
    
    memset(new_node,0,sizeof(client_node));

    new_node->next = new_node;
    new_node->prev = new_node;

    return new_node;
}

bool  Wait_For_Client_Connect(P_SI p_si)
{   
    struct sockaddr_in cli_inf;
    int len = sizeof(cli_inf);
    while(1)
    {
        memset(&cli_inf,0,len);

        //创建客户端结点
        client_link new_client_node = Create_Client_Node();
        if(new_client_node == (client_link)-1)
        {
            printf("创建新的客户端结点失败！\n");
            return false;
        }
        if((new_client_node->cli_fd = accept(p_si->ser_fd,(struct sockaddr *)&cli_inf,&len))==-1)
        {
            perror("accept ...");
            free(new_client_node);
            return false;
        }
        strcpy(new_client_node->cli_ip,inet_ntoa(cli_inf.sin_addr));//保存客户端的IP地址
        int read_ret = read(new_client_node->cli_fd,new_client_node->user_name,DATA_MAX_LEN);  //保存客户端姓名
        if(read_ret == -1)
        {
            perror("read ...");
            return false;
        }
        else if(read_ret == 0)
        {
            printf("客户端%s下线了\n",new_client_node->cli_ip);
            return false;
        }
        else
        {
            printf("%s--【ip】:%s上线了\n",new_client_node->user_name,new_client_node->cli_ip);
        }
        new_client_node->p_si = p_si;

        if(Add_Client_Node(p_si->client_list_head,new_client_node) == false)
        {
            printf("添加在线客户端结点失败！\n");
            return false;
        }
        /*服务器TCP多线程设计理念 ---- 一个客户端对应一条线程*/
        if(pthread_create(&new_client_node->cli_pid,NULL,Client_Pthread_Mode_Select,new_client_node) != 0)
        {
            perror("pthread_create ...");
            return false;
        }
    }
    
    return true;
}

bool  Add_Client_Node(client_link client_list_head,client_link new_client_node)
{
    if(client_list_head == (client_link)NULL)
    {
        printf("在线客户端链表头节点异常！\n");
        return false;
    }


    pthread_mutex_lock(&new_client_node->p_si->mutex);    //上锁

    new_client_node->next        = client_list_head->next;
    client_list_head->next->prev = new_client_node;

    client_list_head->next       = new_client_node;
    new_client_node->prev        = client_list_head;

    pthread_mutex_unlock(&new_client_node->p_si->mutex);    //解锁

    return true;
}

void * Client_Pthread_Mode_Select(void * arg)
{

    client_link present_clinet_node = (client_link)arg;
    char msg[DATA_MAX_LEN]; //定义一个数组存放客户端的功能选择
    while(1)
    {
        memset(msg,0,DATA_MAX_LEN);

        int read_ret = read(present_clinet_node->cli_fd,msg,DATA_MAX_LEN);//等待客户端的功能选择需要
        if(read_ret == -1)
        {
            perror("read ...");
            goto exit;
        }
        else if(read_ret == 0)
        {
            printf("客户端%s下线了\n",present_clinet_node->cli_ip);
            goto exit;
        }
        else
        {
            if(strcmp(msg,MODE_PRIVATE) == 0)//私聊
            {
                printf("客户端%s要%s\n",present_clinet_node->cli_ip,MODE_PRIVATE);
                if(Send_Private(present_clinet_node) == false)
                {
                    printf("私聊失败！\n");
                    goto exit;
                }
            }
            else if(strcmp(msg,MODE_BROADCAST) == 0)//群聊
            {
                printf("客户端%s要%s\n",present_clinet_node->cli_ip,MODE_BROADCAST);
                if(Send_All(present_clinet_node) == false)
                {
                    printf("群聊失败！\n");
                    goto exit;
                }
            }
            else if(strcmp(msg,MODE_SHOW_ONLINE) == 0)//显示在线人员
            {
                printf("客户端%s要%s\n",present_clinet_node->cli_ip,MODE_SHOW_ONLINE);
                if(Send_Online_Inf(present_clinet_node) == false)
                {
                    printf("发送在线人员IP失败！\n");
                    goto exit;
                }
            }
            else if(strcmp(msg,MODE_WEATHER) == 0)//查看天气
            {
                printf("客户端%s要%s\n",present_clinet_node->cli_ip,MODE_WEATHER);\
                 Send_All_Weather(present_clinet_node);
            }
            else if(strcmp(msg,FILE_DOWNLOAD) == 0)// 客户要下载
            {
                if(Send_File(present_clinet_node) == false)
                {
                    printf("发送文件给客户失败！\n");
                    goto exit;
                }
            }
            else if(strcmp(msg,FILE_UPLOAD) == 0)//客户要上传
            {
                if(Recv_File(present_clinet_node) == false)
                {
                    printf("接收客户文件失败！\n");
                    goto exit;
                }
            }
            else if(strcmp(msg,MODE_EXIT) == 0)//退出
            {
                printf("客户端%s要%s\n",present_clinet_node->cli_ip,MODE_EXIT);
                goto exit;
            }
            else
            {
                printf("收到未知要求！\n");
            }

        } 
    }
    exit:
    //删除当前客户端结点
    Del_Client_Node(present_clinet_node);
    pthread_detach(pthread_self());
    pthread_exit((void *)0);
}

bool  Del_Client_Node(client_link del_node)
{
    //上锁
    pthread_mutex_lock(&del_node->p_si->mutex);
    del_node->next->prev = del_node->prev;
    del_node->prev->next = del_node->next;

    del_node->next = NULL;
    del_node->prev = NULL;
    //解锁
    pthread_mutex_unlock(&del_node->p_si->mutex);

    free(del_node);
    
    return true;
}

