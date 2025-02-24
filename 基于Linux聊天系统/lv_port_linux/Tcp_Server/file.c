#include "tcp_server.h"

bool  Send_File(client_link present_client_node)
{
    printf("客户端要下载！\n");
    if(File_Search(present_client_node,DEFAULT_FILE_PATH) == false)//进行固定目录检索
    {
        printf("目录检索失败！\n");
        return false;
    }
    printf("-----\n");
    P_FL file_list_head = present_client_node->p_si->file_list_head;

    pthread_mutex_lock(&present_client_node->p_si->mutex); //上锁
    //循环一次发送文件名字给客户端
    char msg[DATA_MAX_LEN];
    for(P_FL tmp_node = file_list_head->next; tmp_node != file_list_head; tmp_node = tmp_node->next)
    {
        memset(msg,0,DATA_MAX_LEN);
        printf("%s----%s\n",tmp_node->file_name,tmp_node->base_file_path);

        if(write(present_client_node->cli_fd,tmp_node->file_name,strlen(tmp_node->file_name)) == -1)//发送一个文件名字给客户端
        {
            perror("write ...");
            return false;
        }
        
        //等待客户端发送FINISH
        int read_ret = read(present_client_node->cli_fd,msg,DATA_MAX_LEN);
        if(read_ret == -1)
        {
            perror("read ...");
            return false;
        }
        else if(read_ret == 0)
        {
            printf("客户端掉线!\n");
            return false;
        }
        else
        {
            if(strcmp(msg,CONTINUE) != 0)
            {
                printf("传输有误！\n");
                break;
            }
        }
    }
    pthread_mutex_unlock(&present_client_node->p_si->mutex); //解锁

    if(write(present_client_node->cli_fd,FINISH,strlen(FINISH)) == -1)
    {
        perror("write ...");
        return -1;
    }

    
    LOOP:
    //等到客户端选择目标文件 ---进行文件传输
    memset(msg,0,DATA_MAX_LEN);

    int read_ret = read(present_client_node->cli_fd,msg,DATA_MAX_LEN);
    if(read_ret == -1)
    {
        perror("read ...");
        return false;
    }
    else if(read_ret == 0)
    {
        printf("客户端掉线!\n");
        return false;
    }
    else
    {
        printf("客户端要下载%s文件\n",msg);
    }

    //遍历链表检索找到对应文件结点，获取绝对路径进行文件创建
    int mask = 0;
    pthread_mutex_lock(&present_client_node->p_si->mutex); //上锁
    P_FL tmp_node;
    for(tmp_node = file_list_head->next; tmp_node != file_list_head; tmp_node = tmp_node->next)
    {
        if(strcmp(tmp_node->file_name,msg) == 0)
        {
            mask = 1;
            break;
        }
    }
    pthread_mutex_unlock(&present_client_node->p_si->mutex); //解锁

    if(mask == 0)
    {
        printf("没有该文件！\n");
        //告诉客户端没有
        if(write(present_client_node->cli_fd,NO,strlen(NO)) == -1)
        {
            perror("write ...");
            return false;
        }
        goto LOOP;
    }
    else
    {
        //告诉客户端有,发送文件大小表示有
        struct stat statbuf;
        if(stat(tmp_node->base_file_path,&statbuf) == -1)
        {
            perror("stat ...");
            return false;
        }

        if(write(present_client_node->cli_fd,&statbuf.st_size,sizeof(int)) == -1)
        {
            perror("write ...");
            return false;
        }
    }

    //打开客户端要下载的文件，进行文件创建
    int obj_file_fd = open(tmp_node->base_file_path,O_RDONLY);
    if(obj_file_fd == -1)
    {
        perror("open ...");
        return false;
    }

    char file_data[DATA_MAX_LEN];
    while(1)
    {
        memset(file_data,0,DATA_MAX_LEN);

        //先读256个文本数据
        int read_ret = read(obj_file_fd,file_data,DATA_MAX_LEN);
        if(read_ret == -1)
        {
            perror("read ...");
            return false;
        }
        else if(read_ret == 0)
        {
            //发送OK给客户端
            if(write(present_client_node->cli_fd,FINISH,strlen(FINISH)) == -1)
            {
                perror("write ...");
                return false;
            }
            break;
        }
        else
        {
            //再发256个文本数据给客户端
            if(write(present_client_node->cli_fd,file_data,read_ret) == -1)
            {
                perror("write ...");
                return false;
            }

            //最后等客户端发送继续
            memset(msg,0,DATA_MAX_LEN);
            int read_ret = read(present_client_node->cli_fd,msg,DATA_MAX_LEN);
            if(read_ret == -1)
            {
                perror("read ...");
                return false;
            }
            else if(read_ret == 0)
            {
                printf("客户端掉线!\n");
                return false;
            }
            else
            {
                if(strcmp(msg,CONTINUE) != 0)   
                {
                    printf("传输有误！\n");
                    return false;
                }
            }
        }
    }



    if(close(obj_file_fd) == -1)
    {
        perror("close ...");
        return false;
    }
    return true;
}

