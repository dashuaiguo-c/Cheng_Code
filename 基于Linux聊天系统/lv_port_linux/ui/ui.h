#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "ui_helpers.h"
#include "ui_events.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "./Tcp_Client/tcp_client.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(P_Cli p_cli);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Image2;
extern lv_obj_t * ui_Image5;
extern lv_obj_t * ui_Image6;
extern lv_obj_t * ui_TextArea1;
extern lv_obj_t * ui_TextArea2;
void ui_event_Button1(lv_event_t * e);
extern lv_obj_t * ui_Button1;
void ui_event_Button2(lv_event_t * e);
extern lv_obj_t * ui_Button2;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Keyboard1;
extern lv_obj_t * ui____initial_actions0;
extern lv_style_t style;
extern lv_style_t styles;
extern lv_style_t styless;
// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
extern lv_obj_t * ui_Screen2;
extern lv_obj_t * ui_Image3;
extern lv_obj_t * ui_Image4;
extern lv_obj_t * ui_TextArea3;
extern lv_obj_t * ui_TextArea4;
void ui_event_Button3(lv_event_t * e);
extern lv_obj_t * ui_Button3;
void ui_event_Button4(lv_event_t * e);
extern lv_obj_t * ui_Button4;
extern lv_obj_t * ui_Image7;
extern lv_obj_t * ui_Image8;
extern lv_obj_t * ui_Keyboard2;
extern lv_obj_t * ui____initial_actions0;
void ui_event_Button5(lv_event_t * e);
// SCREEN: ui_Screen3
void ui_Screen3_screen_init(P_Cli p_cli);
extern lv_obj_t * ui_Screen3;
extern lv_obj_t * ui_Image11;
void ui_event_Image15(lv_event_t * e);
extern lv_obj_t * ui_Image15;
void ui_event_Image17(lv_event_t * e);
extern lv_obj_t * ui_Image17;
void ui_event_Image19(lv_event_t * e);
extern lv_obj_t * ui_Image19;
void ui_event_Image21(lv_event_t * e);
extern lv_obj_t * ui_Image21;
extern lv_obj_t * ui____initial_actions0;
// SCREEN: ui_Screen4
void ui_Screen4_screen_init(P_Cli p_cli);
extern lv_obj_t * ui_Screen4;
extern lv_obj_t * ui_Image13;
extern lv_obj_t *list;
extern lv_obj_t * label_win;
extern lv_timer_t *time1;
extern lv_obj_t *win;
extern lv_obj_t *big_win;
extern lv_obj_t *ui_Keyboard3;
extern lv_obj_t *textarea1;
extern lv_obj_t *send_button;
extern int private_chat_num;
extern lv_obj_t * ui____initial_actions0;
// SCREEN: ui_Screen5
void ui_Screen5_screen_init(P_Cli p_cli);
extern lv_obj_t * ui_Screen5;
extern lv_obj_t * ui_Image14;
extern lv_obj_t * ui_TextArea5;
extern lv_obj_t * ui_Button5;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_TabView1;
extern lv_obj_t * ui_Image18;
extern lv_obj_t * ui_Keyboard4;
extern lv_obj_t * label_tabview;
extern lv_obj_t *list_style;
extern lv_obj_t * ui____initial_actions0;
// SCREEN: ui_Screen6
void ui_Screen6_screen_init(void);
extern lv_obj_t * ui_Screen6;
extern lv_obj_t * ui_Image12;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui____initial_actions0;
// SCREEN: ui_Screen7
void ui_Screen7_screen_init(P_Cli p_cli);
extern lv_obj_t * ui_Screen7;
extern lv_obj_t * ui_Image20;
extern lv_obj_t *label_time;
extern char data_weather[4096];
extern int count_time;
extern lv_obj_t *label_city;
extern lv_obj_t *label_weather;
extern lv_obj_t *label_temp;
extern lv_obj_t *label_wind;
extern lv_obj_t *img_w;
// extern lv_obj_t *textarea_w;
// extern lv_obj_t *send_button_w;
// extern lv_obj_t *ui_Keyboard5;

LV_IMG_DECLARE(ui__temporary_image);
LV_IMG_DECLARE(ui_img_login_png);    // assets/login.png
LV_IMG_DECLARE(ui_img_user_png);    // assets/user.png
LV_IMG_DECLARE(ui_img_459333202);    // assets/密码（关）.png
LV_IMG_DECLARE(ui_img_register_png);    // assets/register.png
LV_IMG_DECLARE(ui_img_main_png);    // assets/main.png
LV_IMG_DECLARE(ui_img_1810374608);    // assets/社交聊天 .png
LV_IMG_DECLARE(ui_img_944254084);    // assets/天气.png
LV_IMG_DECLARE(ui_img_600691551);    // assets/退出.png
LV_IMG_DECLARE(ui_img_private_chat_png);    // assets/chat.png
LV_IMG_DECLARE(ui_img_695783995);    // assets/群聊.png
LV_IMG_DECLARE(ui_img_wukong_png);    // assets/wukong.png
LV_IMG_DECLARE(ui_img_1636180821);    // assets/退出 (1).png
LV_IMG_DECLARE(ui_img_goodbye_png);    // assets/goodbye.png
LV_IMG_DECLARE(ui_img_cloud_png);    // assets/cloud.png
LV_IMG_DECLARE(ui_img_rain_png);    // assets/rain.png
LV_IMG_DECLARE(ui_img_sun_png);    // assets/sun.png


void ui_init(P_Cli p_cli);                                                     //初始化UI(ui_main)
void Init_Freetype();                                                          //初始化字库
void lv_label_set_chinese(lv_label_t *label,char *data);                       //中文标签
void lv_textarea_placeholder_set_chinese(lv_textarea_t *textarea,char *data);  //中文文本框提示
void lv_list_add_chinese(lv_obj_t *list,char *data);                           //中文列表
void lv_win_add_chinese(lv_obj_t *win,char *data);                             //窗口中文
void lv_label_set_big_chinese(lv_label_t *label,char *data);                   //大号中文标签
void lv_label_set_small_chinese(lv_label_t *label,char *data);                 //小号中文标签
void lv_tabview_add_tab_chinese(lv_obj_t *ui_TabView,char *data);              //窗口标签添加中文
int Check_Usr(const char *buf, const char *usr);                               //搜索用户名
int is_empty_or_whitespace(const char *str);                                   //检查空字符
lv_button_t * lv_list_add_button_chinese(lv_obj_t *list,char *data);           //中文按钮
void timer_callback(lv_timer_t * timer);                                       //500ms回调函数
bool Show_Online_style(P_Cli p_cli);                                           //在线用户样式
void *all_chat_chat(void *arg);                                                //聊天线程
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
