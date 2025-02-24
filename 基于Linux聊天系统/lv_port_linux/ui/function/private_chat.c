#include "../ui.h"

//向服务器发送私聊请求
bool Private(P_Cli p_cli,lv_obj_t *label)
{
    p_cli->run=0; //开始私聊
    //发送功能需要给服务器
    if(write(p_cli->socket,MODE_PRIVATE,strlen(MODE_PRIVATE)) == -1)
    {
        perror("write ...");
        return false;
    }
    
    usleep(2000);  //防止服务器一次性读取功能和私聊人员

    //发送要发送的人员信息给服务器
    if(write(p_cli->socket,p_cli->send_name,strlen(p_cli->send_name)) == -1)
    {
        perror("write ...");
        return false;
    }
    pthread_create(&p_cli->tid,NULL,private_chat_chat,p_cli); //创建线程，不断更新聊天界面数据
    pthread_detach(p_cli->tid);  //设置分离属性
    return true;  //继续执行主线程
}

// 定时器回调函数，在主线程中更新 UI
void timer_callback(lv_timer_t * timer)
{
    // 使用子线程中更新的数据来更新 UI
    P_Cli p_cli=timer->user_data;
    lv_label_set_chinese(label_win,p_cli->chat_data);
}

//子线程，不断更新聊天界面数据
void *private_chat_chat(void *arg)
{
    P_Cli p_cli=(P_Cli)arg;
    time1=lv_timer_create(timer_callback,10,p_cli);  //添加时间任务
    fd_set  fs;//定义要多路复用监听的文件描述符集合

    char data[DATA_MAX_LEN*2];  //接收私聊数据
    int ret=0;  //判断函数是否正常执行
    memset(data,0,DATA_MAX_LEN*2);

    struct timeval timeout;  //设置超时更新界面
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    while(1)
    {
        if(p_cli->run==1)
        {
            printf("退出私聊\n");
            break;
        }
        //多路复用
        FD_ZERO(&fs);  //清空文件描述符
        FD_SET(0,&fs);        //把标准输入文件描述符添加到集合中
        FD_SET(p_cli->socket,&fs); //把客户端套接字添加进去
    
        if(select(p_cli->socket+1,&fs,NULL,NULL,&timeout) == -1)
        {
            perror("select ...");
            return false;
        }

        if(FD_ISSET(p_cli->socket,&fs))//判断能不能读取消息
        {
            if(ret=read(p_cli->socket,data,DATA_MAX_LEN*2) == -1)
            {
                perror("Read ...");
                return false;
            }
            if(strstr(data,MODE_EXIT))
            {
                printf("成功退出私聊\n");
                break;
            }
            char data_clean[DATA_MAX_LEN*3]="\0";
            memset(data_clean,0,DATA_MAX_LEN*3);
            sprintf(data_clean,"%s\n",data);
            strcat(p_cli->chat_data,data_clean);
        }
        if(FD_ISSET(0,&fs))
        {
            continue;
        }
    }
    pthread_exit(NULL);  // 线程退出时，清理资源
}