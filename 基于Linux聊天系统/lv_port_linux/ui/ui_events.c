#include "ui.h"

//登录按钮 （检验完成后跳转至主界面）
void login_event(lv_event_t * e)
{
    P_Cli p_cli=lv_event_get_user_data(e);
	//存储用户账号密码的文本数据
    char buf[1024] = {0};

    char file_usr[128] = {0};
    char file_pwd[128] = {0};
    int login_success = 0;

    // 获取用户输入的账号和密码
    const char *usr = lv_textarea_get_text(ui_TextArea1);  // 账号输入框
    const char *pwd = lv_textarea_get_text(ui_TextArea2);  // 密码输入框

	if(is_empty_or_whitespace(usr) || is_empty_or_whitespace(pwd))
	{
		printf("账号或密码不能为null\n");
		return;
	}

    // 读取用户信息文件
    FILE *fp = fopen("/cheng/client.txt", "r");
    if (NULL == fp) 
	{
        perror("文件打开失败");
        return;
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) 
	{
        if (sscanf(buf, "usr:%s pwd:%s", file_usr, file_pwd) == 2) 
		{
            if (strcmp(usr, file_usr) == 0 && strcmp(pwd, file_pwd) == 0) 
			{
                login_success = 1;  // 登录成功
                strcpy(p_cli->name,usr);
                //把自己的名字发送给服务器
                if(write(p_cli->socket,p_cli->name,strlen(p_cli->name)) == -1)
                {
                    perror("write ...");
                    return NULL;
                }
                break;
            }
        }
    }
    fclose(fp);

    if (login_success) 
	{
        printf("登录成功\n");
        // 隐藏登录界面和注册界面
        lv_obj_add_flag(ui_Screen1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_Screen2, LV_OBJ_FLAG_HIDDEN);
        
        // 显示主界面
        lv_obj_remove_flag(ui_Screen3, LV_OBJ_FLAG_HIDDEN);
        lv_disp_load_scr(ui_Screen3);
    } else 
	{
        printf("登录失败：账号或密码错误\n");
        lv_obj_t *box=lv_msgbox_create(ui_Screen1);
        lv_obj_set_size(box,250,45);
        lv_obj_align(box,LV_ALIGN_TOP_MID,0,0);
        lv_obj_t *lb=lv_label_create(box);
        lv_obj_center(lb);
        lv_label_set_chinese(lb,"登录失败：账号或密码错误");
    }
}

//登录界面 注册按钮  （跳转至注册页面）
void register_event(lv_event_t * e)
{
	lv_obj_add_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN); //隐藏登录界面
	lv_obj_add_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN); //隐藏主界面
	lv_obj_add_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN); //隐藏私聊界面
    lv_obj_add_flag(ui_Screen5,LV_OBJ_FLAG_HIDDEN); //隐藏登录界面
	//加载注册界面
	lv_obj_remove_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen2);
}



//文本点击事件1  （重复定义多个文本点击事件，多个按钮链接同一个事件，点击将多次触发）
void text_event1(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta =lv_event_get_target(e);
    lv_obj_t *kb=lv_event_get_user_data(e);
	// lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
    if(code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb,ta);
        lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
    }
    if(code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(kb,NULL);
        lv_obj_add_flag(kb,LV_OBJ_FLAG_HIDDEN);
    }
}

//文本点击事件2
void text_event2(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta =lv_event_get_target(e);
    lv_obj_t *kb=lv_event_get_user_data(e);
	// lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
    if(code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb,ta);
        lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
    }
    if(code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(kb,NULL);
        lv_obj_add_flag(kb,LV_OBJ_FLAG_HIDDEN);
    }
}

//文本点击事件3
void text_event3(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta =lv_event_get_target(e);
    lv_obj_t *kb=lv_event_get_user_data(e);
	// lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
    if(code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb,ta);
        lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
        lv_obj_move_foreground(ui_Keyboard3);  // 确保键盘在前面
    }
    if(code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(kb,NULL);
        lv_obj_add_flag(kb,LV_OBJ_FLAG_HIDDEN);
    }
}

