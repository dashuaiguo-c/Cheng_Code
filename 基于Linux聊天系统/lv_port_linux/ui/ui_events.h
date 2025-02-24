#ifndef _UI_EVENTS_H
#define _UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void login_event(lv_event_t * e);
void register_event(lv_event_t * e);
// void keyboard_event(lv_event_t * e);
void text_event1(lv_event_t * e);
void text_event2(lv_event_t * e);
void text_event3(lv_event_t * e);
void text_event4(lv_event_t * e);
// void text_event5(lv_event_t * e);
void save_usr_event(lv_event_t * e);
void reset_event(lv_event_t * e);
void return_login_event(lv_event_t * e);
void chat_event(lv_event_t * e);
void weather_event(lv_event_t * e);
void exit_event(lv_event_t * e);
void all_chat_event(lv_event_t * e);
void exit_to_main(lv_event_t * e);
void exit_to_mains(lv_event_t * e);
void exit_to_main_w(lv_event_t * e);
void private_chat_event(lv_event_t * e);  //私聊点击事件
void exit_private_event(lv_event_t * e);  //退出私聊功能
void snd_btn_all(lv_event_t * e);
void send_msg_event(lv_event_t * e);
void reset_online_event(lv_event_t * e);
// void send_city_event(lv_event_t * e);

#ifdef __cplusplus

} /*extern "C"*/
#endif

#endif
