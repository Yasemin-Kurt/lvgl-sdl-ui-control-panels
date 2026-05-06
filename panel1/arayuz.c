#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "images/arayuz.h"
#include "images/relay_off.h"
#include "images/home.h"
#include "images/brigthness.h"
#include "images/lightning.h"
#include "images/sound_on.h"
#include <limits.h> 


/* Global objeler */
lv_obj_t *ekran_label = NULL;
lv_obj_t *ekran_img = NULL;

/* Sol panel verileri */
const char *group1_texts[] = {
    "  A Butonu", "B Butonu",
    "  C Butonu", "D Butonu", "deneme\n butn5"
};
const uint8_t *group1_imgs[] = {
    relay_off, relay_off, relay_off, relay_off, relay_off
};

const char *group2_texts[] = {
    "A Butonu","  B Butonu"
};
const uint8_t *group2_imgs[] = {
    relay_off, relay_off
};

const char *group3_texts[] = {
    "  A Butonu",  "  B Butonu"
};
const uint8_t *group3_imgs[] = {
    relay_off, relay_off
};

struct row_group left_groups[] = {
    { group1_texts, group1_imgs, sizeof(group1_texts)/sizeof(group1_texts[0]), 2 },
    { group2_texts, group2_imgs, sizeof(group2_texts)/sizeof(group2_texts[0]), 1 },
    { group3_texts, group3_imgs, sizeof(group3_texts)/sizeof(group3_texts[0]), 1 }
};
const int left_groups_count = sizeof(left_groups)/sizeof(left_groups[0]);

/* Sağ panel butonları */
struct sag_btn sag_buttons[] = {
    {"CIKIS\n    \n   (3/4)", lightning, 650, 10},
    {"   EKRAN\nPARLAKLIGI", brigthness, 650, 155}, // ekran parlaklığı
    {"SES", sound_on, 650, 305},
    {"  ANA \nSAYFA", home, 650, 450}
};
const int sag_buttons_count = sizeof(sag_buttons)/sizeof(sag_buttons[0]);

/* Timer callback: ekran parlaklığı ve img değişimi */
void renk_timer_cb(lv_timer_t *timer) {
    (void)timer;
    if(ekran_label) lv_obj_set_style_text_color(ekran_label, lv_color_make(255, 50, 50), LV_PART_MAIN | LV_STATE_DEFAULT);
    if(ekran_img) lv_img_set_src(ekran_img, home);

    lv_timer_del(timer); // sadece bir kez çalışacak
}

/* Büyük arkaplan butonu olsun mu? */
int show_row_bg[] = {1, 1, 0};

/* Üst başlık yazısı olsun mu? */
int show_top_label[] = {1, 1, 1};

