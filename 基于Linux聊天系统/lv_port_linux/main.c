#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "./ui/ui.h"

static const char * getenv_default(const char * name, const char * dflt)
{
    return getenv(name) ?: dflt;
}

#if LV_USE_LINUX_FBDEV
static void lv_linux_disp_init(void)
{
    const char * device = getenv_default("LV_LINUX_FBDEV_DEVICE", "/dev/fb0");
    lv_display_t * disp = lv_linux_fbdev_create();

    lv_linux_fbdev_set_file(disp, device);
}
#elif LV_USE_LINUX_DRM
static void lv_linux_disp_init(void)
{
    const char * device = getenv_default("LV_LINUX_DRM_CARD", "/dev/dri/card0");
    lv_display_t * disp = lv_linux_drm_create();

    lv_linux_drm_set_file(disp, device, -1);
}
#elif LV_USE_SDL
static void lv_linux_disp_init(void)
{
    const int width  = atoi(getenv("LV_SDL_VIDEO_WIDTH") ?: "800");
    const int height = atoi(getenv("LV_SDL_VIDEO_HEIGHT") ?: "480");

    lv_sdl_window_create(width, height);
}
#else

#endif

//pc端和开发板切换开关 改完还要再改lv_conf.h和Makefile
#define SDL_INPUT 1
#define LINUX_INPUT 0

int main(int argc,char *argv[]) //输入 ip, port
{
    //初始化
    lv_init();
    lv_linux_disp_init();

    /*Linux display device init*/
#if LINUX_INPUT
    lv_indev_t *ts=lv_evdev_create( LV_INDEV_TYPE_POINTER, "/dev/input/event0");
    // lv_evdev_set_calibration(ts,0, 0, 1024, 600);  //黑色边框的屏幕校准
    lv_evdev_set_calibration(ts,0, 0, 800, 480);  //蓝色边框的屏幕校准
#endif

    //init input device
#if SDL_INPUT
    printf("init input\n");
    lv_sdl_mouse_create();  //鼠标
    lv_sdl_keyboard_create();  //键盘
    lv_sdl_mousewheel_create();  //滚轮
    printf("init input  end\n");
#endif

    if(argc != 3) //ip port
    {
        printf("格式错误\n");
        return -1; 
    }  

    P_Cli p_cli=Client_Init(argv[1],atoi(argv[2]));
    if(NULL==p_cli)
    {
        printf("TCP客户端初始化失败！\n");
        return -1;
    }

    ui_init(p_cli);  //初始化ui
    
    /*Handle LVGL tasks*/  //心跳节拍（0.5s更新一次ui界面）
    while(1) {
        lv_timer_handler();
        usleep(5000);
    }
    return 0;
}
