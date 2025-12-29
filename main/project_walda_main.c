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

#include "bsp/esp32_p4_wifi6_touch_lcd_7b.h"
#include "lvgl.h"
#include "iot_button.h"
#include "button_gpio.h"

// Define colors manually
#define LV_COLOR_RED     lv_color_make(0xFF, 0x00, 0x00)
#define LV_COLOR_GREEN   lv_color_make(0x00, 0xFF, 0x00)
#define LV_COLOR_BLUE    lv_color_make(0x00, 0x00, 0xFF)
#define LV_COLOR_WHITE   lv_color_make(0xFF, 0xFF, 0xFF)
#define LV_COLOR_BLACK   lv_color_make(0x00, 0x00, 0x00)
#define LV_COLOR_GRAY    lv_color_make(0x80, 0x80, 0x80)
#define LV_COLOR_YELLOW  lv_color_make(0xFF, 0xFF, 0x00)
#define LV_COLOR_ORANGE  lv_color_make(0xFF, 0xA5, 0x00)

// === Quiz data structures ====================================================

typedef struct {
    const char *question;
    const char *answer_a;
    const char *answer_b;
    const char *answer_c;
    char correct;            // 'A', 'B', 'C'
    char difficulty;         // 'L', 'M', 'H'
    const char *correct_reaction;
    const char *wrong_reaction;
} quiz_question_t;

quiz_question_t quiz_questions[] = {
    {
        "What is the capital of France?",
        "Paris",
        "London",
        "Berlin",
        'A',
        'L',
        "Correct! Paris is the capital of France.",
        "Wrong! The correct answer is Paris."
    },
    {
        "Which planet is known as the Red Planet?",
        "Venus",
        "Mars",
        "Jupiter",
        'B',
        'L',
        "Correct! Mars is the Red Planet.",
        "Wrong! Mars is the Red Planet."
    },
    {
        "What is 2 + 2?",
        "3",
        "4",
        "5",
        'B',
        'L',
        "Correct! 2 + 2 = 4.",
        "Wrong! 2 + 2 = 4."
    },
    {
        "Who wrote 'Romeo and Juliet'?",
        "Charles Dickens",
        "William Shakespeare",
        "Jane Austen",
        'B',
        'M',
        "Correct! William Shakespeare wrote Romeo and Juliet.",
        "Wrong! William Shakespeare wrote Romeo and Juliet."
    },
    {
        "What is the largest ocean on Earth?",
        "Atlantic Ocean",
        "Indian Ocean",
        "Pacific Ocean",
        'C',
        'M',
        "Correct! The Pacific Ocean is the largest.",
        "Wrong! The Pacific Ocean is the largest."
    },
    {
        "In which year did World War II end?",
        "1944",
        "1945",
        "1946",
        'B',
        'M',
        "Correct! World War II ended in 1945.",
        "Wrong! World War II ended in 1945."
    },
    {
        "What is the chemical symbol for gold?",
        "Go",
        "Gd",
        "Au",
        'C',
        'H',
        "Correct! Au is the symbol for gold.",
        "Wrong! Au is the symbol for gold."
    },
    {
        "Which element has atomic number 1?",
        "Helium",
        "Hydrogen",
        "Lithium",
        'B',
        'H',
        "Correct! Hydrogen has atomic number 1.",
        "Wrong! Hydrogen has atomic number 1."
    },
    {
        "What is the square root of 144?",
        "12",
        "14",
        "16",
        'A',
        'H',
        "Correct! The square root of 144 is 12.",
        "Wrong! The square root of 144 is 12."
    },
    {
        "Who painted the Mona Lisa?",
        "Vincent van Gogh",
        "Leonardo da Vinci",
        "Pablo Picasso",
        'B',
        'H',
        "Correct! Leonardo da Vinci painted the Mona Lisa.",
        "Wrong! Leonardo da Vinci painted the Mona Lisa."
    }
};