//文本点击事件4
void text_event4(lv_event_t * e)
{
	lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta =lv_event_get_target(e);
    lv_obj_t *kb=lv_event_get_user_data(e);
	// lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
    if(code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb,ta);
        lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
        lv_obj_move_foreground(ui_Keyboard4);  // 确保键盘在前面
    }
    if(code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(kb,NULL);
        lv_obj_add_flag(kb,LV_OBJ_FLAG_HIDDEN);
    }
}

// //文本点击事件5
// void text_event5(lv_event_t * e)
// {
// 	lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t *ta =lv_event_get_target(e);
//     lv_obj_t *kb=lv_event_get_user_data(e);
// 	// lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
//     if(code == LV_EVENT_FOCUSED)
//     {
//         lv_keyboard_set_textarea(kb,ta);
//         lv_obj_remove_flag(kb,LV_OBJ_FLAG_HIDDEN);
//         lv_obj_move_foreground(ui_Keyboard5);  // 确保键盘在前面
//     }
//     if(code == LV_EVENT_DEFOCUSED)
//     {
//         lv_keyboard_set_textarea(kb,NULL);
//         lv_obj_add_flag(kb,LV_OBJ_FLAG_HIDDEN);
//     }
// }



//注册保存用户按钮
void save_usr_event(lv_event_t *e) {
    char buf[1024] = "\0";
    char usr_buf[128] = "\0";
    char *usr = lv_textarea_get_text(ui_TextArea3);
    char *pwd = lv_textarea_get_text(ui_TextArea4);

	if(is_empty_or_whitespace(usr) || is_empty_or_whitespace(pwd))
	{
		printf("账号或密码不能为null\n");
		return;
	}

    FILE *fp = fopen("/cheng/client.txt", "a+");
    if (NULL == fp) {
        perror("文件打开失败");
        exit(-1);
    }

    // 读取文件到 buf
    size_t ret = fread(buf, 1, sizeof(buf) - 1, fp);
    if (ret < 0) {
        perror("读取文件失败");
        fclose(fp);
        exit(-1);
    }
    buf[ret] = '\0';  // 确保缓冲区以空字符结尾

    // 检查用户是否已经注册
    if (Check_Usr(buf, usr)) {
        printf("注册失败:用户已存在\n");
        fclose(fp);
        return;
    }

    // 追加新用户信息
    snprintf(usr_buf, sizeof(usr_buf), "usr:%s pwd:%s\n", usr, pwd);
    ret = fwrite(usr_buf, strlen(usr_buf), 1, fp);
    if (ret != 1) {
        perror("写入文件失败");
        fclose(fp);
        exit(-1);
    }

    if (fclose(fp) != 0) {
        perror("文件关闭失败");
        exit(-1);
    }

    printf("注册成功\n");
}

//注册界面 重置按钮
void reset_event(lv_event_t * e)
{
	lv_textarea_set_text(ui_TextArea3,"");
	lv_textarea_set_text(ui_TextArea4,"");
}

//返回登录页面按钮
void return_login_event(lv_event_t * e)
{
	lv_obj_add_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN);  //隐藏注册界面
	lv_obj_add_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN);  //隐藏主界面
    lv_obj_add_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN);  //隐藏聊天界面
	//加载登录界面
	lv_obj_remove_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen1);
}

//天气界面显示
void weather_event(lv_event_t * e)
{
    P_Cli p_cli=lv_event_get_user_data(e);
    lv_obj_add_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN);  //隐藏登录界面
	lv_obj_add_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN);  //隐藏注册界面
	lv_obj_add_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN);  //隐藏主界面
    lv_obj_add_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN);  //隐藏聊天界面
    lv_obj_add_flag(ui_Screen5,LV_OBJ_FLAG_HIDDEN);  //隐藏群聊界面
    lv_obj_add_flag(ui_Screen6,LV_OBJ_FLAG_HIDDEN);  //隐藏退出界面
    lv_obj_add_flag(ui_Image20,LV_OBJ_FLAG_HIDDEN);  //隐藏退出图标
    //加载天气界面
	lv_obj_remove_flag(ui_Screen7,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen7);
    
    if(Show_Weather(p_cli)==false)
    {
        printf("查询天气失败\n");
    }    
}