bool  Recv_File(client_link present_client_node)
{
    printf("客户端要上传！\n");

    return true;
}

P_FL Create_File_Node()
{
    P_FL new_node = (P_FL)malloc(sizeof(FL));
    if(new_node == (P_FL)NULL)
    {
        perror("malloc ...");
        return (P_FL)-1;
    }
    
    memset(new_node,0,sizeof(FL));

    new_node->next = new_node;
    new_node->prev = new_node;

    return new_node;

}

bool  File_Search(client_link present_client_node,char * obj_search_path)
{
    DIR * dp = opendir(obj_search_path);
    if(dp == (DIR *)NULL)
    {
        perror("opendir ...");
        return false;
    }

    char complete_path[DATA_MAX_LEN*2];
    while(1)
    {
        struct dirent * eq = readdir(dp);
        if(eq == (struct dirent *)NULL)
        {
            break;
        }

        //过滤.和..
        if(eq->d_name[0] == '.') continue;

        memset(complete_path,0,DATA_MAX_LEN);

        if(obj_search_path[strlen(obj_search_path)-1] == '/')
        {
            sprintf(complete_path,"%s%s",obj_search_path,eq->d_name);
        }
        else
        {
            sprintf(complete_path,"%s/%s",obj_search_path,eq->d_name);

        }

        if(eq->d_type == DT_DIR)
        {
            if(File_Search(present_client_node,complete_path) == false)
            {
                printf("文件递归检索失败！\n");
                return false;
            }

        }

        if(eq->d_type == DT_REG)
        {
            //创建新文件结点，把文件和路径拼接 --- 基于你读到的是文件
            P_FL new_file_node = Create_File_Node();
            if(new_file_node == (P_FL)-1)
            {
                printf("创建文件结点失败！\n");
                return false;
            }

            strcpy(new_file_node->file_name,eq->d_name);
            strcpy(new_file_node->base_file_path,complete_path);
            if(Add_File_Node(present_client_node,new_file_node) == false)
            {
                printf("添加文件结点失败！\n");
                return false;
            }
        }
        
    }

    if(closedir(dp) == -1)
    {
        perror("closedir ...");
        return false;
    }

    return true;
}

bool  Add_File_Node(client_link present_client_node,P_FL new_file_node)
{

    P_FL file_list_head = present_client_node->p_si->file_list_head;

    pthread_mutex_lock(&present_client_node->p_si->mutex);    //上锁

    new_file_node->next        = file_list_head->next;
    file_list_head->next->prev = new_file_node;

    file_list_head->next       = new_file_node;
    new_file_node->prev        = file_list_head;

    pthread_mutex_unlock(&present_client_node->p_si->mutex);    //解锁

    return true;
}