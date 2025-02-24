#include "tcp_server.h"


bool  Send_Online_Inf(client_link present_client_node)
{
    char data[DATA_MAX_LEN*2];
    pthread_mutex_lock(&present_client_node->p_si->mutex);    //上锁
    for(client_link tmp_client_node = present_client_node->p_si->client_list_head->next; 
        tmp_client_node != present_client_node->p_si->client_list_head; 
        tmp_client_node = tmp_client_node->next)
    {
        memset(data,0,DATA_MAX_LEN*2);
        sprintf(data,"在线人员：%s-IP:%s",tmp_client_node->user_name,tmp_client_node->cli_ip);
        if(write(present_client_node->cli_fd,data,strlen(data)) == -1)
        {
            perror("write ...");
            pthread_mutex_unlock(&present_client_node->p_si->mutex);    //解锁
            return false;
        }

        memset(data,0,DATA_MAX_LEN);
        //得等客户端发个continue，在继续下一次循环--避免粘包
        int read_ret = read(present_client_node->cli_fd,data,DATA_MAX_LEN);
        if(read_ret == -1)
        {
            perror("read ...");
            pthread_mutex_unlock(&present_client_node->p_si->mutex);    //解锁
            return false;
        }
        else if(read_ret == 0)
        {
            printf("%s掉线了！\n",present_client_node->cli_ip);
             pthread_mutex_unlock(&present_client_node->p_si->mutex);    //解锁
            return false;
        }
        else
        {
            if(strcmp(data,CONTINUE) != 0)
            {
                printf("传输异常！\n");
                 pthread_mutex_unlock(&present_client_node->p_si->mutex);    //解锁
                return false;
            }
        }
    }

    pthread_mutex_unlock(&present_client_node->p_si->mutex);    //解锁

    //发送ok让客户端跳出while
    if(write(present_client_node->cli_fd,FINISH,strlen(FINISH)) == -1)
    {
        perror("write ...");
        return false;
    }

    return true;
}