//天气界面退出到主界面
void exit_to_main_w(lv_event_t * e) 
{
    P_Cli p_cli=lv_event_get_user_data(e);
    pthread_mutex_lock(&p_cli->mutxe);
    if(time1!=NULL)
    {
        lv_timer_delete(time1); //清除时间任务
        time1 = NULL;
    }
    lv_obj_delete(label_city);
    lv_obj_delete(label_temp);
    count_time=0;
    lv_obj_delete(label_weather);
    lv_obj_delete(label_wind);
    lv_obj_delete(img_w);
    pthread_mutex_unlock(&p_cli->mutxe);
    lv_obj_add_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN);  //隐藏登录界面
	lv_obj_add_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN);  //隐藏注册界面
	lv_obj_add_flag(ui_Screen7,LV_OBJ_FLAG_HIDDEN);  //隐藏天气界面
    lv_obj_add_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN);  //隐藏聊天界面
    lv_obj_add_flag(ui_Screen5,LV_OBJ_FLAG_HIDDEN);  //隐藏群聊界面
    lv_obj_add_flag(ui_Screen6,LV_OBJ_FLAG_HIDDEN);  //隐藏退出界面
    //加载主界面
	lv_obj_remove_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen3);
}

// void send_city_event(lv_event_t * e)  //发送城市信息
// {
//     P_Cli p_cli=lv_event_get_user_data(e);
//     char address[17]="\0";
//     strcpy(address,lv_textarea_get_text(textarea_w));  //获取文本框数据
//     if(write(p_cli->socket,address,sizeof(address)) == -1)
//     {
//         perror("write ...");
//         return false;
//     }
// }


//群聊界面
void all_chat_event(lv_event_t * e)
{
	P_Cli p_cli=lv_event_get_user_data(e);
    p_cli->run=0;
	lv_obj_add_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN); //隐藏登录界面
	lv_obj_add_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN); //隐藏注册界面
	lv_obj_add_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN); //隐藏主界面
    lv_obj_add_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN); //隐藏私聊界面
	//加载chat_all界面
	lv_obj_remove_flag(ui_Screen5,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen5);
    //显示在线人员
    if(Show_Online_style(p_cli)==false)
    {
        printf("显示在线人员失败\n");
    }
    if(BroadCast(p_cli)==false)
    {
        printf("群聊失败\n");
    }
}

//群聊发送消息按钮
void snd_btn_all(lv_event_t * e)
{
    P_Cli p_cli=lv_event_get_user_data(e);
    char data[DATA_MAX_LEN];
    memset(data,0,DATA_MAX_LEN);
    strcpy(data,lv_textarea_get_text(ui_TextArea5));  //获取文本框数据

    if(write(p_cli->socket,data,strlen(data)) == -1)
    {
        perror("write ...");
        return false;
    }
}

//群聊退出到主界面
void exit_to_main(lv_event_t * e)
{
    P_Cli p_cli=lv_event_get_user_data(e);
    pthread_mutex_lock(&p_cli->mutxe);
    if(time1!=NULL)
    {
        lv_timer_delete(time1); //清除时间任务
        time1 = NULL;
    }
    int ret=write(p_cli->socket,MODE_EXIT,strlen(MODE_EXIT)); //发送给服务器我不聊天了
    if(-1==ret)
    {
        perror("退出失败");
    }
    p_cli->run=1; //使群聊中断
    pthread_mutex_unlock(&p_cli->mutxe);
    lv_obj_add_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN); //隐藏登录界面
	lv_obj_add_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN); //隐藏注册界面
	lv_obj_add_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN); //隐藏私聊界面
    lv_obj_add_flag(ui_Screen5,LV_OBJ_FLAG_HIDDEN); //隐藏群聊界面
    lv_obj_add_flag(ui_Screen6,LV_OBJ_FLAG_HIDDEN); //隐藏退出界面
    lv_obj_add_flag(ui_Screen7,LV_OBJ_FLAG_HIDDEN); //隐藏天气界面
	//加载主界面
	lv_obj_remove_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen3);
}


