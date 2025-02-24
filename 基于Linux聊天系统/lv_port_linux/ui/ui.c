#include "ui.h"
#include "ui_helpers.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(P_Cli p_cli);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Image2;
lv_obj_t * ui_Image5;
lv_obj_t * ui_Image6;
lv_obj_t * ui_TextArea1;
lv_obj_t * ui_TextArea2;
void ui_event_Button1(lv_event_t * e);
lv_obj_t * ui_Button1;
void ui_event_Button2(lv_event_t * e);
lv_obj_t * ui_Button2;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Keyboard1;
lv_obj_t * ui____initial_actions0;
lv_style_t style;
lv_style_t styles;
lv_style_t styless;

// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
lv_obj_t * ui_Screen2;
lv_obj_t * ui_Image3;
lv_obj_t * ui_Image4;
lv_obj_t * ui_TextArea3;
lv_obj_t * ui_TextArea4;
void ui_event_Button3(lv_event_t * e);
lv_obj_t * ui_Button3;
void ui_event_Button4(lv_event_t * e);
lv_obj_t * ui_Button4;
lv_obj_t * ui_Image7;
lv_obj_t * ui_Image8;
lv_obj_t * ui_Keyboard2;
lv_obj_t * ui____initial_actions0;
void ui_event_Button5(lv_event_t * e);

// SCREEN: ui_Screen3
void ui_Screen3_screen_init(P_Cli p_cli);
lv_obj_t * ui_Screen3;
lv_obj_t * ui_Image11;
void ui_event_Image15(lv_event_t * e);
lv_obj_t * ui_Image15;
void ui_event_Image17(lv_event_t * e);
lv_obj_t * ui_Image17;
void ui_event_Image19(lv_event_t * e);
lv_obj_t * ui_Image19;
void ui_event_Image21(lv_event_t * e);
lv_obj_t * ui_Image21;
lv_obj_t * ui____initial_actions0;

// SCREEN: ui_Screen4
void ui_Screen4_screen_init(P_Cli p_cli);
lv_obj_t * ui_Screen4;
lv_obj_t * ui_Image13;
lv_obj_t *list;  //在show online中
lv_obj_t * label_win;
lv_timer_t *time1;
lv_obj_t *win;
lv_obj_t *big_win;
lv_obj_t *ui_Keyboard3;
lv_obj_t *textarea1;
lv_obj_t *send_button;
int private_chat_num;
lv_obj_t * ui____initial_actions0;

// SCREEN: ui_Screen5
void ui_Screen5_screen_init(P_Cli p_cli);
lv_obj_t * ui_Screen5;
lv_obj_t * ui_Image14;
lv_obj_t * ui_TextArea5;
lv_obj_t * ui_Button5;
lv_obj_t * ui_Label4;
lv_obj_t * ui_TabView1;
lv_obj_t * ui_Image18;
lv_obj_t * ui_Keyboard4;
lv_obj_t * label_tabview;
lv_obj_t *list_style;
lv_obj_t * ui____initial_actions0;

// SCREEN: ui_Screen6
void ui_Screen6_screen_init(void);
lv_obj_t * ui_Screen6;
lv_obj_t * ui_Image12;
lv_obj_t * ui_Label5;
lv_obj_t * ui____initial_actions0;

// SCREEN: ui_Screen7
void ui_Screen7_screen_init(P_Cli p_cli);
lv_obj_t * ui_Screen7;
lv_obj_t *label_time;
int count_time;
lv_obj_t * ui_Image20;
char data_weather[4096];
lv_obj_t *label_city;
lv_obj_t *label_weather;
lv_obj_t *label_temp;
lv_obj_t *label_wind;
lv_obj_t *img_w;
// lv_obj_t *textarea_w;
// lv_obj_t *send_button_w;
// lv_obj_t *ui_Keyboard5;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////  
//点击事件中转站（浪费编译时间，shit）
void ui_event_Button1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        login_event(e);
    }
}
void ui_event_Button2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        register_event(e);
    }
}
void ui_event_Button3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        save_usr_event(e);
    }
}
void ui_event_Button4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        reset_event(e);
    }
}
void ui_event_Button5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        return_login_event(e);
    }
}
void ui_event_Image15(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        chat_event(e);
    }
}
void ui_event_Image17(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        weather_event(e);
    }
}
void ui_event_Image19(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        exit_event(e);
    }
}
void ui_event_Image21(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        all_chat_event(e);
    }
}
///////////////////// SCREENS ////////////////////

//LVGL UI界面主函数
void ui_init(P_Cli p_cli)
{
    lv_disp_t * dispp = lv_display_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init(p_cli);
    ui_Screen2_screen_init();
    ui_Screen3_screen_init(p_cli);
    ui_Screen4_screen_init(p_cli);
    ui_Screen5_screen_init(p_cli);
    ui_Screen6_screen_init();
    ui_Screen7_screen_init(p_cli);
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);  //加载出登录页面
}
