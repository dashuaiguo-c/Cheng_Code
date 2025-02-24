SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_login_png.c
    images/ui_img_user_png.c
    images/ui_img_459333202.c
    ui_temporary_image.c)

add_library(ui ${SOURCES})
