#include "../ui.h"

//初始化字库20字体
void Init_Freetype()
{
    /*Create a font*/
    //"/home/dragon/simkai.ttf"  //pc路径
    //"/cheng/simkai.ttf" //开发板路径
    lv_font_t * font = lv_freetype_font_create("/cheng/simkai.ttf",
                                               LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                               20,
                                               LV_FREETYPE_FONT_STYLE_NORMAL);
    if(!font) {
        LV_LOG_ERROR("freetype font create failed.");
        return;
    }
    /*Create style with the new font*/
    // static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, font);
}

//初始化字库48字体
void Init_Freetype1()
{
    lv_font_t * font = lv_freetype_font_create("/cheng/simkai.ttf",
                                               LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                               48,
                                               LV_FREETYPE_FONT_STYLE_NORMAL);
    if(!font) {
        LV_LOG_ERROR("freetype font create failed.");
        return;
    }
    /*Create style with the new font*/
    // static lv_style_t style;
    lv_style_init(&styles);
    lv_style_set_text_font(&styles, font);
    lv_style_set_text_align(&styles, LV_TEXT_ALIGN_CENTER);
}

//初始化字库16字体
void Init_Freetype2()
{
    lv_font_t * font = lv_freetype_font_create("/cheng/simkai.ttf",
                                               LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                               16,
                                               LV_FREETYPE_FONT_STYLE_NORMAL);
    if(!font) {
        LV_LOG_ERROR("freetype font create failed.");
        return;
    }
    /*Create style with the new font*/
    // static lv_style_t style;
    lv_style_init(&styless);
    lv_style_set_text_font(&styless, font);
    lv_style_set_text_align(&styless, LV_TEXT_ALIGN_CENTER);
}

//label标签使用简体中文
void lv_label_set_chinese(lv_label_t *label,char *data)
{
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label,data);
}

//textarea标签使用简体中文
void lv_textarea_placeholder_set_chinese(lv_textarea_t *textarea,char *data)
{
    lv_obj_add_style(textarea, &style, 0);
    lv_textarea_set_placeholder_text(textarea,data);
}

//list_button标签使用简体中文
lv_button_t * lv_list_add_button_chinese(lv_obj_t *list,char *data)
{
    lv_obj_add_style(list, &style, 0);
    lv_button_t *btn=lv_list_add_button(list,NULL,data);
    return btn;
}

//list标签使用简体中文
void lv_list_add_chinese(lv_obj_t *list,char *data)
{
    lv_obj_add_style(list, &style, 0);
    lv_list_add_text(list,data);
}

//win标签使用简体中文
void lv_win_add_chinese(lv_obj_t *win,char *data)
{
    lv_obj_add_style(win, &style, 0);
    lv_win_add_title(win,data);
}

//tabview标签使用简体中文
void lv_tabview_add_tab_chinese(lv_obj_t *ui_TabView,char *data)
{
    lv_obj_add_style(ui_TabView, &style, 0);
    lv_tabview_add_tab(ui_TabView,data);
}

//label标签使用48字体简体中文
void lv_label_set_big_chinese(lv_label_t *label,char *data)
{
    lv_obj_add_style(label, &styles, 0);
    lv_label_set_text(label,data);
}


//label标签使用16字体简体中文
void lv_label_set_small_chinese(lv_label_t *list,char *data)
{
    lv_obj_add_style(list, &styless, 0);
    lv_list_add_text(list,data);
}