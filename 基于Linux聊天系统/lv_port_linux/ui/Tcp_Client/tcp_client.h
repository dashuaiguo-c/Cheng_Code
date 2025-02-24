#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_
#include <lvgl.h>
#include <stdio.h>
#include <sys/select.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cjson/cJSON.h>
#include <pthread.h>

#define DATA_MAX_LEN 256
#define MODE_BROADCAST   "群聊"
#define MODE_PRIVATE     "私聊"
#define MODE_SHOW_ONLINE "显示在线人员"
#define MODE_WEATHER     "显示天气"
// #define FILE_DOWNLOAD    "文件下载"
// #define FILE_UPLOAD      "文件上传"
#define MODE_EXIT        "退出"
#define FINISH           "OK"
#define CONTINUE         "continue"
#define SAVE_PATH        "./save_file/"
#define NO                "404"

typedef struct client{  //存储客户端数据
    int socket;  //套接字
    char name[18];  //姓名
    char send_name[18]; //私聊对象
    char chat_data[2048];  //私聊聊天数据
    char chat_data_plus[4096]; //群聊聊天数据
    int  run;
    pthread_t tid;  //线程id
    pthread_t tid1;
    pthread_t tid2;
    pthread_mutex_t mutxe;  //锁
}Cli,*P_Cli;

P_Cli Client_Init(char * ser_ip,int ser_port_num);  //客户端初始化
bool Private(P_Cli p_cli,lv_obj_t *label);  //私聊界面初始化
void *private_chat_chat(void *arg);  //私聊线程
bool Show_Online(P_Cli p_cli);  //展示在线renyuan
bool BroadCast(P_Cli p_cli);  //群聊
bool Show_Weather(P_Cli p_cli);
bool Get_Data(char *p);
void *weather_task(void *arg);
// bool Download_File(int cli_fd);
// bool UPload_File(int cli_fd);
// bool Get_File_Name(int cli_fd);
#endif