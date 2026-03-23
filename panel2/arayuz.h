#ifndef ARAYUZ_H
#define ARAYUZ_H

#include "lvgl.h"

/* Sol paneldeki satır butonları için yapı */
struct row_group {
    const char **texts;
    const uint8_t **imgs; // uint8_t[] tipine uyumlu
    int total_count;
    int row_count;
};

/* Sağ panel butonları için yapı */
struct sag_btn {
    const char *text;
    const uint8_t *img;
    int x;
    int y;
};

/* Sağ paneldeki parlaklık için globale gerek varsa */
extern lv_obj_t *ekran_label;
extern lv_obj_t *ekran_img;

/* Sol ve sağ panel verileri */
extern struct row_group left_groups[];
extern const int left_groups_count;

extern struct sag_btn sag_buttons[];
extern const int sag_buttons_count;

/* ---- Fonksiyon prototipleri ---- */
void create_left_panel_groups(lv_obj_t *parent,
                              struct row_group groups[],
                              int group_count,
                              int start_y,
                              int btn_w,
                              int btn_h,
                              int gap_y,
                              int panel_height);

void create_main_menu(void);
void renk_timer_cb(lv_timer_t *timer);

#endif
