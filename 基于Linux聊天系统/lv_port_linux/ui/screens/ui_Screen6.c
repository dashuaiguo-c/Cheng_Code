#include "../ui.h"

//退出界面
void ui_Screen6_screen_init(void)
{
    ui_Screen6 = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Screen6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image12 = lv_image_create(ui_Screen6);
    lv_image_set_src(ui_Image12, &ui_img_goodbye_png);
    lv_obj_set_width(ui_Image12, LV_SIZE_CONTENT);   /// 800
    lv_obj_set_height(ui_Image12, LV_SIZE_CONTENT);    /// 480
    lv_obj_set_align(ui_Image12, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image12, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_remove_flag(ui_Image12, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    // 设置文本颜色为红色
    lv_color_t red = lv_color_hex(0xFF0000);  // 创建红色
    ui_Label5 = lv_label_create(ui_Screen6);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label5, -8);
    lv_obj_set_y(ui_Label5, -16);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_Label5, red, LV_STATE_DEFAULT);
    lv_label_set_big_chinese(ui_Label5, "再见");
    
    lv_obj_add_flag(ui_Screen6,LV_OBJ_FLAG_HIDDEN); //隐藏登录界面
}
