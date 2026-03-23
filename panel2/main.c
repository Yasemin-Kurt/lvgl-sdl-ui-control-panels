#include "lvgl/lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "images/relay_off.h"
#include "images/brigthness.h"
#include "images/lightning.h"
#include "images/sound_on.h"
#include "images/home.h"
#include <math.h>


/* Prototipler */
static lv_display_t * hal_init(int32_t w, int32_t h);
static void create_main_menu(void);

/* Globaller */
static lv_obj_t * main_screen;

/* Ek özellikler */

/* main */
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


/* Sol paneldeki satır butonları için yapı */
struct row_group {
    const char **texts;       // Buton yazıları
    const lv_img_dsc_t **imgs; // Buton görselleri
    int total_count;          // Toplam buton sayısı
    int row_count;            // Bu gruptaki fiziksel satır sayısı
};

/* Sol panel veri - Grup 1: ilk iki satır bir arada */
const char *group1_texts[] = {
    "  KULLANICI\nBILGISAYARI", "OPERATOR\n     ISITICI",
    "KAMERA", "KLIMA-1",
    "KLIMA-2", "      KGK\n      (GY1)\n(GY2 & GY3)", "SELTER ICI\n     PRIZ","SELTER DIS\n     PRIZ","Extra1"
};

struct { const void *img; } group1_imgs[] = {
    {&relay_off}, {&relay_off}, {&relay_off}, {&relay_off},
    {&relay_off}, {&relay_off}, {&relay_off}, {&relay_off},{&sound_on}
};

/* Grup 2: son iki satır bir arada */
const char *group2_texts[] = {
    "YEDEK AC\n    (3FAZ)","YEDEK AC\n    (1FAZ)", "AYDINLATMA",
    "   AC DC\nCEVIRICI 1", "   AC DC\nCEVIRICI 2", "   AC DC\nCEVIRICI 3"
};

struct { const void *img; } group2_imgs[] = {
    {&relay_off}, {&relay_off}, {&relay_off},
    {NULL}, {NULL}, {NULL}
};

/* Tüm sol panel grupları */
struct row_group left_groups[] = {
    {group1_texts, (const lv_img_dsc_t **)group1_imgs, sizeof(group1_texts)/sizeof(group1_texts[0]), 2},
    {group2_texts, (const lv_img_dsc_t **)group2_imgs, sizeof(group2_texts)/sizeof(group2_texts[0]), 2}
};

/* Fonksiyon: grup mantığıyla sol paneli yerleştir */
static void create_left_panel_groups(lv_obj_t *parent, struct row_group groups[], int group_count, int start_y, int btn_w, int btn_h, int gap, int screen_right_limit) {
    int y = start_y;

    for (int g = 0; g < group_count; g++) {
        int per_row = ceil((double)groups[g].total_count / groups[g].row_count);
        int assigned = 0;

        for (int r = 0; r < groups[g].row_count; r++) {
            int remaining = groups[g].total_count - assigned;
            int count_this_row = per_row < remaining ? per_row : remaining;
            int total_width = count_this_row * btn_w + (count_this_row - 1) * gap;
            int x = (screen_right_limit - total_width) / 2;

            for (int i = 0; i < count_this_row; i++) {
                lv_obj_t *btn = lv_btn_create(parent);
                lv_obj_set_size(btn, btn_w, btn_h);
                lv_obj_align(btn, LV_ALIGN_TOP_LEFT, x, y);
                lv_obj_set_style_bg_color(btn, lv_color_make(35, 45, 63), 0);

                lv_obj_t *label = lv_label_create(btn);
                lv_label_set_text(label, groups[g].texts[assigned + i]);
                lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 5);

                lv_obj_t *img = lv_img_create(btn);
                lv_img_set_src(img, groups[g].imgs[assigned + i]);
                lv_obj_align(img, LV_ALIGN_BOTTOM_MID, 0, 0);

                x += btn_w + gap;
            }
            assigned += count_this_row;
            y += btn_h + gap;
        }
    }
}

/* Sağ panel butonları */
struct {
    const char *text;
    const void *img;
    int x;
    int y;
} sag_buttons[] = {
    {"    GUC CIKIS\n   DURUMLARI \n          (4/4)", &lightning, 650, 10},
    {"   EKRAN\nPARLAKLIGI", &brigthness, 650, 155},
    {"SES", &sound_on, 650, 305},
    {"  ANA \nSAYFA", &home, 650, 450}
};

/* Ana Menü */
static void create_main_menu(void) {
    lv_obj_t *main_screen = lv_scr_act();

    /* Arka plan */
    static lv_style_t bg_style;
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, lv_color_make(39, 40, 41));
    lv_style_set_bg_opa(&bg_style, LV_OPA_COVER);
    lv_obj_add_style(main_screen, &bg_style, 0);

    /* Sol panel (grup mantığıyla) */
    create_left_panel_groups(main_screen, left_groups, sizeof(left_groups)/sizeof(left_groups[0]), 40, 110, 110, 10, 650);

    /* Sağ panel */
    for (int i = 0; i < sizeof(sag_buttons)/sizeof(sag_buttons[0]); i++) {
        lv_obj_t *btn = lv_btn_create(main_screen);
        lv_obj_set_size(btn, 125, 125);
        lv_obj_align(btn, LV_ALIGN_TOP_LEFT, sag_buttons[i].x, sag_buttons[i].y);
        lv_obj_set_style_bg_color(btn, lv_color_make(35, 45, 63), 0);

        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, sag_buttons[i].text);
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 5);

        lv_obj_t *img = lv_img_create(btn);
        lv_img_set_src(img, sag_buttons[i].img);
        lv_obj_align(img, LV_ALIGN_TOP_MID, 0, 0);
    }
}