//与项目无关，不必理会
#include "lvgl.h"
#include <pthread.h>

//创建9个不同位置的对象  组成方块
void create_screen()
{
    lv_obj_t *obj=lv_obj_create(lv_screen_active());  //创建base对象
    lv_obj_set_size(obj,100,100);
    lv_obj_align(obj,LV_ALIGN_CENTER,0,0);

    lv_obj_t *obj1=lv_obj_create(lv_screen_active());  
    lv_obj_set_size(obj1,100,100);
    lv_obj_align_to(obj1,obj,LV_ALIGN_OUT_TOP_LEFT,-100,0);

    lv_obj_t *obj2=lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj2,100,100);
    lv_obj_align_to(obj2,obj,LV_ALIGN_OUT_TOP_MID,0,0); 

    lv_obj_t *obj3=lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj3,100,100);
    lv_obj_align_to(obj3,obj,LV_ALIGN_OUT_TOP_RIGHT,100,0);

    lv_obj_t *obj4=lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj4,100,100);
    lv_obj_align_to(obj4,obj,LV_ALIGN_OUT_RIGHT_MID,0,0);  

    lv_obj_t *obj5=lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj5,100,100);
    lv_obj_align_to(obj5,obj,LV_ALIGN_OUT_LEFT_MID,0,0);

    lv_obj_t *obj6=lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj6,100,100);
    lv_obj_align_to(obj6,obj,LV_ALIGN_OUT_BOTTOM_LEFT,-100,0);

    lv_obj_t *obj7=lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj7,100,100);
    lv_obj_align_to(obj7,obj,LV_ALIGN_OUT_BOTTOM_RIGHT,100,0);

    lv_obj_t *obj8=lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj8,100,100);
    lv_obj_align_to(obj8,obj,LV_ALIGN_OUT_BOTTOM_MID,0,0);    
}

//全局变量
lv_obj_t *text=NULL;  //输出标签
lv_obj_t * img=NULL;  //图片
char imgs[6][100]={"A:/home/dragon/jj.bmp",\
                  "A:/home/dragon/jj1.bmp",\
                  "A:/home/dragon/jj2.bmp",\
                  "A:/home/dragon/jj3.bmp",\
                  "A:/home/dragon/jj4.bmp"};
int i=0;  //图片索引

//上一张
static void event_handler1(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);  //获取按钮的事件
    if(code == LV_EVENT_CLICKED) 
    {
        printf("上一张\n");
        i--;
        if(i<0)
        {
            i=4;
        }
        lv_image_set_src(img, imgs[i]); //设置路径
    }
}

//下一张
static void event_handler2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);  //获取按钮的事件
    if(code == LV_EVENT_CLICKED) 
    {
        printf("下一张\n");
        i++;
        if(i>4)
        {
            i=0;
        }
        lv_image_set_src(img, imgs[i]); //设置路径
    }
}

//点击按钮切换图片
void diswin()  
{


    lv_obj_t *btn1 = lv_button_create(lv_screen_active());  //按钮1
    lv_obj_add_event_cb(btn1, event_handler1, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_LEFT_MID,80,0);

    lv_obj_t *label1 = lv_label_create(btn1);
    lv_label_set_text(label1, "Last");
    lv_obj_center(label1);

    lv_obj_t * btn2 = lv_button_create(lv_screen_active());  //按钮2
    lv_obj_add_event_cb(btn2, event_handler2, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2,LV_ALIGN_RIGHT_MID,-80,0);

    lv_obj_t *label2 = lv_label_create(btn2);
    lv_label_set_text(label2, "Next");
    lv_obj_center(label2);

    // text=lv_label_create(lv_screen_active());  //在屏幕上创建标签
    // lv_obj_align(text,LV_ALIGN_TOP_MID,0,0);  //居中标签

    img = lv_image_create(lv_screen_active());  //创建图片对象
    lv_obj_align(img,LV_ALIGN_TOP_MID,0,0);  //设置位置
}
extern lv_obj_t *main1_t;
extern lv_obj_t *main2_t;

