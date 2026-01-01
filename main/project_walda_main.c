/*
 * Author: Ernst Sikora
 *
 * Created on: December 26, 2025
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_random.h"
#include "driver/gpio.h"

#include "bsp/esp32_p4_wifi6_touch_lcd_7b.h"
#include "lvgl.h"
#include "iot_button.h"
#include "button_gpio.h"

#include "fonts/lv_font_dejavu_16_german.c"
#include "fonts/lv_font_dejavu_18_german.c"
#include "fonts/lv_font_dejavu_20_german.c"
#include "fonts/lv_font_dejavu_24_german.c"

#include "quiz_data.h"  // Contains quiz question data

// Define colors manually
#define LV_COLOR_RED     lv_color_make(0xFF, 0x00, 0x00)
#define LV_COLOR_GREEN   lv_color_make(0x00, 0xFF, 0x00)
#define LV_COLOR_BLUE    lv_color_make(0x00, 0x00, 0xFF)
#define LV_COLOR_WHITE   lv_color_make(0xFF, 0xFF, 0xFF)
#define LV_COLOR_BLACK   lv_color_make(0x00, 0x00, 0x00)
#define LV_COLOR_GRAY    lv_color_make(0x80, 0x80, 0x80)
#define LV_COLOR_YELLOW  lv_color_make(0xFF, 0xFF, 0x00)
#define LV_COLOR_ORANGE  lv_color_make(0xFF, 0xA5, 0x00)

// WWTBAM Color Palette
#define WWTBAM_BG            lv_color_make(0x00, 0x00, 0x33)   // deep navy
#define WWTBAM_GOLD          lv_color_make(0xFF, 0xD7, 0x00)   // gold
#define WWTBAM_BLUE          lv_color_make(0x00, 0x33, 0x99)   // bright blue
#define WWTBAM_BLUE_DARK     lv_color_make(0x00, 0x22, 0x66)
#define WWTBAM_BLUE_LIGHT    lv_color_make(0x33, 0x99, 0xFF)   // electric blue
#define WWTBAM_WHITE         lv_color_make(0xFF, 0xFF, 0xFF)
#define WWTBAM_ORANGE_DARK   lv_color_make(0xE6, 0x80, 0x00)
#define WWTBAM_GREEN_DARK    lv_color_make(0x00, 0x66, 0x00)   // deeper green

#define WWTBAM_HIGHLIGHT_BG     lv_color_make(0x44, 0x44, 0xAA)   // glowing blue
#define WWTBAM_HIGHLIGHT_BORDER lv_color_make(0x33, 0x99, 0xFF)   // electric blue

#define UI_BOTTOM_LABELS_OFFSET_Y -10

#define WINNING_SCORE 12


typedef enum {
    QUIZ_STATE_IDLE,
    QUIZ_STATE_START_SCREEN,
    QUIZ_STATE_SHOWING_QUESTION,
    QUIZ_STATE_WAITING_ANSWER,
    QUIZ_STATE_SHOWING_REACTION,
    QUIZ_STATE_WINNER,
    QUIZ_STATE_FAIL,
    QUIZ_STATE_SHUTDOWN_PROMPT
} quiz_state_t;

// === Global quiz state =======================================================

static quiz_state_t quiz_state = QUIZ_STATE_IDLE;
static int score = 0;
static int tries = 0;
static bool used_questions[NUM_QUIZ_QUESTIONS] = {false};
static int current_question_index = -1;
static int timer_remaining = 0;
static char user_answer = 0;
static lv_timer_t *quiz_timer = NULL;
static bool system_shutdown = false;

// === Button information ======================================================

typedef struct {
    int gpio_num;
    lv_color_t color;
    lv_obj_t *btn_obj;       // LVGL button widget
    button_handle_t handle;  // physical button
    bool is_pressed;
} button_info_t;

#define NUM_BUTTONS 3
static button_info_t buttons[NUM_BUTTONS];

// === UI structure: all LVGL objects live here ===============================

typedef struct {
    lv_obj_t *root;                  // main container

    lv_obj_t *title_label;          // used for start/winner/fail/shutdown screens
    lv_obj_t *instructions_label;     // used for start screen instructions
    lv_obj_t *question_label;
    lv_obj_t *answer_labels[3];
    lv_obj_t *countdown_label;
    lv_obj_t *system_message_label;  // used for reactions and system instructions
    lv_obj_t *score_label;

    lv_obj_t *answer_frames[3];
    lv_obj_t *buttons[3];            // LVGL button widgets

    lv_obj_t *score_leds[WINNING_SCORE];  // LED bar segments for score visualization

} quiz_ui_t;

static quiz_ui_t ui = {0};

// === Helper: Difficulty to time ============================================

static int get_timer_duration(char difficulty)
{
    switch (difficulty) {
    case 'L': return 15;
    case 'M': return 30;
    case 'H': return 45;
    default:  return 30;
    }
}

// === Question selection =====================================================

static void init_quiz_logic(void)
{
    score = 0;
    tries = 0;
    memset(used_questions, 0, sizeof(used_questions));
    current_question_index = -1;
    timer_remaining = 0;
    user_answer = 0;

    // No need for srand with esp_random()
}

static int select_random_question(void)
{
    int available = 0;
    for (int i = 0; i < NUM_QUIZ_QUESTIONS; i++) {
        if (!used_questions[i]) available++;
    }

    if (available == 0) return -1;

    int target = esp_random() % available;
    int count = 0;
    for (int i = 0; i < NUM_QUIZ_QUESTIONS; i++) {
        if (!used_questions[i]) {
            if (count == target) {
                used_questions[i] = true;
                return i;
            }
            count++;
        }
    }
    return -1;
}

// === UI creation & update functions (no deletes!) ===========================

static void create_quiz_ui_once(void)
{
    if (ui.root) {
        // Already created
        return;
    }

    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLL_CHAIN_VER);

    // Root container for all quiz elements
    ui.root = lv_obj_create(scr);
    lv_obj_set_size(ui.root, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(ui.root, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_obj_clear_flag(ui.root, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_update_layout(ui.root);

    // Determine screen width for layout calculations
    lv_coord_t screen_width = lv_obj_get_width(ui.root);
    lv_coord_t content_width = lv_obj_get_content_width(ui.root);
    ESP_LOGI("QUIZ", "UI root object width=%d, content width=%d", screen_width, content_width);

    // Central label for start/winner/fail/shutdown screens
    ui.title_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.title_label, &lv_font_dejavu_24_german, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.title_label, WWTBAM_GOLD, LV_PART_MAIN);
    lv_obj_align(ui.title_label, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_add_flag(ui.title_label, LV_OBJ_FLAG_HIDDEN);

    // Instructions label
    ui.instructions_label = lv_label_create(ui.root);
    lv_label_set_long_mode(ui.instructions_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_line_space(ui.instructions_label, 10, LV_PART_MAIN);
    lv_obj_set_width(ui.instructions_label, 700);
    lv_obj_align(ui.instructions_label, LV_ALIGN_TOP_MID, 0, 120);

    lv_obj_set_style_text_font(ui.instructions_label, &lv_font_dejavu_20_german, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.instructions_label, WWTBAM_BLUE_LIGHT, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.instructions_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    lv_obj_add_flag(ui.instructions_label, LV_OBJ_FLAG_HIDDEN);

    // Instructions frame styling
    lv_obj_set_style_bg_color(ui.instructions_label, WWTBAM_BLUE_DARK, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.instructions_label, LV_OPA_80, LV_PART_MAIN);
    lv_obj_set_style_border_color(ui.instructions_label, WWTBAM_WHITE, LV_PART_MAIN);
    lv_obj_set_style_border_width(ui.instructions_label, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.instructions_label, 16, LV_PART_MAIN);
    lv_obj_set_style_pad_all(ui.instructions_label, 20, LV_PART_MAIN);


    // Question box (framed, centered)
    ui.question_label = lv_label_create(ui.root);
    lv_label_set_long_mode(ui.question_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_line_space(ui.question_label, 5, LV_PART_MAIN);
    lv_obj_set_width(ui.question_label, 700);
    lv_obj_align(ui.question_label, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_set_style_text_font(ui.question_label, &lv_font_dejavu_24_german, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.question_label, WWTBAM_GOLD, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.question_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    lv_obj_add_flag(ui.instructions_label, LV_OBJ_FLAG_HIDDEN);

    // Frame styling
    lv_obj_set_style_bg_color(ui.question_label, WWTBAM_BLUE_DARK, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui.question_label, LV_OPA_80, LV_PART_MAIN);
    lv_obj_set_style_border_color(ui.question_label, WWTBAM_GOLD, LV_PART_MAIN);
    lv_obj_set_style_border_width(ui.question_label, 2, LV_PART_MAIN);
    lv_obj_set_style_radius(ui.question_label, 16, LV_PART_MAIN);
    lv_obj_set_style_pad_all(ui.question_label, 20, LV_PART_MAIN);

    // Score label (bottom left)
    ui.score_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.score_label, &lv_font_dejavu_18_german, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.score_label, WWTBAM_GOLD, LV_PART_MAIN);
    lv_obj_align(ui.score_label, LV_ALIGN_BOTTOM_LEFT, 0, UI_BOTTOM_LABELS_OFFSET_Y);

    // Score LED bar (bottom center)
    int led_spacing = 4;
    int led_extent = (content_width + led_spacing) / WINNING_SCORE;
    int led_width = led_extent - led_spacing;  // 2px spacing between LEDs
    int led_height = 10;
    int y_offset = 7;

    for (int i = 0; i < WINNING_SCORE; i++) {
        ui.score_leds[i] = lv_obj_create(ui.root);
        lv_obj_set_size(ui.score_leds[i], led_width, led_height);
        int x_offset = i * led_extent;
        lv_obj_align(ui.score_leds[i], LV_ALIGN_BOTTOM_LEFT, x_offset, y_offset);
        ESP_LOGI("QUIZ", "Created LED %d at x=%d, y=%d, width=%d, height=%d", i, x_offset, y_offset, led_width, led_height);

        // Default: dark/off state
        lv_obj_set_style_bg_color(ui.score_leds[i], WWTBAM_BLUE_DARK, LV_PART_MAIN);
        lv_obj_set_style_border_color(ui.score_leds[i], WWTBAM_BLUE, LV_PART_MAIN);
        lv_obj_set_style_border_width(ui.score_leds[i], 1, LV_PART_MAIN);
        lv_obj_set_style_radius(ui.score_leds[i], 2, LV_PART_MAIN);
    }

    // Countdown label (bottom right)
    ui.countdown_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.countdown_label, &lv_font_dejavu_18_german, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.countdown_label, WWTBAM_GOLD, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui.countdown_label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);
    lv_obj_align(ui.countdown_label, LV_ALIGN_BOTTOM_RIGHT, 0, UI_BOTTOM_LABELS_OFFSET_Y);

    // System message label (bottom center - used for reactions and instructions)
    ui.system_message_label = lv_label_create(ui.root);
    lv_obj_set_style_text_align(ui.system_message_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui.system_message_label, &lv_font_dejavu_18_german, LV_PART_MAIN);
    lv_label_set_long_mode(ui.system_message_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_line_space(ui.system_message_label, 3, LV_PART_MAIN);
    lv_obj_set_width(ui.system_message_label, 600);
    lv_obj_align(ui.system_message_label, LV_ALIGN_BOTTOM_MID, 0, UI_BOTTOM_LABELS_OFFSET_Y);
    lv_obj_add_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);

    // Create LVGL button widgets (3 buttons)
    const int frame_width = 700;
    const int frame_height = 80;
    const int spacing = 20;

    for (int i = 0; i < 3; i++) {

        // Outer frame (button + text)
        ui.answer_frames[i] = lv_obj_create(ui.root);
        lv_obj_set_size(ui.answer_frames[i], frame_width, frame_height);
        lv_obj_align(ui.answer_frames[i], LV_ALIGN_CENTER, 0, (i - 1) * (frame_height + spacing));

        lv_obj_set_style_bg_color(ui.answer_frames[i], WWTBAM_BLUE_DARK, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(ui.answer_frames[i], LV_OPA_80, LV_PART_MAIN);
        lv_obj_set_style_border_color(ui.answer_frames[i], WWTBAM_GOLD, LV_PART_MAIN);
        lv_obj_set_style_border_width(ui.answer_frames[i], 2, LV_PART_MAIN);
        lv_obj_set_style_radius(ui.answer_frames[i], 16, LV_PART_MAIN);
        lv_obj_set_style_pad_all(ui.answer_frames[i], 10, LV_PART_MAIN);

        // BUTTON inside the frame
        ui.buttons[i] = lv_button_create(ui.answer_frames[i]);
        lv_obj_set_size(ui.buttons[i], 120, 60);
        lv_obj_align(ui.buttons[i], LV_ALIGN_LEFT_MID, 0, 0);

        lv_color_t btn_color =
            (i == 0) ? WWTBAM_BLUE :
            (i == 1) ? WWTBAM_GREEN_DARK :
                    LV_COLOR_RED;

        lv_obj_set_style_bg_color(ui.buttons[i], btn_color, LV_PART_MAIN);
        lv_obj_set_style_border_color(ui.buttons[i], WWTBAM_GOLD, LV_PART_MAIN);
        lv_obj_set_style_border_width(ui.buttons[i], 1, LV_PART_MAIN);
        lv_obj_set_style_radius(ui.buttons[i], 12, LV_PART_MAIN);

        // Letter label (A/B/C)
        lv_obj_t *letter = lv_label_create(ui.buttons[i]);
        lv_label_set_text(letter, (i == 0) ? "A" : (i == 1) ? "B" : "C");
        lv_obj_set_style_text_color(letter, WWTBAM_GOLD, LV_PART_MAIN);
        lv_obj_set_style_text_font(letter, &lv_font_dejavu_20_german, LV_PART_MAIN);
        lv_obj_center(letter);

        // Answer text OUTSIDE the button, inside the frame
        ui.answer_labels[i] = lv_label_create(ui.answer_frames[i]);
        lv_obj_set_style_text_color(ui.answer_labels[i], WWTBAM_WHITE, LV_PART_MAIN);
        lv_obj_set_style_text_font(ui.answer_labels[i], &lv_font_dejavu_18_german, LV_PART_MAIN);
        lv_obj_align(ui.answer_labels[i], LV_ALIGN_LEFT_MID, 150, 0);
    }

}

static void highlight_answer_frame(int index)
{
    for (int i = 0; i < 3; i++) {
        if (i == index) {
            // Selected frame
            lv_obj_set_style_bg_color(ui.answer_frames[i], WWTBAM_HIGHLIGHT_BG, LV_PART_MAIN);
            lv_obj_set_style_border_color(ui.answer_frames[i], WWTBAM_HIGHLIGHT_BORDER, LV_PART_MAIN);
            lv_obj_set_style_border_width(ui.answer_frames[i], 5, LV_PART_MAIN);
        } else {
            // Reset others
            lv_obj_set_style_bg_color(ui.answer_frames[i], WWTBAM_BLUE_DARK, LV_PART_MAIN);
            lv_obj_set_style_border_color(ui.answer_frames[i], WWTBAM_GOLD, LV_PART_MAIN);
            lv_obj_set_style_border_width(ui.answer_frames[i], 2, LV_PART_MAIN);
        }
    }
}

static void update_score_display(void)
{
    if (!ui.score_label) return;
    char buf[32];
    snprintf(buf, sizeof(buf), "Punkte: %d", score);
    lv_label_set_text(ui.score_label, buf);

    // Update LED bar
    for (int i = 0; i < WINNING_SCORE; i++) {
        if (ui.score_leds[i]) {
            if (i < score) {
                // Lit: gold color
                lv_obj_set_style_bg_color(ui.score_leds[i], LV_COLOR_GREEN, LV_PART_MAIN);
            } else {
                // Unlit: dark
                lv_obj_set_style_bg_color(ui.score_leds[i], WWTBAM_BLUE_DARK, LV_PART_MAIN);
            }
        } else {
            ESP_LOGW("LED", "LED %d is NULL!", i);
        }
    }
}

static void update_countdown_display(void)
{
    if (!ui.countdown_label) return;
    char buf[32];
    snprintf(buf, sizeof(buf), "Zeit: %d", timer_remaining);
    lv_label_set_text(ui.countdown_label, buf);

    if (timer_remaining <= 0) {
        lv_obj_set_style_text_color(ui.countdown_label, LV_COLOR_RED, LV_PART_MAIN);
        return;
    }

    if (timer_remaining <= 5) {
        lv_obj_set_style_text_color(ui.countdown_label, WWTBAM_ORANGE_DARK, LV_PART_MAIN);
        return;
    }

    lv_obj_set_style_text_color(ui.countdown_label, WWTBAM_GREEN_DARK, LV_PART_MAIN);
}

static void show_question_ui(int q_index)
{
    create_quiz_ui_once();

    lv_obj_set_style_bg_color(ui.root, WWTBAM_BG, LV_PART_MAIN);

    lv_obj_clear_flag(ui.question_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui.score_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui.countdown_label, LV_OBJ_FLAG_HIDDEN);
    ESP_LOGI("LED", "Showing score LEDs");
    for (int i = 0; i < WINNING_SCORE; i++) {
        lv_obj_clear_flag(ui.score_leds[i], LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_add_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.title_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.instructions_label, LV_OBJ_FLAG_HIDDEN);

    highlight_answer_frame(-1);  // reset highlights 

    for (int i = 0; i < 3; i++) {
        lv_obj_clear_flag(ui.answer_frames[i], LV_OBJ_FLAG_HIDDEN);
    }

    lv_label_set_text(ui.question_label, quiz_questions[q_index].question);

    lv_label_set_text(ui.answer_labels[0], quiz_questions[q_index].answer_a);
    lv_label_set_text(ui.answer_labels[1], quiz_questions[q_index].answer_b);
    lv_label_set_text(ui.answer_labels[2], quiz_questions[q_index].answer_c);

    update_score_display();

    timer_remaining = get_timer_duration(quiz_questions[q_index].difficulty);
    update_countdown_display();
}

static void show_reaction_ui(bool correct, const char *custom_message)
{
    if (!ui.system_message_label) return;

    const char *reaction;
    if (custom_message) {
        reaction = custom_message;
    } else {
        reaction = correct ?
                   quiz_questions[current_question_index].correct_reaction :
                   quiz_questions[current_question_index].wrong_reaction;
    }

    lv_label_set_text(ui.system_message_label, reaction);
    lv_obj_set_style_text_color(ui.system_message_label,
                                correct ? LV_COLOR_GREEN : LV_COLOR_RED,
                                LV_PART_MAIN);

    lv_obj_clear_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);
}

static void show_winner_ui(void)
{
    create_quiz_ui_once();

    lv_obj_set_style_bg_color(ui.root, WWTBAM_BG, LV_PART_MAIN);

    // Hide quiz elements
    lv_obj_add_flag(ui.question_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.score_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.countdown_label, LV_OBJ_FLAG_HIDDEN);
    ESP_LOGI("LED", "Hiding score LEDs (winner)");
    for (int i = 0; i < WINNING_SCORE; i++) {
        lv_obj_add_flag(ui.score_leds[i], LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_add_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        lv_obj_add_flag(ui.answer_frames[i], LV_OBJ_FLAG_HIDDEN);
    }

    // Show title label
    lv_obj_clear_flag(ui.title_label, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui.title_label, "Herzlichen Glückwunsch!");

    // Show instructions label with additional info
    lv_obj_clear_flag(ui.instructions_label, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui.instructions_label,
        "Du hast das Quiz gewonnen!\n"
        "Der Code zum Finale lautet:\n\n"
        "7777"
    );
}

static void show_fail_ui(void)
{
    create_quiz_ui_once();

    lv_obj_set_style_bg_color(ui.root, WWTBAM_BG, LV_PART_MAIN);

    // Hide quiz elements
    lv_obj_add_flag(ui.question_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.score_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.countdown_label, LV_OBJ_FLAG_HIDDEN);
    ESP_LOGI("LED", "Hiding score LEDs (fail)");
    for (int i = 0; i < WINNING_SCORE; i++) {
        lv_obj_add_flag(ui.score_leds[i], LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_add_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        lv_obj_add_flag(ui.answer_frames[i], LV_OBJ_FLAG_HIDDEN);
    }

    // Show title label
    lv_obj_clear_flag(ui.title_label, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui.title_label, "Oh nein, du hast leider verloren!");

    // Show instructions label with question
    lv_obj_clear_flag(ui.instructions_label, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui.instructions_label, "Möchtest du es nochmal versuchen?");

    // Show system message with button instructions
    lv_obj_clear_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui.system_message_label, WWTBAM_GOLD, LV_PART_MAIN);
    lv_label_set_text(ui.system_message_label,
        "Betätige die grüne Taste für einen neuen Versuch.\n"
        "Halte die rote Taste gedrückt, um das Spiel zu beenden.");
}

static void show_shutdown_prompt_ui(void)
{
    create_quiz_ui_once();

    // Keep the winner UI background and content
    // Show system message at bottom
    lv_obj_clear_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui.system_message_label, "Drücke eine beliebige Taste, um das Spiel zu beenden.");
    lv_obj_set_style_text_color(ui.system_message_label, WWTBAM_GOLD, LV_PART_MAIN);
}

static void show_start_screen_ui(void)
{
    create_quiz_ui_once();

    lv_obj_set_style_bg_color(ui.root, WWTBAM_BG, LV_PART_MAIN);

    // Hide quiz elements
    lv_obj_add_flag(ui.question_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.score_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.countdown_label, LV_OBJ_FLAG_HIDDEN);
    ESP_LOGI("LED", "Hiding score LEDs (start screen)");
    for (int i = 0; i < WINNING_SCORE; i++) {
        lv_obj_add_flag(ui.score_leds[i], LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_add_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        lv_obj_add_flag(ui.answer_frames[i], LV_OBJ_FLAG_HIDDEN);
    }

    // Show center label with welcome message
    lv_obj_clear_flag(ui.title_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui.system_message_label, WWTBAM_GOLD, LV_PART_MAIN);
    lv_label_set_text(ui.title_label, "Herzlich Willkommen im Quiz-Hotel!");

    // Show instructions label
    lv_obj_clear_flag(ui.instructions_label, LV_OBJ_FLAG_HIDDEN);
    char instructions_buf[512];
    snprintf(instructions_buf, sizeof(instructions_buf),
        "Spielregeln:\n"
        "1. Antworte innerhalb der vorgegebenen Zeit!\n"
        "2. Für eine richtige Antwort bekommst du einen Punkt.\n"
        "3. Für eine falsche Antwort wird ein Punkt abgezogen.\n"
        "4. Die nächste Frage erscheint automatisch.\n"
        "5. Bei %d Punkten erhälst du eine Belohnung.\n"
        "6. Nach höchstens 50 Versuchen ist das Spiel vorbei.",
        WINNING_SCORE
    );
    lv_label_set_text(ui.instructions_label, instructions_buf);

    // Show system message to start
    lv_obj_clear_flag(ui.system_message_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui.system_message_label, WWTBAM_GOLD, LV_PART_MAIN);
    lv_label_set_text(ui.system_message_label, "Betätige eine beliebige Taste, um zu starten.");
}

// === Quiz timer callback (only uses LVGL safely, no deletes) ================

static void quiz_timer_callback(lv_timer_t *timer)
{
    static int second_counter = 0;
    static int winner_counter = 0;
    static int fail_counter = 0;

    second_counter++;

    ESP_LOGV("QUIZ", "Timer callback: state=%d, second_counter=%d", quiz_state, second_counter);

    switch (quiz_state) {
    case QUIZ_STATE_SHOWING_QUESTION: {
        ESP_LOGI("QUIZ", "Timer: SHOWING_QUESTION - selecting question");
        current_question_index = select_random_question();
        if (current_question_index == -1) {
            // All questions used
            if (score >= WINNING_SCORE) {
                ESP_LOGI("QUIZ", "Timer: All questions used, score >= WINNING_SCORE -> WINNER");
                quiz_state = QUIZ_STATE_WINNER;
                winner_counter = 0;
                show_winner_ui();
                lv_timer_set_period(quiz_timer, 100);  // 100 ms for winner timer
            } else {
                ESP_LOGI("QUIZ", "Timer: All questions used, score < WINNING_SCORE -> FAIL");
                quiz_state = QUIZ_STATE_FAIL;
                fail_counter = 0;
                show_fail_ui();
                lv_timer_set_period(quiz_timer, 100);  // 100 ms for fail timer
            }
            second_counter = 0;
            break;
        }

        // Show a new question
        ESP_LOGI("QUIZ", "Timer: Showing question %d, setting state to WAITING_ANSWER", current_question_index);
        show_question_ui(current_question_index);
        quiz_state = QUIZ_STATE_WAITING_ANSWER;
        lv_timer_set_period(quiz_timer, 1000); // 1 second for countdown
        second_counter = 0;
        break;
    }

    case QUIZ_STATE_WAITING_ANSWER:
        if (second_counter >= 1) {
            timer_remaining--;
            update_countdown_display();
            second_counter = 0;

            if (timer_remaining <= 0) {
                // Time's up
                ESP_LOGI("QUIZ", "Timer: Time's up in WAITING_ANSWER - setting state to SHOWING_REACTION");
                quiz_state = QUIZ_STATE_SHOWING_REACTION;
                bool correct = false;
                if (score > 0) score--;
                tries++;
                update_score_display();
                show_reaction_ui(correct, "Die Zeit ist leider um!");
                lv_timer_set_period(quiz_timer, 2000); // show reaction 2 sec
                second_counter = 0;
            }
        }
        break;

    case QUIZ_STATE_SHOWING_REACTION:
        if (second_counter >= 2) {
            if (score >= WINNING_SCORE) {
                ESP_LOGI("QUIZ", "Timer: Reaction shown, score >= WINNING_SCORE -> WINNER");
                quiz_state = QUIZ_STATE_WINNER;
                winner_counter = 0;
                show_winner_ui();
                lv_timer_set_period(quiz_timer, 100);
            } else if (tries >= 50) {
                ESP_LOGI("QUIZ", "Timer: Reaction shown, tries >= 50 - FAIL");
                quiz_state = QUIZ_STATE_FAIL;
                fail_counter = 0;
                show_fail_ui();
                lv_timer_set_period(quiz_timer, 100);
            } else {
                ESP_LOGI("QUIZ", "Timer: Reaction shown, continuing to next question");
                quiz_state = QUIZ_STATE_SHOWING_QUESTION;
                lv_timer_set_period(quiz_timer, 100);
            }
            second_counter = 0;
        }
        break;

    case QUIZ_STATE_WINNER:
        winner_counter++;
        if (winner_counter >= 150) {  // 15 seconds
            ESP_LOGI("QUIZ", "Timer: Winner timeout - SHUTDOWN_PROMPT");
            quiz_state = QUIZ_STATE_SHUTDOWN_PROMPT;
            show_shutdown_prompt_ui();
            winner_counter = 0;
        }
        break;

    case QUIZ_STATE_FAIL:
        fail_counter++;
        if (fail_counter >= 50) {  // 5 seconds
            // Refresh fail screen occasionally (optional)
            show_fail_ui();
            fail_counter = 0;
        }
        break;

    case QUIZ_STATE_SHUTDOWN_PROMPT:
    case QUIZ_STATE_START_SCREEN:
    case QUIZ_STATE_IDLE:
    default:
        // nothing
        break;
    }
}

// === Answer handling in LVGL context via lv_async_call =======================

static void handle_answer_async(void *user_data)
{
    int btn_index = (int)user_data;

    ESP_LOGI("QUIZ", "handle_answer_async: Processing answer for button %d", btn_index);

    if (quiz_state != QUIZ_STATE_WAITING_ANSWER) {
        ESP_LOGW("QUIZ", "handle_answer_async: State is not WAITING_ANSWER (current: %d), ignoring", quiz_state);
        return;
    }

    user_answer = 'A' + btn_index;
    ESP_LOGI("QUIZ", "handle_answer_async: User selected answer %c", user_answer);
    highlight_answer_frame(btn_index);

    bool correct = (user_answer == quiz_questions[current_question_index].correct);
    ESP_LOGI("QUIZ", "handle_answer_async: Answer is %s (correct: %c)", correct ? "CORRECT" : "WRONG", quiz_questions[current_question_index].correct);
    if (correct) {
        score++;
    } else {
        if (score > 0) score--;
    }
    tries++;
    update_score_display();

    ESP_LOGI("QUIZ", "handle_answer_async: Setting state to SHOWING_REACTION");
    quiz_state = QUIZ_STATE_SHOWING_REACTION;
    show_reaction_ui(correct, NULL);
    lv_timer_set_period(quiz_timer, 3000); // 3 seconds reaction
}

// === Shutdown or restart from LVGL context ==================================

static void handle_start_quiz_async(void *user_data)
{
    (void)user_data;

    ESP_LOGI("QUIZ", "handle_start_quiz_async: Starting quiz initialization");
    init_quiz_logic();
    ESP_LOGI("QUIZ", "handle_start_quiz_async: Setting state to SHOWING_QUESTION");
    quiz_state = QUIZ_STATE_SHOWING_QUESTION;
    lv_timer_reset(quiz_timer);
    lv_timer_set_period(quiz_timer, 100);
    ESP_LOGI("QUIZ", "handle_start_quiz_async: Timer reset and period set");
}

static void handle_restart_async(void *user_data)
{
    (void)user_data;

    init_quiz_logic();
    quiz_state = QUIZ_STATE_SHOWING_QUESTION;
    lv_timer_reset(quiz_timer);
    lv_timer_set_period(quiz_timer, 100);
}

static void handle_shutdown_async(void *user_data)
{
    (void)user_data;
    
    ESP_LOGI("QUIZ", "Initiating low-power shutdown...");
    
    // Turn off LCD backlight
    bsp_display_backlight_off();
    
    // Stop and delete the quiz timer to save power
    if (quiz_timer) {
        lv_timer_del(quiz_timer);
        quiz_timer = NULL;
    }
    
    // Delete button handles to free resources and reduce power
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (buttons[i].handle) {
            iot_button_delete(buttons[i].handle);
            buttons[i].handle = NULL;
        }
    }
    
    // Configure button GPIOs for low power (input with pull-down)
    for (int i = 0; i < NUM_BUTTONS; i++) {
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << buttons[i].gpio_num),
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_ENABLE,
            .intr_type = GPIO_INTR_DISABLE
        };
        gpio_config(&io_conf);
    }
    
    // Set shutdown flag to stop processing and button reactions
    system_shutdown = true;
    
    ESP_LOGI("QUIZ", "System shutdown complete - entering low power mode");
}

// === Button event callback (no direct LVGL calls, only lv_async_call) ========

static void button_event_cb(void *arg, void *data)
{
    // Ignore all button events when system is shutdown
    if (system_shutdown) {
        return;
    }
    
    button_handle_t btn_handle = (button_handle_t)arg;
    button_event_t event = iot_button_get_event(btn_handle);

    int btn_index = -1;
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (buttons[i].handle == btn_handle) {
            btn_index = i;
            break;
        }
    }

    if (btn_index == -1) {
        ESP_LOGE("BUTTON", "Unknown button handle");
        return;
    }

    ESP_LOGI("BUTTON", "Button %d event: %s (current quiz_state: %d)",
             btn_index, iot_button_get_event_str(event), quiz_state);

    const char *color_names[] = {"BLUE", "GREEN", "RED"};
    ESP_LOGI("BUTTON", "%s button event: %s",
             color_names[btn_index], iot_button_get_event_str(event));

    if (BUTTON_PRESS_REPEAT == event || BUTTON_PRESS_REPEAT_DONE == event) {
        ESP_LOGI("BUTTON", "\tREPEAT[%d]", iot_button_get_repeat(btn_handle));
    }

    if (BUTTON_PRESS_UP == event || BUTTON_LONG_PRESS_HOLD == event || BUTTON_LONG_PRESS_UP == event) {
        ESP_LOGI("BUTTON", "\tPressed Time[%" PRIu32 " ms]", iot_button_get_pressed_time(btn_handle));
    }

    if (BUTTON_MULTIPLE_CLICK == event) {
        ESP_LOGI("BUTTON", "\tMULTIPLE[%d]", (int)data);
    }

    // Visual button state
    if (BUTTON_PRESS_DOWN == event) {
        buttons[btn_index].is_pressed = true;
    } else if (BUTTON_PRESS_UP == event) {
        buttons[btn_index].is_pressed = false;

        // Quiz logic (through async handlers) - only on BUTTON_PRESS_UP
        if (quiz_state == QUIZ_STATE_WAITING_ANSWER) {
            ESP_LOGI("QUIZ", "Button %d pressed in WAITING_ANSWER state - scheduling answer", btn_index);
            lv_async_call(handle_answer_async, (void *)btn_index);
        } else if (quiz_state == QUIZ_STATE_START_SCREEN) {
            // Any button starts the quiz
            ESP_LOGI("QUIZ", "Button %d pressed in START_SCREEN state - scheduling quiz start", btn_index);
            lv_async_call(handle_start_quiz_async, NULL);
        } else if (quiz_state == QUIZ_STATE_SHUTDOWN_PROMPT) {
            // Any button shuts down
            ESP_LOGI("QUIZ", "Button %d pressed in SHUTDOWN_PROMPT state - scheduling shutdown", btn_index);
            lv_async_call(handle_shutdown_async, NULL);
        } else if (quiz_state == QUIZ_STATE_FAIL) {
            if (btn_index == 1) { // Green button - restart
                ESP_LOGI("QUIZ", "Green button pressed in FAIL state - scheduling restart");
                lv_async_call(handle_restart_async, NULL);
            }
            // Removed long press shutdown from PRESS_UP
        }
    } else if (BUTTON_LONG_PRESS_HOLD == event && quiz_state == QUIZ_STATE_FAIL && btn_index == 2) {
        uint32_t pressed_ms = iot_button_get_pressed_time(btn_handle);
        if (pressed_ms >= 2000) {
            ESP_LOGI("QUIZ", "Red button held for >2s in FAIL state - scheduling shutdown");
            lv_async_call(handle_shutdown_async, NULL);
        }
    } else if (BUTTON_PRESS_END == event) {
        // TODO: is this needed, or is BUTTON_PRESS_UP sufficient?

        // BUTTON_PRESS_END is handled separately for visual state only
        ESP_LOGV("BUTTON", "Button %d PRESS_END event - visual state only", btn_index);
        buttons[btn_index].is_pressed = false;
    }
}

// === Start quiz =============================================================

static void start_quiz(void)
{
    init_quiz_logic();
    quiz_state = QUIZ_STATE_START_SCREEN;
    show_start_screen_ui();
    if (!quiz_timer) {
        quiz_timer = lv_timer_create(quiz_timer_callback, 100, NULL);
    } else {
        lv_timer_reset(quiz_timer);
        lv_timer_set_period(quiz_timer, 100);
    }
}

// === app_main ===============================================================

void app_main(void)
{
    // Initialize logical button configurations
    buttons[0] = (button_info_t){ .gpio_num = 2, .color = LV_COLOR_BLUE,  .btn_obj = NULL, .handle = NULL, .is_pressed = false };
    buttons[1] = (button_info_t){ .gpio_num = 3, .color = LV_COLOR_GREEN, .btn_obj = NULL, .handle = NULL, .is_pressed = false };
    buttons[2] = (button_info_t){ .gpio_num = 4, .color = LV_COLOR_RED,   .btn_obj = NULL, .handle = NULL, .is_pressed = false };

    // Initialize display
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
            .buff_dma = true,
            .buff_spiram = false,
            .sw_rotate = false,
        }
    };

    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();

    // Create UI once
    create_quiz_ui_once();

    // Initialize physical buttons
    const button_config_t btn_cfg = {0};
    const char *color_names[] = {"BLUE", "GREEN", "RED"};

    for (int i = 0; i < NUM_BUTTONS; i++) {
        const button_gpio_config_t btn_gpio_cfg = {
            .gpio_num = buttons[i].gpio_num,
            .active_level = 0,  // Active low
        };

        esp_err_t ret = iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &buttons[i].handle);
        if (ret != ESP_OK) {
            ESP_LOGE("BUTTON", "Failed to create %s button device: %s",
                     color_names[i], esp_err_to_name(ret));
        } else {
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_DOWN,       NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_UP,         NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_REPEAT,     NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_REPEAT_DONE,NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_SINGLE_CLICK,     NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_DOUBLE_CLICK,     NULL, button_event_cb, NULL);

            button_event_args_t args = {
                .multiple_clicks.clicks = 3,
                .long_press.press_time = 2000
            };
            iot_button_register_cb(buttons[i].handle, BUTTON_MULTIPLE_CLICK, &args, button_event_cb, (void *)3);

            iot_button_register_cb(buttons[i].handle, BUTTON_LONG_PRESS_START, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_LONG_PRESS_HOLD,  NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_LONG_PRESS_UP,    NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_END,        NULL, button_event_cb, NULL);

            ESP_LOGI("BUTTON", "%s button initialized on GPIO%d",
                     color_names[i], buttons[i].gpio_num);
        }
    }

    ESP_LOGI("QUIZ", "Quiz system initialized. Starting quiz...");
    start_quiz();

    while (!system_shutdown) {
        lv_timer_handler();                 // LVGL processing
        vTaskDelay(pdMS_TO_TICKS(5));       // 5 ms tick
    }
    
    ESP_LOGI("QUIZ", "System shutdown complete - main loop exited");
}
