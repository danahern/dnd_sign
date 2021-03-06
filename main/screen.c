/* 
    For displaying stuff on the screen
*/

/* Standard Includes */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FreeRTOS and ESP Includes */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_console.h"
#include "argtable3/argtable3.h"


#include "screen.h"

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "lvgl_helpers.h"


/*********************
 *      DEFINES
 *********************/
#define TAG "screen"
#define LV_TICK_PERIOD_MS 1
#define GUI_TASK_STACK 4096 //8192

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_tick_task(void *arg);
static void guiTask(void *pvParameter);
static void register_screen();

/**********************
 *  MODULE VARIABLES
 **********************/
/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;
/* Hold button style */
lv_style_t style_btn;


/**********************
 *   Public Functions
 **********************/
void dnd_screen_init() {

    /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */
    xTaskCreatePinnedToCore(guiTask, "gui", GUI_TASK_STACK, NULL, 0, NULL, 1);
    register_screen();
}

void dnd_screen_set_free(void)
{
    lv_style_init(&style_btn);

    /* use a pretty small demo for monochrome displays */
    /* Get the current screen  */
    lv_obj_t * scr = lv_disp_get_scr_act(NULL);

    lv_obj_t * btn1 = lv_btn_create(scr, NULL);

    lv_style_set_radius(&style_btn, LV_STATE_DEFAULT, 20);
    lv_style_set_bg_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_GREEN);
    lv_style_set_text_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(btn1, LV_BTN_PART_MAIN, &style_btn);

    // /*Create a Label on the currently active screen*/
    lv_obj_t * label1 =  lv_label_create(btn1, NULL);

    // /*Modify the Label's text*/
    lv_label_set_text(label1, "Free");

    // /* Align the Label to the center
    //  * NULL means align on parent (which is the screen now)
    //  * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 0);

}

void dnd_screen_set_busy(void)
{
    lv_style_init(&style_btn);

    /* Get the current screen  */
    lv_obj_t * scr = lv_disp_get_scr_act(NULL);

    lv_obj_t * btn1 = lv_btn_create(scr, NULL);

    lv_style_set_radius(&style_btn, LV_STATE_DEFAULT, 20);
    lv_style_set_bg_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_text_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_add_style(btn1, LV_BTN_PART_MAIN, &style_btn);

    // /*Create a Label on the currently active screen*/
    lv_obj_t * label1 =  lv_label_create(btn1, NULL);

    // /*Modify the Label's text*/
    lv_label_set_text(label1, "Busy");

    // /* Align the Label to the center
    //  * NULL means align on parent (which is the screen now)
    //  * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 0);

}

/***********************
 *   Private Functions
 ***********************/

static void guiTask(void *pvParameter) {

    (void) pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();

    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    lv_color_t* buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf1 != NULL);

    /* Use double buffered when not working with monochrome displays */
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    lv_color_t* buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
    assert(buf2 != NULL);
#else
    static lv_color_t *buf2 = NULL;
#endif

    static lv_disp_buf_t disp_buf;

    uint32_t size_in_px = DISP_BUF_SIZE;

#if defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820         \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A    \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D     \
    || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306

    /* Actual size in pixels, not bytes. */
    size_in_px *= 8;
#endif

    /* Initialize the working buffer depending on the selected display.
     * NOTE: buf2 == NULL when using monochrome displays. */
    lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

    /* When using a monochrome display we need to register the callbacks:
     * - rounder_cb
     * - set_px_cb */
#ifdef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    disp_drv.rounder_cb = disp_driver_rounder;
    disp_drv.set_px_cb = disp_driver_set_px;
#endif

    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    /* Register an input device when enabled on the menuconfig */
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = touch_driver_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    /* Create the demo application */
    dnd_screen_set_free();

    while (1) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
       }
    }

    /* A task should NEVER return */
    free(buf1);
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
    free(buf2);
#endif
    vTaskDelete(NULL);
}

static void lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}


/** Arguments used by 'screen_swap' function */
static struct {
    struct arg_int *number;
    struct arg_end *end;
} screen_swap_args;

static int screen_swap(int argc, char **argv)
{
    int nerrors = arg_parse(argc, argv, (void **) &screen_swap_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, screen_swap_args.end, argv[0]);
        return 1;
    }

    if ( screen_swap_args.number->count)
    {
        if (screen_swap_args.number->ival[0] == 1)
        {
            dnd_screen_set_free();
        }
        if (screen_swap_args.number->ival[0] == 2)
        {
            dnd_screen_set_busy();
        }
    }
    
    return 0;
}
static void register_screen(void)
{
    screen_swap_args.number = arg_int0(NULL, NULL, "<n>", "Screen number to display");
    screen_swap_args.end = arg_end(2);

    const esp_console_cmd_t screen_swap_cmd = {
        .command = "screen",
        .help = "Swaps between screens",
        .hint = NULL,
        .func = &screen_swap,
        .argtable = &screen_swap_args
    };

    ESP_ERROR_CHECK( esp_console_cmd_register(&screen_swap_cmd) );
}