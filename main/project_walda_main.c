/*
 * Author: Ernst Sikora
 *
 * Created on: December 26, 2025
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"

#include "bsp/esp32_p4_wifi6_touch_lcd_7b.h"
#include "lvgl.h"
#include "iot_button.h"
#include "button_gpio.h"

// Define colors manually
#define LV_COLOR_RED lv_color_make(0xFF, 0x00, 0x00)
#define LV_COLOR_GREEN lv_color_make(0x00, 0xFF, 0x00)
#define LV_COLOR_BLUE lv_color_make(0x00, 0x00, 0xFF)
#define LV_COLOR_WHITE lv_color_make(0xFF, 0xFF, 0xFF)
#define LV_COLOR_BLACK lv_color_make(0x00, 0x00, 0x00) // Define black color
#define LV_COLOR_GRAY lv_color_make(0x80, 0x80, 0x80) // Define gray color for pressed state

// Button information structure
typedef struct {
    int gpio_num;
    lv_color_t color;
    lv_obj_t *btn_obj;
    button_handle_t handle;
    bool is_pressed;
} button_info_t;

// Global button array - initialized at runtime
#define NUM_BUTTONS 3
button_info_t buttons[NUM_BUTTONS];

// Function to update the visual appearance of a button
void update_button_appearance(int btn_index)
{
    if (buttons[btn_index].btn_obj == NULL) return;
    
    lv_color_t base_color = buttons[btn_index].color;
    lv_color_t pressed_color = buttons[btn_index].is_pressed ? 
        lv_color_darken(base_color, LV_OPA_50) : base_color;
    
    // Update button background color
    lv_obj_set_style_bg_color(buttons[btn_index].btn_obj, pressed_color, LV_PART_MAIN);
    
    // Add a slight shadow effect when pressed
    if (buttons[btn_index].is_pressed) {
        lv_obj_set_style_shadow_width(buttons[btn_index].btn_obj, 3, LV_PART_MAIN);
        lv_obj_set_style_shadow_color(buttons[btn_index].btn_obj, LV_COLOR_BLACK, LV_PART_MAIN);
        lv_obj_set_style_shadow_opa(buttons[btn_index].btn_obj, LV_OPA_50, LV_PART_MAIN);
    } else {
        lv_obj_set_style_shadow_width(buttons[btn_index].btn_obj, 0, LV_PART_MAIN);
    }
}

// Function to update the visual appearance of a button (called asynchronously)
void update_button_appearance_async(void *user_data)
{
    int btn_index = (int)user_data;
    if (btn_index < 0 || btn_index >= NUM_BUTTONS) {
        ESP_LOGE("BUTTON", "Invalid button index: %d", btn_index);
        return;
    }
    update_button_appearance(btn_index);
}

// Function to create graphical buttons on screen
void create_graphical_buttons()
{
    lv_obj_t *scr = lv_scr_act();
    
    // Clear screen and set white background
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, LV_COLOR_WHITE, LV_PART_MAIN);
    
    // Button dimensions and spacing
    const int btn_width = 120;
    const int btn_height = 80;
    const int spacing = 40;
    const int start_y = 100;
    
    // Screen center calculation
    lv_coord_t screen_width = lv_display_get_horizontal_resolution(NULL);
    lv_coord_t total_width = (btn_width * NUM_BUTTONS) + (spacing * (NUM_BUTTONS - 1));
    lv_coord_t start_x = (screen_width - total_width) / 2;
    
    const char *labels[] = {"BLUE", "GREEN", "RED"};
    
    for (int i = 0; i < NUM_BUTTONS; i++) {
        // Create button object
        lv_obj_t *btn = lv_button_create(scr);
        buttons[i].btn_obj = btn;
        
        // Set position
        lv_obj_set_pos(btn, start_x + i * (btn_width + spacing), start_y);
        lv_obj_set_size(btn, btn_width, btn_height);
        
        // Set initial appearance
        lv_obj_set_style_bg_color(btn, buttons[i].color, LV_PART_MAIN);
        lv_obj_set_style_border_color(btn, LV_COLOR_BLACK, LV_PART_MAIN);
        lv_obj_set_style_border_width(btn, 2, LV_PART_MAIN);
        lv_obj_set_style_radius(btn, 10, LV_PART_MAIN);
        
        // Create label
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, labels[i]);
        lv_obj_center(label);
        lv_obj_set_style_text_color(label, LV_COLOR_WHITE, LV_PART_MAIN);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_16, LV_PART_MAIN);
        
        // Initial state
        update_button_appearance(i);
    }
}

static void button_event_cb(void *arg, void *data)
{
    button_handle_t btn_handle = (button_handle_t)arg;
    button_event_t event = iot_button_get_event(btn_handle);
    
    // Find which button this is
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
    ESP_LOGI("BUTTON", "%s button event: %s", color_names[btn_index], iot_button_get_event_str(event));

    if (BUTTON_PRESS_REPEAT == event || BUTTON_PRESS_REPEAT_DONE == event) {
        ESP_LOGI("BUTTON", "\tREPEAT[%d]", iot_button_get_repeat(btn_handle));
    }

    if (BUTTON_PRESS_UP == event || BUTTON_LONG_PRESS_HOLD == event || BUTTON_LONG_PRESS_UP == event) {
        ESP_LOGI("BUTTON", "\tPressed Time[%"PRIu32" ms]", iot_button_get_pressed_time(btn_handle));
    }

    if (BUTTON_MULTIPLE_CLICK == event) {
        ESP_LOGI("BUTTON", "\tMULTIPLE[%d]", (int)data);
    }
    
    // Update graphical button state
    if (BUTTON_PRESS_DOWN == event) {
        buttons[btn_index].is_pressed = true;
        lv_async_call(update_button_appearance_async, (void *)btn_index);
    } else if (BUTTON_PRESS_UP == event || BUTTON_PRESS_END == event) {
        buttons[btn_index].is_pressed = false;
        lv_async_call(update_button_appearance_async, (void *)btn_index);
    }
}

// Function to fill the screen with a specific color and clear previous content
void fill_screen_with_color(lv_color_t color)
{
    lv_obj_t *scr = lv_scr_act();                             // Get the active screen
    lv_obj_clean(scr);                                        // Clear the screen (removes all objects)
    lv_obj_set_style_bg_color(scr, color, LV_PART_MAIN);      // Set the background color
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN); // Ensure full opacity
}

void app_main(void)
{
    // Initialize button configurations
    buttons[0] = (button_info_t){2, LV_COLOR_BLUE, NULL, NULL, false};   // GPIO02 - Blue
    buttons[1] = (button_info_t){3, LV_COLOR_GREEN, NULL, NULL, false};  // GPIO03 - Green
    buttons[2] = (button_info_t){4, LV_COLOR_RED, NULL, NULL, false};    // GPIO04 - Red

    // Initialize display first
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
            .buff_dma = true,
            .buff_spiram = false,
            .sw_rotate = false, // must be set to true for software rotation
        }};

    bsp_display_start_with_config(&cfg);

    // if (disp != NULL)
    // {
    //     bsp_display_rotate(disp, LV_DISPLAY_ROTATION_90); // 90、180、270
    // }
    bsp_display_backlight_on();

    // Create graphical buttons on screen
    create_graphical_buttons();

    // Initialize physical buttons
    const button_config_t btn_cfg = {0};
    const char *color_names[] = {"BLUE", "GREEN", "RED"};
    
    for (int i = 0; i < NUM_BUTTONS; i++) {
        const button_gpio_config_t btn_gpio_cfg = {
            .gpio_num = buttons[i].gpio_num,
            .active_level = 0,  // Active low (pressed when low)
        };

        esp_err_t ret = iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &buttons[i].handle);
        if (ret != ESP_OK) {
            ESP_LOGE("BUTTON", "Failed to create %s button device: %s", color_names[i], esp_err_to_name(ret));
        } else {
            // Register callbacks for various button events
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_DOWN, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_UP, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_REPEAT, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_REPEAT_DONE, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_SINGLE_CLICK, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_DOUBLE_CLICK, NULL, button_event_cb, NULL);

            // Register for triple click
            button_event_args_t args = {
                .multiple_clicks.clicks = 3,
            };
            iot_button_register_cb(buttons[i].handle, BUTTON_MULTIPLE_CLICK, &args, button_event_cb, (void *)3);

            iot_button_register_cb(buttons[i].handle, BUTTON_LONG_PRESS_START, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_LONG_PRESS_HOLD, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_LONG_PRESS_UP, NULL, button_event_cb, NULL);
            iot_button_register_cb(buttons[i].handle, BUTTON_PRESS_END, NULL, button_event_cb, NULL);

            ESP_LOGI("BUTTON", "%s button initialized on GPIO%d", color_names[i], buttons[i].gpio_num);
        }
    }

    // Disable scrolling for the entire screen
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLL_CHAIN_VER);

    ESP_LOGI("BUTTON", "Button monitoring system initialized. Press buttons to see visual feedback.");

    while (true)
    {
        // Let LVGL handle rendering and input
        vTaskDelay(pdMS_TO_TICKS(1));
        lv_task_handler(); // Call LVGL's task handler periodically
    }
}