//私聊界面
void chat_event(lv_event_t * e)
{
    P_Cli p_cli=lv_event_get_user_data(e);
	lv_obj_add_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN); //隐藏登录界面
	lv_obj_add_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN); //隐藏注册界面
	lv_obj_add_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN); //隐藏主界面
	//加载chat界面
	lv_obj_remove_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen4);
    //显示在线人员
    if(Show_Online(p_cli)==false)
    {
        printf("显示在线人员失败\n");
    }
}

//点击列表按钮 私聊窗口初始化
void private_chat_event(lv_event_t * e)
{
    //防止多次点击窗口
    if(private_chat_num==1)
    {
        return;
    }
    private_chat_num=1;

    lv_obj_remove_flag(send_button,LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(textarea1,LV_OBJ_FLAG_HIDDEN);

     P_Cli p_cli = (P_Cli)lv_event_get_user_data(e);

     p_cli->run=0;//重置聊天循环判断

    //聊天数据清洗
    char *p = strstr(p_cli->chat_data, "退出");
    while (p != NULL) 
    {
        *p = '\0';  // 截断 "退出" 及其后的内容
        p = strstr(p + 1, "退出");  // 继续查找下一个 "退出"
    }
    //创建窗口
    win = lv_win_create(ui_Screen4);
    lv_obj_set_size(win,450,400);
    lv_obj_align(win,LV_ALIGN_CENTER,90,20);
    // 获取事件源对象（这是按钮）
    lv_obj_t * list_btn = lv_event_get_target(e);
    // 获取按钮的文本（私聊对象名字）
    char * btn_name = lv_list_get_button_text(list,list_btn);

    //获取要发送的人员姓名并且保存到结构体中
    char *data=btn_name;  
    int count=0;
    char name[18]="\0";
    while(*data!='-')
    {
        name[count]=*data;
        count++;
        data++;
    }
    memset(p_cli->send_name,0,sizeof(p_cli->send_name)); //清空原私聊对象
    strcpy(p_cli->send_name,name);
    //创建标题
    char username[18]="\0";
    sprintf(username,"昵称：%s",name);
    lv_win_add_chinese(win,username);
    //添加按钮
    lv_obj_t * btn;
    btn = lv_win_add_button(win,NULL, 80);
    lv_label_set_chinese(lv_label_create(btn),"退出");
    lv_obj_add_event_cb(btn,exit_private_event,LV_EVENT_CLICKED,p_cli);

    lv_obj_t * cont = lv_win_get_content(win); //窗口设置
    label_win = lv_label_create(cont);
    lv_obj_set_scrollbar_mode(cont,LV_SCROLL_SNAP_NONE);
    Private(p_cli,label_win);
}

//刷新在线人员按钮点击事件
void reset_online_event(lv_event_t * e)
{
    printf("刷新在线人员\n");
    lv_obj_clean(list);
    lv_obj_delete(list); //清除列表
    P_Cli p_cli=lv_event_get_user_data(e);
    Show_Online(p_cli);  
}

//私聊发送消息按钮
void send_msg_event(lv_event_t * e)
{
    P_Cli p_cli=lv_event_get_user_data(e);
    char data2[DATA_MAX_LEN*16];
    memset(data2,0,DATA_MAX_LEN);
    strcpy(data2,lv_textarea_get_text(textarea1));  //获取文本框数据

    // char data3[126]="\0";
    // sprintf(data3,"%s:%s\n",p_cli->name,data2);  //数据拼接,存储到聊天数据
    int ret=0;
    if(ret=write(p_cli->socket,data2,strlen(data2)) == -1)
    {
        perror("write ...");
        return false;
    }
    // strcat(p_cli->chat_data,data3);
}

//清除私聊窗口
void exit_private_event(lv_event_t * e)
{
    P_Cli p_cli=lv_event_get_user_data(e);
    pthread_mutex_lock(&p_cli->mutxe);
    private_chat_num=1; //不与人私聊
    if(time1!=NULL)
    {
        lv_timer_delete(time1); //清除时间任务
        time1 = NULL;
    }
    int ret=write(p_cli->socket,MODE_EXIT,strlen(MODE_EXIT)); //发送给服务器我不聊天了
    if(-1==ret)
    {
        perror("退出失败");
    }
    p_cli->run=1;
    private_chat_num=0;
    lv_obj_delete(win);  //删除界面
    lv_obj_add_flag(send_button,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(textarea1,LV_OBJ_FLAG_HIDDEN);
    pthread_mutex_unlock(&p_cli->mutxe);
}

//私聊界面退出到主界面
void exit_to_mains(lv_event_t * e)
{
    P_Cli p_cli=lv_event_get_user_data(e);
    pthread_mutex_lock(&p_cli->mutxe);
    if(time1!=NULL)
    {
        lv_timer_delete(time1); //清除时间任务
        time1 = NULL;
    }
    if(p_cli->run!=1)
    {
        int ret=write(p_cli->socket,MODE_EXIT,strlen(MODE_EXIT)); //发送给服务器我不聊天了
        if(-1==ret)
        {
            perror("退出失败");
        }
    }
    p_cli->run=1; //使私聊中断
    private_chat_num=0; //没有与人私聊
    if (lv_obj_is_valid(win)) 
    {
        lv_obj_add_flag(send_button,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(textarea1,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clean(win);  //删除界面
        lv_obj_delete(win);  //删除界面
    }
    // lv_obj_clean(list);  //删除界面
    // lv_obj_delete(list);  //删除界面
    pthread_mutex_unlock(&p_cli->mutxe);
    lv_obj_add_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN); //隐藏登录界面
	lv_obj_add_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN); //隐藏注册界面
	lv_obj_add_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN); //隐藏私聊界面
    lv_obj_add_flag(ui_Screen5,LV_OBJ_FLAG_HIDDEN); //隐藏群聊界面
    lv_obj_add_flag(ui_Screen6,LV_OBJ_FLAG_HIDDEN); //隐藏退出界面
    lv_obj_add_flag(ui_Screen7,LV_OBJ_FLAG_HIDDEN); //隐藏天气界面
	//加载主界面
	lv_obj_remove_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen3);
}


//退出所有，断开连接，释放一切资源
void exit_event(lv_event_t * e) 
{
    P_Cli p_cli=lv_event_get_user_data(e);
	lv_obj_add_flag(ui_Screen1,LV_OBJ_FLAG_HIDDEN); //隐藏登录界面
	lv_obj_add_flag(ui_Screen2,LV_OBJ_FLAG_HIDDEN); //隐藏注册界面
	lv_obj_add_flag(ui_Screen3,LV_OBJ_FLAG_HIDDEN); //隐藏主界面
    lv_obj_add_flag(ui_Screen4,LV_OBJ_FLAG_HIDDEN); //隐藏私聊界面
    lv_obj_add_flag(ui_Screen5,LV_OBJ_FLAG_HIDDEN); //隐藏群聊界面
    //加载chat_all界面
	lv_obj_remove_flag(ui_Screen6,LV_OBJ_FLAG_HIDDEN);
	lv_disp_load_scr(ui_Screen6);
    if(close(p_cli->socket)==-1) //关闭套接字
    {
        printf("无法断开连接");
    }
    free(p_cli);
}