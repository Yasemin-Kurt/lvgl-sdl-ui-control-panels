#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "images/relay_off.h"
#include "images/home.h"
#include "images/lightning.h"
#include "images/brigthness.h"
#include "images/sound_on.h"
#include "images/arayuz.h"

/* Global objeler */
lv_obj_t *ekran_label = NULL;
lv_obj_t *ekran_img = NULL;

/* Sol panel verileri */
const char *group1_texts[] = {
    "  OPERATOR\n   KONSOLU", "SES ANH\n MATRISI",
    "  IC KONUSMA\nUZAK KOMUTA"
};
const uint8_t *group1_imgs[] = {
    relay_off, relay_off, relay_off
};

const char *group2_texts[] = {
    "KESTIRME\n ALMACI","  KESTIRME\nANTEN ANH"
};
const uint8_t *group2_imgs[] = {
    relay_off, relay_off
};

const char *group3_texts[] = {
    "  YEDEK\n   DC-1",  "  YEDEK\n   DC-2"
};
const uint8_t *group3_imgs[] = {
    relay_off, relay_off
};

struct row_group left_groups[] = {
    { group1_texts, group1_imgs, sizeof(group1_texts)/sizeof(group1_texts[0]), 1 },
    { group2_texts, group2_imgs, sizeof(group2_texts)/sizeof(group2_texts[0]), 1 },
    { group3_texts, group3_imgs, sizeof(group3_texts)/sizeof(group3_texts[0]), 1 }
};
const int left_groups_count = sizeof(left_groups)/sizeof(left_groups[0]);

/* Sağ panel butonları */
struct sag_btn sag_buttons[] = {
    {"    GUC CIKIS\n   DURUMLARI \n          (3/4)", lightning, 650, 10},
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

/* Sol panel butonlarını oluştur */
void create_left_panel_groups(lv_obj_t *parent,
                              struct row_group groups[],
                              int group_count,
                              int start_y,
                              int btn_w,
                              int btn_h,
                              int gap,
                              int screen_right_limit) {

    int y = start_y;

    static lv_style_t shadow_style;
    lv_style_init(&shadow_style);
    lv_style_set_shadow_width(&shadow_style, 15);
    lv_style_set_shadow_color(&shadow_style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_shadow_ofs_x(&shadow_style, 2);
    lv_style_set_shadow_ofs_y(&shadow_style, 2);

    static lv_style_t row_bg_style;
    lv_style_init(&row_bg_style);
    lv_style_set_bg_color(&row_bg_style, lv_color_make(25, 35, 55));
    lv_style_set_radius(&row_bg_style, 10);

    /* Büyük buton üstü başlıklar */
    const char *top_labels[] = {
        "KONSOL VE KONUSMA BIRIMLERI",  // 1. büyük buton
        "KESTIRME BIRIMLERI",           // 2. büyük buton
        ""                               // 3. büyük buton boş
    };

    for (int g = 0; g < group_count; g++) {
        int per_row = ceil((double)groups[g].total_count / groups[g].row_count);
        int assigned = 0;

        for (int r = 0; r < groups[g].row_count; r++) {
            int remaining = groups[g].total_count - assigned;
            int count_this_row = per_row < remaining ? per_row : remaining;
            int total_width = count_this_row * btn_w + (count_this_row - 1) * gap;
            int x = (screen_right_limit - total_width) / 2;

            /* Satırın arkaplan butonu */
            lv_obj_t *row_bg = lv_btn_create(parent);
            lv_obj_set_size(row_bg, total_width + 50, btn_h + 25);
            lv_obj_align(row_bg, LV_ALIGN_TOP_LEFT, x - 25, y - 20);
            lv_obj_add_style(row_bg, &row_bg_style, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(row_bg, LV_OBJ_FLAG_CLICKABLE);

            /* Büyük buton üstü label ekle (row_bg üzerine) */
            if (top_labels[g][0] != '\0') {
                lv_obj_t *top_label = lv_label_create(row_bg);
                lv_label_set_text(top_label, top_labels[g]);
                lv_obj_align(top_label, LV_ALIGN_TOP_MID, 0, -8); // üst ortalanmış
            }

            /* Küçük butonlar */
            for (int i = 0; i < count_this_row; i++) {
                lv_obj_t *btn = lv_btn_create(parent);
                lv_obj_set_size(btn, btn_w, btn_h);
                lv_obj_align(btn, LV_ALIGN_TOP_LEFT, x, y + 1);
                lv_obj_set_style_bg_color(btn, lv_color_make(35, 45, 63), 0);
                lv_obj_add_style(btn, &shadow_style, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

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
                             40, 110, 110, 40, 650);

    /* Sağ panel stilleri */
    static lv_style_t shadow_right;
    lv_style_init(&shadow_right);
    lv_style_set_shadow_width(&shadow_right, 25);
    lv_style_set_shadow_color(&shadow_right, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_shadow_ofs_x(&shadow_right, 2);
    lv_style_set_shadow_ofs_y(&shadow_right, 2);

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
