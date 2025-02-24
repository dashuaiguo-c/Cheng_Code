#include "tcp_server.h"

bool  Send_All(client_link present_client_node)
{
    //先接收客户端的消息然后进行群发
    char data[DATA_MAX_LEN];
    char buf[DATA_MAX_LEN*3];
    while(1)
    {
        memset(data,0,DATA_MAX_LEN);
        memset(buf,0,DATA_MAX_LEN*3);
        int read_ret = read(present_client_node->cli_fd,data,DATA_MAX_LEN);
        if(read_ret == -1)
        {
            perror("read ...");
            return false;
        }
        else if(read_ret == 0)
        {
            printf("%s掉线了！\n",present_client_node->cli_ip);
            return false;
        }
        else if(strcmp(MODE_EXIT,data) == 0)
        {
            printf("%s退出聊天！\n",present_client_node->cli_ip);
            break;
        }
        else
        {
            printf("%s\n","我来了");
            pthread_mutex_lock(&present_client_node->p_si->mutex);  //加锁
            for(client_link tmp_client_node = present_client_node->p_si->client_list_head->next; 
                tmp_client_node != present_client_node->p_si->client_list_head; 
                tmp_client_node = tmp_client_node->next)
            {
                sprintf(buf,"【群聊消息-%s】：%s",present_client_node->user_name,data);
                // if(tmp_client_node != present_client_node)
                // {
                    if(write(tmp_client_node->cli_fd,buf,strlen(buf)) == -1)
                    {
                        perror("write ...");
                        pthread_mutex_unlock(&present_client_node->p_si->mutex);  //解锁
                        return false;
                    }
                // }
            }
            pthread_mutex_unlock(&present_client_node->p_si->mutex);  //解锁
        }
    }
    return true;
}

bool  Send_Private(client_link present_client_node)
{
    //获取客户端需要私聊的人
    char data[DATA_MAX_LEN];
    memset(data,0,DATA_MAX_LEN);
    int ret=read(present_client_node->cli_fd,data,DATA_MAX_LEN);
    if(ret==-1)
    {
        perror("read name ...");
        return false;
    }
     printf("%s要给%s发送消息\n",present_client_node->user_name,data);
    char buf[DATA_MAX_LEN*3];
    memset(buf,0,DATA_MAX_LEN*3);

    for(client_link tmp_client_node = present_client_node->p_si->client_list_head->next; 
    tmp_client_node != present_client_node->p_si->client_list_head; 
    tmp_client_node = tmp_client_node->next)  
    {
        if(strcmp(tmp_client_node->user_name,data)==0)  //查找被私聊客户端
        {
            printf("找到目标客户端：%d\n",tmp_client_node->cli_fd);
            while(1)
            {
                ret=read(present_client_node->cli_fd,buf,sizeof(buf));
                printf("%s发出的消息：%s\n",present_client_node->user_name,buf);
                if(-1==ret)
                {
                    perror("用户私聊数据获取失败 ...");
                    return false;
                }
                else if(ret == 0)
                {
                    printf("%s掉线了！\n",present_client_node->cli_ip);
                    return false;
                }
                else if(strstr(buf,MODE_EXIT))
                {
                    printf("%s退出聊天！\n",present_client_node->cli_ip);
                    // ret=write(present_client_node->cli_fd,MODE_EXIT,strlen(MODE_EXIT));  //发送消息让客户端退出循环
                    // if(-1==ret)
                    // {
                    //     perror("发送消息失败");
                    //     return false;
                    // }
                    break;
                }
                if(strstr(buf,MODE_EXIT) || strstr(buf,MODE_PRIVATE))
                {
                    continue;
                }
                pthread_mutex_lock(&present_client_node->p_si->mutex);  //锁
                char datas[1024]="\0";
                sprintf(datas,"%s:%s",present_client_node->user_name,buf);
                ret=write(tmp_client_node->cli_fd,datas,strlen(datas));  //发送消息
                if(-1==ret)
                {
                    perror("发送消息失败");
                    pthread_mutex_unlock(&present_client_node->p_si->mutex);  //解锁
                    return false;
                }
                pthread_mutex_unlock(&present_client_node->p_si->mutex);  //解锁
            }
        }
    }
    return true;
}
    // char data[DATA_MAX_LEN];
    // char buf[DATA_MAX_LEN*3];
    // while(1)
    // {
    //     memset(data,0,DATA_MAX_LEN);
    //     memset(buf,0,DATA_MAX_LEN*2);
    //     int read_ret = read(present_client_node->cli_fd,data,DATA_MAX_LEN);
    //     if(read_ret == -1)
    //     {
    //         perror("read ...");
    //         return false;
    //     }
    //     else if(read_ret == 0)
    //     {
    //         printf("%s掉线了！\n",present_client_node->cli_ip);
    //         return false;
    //     }
    //     else if(strcmp(MODE_EXIT,data) == 0)
    //     {
    //         printf("%s退出聊天！\n",present_client_node->cli_ip);
    //         break;
    //     }
    
    //     //过滤私聊消息中的私聊对象
    //     if(strcmp(tmp_client_node->user_name,))
    //     {

    //     }
    //     char * obj_p = strrchr(data,'@'); 
    //     if(obj_p == NULL)
    //     {
    //         printf("收到错误格式消息！\n");
    //         pthread_mutex_unlock(&present_client_node->p_si->mutex);
    //     }
        
    //     if(strcmp(tmp_client_node->user_name,obj_p+1) == 0)//判断tmp_client_node里面的用户昵称是否是你想发送的
    //     {
    //         *obj_p = '\0';//data:hello\0小红           256                   256
    //         sprintf(buf,"【私聊消息-%s】：%s",present_client_node->user_name,data);
    //         if(write(tmp_client_node->cli_fd,buf,strlen(buf)) == -1)
    //         {
    //             perror("write ...");
    //             pthread_mutex_unlock(&present_client_node->p_si->mutex);
    //             return false;
    //         }        
    //     }
    // }


