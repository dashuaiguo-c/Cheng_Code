#include "../ui.h"

//向服务器发送天气请求
bool Show_Weather(P_Cli p_cli)
{
    //发送功能需要给服务器
    if(write(p_cli->socket,MODE_WEATHER,strlen(MODE_WEATHER)) == -1)
    {
        perror("write ...");
        return false;
    }
    pthread_create(&p_cli->tid2,NULL,weather_task,p_cli); //创建线程，不断更新聊天界面数据
    pthread_detach(p_cli->tid2);  //设置分离属性
    return true;  //继续执行主线程
}

//时间回调函数，定时刷新UI界面，1秒钟刷新一次（时间）
void timer_callback2(lv_timer_t * timer)  //1秒钟在主线程中刷新一次
{
    //显示时间
    if(label_time!=NULL)
    {
        lv_obj_delete(label_time);
    }
    time_t t;
    t = time(NULL);                // 获取当前时间
    struct tm *time_now = localtime(&t); // 转换为本地时间
    char date[50]="\0";
    char day[8]  ="\0";
    if(time_now->tm_mday<10)  //monday
    {
        sprintf(day,"0%d",time_now->tm_mday);
    }
    else
    {
        sprintf(day,"%d",time_now->tm_mday);
    }
    sprintf(date,"%d-%d-%s %d:%d:%d",time_now->tm_year+1900,time_now->tm_mon+1,day,\
    time_now->tm_hour,time_now->tm_min,time_now->tm_sec);
    // 设置文本颜色为红色
    lv_color_t red = lv_color_hex(0xFF0000);  // 创建红色
    label_time= lv_label_create(ui_Screen7);
    lv_obj_set_align(label_time, LV_ALIGN_TOP_MID);
    lv_obj_set_style_text_color(label_time, red, LV_STATE_DEFAULT);
    lv_label_set_chinese(label_time,date);   //设置时间标签
    if(count_time==1)  //显示过的标签,不用叠加
    {
        return;
    }
    //显示数据
    label_city=lv_label_create(ui_Screen7);  //城市
    lv_obj_align(label_city,LV_ALIGN_TOP_LEFT,100,0);

    label_weather=lv_label_create(ui_Screen7);  //天气
    lv_obj_align_to(label_weather,label_time,LV_ALIGN_BOTTOM_MID,-250,60);

    label_temp=lv_label_create(ui_Screen7); //温度
    lv_obj_align_to(label_temp,label_weather,LV_ALIGN_RIGHT_MID,200,0);

    label_wind=lv_label_create(ui_Screen7); //风力
    lv_obj_align_to(label_wind,label_weather,LV_ALIGN_RIGHT_MID,400,0);

    img_w=lv_image_create(ui_Screen7);  //图标
    lv_obj_align_to(img_w,label_weather,LV_ALIGN_LEFT_MID,-60,-30);
    //逐行解析
    char city[30]="\0";
    char weather[16]="\0";
    char weather_day[32] = "\0";
    char temp[20]="\0";
    char wind_tp[20]="\0";
    char wind[20]="\0";
    int temp_day = 0, temp_night = 0;
    int count_data=0;
    char *line = NULL;
    line = strtok(data_weather, "\n");  //按照下划线区分结点
    while (line != NULL)  //line为指向下一个结点的指针
    {  
        if(sscanf(line,"城市:%s",city) == 1) 
        {
            lv_obj_set_style_text_color(label_city, red, LV_STATE_DEFAULT);  //设置城市
            lv_label_set_chinese(label_city,city);
            printf("城市: %s\n",city);
        }
        else if (sscanf(line, "白天天气:%s", weather_day) == 1) 
        {
            lv_obj_set_style_text_color(label_weather, red, LV_STATE_DEFAULT);
            sprintf(weather,"天气:%s",weather_day);
            lv_label_set_chinese(label_weather, weather); // 设置天气到标签
            printf("天气: %s\n",weather_day);
        }
        else if (sscanf(line, "白天温度:%d", &temp_day) == 1)  //温度
        {
            printf("白天温度: %d\n", temp_day);
        }
        else if (sscanf(line, "夜晚温度:%d", &temp_night) == 1) 
        {
            lv_obj_set_style_text_color(label_temp, red, LV_STATE_DEFAULT);
            sprintf(temp,"温度:%d~%d",temp_night,temp_day);
            lv_label_set_chinese(label_temp, temp); // 设置温度标签
            printf("夜晚温度: %d\n", temp_night);
        }
        else if(sscanf(line,"白天风力:%s",wind_tp) == 1) 
        {
            lv_obj_set_style_text_color(label_wind, red, LV_STATE_DEFAULT);
            sprintf(wind,"风力:%s",wind_tp);
            lv_label_set_chinese(label_wind, wind); // 设置风力标签
            printf("白天风力: %s\n",wind);
        }
        count_data++;
        line = strtok(NULL, "\n");
        if(count_data==10)
        {
            break;
        }
    }
    if(strstr(weather_day,"晴"))  //显示背景图片
    {
        lv_image_set_src(img_w,"A:/cheng/images/晴天.png");
        lv_obj_set_style_bg_img_src(ui_Screen7, &ui_img_sun_png, LV_PART_MAIN);
        
    }
    else if(strstr(weather_day,"雨"))
    {
        lv_image_set_src(img_w,"A:/cheng/images/下雨.png");
        lv_obj_set_style_bg_img_src(ui_Screen7, &ui_img_rain_png, LV_PART_MAIN);
    }
    else
    {
        lv_image_set_src(img_w,"A:/cheng/images/多云.png");
        lv_obj_set_style_bg_img_src(ui_Screen7, &ui_img_cloud_png, LV_PART_MAIN);
    }
    count_time=1;
}