lv_obj_t *main_t = NULL;  //主界面
lv_obj_t *main1_t = NULL; //主界面1
lv_obj_t *main2_t = NULL;  //主界面2
void event_handler_1(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);  //获取按钮的事件
    if(code == LV_EVENT_CLICKED) 
    {
        lv_obj_add_flag(main1_t,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(main2_t,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(main_t,LV_OBJ_FLAG_HIDDEN);

        lv_obj_remove_flag(main1_t,LV_OBJ_FLAG_HIDDEN);
    }
}

void event_handler_2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);  //获取按钮的事件
    if(code == LV_EVENT_CLICKED) 
    {
        lv_obj_add_flag(main1_t,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(main2_t,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(main_t,LV_OBJ_FLAG_HIDDEN);

        lv_obj_remove_flag(main_t,LV_OBJ_FLAG_HIDDEN);
    }
}

void event_handler_3(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);  //获取按钮的事件
    if(code == LV_EVENT_CLICKED) 
    {
        lv_obj_add_flag(main1_t,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(main2_t,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(main_t,LV_OBJ_FLAG_HIDDEN);

        lv_obj_remove_flag(main2_t,LV_OBJ_FLAG_HIDDEN);
    }
}

void event_handler_4(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);  //获取按钮的事件
    if(code == LV_EVENT_CLICKED) 
    {
        lv_obj_add_flag(main1_t,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(main2_t,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(main_t,LV_OBJ_FLAG_HIDDEN);

        lv_obj_remove_flag(main1_t,LV_OBJ_FLAG_HIDDEN);
    }
}


//点击按钮切换界面
void aspect()
{
    main_t = lv_obj_create(lv_screen_active());  //主界面
    main1_t = lv_obj_create(lv_screen_active()); //界面1
    main2_t = lv_obj_create(lv_screen_active());  //界面2

    //设置界面大小
    lv_obj_set_size(main_t,800,480);  
    lv_obj_set_size(main1_t,800,480);
    lv_obj_set_size(main2_t,800,480);

    //设置界面内容
    lv_obj_t *label_1=lv_label_create(main_t);
    lv_label_set_text(label_1,"main");
    lv_obj_center(label_1);
    lv_obj_t *label_2=lv_label_create(main1_t);
    lv_label_set_text(label_2,"main2");
    lv_obj_center(label_2);
    lv_obj_t *label_3=lv_label_create(main2_t);
    lv_label_set_text(label_3,"main3");
    lv_obj_center(label_3);

    //隐藏界面1，2
    lv_obj_add_flag(main1_t,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(main2_t,LV_OBJ_FLAG_HIDDEN);

    lv_obj_t *btn1 = lv_button_create(main_t);  //主界面按钮
    lv_obj_t *btn2 = lv_button_create(main1_t);  //主界面1按钮
    lv_obj_t *btn22 = lv_button_create(main1_t);  //主界面1按钮
    lv_obj_t *btn3 = lv_button_create(main2_t);  //主界面2按钮

    //设置按钮位置
    lv_obj_align(btn1,LV_ALIGN_BOTTOM_RIGHT,0,0); 
    lv_obj_align(btn2,LV_ALIGN_BOTTOM_LEFT,0,0); 
    lv_obj_align(btn22,LV_ALIGN_BOTTOM_RIGHT,0,0); 
    lv_obj_align(btn3,LV_ALIGN_BOTTOM_LEFT,0,0);

    //设置按钮标签名
    lv_obj_t *label1 = lv_label_create(btn1);
    lv_obj_center(label1);
    lv_label_set_text(label1,"NEXT");

    lv_obj_t *label2 = lv_label_create(btn2);
    lv_obj_center(label2);
    lv_label_set_text(label2,"LAST");

    lv_obj_t *label3 = lv_label_create(btn22);
    lv_obj_center(label3);
    lv_label_set_text(label3,"NEXT");

    lv_obj_t *label4 = lv_label_create(btn3);
    lv_obj_center(label4);
    lv_label_set_text(label4,"LAST");

    //设置按钮点击事件
    lv_obj_add_event_cb(btn1, event_handler_1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(btn2, event_handler_2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(btn22, event_handler_3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(btn3, event_handler_4, LV_EVENT_ALL, NULL);
}

//图层的切换
void update_img()
{
    lv_obj_t * img1 = lv_image_create(lv_screen_active());
    lv_image_set_src(img1, "A:/home/dragon/jj.bmp");
    lv_obj_center(img1);

    lv_obj_t * img2 = lv_image_create(lv_screen_active());
    lv_image_set_src(img2, "A:/home/dragon/jj1.bmp");
    lv_obj_align(img2, LV_ALIGN_CENTER, -50, -50);

    lv_obj_t * img3 = lv_image_create(lv_screen_active());
    lv_image_set_src(img3, "A:/home/dragon/jj2.bmp");
    lv_obj_align(img3, LV_ALIGN_CENTER, 50, 50);

    lv_obj_move_foreground(img1);  
}

//全局变量
lv_obj_t *ta1=NULL;
lv_obj_t *ta2=NULL;
//用户信息
typedef struct user{
    char Account[50];
    char Password[50];
}user;

//用户列表
user userlist[50];

//用户数
int num=0;

//文本点击事件
static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta =lv_event_get_target(e);
    lv_obj_t *kb=lv_event_get_user_data(e);
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

//账号已经存在线程
void *msg_task(void *arg)
{
    char *msg=arg;  //存储输出信息
    lv_obj_t *info=lv_obj_create(lv_screen_active());
    lv_obj_t *label=lv_label_create(info);

    lv_obj_set_size(info,200,100);

    lv_obj_center(label);
    lv_obj_center(info);

    lv_label_set_text(label,msg);

    sleep(2);

    lv_obj_delete(info);
    pthread_exit(NULL);
}

void btn1_event_cb(lv_event_t *e)  //登录按钮点击事件
{
    const char *Account = lv_textarea_get_text(ta1);
    const char *Password = lv_textarea_get_text(ta2);
}

void btn2_event_cb(lv_event_t *e)  //注册按钮点击事件
{
    const char *Account = lv_textarea_get_text(ta1);
    const char *Password = lv_textarea_get_text(ta2);
    printf("账号:%s\n",Account);
    printf("密码:%s\n",Password);
    for(int i=0;i<num;i++)
    {
        if(strcmp(userlist[i].Account,Account)==0)
        {
            pthread_t tid;
            pthread_create(&tid,NULL,msg_task,"AccountExists");
            return;
        }
    }
    //添加用户
    strcpy(userlist[num].Account,Account);
    strcpy(userlist[num].Password,Password);
    
    pthread_t tid;
    pthread_create(&tid,NULL,msg_task,"Register Successful");
    num++;
    return;
}
//注册登录
void login_keyboard()
{
    lv_obj_t *kb=lv_keyboard_create(lv_screen_active());  //创建一个键盘用于输入文本

    ta1=lv_textarea_create(lv_screen_active());  //账号输入框
    lv_obj_align(ta1,LV_ALIGN_CENTER,0,-200);  //设置文本位置
    lv_obj_add_event_cb(ta1,ta_event_cb,LV_EVENT_ALL,kb);
    lv_textarea_set_placeholder_text(ta1,"Acount");
    lv_obj_set_size(ta1,400,50);

    ta2=lv_textarea_create(lv_screen_active());  //密码输入框
    lv_obj_align(ta2,LV_ALIGN_CENTER,0,-100);  //设置文本位置
    lv_obj_add_event_cb(ta2,ta_event_cb,LV_EVENT_ALL,kb);
    lv_textarea_set_placeholder_text(ta2,"Password");
    lv_obj_set_size(ta2,400,50);

    lv_obj_add_flag(kb,LV_OBJ_FLAG_HIDDEN);

    //创建两个按钮
    lv_obj_t *btn1=lv_button_create(lv_screen_active()); //登录按钮
    lv_obj_t *btn2=lv_button_create(lv_screen_active()); //注册按钮

    lv_obj_set_size(btn1,70,30);
    lv_obj_set_size(btn2,70,30);

    lv_obj_align(btn1,LV_ALIGN_LEFT_MID,200,0);
    lv_obj_align(btn2,LV_ALIGN_RIGHT_MID,-200,0);

    lv_obj_t *label1=lv_label_create(btn1);
    lv_obj_t *label2=lv_label_create(btn2);

    lv_label_set_text(label1,"login");
    lv_label_set_text(label2,"register");

    lv_obj_center(label1);
    lv_obj_center(label2);

    lv_obj_add_event_cb(btn1,btn1_event_cb,LV_EVENT_CLICKED,kb);  //设置按钮点击事件
    lv_obj_add_event_cb(btn2,btn2_event_cb,LV_EVENT_CLICKED,kb);
}

    // mydream();  //测试中文显示
    // lv_demo_widgets();  //官方示例
    // login_keyboard();  //登录界面
    // update_img();  //鸡哥图片图层
    // aspect();  //切换界面
    // create_screen(); //9个对象
    // diswin();  //图片切换
    /*Create a Demo*/
    //lv_example_button_1();
    // lv_demo_widgets();
    // lv_demo_widgets_start_slideshow();
    //  lv_example_ime_pinyin_2();