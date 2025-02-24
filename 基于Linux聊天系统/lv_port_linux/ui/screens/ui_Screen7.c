#include "../ui.h"

//天气界面
void ui_Screen7_screen_init(P_Cli p_cli)
{
    ui_Screen7 = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Screen6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t *ui_Image3 = lv_image_create(ui_Screen7);
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);   /// 800
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);    /// 480
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image20 = lv_image_create(ui_Screen7);
    lv_image_set_src(ui_Image20, &ui_img_1636180821);
    lv_obj_set_width(ui_Image20, LV_SIZE_CONTENT);   /// 50
    lv_obj_set_height(ui_Image20, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Image20, 379);
    lv_obj_set_y(ui_Image20, -221);
    lv_obj_set_align(ui_Image20, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image20, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_Image20, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_Image20,exit_to_main_w,LV_EVENT_CLICKED, p_cli);
    lv_obj_add_flag(ui_Image20,LV_OBJ_FLAG_HIDDEN);
    // textarea_w=lv_textarea_create(ui_Screen7);  //消息输入框
    // lv_obj_set_size(textarea_w,300,50);
    // lv_obj_align(textarea_w,LV_ALIGN_TOP_MID,-50,0);
    // lv_textarea_placeholder_set_chinese(textarea_w,"城市:");

    // send_button_w=lv_button_create(ui_Screen7);  //发送按钮
    // lv_obj_set_size(send_button_w,80,50);
    // lv_obj_align_to(send_button_w,textarea_w,LV_ALIGN_OUT_RIGHT_TOP,0,0);
    // lv_obj_t *send_label=lv_label_create(send_button_w);
    // lv_label_set_chinese(send_label,"发送");
    // lv_obj_add_event_cb(send_button_w,send_city_event,LV_EVENT_CLICKED, p_cli);

    // ui_Keyboard5 = lv_keyboard_create(ui_Screen7);
    // lv_obj_set_width(ui_Keyboard5, 806);
    // lv_obj_set_height(ui_Keyboard5, 218);
    // lv_obj_set_x(ui_Keyboard5, 2);
    // lv_obj_set_y(ui_Keyboard5, 134);
    // lv_obj_set_align(ui_Keyboard5, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Keyboard5,LV_OBJ_FLAG_HIDDEN);
    // lv_obj_add_event_cb(textarea_w,text_event5, LV_EVENT_ALL, ui_Keyboard5);

    lv_obj_add_flag(ui_Screen7,LV_OBJ_FLAG_HIDDEN); //隐藏天气界面 
}