//天气查询
void *weather_task(void *arg)
{
    P_Cli p_cli=(P_Cli)arg;
    char address[17]="\0";
    memset(address,0,sizeof(address));
    printf("请输入你要查询的城市:\n");
    scanf("%s",address);
    write(p_cli->socket,address,sizeof(address));
    lv_obj_remove_flag(ui_Image20,LV_OBJ_FLAG_HIDDEN);
    usleep(200);
    time1=lv_timer_create(timer_callback2,1000,p_cli);  //添加时间任务
    fd_set  fs;  //定义要多路复用监听的文件描述符集合
    char data[DATA_MAX_LEN*16];
    while(1)
    {
        //多路复用
        FD_ZERO(&fs); //清空文件描述符
        FD_SET(STDIN_FILENO,&fs);        //把标准输入文件描述符添加到集合中
        FD_SET(p_cli->socket,&fs);              //把客户端套接字添加进去
    
        if(select(p_cli->socket+1,&fs,NULL,NULL,NULL) == -1)
        {
            perror("select ...");
            return false;
        }

        if(FD_ISSET(p_cli->socket,&fs))//判断能不能读取消息
        {
            memset(data,0,DATA_MAX_LEN*16);
            if(read(p_cli->socket,data,DATA_MAX_LEN*16) == -1)
            {
                perror("Read ...");
                return false;
            }
            if(strcmp(data,FINISH) == 0) 
            {
                break;
            }
            if(Get_Data(data)!=true)
            {
                printf("获取天气数据失败\n");
                return false;
            }
        }
    }
    pthread_exit(NULL);  // 线程退出时，清理资源
    return true;
}

//json数据清洗，获取天气数据
bool Get_Data(char *p)
{
    //JSON数据解析
    // printf("%s\n",p);
    memset(data_weather,0,sizeof(data_weather));//清空天气数据
    char data_clean[256]="\0";

	cJSON *data=cJSON_Parse(p);  //将数据转换为cjson

	cJSON *item1=cJSON_GetObjectItem(data,"forecasts");  //获取cjson数组1
	cJSON *body=cJSON_GetArrayItem(item1,0);  //获取数组中的首元素1

	char *new_data=cJSON_Print(body); //获取到cjson天气预报时间
	// printf("城市:%s%s\n",cJSON_GetObjectItem(body,"province")->valuestring,cJSON_GetObjectItem(body,"city")->valuestring);
    sprintf(data_clean,"城市:%s%s\n",cJSON_GetObjectItem(body,"province")->valuestring,cJSON_GetObjectItem(body,"city")->valuestring);
    strcat(data_weather,data_clean);

	// printf("天气预报时间:%s\n",cJSON_GetObjectItem(body,"reporttime")->valuestring);
    memset(data_clean,0,sizeof(data_clean));
    sprintf(data_clean,"天气预报时间:%s\n",cJSON_GetObjectItem(body,"reporttime")->valuestring);
    strcat(data_weather,data_clean);

    cJSON *item2=cJSON_GetObjectItem(body,"casts"); //获取cjson数组2
    cJSON *body2=cJSON_GetArrayItem(item2,0);  //获取数组中的首元素2
    while(body2!=NULL)
    {
        // printf("\r\n");
        // printf("日期:%s\n",cJSON_GetObjectItem(body2,"date")->valuestring); //获取到cjson天气信息
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"日期:%s\n",cJSON_GetObjectItem(body2,"date")->valuestring);
        strcat(data_weather,data_clean);

        // printf("白天天气:%s\n",cJSON_GetObjectItem(body2,"dayweather")->valuestring);
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"白天天气:%s\n",cJSON_GetObjectItem(body2,"dayweather")->valuestring);
        strcat(data_weather,data_clean);

        // printf("夜晚天气:%s\n",cJSON_GetObjectItem(body2,"nightweather")->valuestring);
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"夜晚天气:%s\n",cJSON_GetObjectItem(body2,"nightweather")->valuestring);
        strcat(data_weather,data_clean);

        // printf("白天温度:%s\n",cJSON_GetObjectItem(body2,"daytemp")->valuestring);
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"白天温度:%s\n",cJSON_GetObjectItem(body2,"daytemp")->valuestring);
        strcat(data_weather,data_clean);

        // printf("夜晚温度:%s\n",cJSON_GetObjectItem(body2,"nighttemp")->valuestring);
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"夜晚温度:%s\n",cJSON_GetObjectItem(body2,"nighttemp")->valuestring);
        strcat(data_weather,data_clean);

        // printf("白天风向:%s\n",cJSON_GetObjectItem(body2,"daywind")->valuestring);
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"白天风向:%s\n",cJSON_GetObjectItem(body2,"daywind")->valuestring);
        strcat(data_weather,data_clean);

        // printf("夜晚风向:%s\n",cJSON_GetObjectItem(body2,"nightwind")->valuestring);
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"夜晚风向:%s\n",cJSON_GetObjectItem(body2,"nightwind")->valuestring);
        strcat(data_weather,data_clean);

        // printf("白天风力:%s\n",cJSON_GetObjectItem(body2,"daypower")->valuestring);
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"白天风力:%s\n",cJSON_GetObjectItem(body2,"daypower")->valuestring);
        strcat(data_weather,data_clean);

        // printf("夜晚风力:%s\n",cJSON_GetObjectItem(body2,"nightpower")->valuestring);
        memset(data_clean,0,sizeof(data_clean));
        sprintf(data_clean,"夜晚风力:%s\n",cJSON_GetObjectItem(body2,"nightpower")->valuestring);
        strcat(data_weather,data_clean);  
        body2=body2->next;
    }
	cJSON_Delete(data);//释放空间
	free(new_data);

	return true;
}