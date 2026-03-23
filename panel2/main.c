#include "lvgl/lvgl.h"
#include "images/arayuz.h"

/* HAL - SDL simülasyonu */
static lv_display_t * hal_init(int32_t w, int32_t h)
{
    lv_group_set_default(lv_group_create());
    lv_display_t * disp = lv_sdl_window_create(w, h);

    lv_indev_t * mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_indev_set_display(mouse, disp);

    lv_display_set_default(disp);
    return disp;
}

int main(int argc, char **argv)
{
    lv_init();
    hal_init(800, 600);

    create_main_menu();

    while(1) {
        lv_timer_handler();
        lv_tick_inc(5);
    }

    lv_deinit();
    return 0;
}