#define NUM_QUIZ_QUESTIONS (sizeof(quiz_questions) / sizeof(quiz_question_t))

typedef enum {
    QUIZ_STATE_IDLE,
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

    lv_obj_t *question_label;
    lv_obj_t *answer_labels[3];
    lv_obj_t *countdown_label;
    lv_obj_t *reaction_label;
    lv_obj_t *score_label;
    lv_obj_t *fail_instr_label;

    lv_obj_t *buttons[3];            // LVGL button widgets

    lv_obj_t *center_label;          // used for winner/fail/shutdown screens
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

    // random seed
    srand((unsigned)esp_random());
}

static int select_random_question(void)
{
    int available = 0;
    for (int i = 0; i < NUM_QUIZ_QUESTIONS; i++) {
        if (!used_questions[i]) available++;
    }

    if (available == 0) return -1;

    int target = rand() % available;
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

static void update_button_appearance(int btn_index)
{
    if (btn_index < 0 || btn_index >= NUM_BUTTONS) return;
    if (!ui.buttons[btn_index]) return;

    lv_color_t base_color = buttons[btn_index].color;
    lv_color_t pressed_color = buttons[btn_index].is_pressed ?
                               lv_color_darken(base_color, LV_OPA_50) : base_color;

    lv_obj_set_style_bg_color(ui.buttons[btn_index], pressed_color, LV_PART_MAIN);

    if (buttons[btn_index].is_pressed) {
        lv_obj_set_style_shadow_width(ui.buttons[btn_index], 3, LV_PART_MAIN);
        lv_obj_set_style_shadow_color(ui.buttons[btn_index], LV_COLOR_BLACK, LV_PART_MAIN);
        lv_obj_set_style_shadow_opa(ui.buttons[btn_index], LV_OPA_50, LV_PART_MAIN);
    } else {
        lv_obj_set_style_shadow_width(ui.buttons[btn_index], 0, LV_PART_MAIN);
    }
}

static void update_button_appearance_async(void *user_data)
{
    int btn_index = (int)user_data;
    update_button_appearance(btn_index);
}

static void highlight_button(int btn_index, bool highlight)
{
    if (btn_index < 0 || btn_index >= NUM_BUTTONS) return;
    if (!ui.buttons[btn_index]) return;

    if (highlight) {
        lv_obj_set_style_bg_color(ui.buttons[btn_index], LV_COLOR_YELLOW, LV_PART_MAIN);
    } else {
        lv_obj_set_style_bg_color(ui.buttons[btn_index], buttons[btn_index].color, LV_PART_MAIN);
    }
}

static void reset_button_highlights(void)
{
    for (int i = 0; i < NUM_BUTTONS; i++) {
        highlight_button(i, false);
    }
}

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

    // Question label
    ui.question_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.question_label, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.question_label, LV_COLOR_BLACK, LV_PART_MAIN);
    lv_obj_align(ui.question_label, LV_ALIGN_TOP_MID, 0, 20);
    lv_label_set_long_mode(ui.question_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(ui.question_label, 700);

    // Score label (top-left)
    ui.score_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.score_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.score_label, LV_COLOR_BLACK, LV_PART_MAIN);
    lv_obj_align(ui.score_label, LV_ALIGN_TOP_LEFT, 10, 10);

    // Countdown label (bottom middle)
    ui.countdown_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.countdown_label, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.countdown_label, LV_COLOR_RED, LV_PART_MAIN);
    lv_obj_align(ui.countdown_label, LV_ALIGN_BOTTOM_MID, 0, -20);

    // Reaction label (center)
    ui.reaction_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.reaction_label, &lv_font_montserrat_18, LV_PART_MAIN);
    lv_label_set_long_mode(ui.reaction_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(ui.reaction_label, 600);
    lv_obj_align(ui.reaction_label, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_flag(ui.reaction_label, LV_OBJ_FLAG_HIDDEN);

    // Central label for winner/fail/shutdown screens
    ui.center_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.center_label, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.center_label, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_obj_align(ui.center_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(ui.center_label, LV_OBJ_FLAG_HIDDEN);

    // Additional label for fail instructions (only used in FAIL state)
    ui.fail_instr_label = lv_label_create(ui.root);
    lv_obj_set_style_text_font(ui.fail_instr_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui.fail_instr_label, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_obj_align(ui.fail_instr_label, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_flag(ui.fail_instr_label, LV_OBJ_FLAG_HIDDEN);

    // Create LVGL button widgets (3 buttons)
    const int btn_width = 120;
    const int btn_height = 80;
    const int spacing = 40;
    const int start_y = 120;

    lv_coord_t screen_width = lv_display_get_horizontal_resolution(NULL);
    lv_coord_t total_width = (btn_width * NUM_BUTTONS) + (spacing * (NUM_BUTTONS - 1));
    lv_coord_t start_x = (screen_width - total_width) / 2;

    const char *btn_labels[3] = {"A", "B", "C"};

    for (int i = 0; i < NUM_BUTTONS; i++) {
        ui.buttons[i] = lv_button_create(ui.root);
        lv_obj_set_size(ui.buttons[i], btn_width, btn_height);
        lv_obj_set_pos(ui.buttons[i], start_x + i * (btn_width + spacing), start_y);
        lv_obj_set_style_bg_color(ui.buttons[i], buttons[i].color, LV_PART_MAIN);
        lv_obj_set_style_border_color(ui.buttons[i], LV_COLOR_BLACK, LV_PART_MAIN);
        lv_obj_set_style_border_width(ui.buttons[i], 2, LV_PART_MAIN);
        lv_obj_set_style_radius(ui.buttons[i], 10, LV_PART_MAIN);

        // Label "A/B/C" at top
        lv_obj_t *btn_label = lv_label_create(ui.buttons[i]);
        lv_label_set_text(btn_label, btn_labels[i]);
        lv_obj_align(btn_label, LV_ALIGN_TOP_MID, 0, 5);
        lv_obj_set_style_text_color(btn_label, LV_COLOR_WHITE, LV_PART_MAIN);
        lv_obj_set_style_text_font(btn_label, &lv_font_montserrat_12, LV_PART_MAIN);

        // Answer label at bottom
        ui.answer_labels[i] = lv_label_create(ui.buttons[i]);
        lv_obj_align(ui.answer_labels[i], LV_ALIGN_BOTTOM_MID, 0, -5);
        lv_obj_set_style_text_color(ui.answer_labels[i], LV_COLOR_WHITE, LV_PART_MAIN);
        lv_obj_set_style_text_font(ui.answer_labels[i], &lv_font_montserrat_10, LV_PART_MAIN);
    }
}

static void update_score_display(void)
{
    if (!ui.score_label) return;
    char buf[32];
    snprintf(buf, sizeof(buf), "Score: %d", score);
    lv_label_set_text(ui.score_label, buf);
}

static void update_countdown_display(void)
{
    if (!ui.countdown_label) return;
    char buf[32];
    snprintf(buf, sizeof(buf), "Time: %d", timer_remaining);
    lv_label_set_text(ui.countdown_label, buf);
}

static void show_question_ui(int q_index)
{
    create_quiz_ui_once();

    // Background normal
    lv_obj_set_style_bg_color(ui.root, LV_COLOR_WHITE, LV_PART_MAIN);

    // Show quiz elements
    lv_obj_clear_flag(ui.question_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui.score_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui.countdown_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.reaction_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.center_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.fail_instr_label, LV_OBJ_FLAG_HIDDEN);

    for (int i = 0; i < NUM_BUTTONS; i++) {
        lv_obj_clear_flag(ui.buttons[i], LV_OBJ_FLAG_HIDDEN);
    }

    // Set question text
    lv_label_set_text(ui.question_label, quiz_questions[q_index].question);

    // Set answer texts
    lv_label_set_text(ui.answer_labels[0], quiz_questions[q_index].answer_a);
    lv_label_set_text(ui.answer_labels[1], quiz_questions[q_index].answer_b);
    lv_label_set_text(ui.answer_labels[2], quiz_questions[q_index].answer_c);

    reset_button_highlights();
    update_score_display();

    timer_remaining = get_timer_duration(quiz_questions[q_index].difficulty);
    update_countdown_display();
}

static void show_reaction_ui(bool correct)
{
    if (!ui.reaction_label) return;

    const char *reaction = correct ?
                           quiz_questions[current_question_index].correct_reaction :
                           quiz_questions[current_question_index].wrong_reaction;

    lv_label_set_text(ui.reaction_label, reaction);
    lv_obj_set_style_text_color(ui.reaction_label,
                                correct ? LV_COLOR_GREEN : LV_COLOR_RED,
                                LV_PART_MAIN);

    lv_obj_clear_flag(ui.reaction_label, LV_OBJ_FLAG_HIDDEN);
}

static void show_winner_ui(void)
{
    create_quiz_ui_once();

    lv_obj_set_style_bg_color(ui.root, LV_COLOR_GREEN, LV_PART_MAIN);

    // Hide quiz elements
    lv_obj_add_flag(ui.question_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.score_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.countdown_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.reaction_label, LV_OBJ_FLAG_HIDDEN);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        lv_obj_add_flag(ui.buttons[i], LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_add_flag(ui.fail_instr_label, LV_OBJ_FLAG_HIDDEN);

    // Show center label
    lv_obj_clear_flag(ui.center_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui.center_label, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_label_set_text(ui.center_label, "Congratulations!\nYou won the quiz!");
}

static void show_fail_ui(void)
{
    create_quiz_ui_once();

    lv_obj_set_style_bg_color(ui.root, LV_COLOR_RED, LV_PART_MAIN);

    // Hide quiz elements
    lv_obj_add_flag(ui.question_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.score_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.countdown_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.reaction_label, LV_OBJ_FLAG_HIDDEN);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        lv_obj_add_flag(ui.buttons[i], LV_OBJ_FLAG_HIDDEN);
    }

    // Show center + instruction
    lv_obj_clear_flag(ui.center_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui.center_label, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_label_set_text(ui.center_label, "Game Over!\nTry again?");

    lv_obj_clear_flag(ui.fail_instr_label, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui.fail_instr_label, "Green: Restart\nLong Red: Shutdown");
}

static void show_shutdown_prompt_ui(void)
{
    create_quiz_ui_once();

    lv_obj_set_style_bg_color(ui.root, LV_COLOR_ORANGE, LV_PART_MAIN);

    // Hide quiz elements
    lv_obj_add_flag(ui.question_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.score_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.countdown_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui.reaction_label, LV_OBJ_FLAG_HIDDEN);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        lv_obj_add_flag(ui.buttons[i], LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_add_flag(ui.fail_instr_label, LV_OBJ_FLAG_HIDDEN);

    // Show center label
    lv_obj_clear_flag(ui.center_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui.center_label, LV_COLOR_BLACK, LV_PART_MAIN);
    lv_label_set_text(ui.center_label, "Press any button to shutdown");
}

// === Quiz timer callback (only uses LVGL safely, no deletes) ================

static void quiz_timer_callback(lv_timer_t *timer)
{
    static int second_counter = 0;
    static int winner_counter = 0;
    static int fail_counter = 0;

    second_counter++;

    switch (quiz_state) {
    case QUIZ_STATE_SHOWING_QUESTION: {
        current_question_index = select_random_question();
        if (current_question_index == -1) {
            // All questions used
            if (score >= 10) {
                quiz_state = QUIZ_STATE_WINNER;
                winner_counter = 0;
                show_winner_ui();
                lv_timer_set_period(quiz_timer, 100);  // 100 ms for winner timer
            } else {
                quiz_state = QUIZ_STATE_FAIL;
                fail_counter = 0;
                show_fail_ui();
                lv_timer_set_period(quiz_timer, 100);  // 100 ms for fail timer
            }
            second_counter = 0;
            break;
        }

        // Show a new question
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

            if (timer_remaining < 0) {
                // Time's up
                quiz_state = QUIZ_STATE_SHOWING_REACTION;
                bool correct = false;
                if (score > 0) score--;
                tries++;
                update_score_display();
                show_reaction_ui(correct);
                lv_timer_set_period(quiz_timer, 3000); // show reaction 3 sec
                second_counter = 0;
            }
        }
        break;

    case QUIZ_STATE_SHOWING_REACTION:
        if (second_counter >= 3) {
            if (score >= 10) {
                quiz_state = QUIZ_STATE_WINNER;
                winner_counter = 0;
                show_winner_ui();
                lv_timer_set_period(quiz_timer, 100);
            } else if (tries >= 20) {
                quiz_state = QUIZ_STATE_FAIL;
                fail_counter = 0;
                show_fail_ui();
                lv_timer_set_period(quiz_timer, 100);
            } else {
                quiz_state = QUIZ_STATE_SHOWING_QUESTION;
                reset_button_highlights();
                lv_timer_set_period(quiz_timer, 100);
            }
            second_counter = 0;
        }
        break;

    case QUIZ_STATE_WINNER:
        winner_counter++;
        if (winner_counter >= 150) {  // 15 seconds
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

    if (quiz_state != QUIZ_STATE_WAITING_ANSWER) {
        return;
    }

    user_answer = 'A' + btn_index;
    highlight_button(btn_index, true);

    bool correct = (user_answer == quiz_questions[current_question_index].correct);
    if (correct) {
        score++;
    } else {
        if (score > 0) score--;
    }
    tries++;
    update_score_display();

    quiz_state = QUIZ_STATE_SHOWING_REACTION;
    show_reaction_ui(correct);
    lv_timer_set_period(quiz_timer, 3000); // 3 seconds reaction
}

// === Shutdown or restart from LVGL context ==================================

static void handle_restart_async(void *user_data)
{
    (void)user_data;

    init_quiz_logic();
    quiz_state = QUIZ_STATE_SHOWING_QUESTION;
    lv_timer_set_period(quiz_timer, 100);
}

static void handle_shutdown_async(void *user_data)
{
    (void)user_data;
    esp_restart();
}

// === Button event callback (no direct LVGL calls, only lv_async_call) ========

static void button_event_cb(void *arg, void *data)
{
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
        lv_async_call(update_button_appearance_async, (void *)btn_index);
    } else if (BUTTON_PRESS_UP == event || BUTTON_PRESS_END == event) {
        buttons[btn_index].is_pressed = false;
        lv_async_call(update_button_appearance_async, (void *)btn_index);

        // Quiz logic (through async handlers)
        if (quiz_state == QUIZ_STATE_WAITING_ANSWER) {
            lv_async_call(handle_answer_async, (void *)btn_index);
        } else if (quiz_state == QUIZ_STATE_SHUTDOWN_PROMPT) {
            // Any button shuts down
            lv_async_call(handle_shutdown_async, NULL);
        } else if (quiz_state == QUIZ_STATE_FAIL) {
            uint32_t pressed_ms = iot_button_get_pressed_time(btn_handle);
            if (btn_index == 1) { // Green button - restart
                lv_async_call(handle_restart_async, NULL);
            } else if (btn_index == 2 && pressed_ms > 2000) { // Long red press - shutdown
                lv_async_call(handle_shutdown_async, NULL);
            }
        }
    }
}

// === Start quiz =============================================================

static void start_quiz(void)
{
    init_quiz_logic();
    quiz_state = QUIZ_STATE_SHOWING_QUESTION;
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

    while (true) {
        lv_timer_handler();                 // LVGL processing
        vTaskDelay(pdMS_TO_TICKS(5));       // 5 ms tick
    }
}