/* Sol panel butonlarını oluştur */
void create_left_panel_groups(lv_obj_t *parent,
                              struct row_group groups[],
                              int group_count,
                              int start_y,
                              int btn_w,
                              int btn_h,
                              int gap_x,
                              int gap_y,
                              int screen_right_limit) {

    int y = start_y;

    static lv_style_t shadow_style;
    lv_style_init(&shadow_style);
    lv_style_set_shadow_width(&shadow_style, 25);
    lv_style_set_shadow_color(&shadow_style, lv_color_make(0, 0, 0));
    lv_style_set_shadow_ofs_x(&shadow_style, -5);
    lv_style_set_shadow_ofs_y(&shadow_style, 5);

    //switch arkası gölgesi
    static lv_style_t img_green_shadow;
    lv_style_init(&img_green_shadow);
    lv_style_set_shadow_width(&img_green_shadow, 50);
    lv_style_set_shadow_color(&img_green_shadow, lv_color_make(0, 255, 0));  // YEŞİL
    lv_style_set_shadow_ofs_x(&img_green_shadow, 0);
    lv_style_set_shadow_ofs_y(&img_green_shadow, 0);
    lv_style_set_shadow_opa(&img_green_shadow, LV_OPA_60);

    static lv_style_t row_bg_style;
    lv_style_init(&row_bg_style);
    lv_style_set_bg_color(&row_bg_style, lv_color_make(25, 35, 55));
    lv_style_set_radius(&row_bg_style, 10);

    /* Büyük buton üstü başlıklar */
    const char *top_labels[] = {
        "BIRIM 1",  // 1. büyük buton
        "BIRIM 2",           // 2. büyük buton
        ""                               // 3. büyük buton boş
    };

    for (int g = 0; g < group_count; g++) {

    int per_row = ceil((double)groups[g].total_count / groups[g].row_count);
    int assigned = 0;

    /* --- GRUP toplam yüksekliği hesapla (satır sayısına göre) --- */
    int group_total_height = groups[g].row_count * (btn_h + gap_y);

    /* Yatay genişlik hesaplamak için ilk satırı kullanıyoruz */
    int first_row_count = (groups[g].total_count < per_row) ? groups[g].total_count : per_row;
    int first_row_width = first_row_count * btn_w + (first_row_count - 1) * gap_x;

    int bg_x = (screen_right_limit - first_row_width - 40) / 2;  // +40 margin
    int bg_y = y - 20;

    /* --- TEK BÜYÜK GRUP ARKA BUTONU --- */
    lv_obj_t *group_bg = NULL;
    if (show_row_bg[g]) {
        group_bg = lv_btn_create(parent);

        /* Tüm satırları kapsayan yükseklik */
        lv_obj_set_size(group_bg,
                        first_row_width + 40,      // genişlik (her zaman ilk satıra göre)
                        group_total_height +5);  // yükseklik (tüm satırlar)

        lv_obj_align(group_bg, LV_ALIGN_TOP_LEFT, bg_x, bg_y);
        lv_obj_add_style(group_bg, &row_bg_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_clear_flag(group_bg, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_style(group_bg, &shadow_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    /* --- ÜST BAŞLIK --- */
    if (show_top_label[g] && group_bg != NULL && top_labels[g][0] != '\0') {
        lv_obj_t *top_label = lv_label_create(group_bg);
        lv_label_set_text(top_label, top_labels[g]);
        lv_obj_align(top_label, LV_ALIGN_TOP_MID, 0, -8);
    }

    /* --- KÜÇÜK BUTONLARI SIRALARINA YERLEŞTİR --- */
    for (int r = 0; r < groups[g].row_count; r++) {

        int remaining = groups[g].total_count - assigned;
        int count_this_row = per_row < remaining ? per_row : remaining;
        int total_width = count_this_row * btn_w + (count_this_row - 1) * gap_x;

        int x = (screen_right_limit - total_width) / 2;
        int row_y = y + r * (btn_h + gap_y);

        for (int i = 0; i < count_this_row; i++) {

            lv_obj_t *btn = lv_btn_create(parent);
            lv_obj_set_size(btn, btn_w, btn_h);
            lv_obj_align(btn, LV_ALIGN_TOP_LEFT,
                         x + i * (btn_w + gap_x),
                         row_y);

            lv_obj_set_style_bg_color(btn, lv_color_make(35, 45, 63), 0);
            lv_obj_add_style(btn, &shadow_style, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

            lv_obj_t *label = lv_label_create(btn);
            lv_label_set_text(label, groups[g].texts[assigned + i]);
            lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 5);

            /* Image holder */
            lv_obj_t *img_holder = lv_obj_create(btn);
            lv_obj_set_size(img_holder, 33, 33);
            lv_obj_align(img_holder, LV_ALIGN_BOTTOM_MID, 0, -3);

            lv_obj_clear_flag(img_holder, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(img_holder, lv_color_make(35, 45, 63), 0);
            lv_obj_set_style_bg_opa(img_holder, LV_OPA_COVER, 0);
            lv_obj_set_style_border_width(img_holder, 0, 0);
            lv_obj_add_style(img_holder, &img_green_shadow, 0);

            lv_obj_t *img = lv_img_create(img_holder);
            lv_img_set_src(img, groups[g].imgs[assigned + i]);
            lv_obj_center(img);
        }

        assigned += count_this_row;
    }

    /* --- Grup bitti, dikeyde ilerle --- */
    y += group_total_height + 30;
}
}

void create_main_menu(void) {
    lv_obj_t *main_screen = lv_scr_act();

    /* Arka plan */
    static lv_style_t bg_style;
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, lv_color_make(39, 40, 41));
    lv_style_set_bg_opa(&bg_style, LV_OPA_COVER);
    lv_obj_add_style(main_screen, &bg_style, 0);

    /* Sol panel */
    create_left_panel_groups(main_screen,
                             left_groups,
                             left_groups_count,
                             30, 110, 110, 12, 20, 650);

    /* Sağ panel stilleri */
    static lv_style_t shadow_right;
    lv_style_init(&shadow_right);
    lv_style_set_shadow_width(&shadow_right, 40);
    lv_style_set_shadow_color(&shadow_right, lv_color_make(0, 0, 0));
    lv_style_set_shadow_ofs_x(&shadow_right, -5);
    lv_style_set_shadow_ofs_y(&shadow_right, 5);

    static lv_style_t text_white;
    lv_style_init(&text_white);
    lv_style_set_text_color(&text_white, lv_color_white());

    /* Sağ panel butonları */
    for (int i = 0; i < sag_buttons_count; i++) {
        lv_obj_t *btn = lv_btn_create(main_screen);
        lv_obj_set_size(btn, 125, 125);
        lv_obj_align(btn, LV_ALIGN_TOP_LEFT, sag_buttons[i].x, sag_buttons[i].y);
        lv_obj_set_style_bg_color(btn, lv_color_make(35, 45, 63), 0);
        lv_obj_add_style(btn, &shadow_right, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, sag_buttons[i].text);
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 5);

        lv_obj_t *img = lv_img_create(btn);
        lv_img_set_src(img, sag_buttons[i].img);
        lv_obj_align(img, LV_ALIGN_TOP_MID, 0, 0);

        if(i == 1) { // ekran parlaklığı
            ekran_label = label;
            ekran_img = img;
        } else {
            lv_obj_add_style(label, &text_white, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    /* Timer: 5 saniye sonra ekran parlaklığı değişecek */
    lv_timer_create(renk_timer_cb, 5000, NULL);
}
