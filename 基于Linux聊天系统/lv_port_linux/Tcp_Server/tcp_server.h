#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <dirent.h>

#define DATA_MAX_LEN 256
#define MODE_BROADCAST    "群聊"
#define MODE_PRIVATE      "私聊"
#define MODE_SHOW_ONLINE  "显示在线人员"
#define FILE_DOWNLOAD     "文件下载"
#define FILE_UPLOAD       "文件上传"
#define MODE_EXIT         "退出"
#define MODE_WEATHER      "显示天气"
#define FINISH            "OK"
#define CONTINUE          "continue"
#define NO                "404"
#define DEFAULT_FILE_PATH "./shared_file"

struct file_list;
struct client_list;

typedef struct server_inf
{
    int ser_fd;//服务器套接字
    //链表头节点 --- 存放每一个在线人员的信息
    struct client_list * client_list_head;
    struct file_list * file_list_head; //上传文件链表头
    pthread_mutex_t mutex;
}SI,*P_SI;

typedef struct file_list
{
    char file_name[DATA_MAX_LEN];
    char base_file_path[DATA_MAX_LEN];

    struct file_list * next ,* prev;
}FL,*P_FL;

typedef struct client_list
{
    int  cli_fd;
    char cli_ip[16];
    char user_name[DATA_MAX_LEN];
    pthread_t cli_pid;
    P_SI p_si;
    struct client_list * next, * prev;
}client_node,*client_link;

P_SI  Tcp_Server_Init(int prot_num);
client_link Create_Client_Node();
bool  Wait_For_Client_Connect(P_SI p_si);
bool  Add_Client_Node(client_link client_list_head,client_link new_client_node);
void  * Client_Pthread_Mode_Select(void * arg);
bool  Send_Online_Inf(client_link present_client_node);
bool  Del_Client_Node(client_link del_node);
bool  Send_All(client_link present_client_node);
bool  Send_All_Weather(client_link present_client_node);
bool  Send_File(client_link present_client_node);
bool  Recv_File(client_link present_client_node);
int   Cilent_Init();
int   Send_Request(int sock_fd,client_link present_client_node);
char  *Get_Alaysis_Response(int sock_fd);
// bool  Get_Data(char *p);
bool  Send_File(client_link present_client_node);
bool  Recv_File(client_link present_client_node);
bool  File_Search(client_link present_client_node,char * obj_search_path);
bool  Add_File_Node(client_link present_client_node,P_FL new_file_node);
bool  Send_Private(client_link present_client_node);
#endif