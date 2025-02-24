#include "../ui.h"

//向服务器发送群聊申请
bool BroadCast(P_Cli p_cli) //connect之后，客户端可以使用自己的套接字给服务器发送接收信息
{
    p_cli->run=0; //开始群聊
    // time1=lv_timer_create(timer_callback,10,p_cli);  //添加时间任务
    //发送功能需要给服务器
    if(write(p_cli->socket,MODE_BROADCAST,strlen(MODE_BROADCAST)) == -1)
    {
        perror("write ...");
        return false;
    }
    pthread_create(&p_cli->tid1,NULL,all_chat_chat,p_cli); //创建线程，不断更新聊天界面数据
    pthread_detach(p_cli->tid1);  //设置分离属性

    return true;  //继续执行主线程
}

// 定时器回调函数，在主线程中更新 UI
void timer_callback1(lv_timer_t * timer)
{
    // 使用子线程中更新的数据来更新 UI
    P_Cli p_cli=timer->user_data;
    lv_label_set_chinese(label_tabview,p_cli->chat_data_plus);
}

// 线程函数，不断更新聊天界面数据
void *all_chat_chat(void *arg)
{
    P_Cli p_cli=(P_Cli)arg;
    time1=lv_timer_create(timer_callback1,10,p_cli);  //添加时间任务0.01秒执行一次
    char data[DATA_MAX_LEN];
    fd_set fs;//定义要多路复用监听的文件描述符集合
    struct timeval timeout;  //设置超时更新界面
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    while(1)
    {
        if(p_cli->run==1)
        {
            printf("退出群聊\n");
            break;
        }
        //多路复用
        FD_ZERO(&fs); //清空文件描述符
        FD_SET(0,&fs);        //把标准输入文件描述符添加到集合中
        FD_SET(p_cli->socket,&fs);              //把客户端套接字添加进去
    
        if(select(p_cli->socket+1,&fs,NULL,NULL,&timeout) == -1)
        {
            perror("select ...");
            return false;
        }
        if(FD_ISSET(p_cli->socket,&fs))//判断能不能读取消息
        {
            memset(data,0,DATA_MAX_LEN);
            if(read(p_cli->socket,data,DATA_MAX_LEN) == -1)
            {
                perror("Read ...");
                return false;
            }
            printf("%s\n",data);
            char data_clean[DATA_MAX_LEN*3]="\0";
            memset(data_clean,0,DATA_MAX_LEN*3);
            sprintf(data_clean,"%s\n",data);
            strcat(p_cli->chat_data_plus,data_clean);
        }

        if(FD_ISSET(0,&fs))//是不是能读取键盘
        {
            continue;
        }
    }
    pthread_exit(NULL);  // 线程退出时，清理资源
    return true;
}
