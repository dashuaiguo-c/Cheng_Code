#include "../ui.h"

//显示在线人员，可点击触发私聊
bool Show_Online(P_Cli p_cli)
{
    //初始化在线人员列表
    list = lv_list_create(ui_Screen4);
    lv_obj_set_size(list,200,480);
    lv_obj_align(list,LV_ALIGN_TOP_LEFT,0,0);
    char title[18]="\0";
    sprintf(title,"%s-在线人员",p_cli->name);
    lv_list_add_chinese(list,title);
     //发送功能需要给服务器
    if(write(p_cli->socket,MODE_SHOW_ONLINE,strlen(MODE_SHOW_ONLINE)) == -1)
    {
        perror("write ...");
        return false;
    }
    //循环接收服务器发送过来的在线人员IP信息 --- 当收到finish
    char data[DATA_MAX_LEN];
    while(1)
    {
        memset(data,0,DATA_MAX_LEN);
        int ret=0;
        if(ret=read(p_cli->socket,data,DATA_MAX_LEN) == -1)
        {
            perror("read ...");
            return false;
        }
        if(strcmp(data,FINISH) == 0) //接收是否发送完成
        {
            break;
        }
        if(!(strstr(data,"在线人员")))//判断该消息不是在线人员信息
        {
            continue;
        }

        //数据拆分
        char datas[DATA_MAX_LEN];
        memset(datas,0,DATA_MAX_LEN);
        sscanf(data,"在线人员：%s",datas);

        //添加在线人员到列表中
        lv_button_t *btn=lv_list_add_button_chinese(list,datas);
        //添加列表点击事件（私聊）
        lv_obj_add_event_cb(btn,private_chat_event, LV_EVENT_CLICKED,p_cli);
        //把continue发送告诉服务器继续发
        if(write(p_cli->socket,CONTINUE,strlen(CONTINUE)) == -1)
        {
            perror("write ...");
            return false;
        }
    }
    return true;  //继续主线程
}

//特殊显示在线人员，仅显示
bool Show_Online_style(P_Cli p_cli)
{
    //初始化在线人员列表
    list_style = lv_list_create(ui_Screen5);
    lv_obj_set_size(list_style,220,480);
    lv_obj_align(list_style,LV_ALIGN_TOP_LEFT,0,0);
    char title[18]="\0";
    sprintf(title,"%s-在线人员",p_cli->name);
    lv_list_add_chinese(list_style,title);
     //发送功能需要给服务器
    if(write(p_cli->socket,MODE_SHOW_ONLINE,strlen(MODE_SHOW_ONLINE)) == -1)
    {
        perror("write ...");
        return false;
    }
    //循环接收服务器发送过来的在线人员IP信息 --- 当收到finish
    char data[DATA_MAX_LEN];
    while(1)
    {
        memset(data,0,DATA_MAX_LEN);
        int ret=0;
        if(ret=read(p_cli->socket,data,DATA_MAX_LEN) == -1)
        {
            perror("read ...");
            return false;
        }
        if(strcmp(data,FINISH) == 0) //接收是否发送完成
        {
            break;
        }
        if(!(strstr(data,"在线人员")))//判断该消息不是在线人员信息
        {
            continue;
        }

        //数据拆分
        char datas[DATA_MAX_LEN];
        memset(datas,0,DATA_MAX_LEN);
        sscanf(data,"在线人员：%s",datas);

        //添加在线人员到列表中
        lv_label_set_small_chinese(list_style,datas);
        //把continue发送告诉服务器继续发
        if(write(p_cli->socket,CONTINUE,strlen(CONTINUE)) == -1)
        {
            perror("write ...");
            return false;
        }
    }
    return true;  //继续主线程
}