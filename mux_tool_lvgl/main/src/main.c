
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include "lvgl_page_ctrl.h"

#include "main_page.h"
#include "osc_page.h"
#include "uart_page.h"
#include "iic_page.h"
#include "usbmk_page.h"
#include "game2048_page.h"
#include "mlx_page.h"
#include "audio_page.h"
#include "elec_page.h"
#include "signal_page.h"
#include "nes_page.h"
#include "enter_page.h"
#include "show_page.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_display_t *hal_init(int32_t w, int32_t h);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void all_page_init(void)
{
    page_set_default_style();
    app_set_default_style();
    page_create_new_page("main_page", page_set_default_screen, 0, main_page_init, main_page_exit, 1);
    page_create_new_page("osc_page", page_set_default_screen, 0, osc_page_init, osc_page_exit, 0);
    page_create_new_page("uart_page", page_set_default_screen, 0, uart_page_init, uart_page_exit, 0);
    page_create_new_page("iic_page", page_set_default_screen, 0, iic_page_init, iic_page_exit, 0);
    page_create_new_page("usbmk_pages", page_set_default_screen, 0, usbmk_page_init, usbmk_page_exit, 0);
    page_create_new_page("game2048_page", page_set_default_screen, 0, game2048_page_init, game2048_page_exit, 0);
    page_create_new_page("audio_page", page_set_default_screen, 0, audio_page_init, audio_page_exit, 0);
    page_create_new_page("mlx_page", page_set_default_screen, 0, mlx_page_init, mlx_page_exit, 0);
    page_create_new_page("elec_page", page_set_default_screen, 0, elec_page_init, elec_page_exit, 0);
    page_create_new_page("signal_page", page_set_default_screen, 0, signal_page_init, signal_page_exit, 0);
    page_create_new_page("nes_page", page_set_default_screen, 0, nes_page_init, nes_page_exit, 0);
    page_create_new_page("enter_page", page_set_default_screen, 0, enter_page_init, enter_page_exit, 0);
    page_create_new_page("show_page", page_set_default_screen, 0, show_page_init, show_page_exit, 0);
}

int main(int argc, char **argv)
{
    (void)argc; /*Unused*/
    (void)argv; /*Unused*/

    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    hal_init(320, 240);

    // lv_demo_widgets();

    /* 初始化所有的页面 */
    all_page_init();
    while (1)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_timer_handler();
        usleep(5 * 1000);
    }

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t *hal_init(int32_t w, int32_t h)
{

    lv_group_set_default(lv_group_create());

    lv_display_t *disp = lv_sdl_window_create(w, h);

    lv_indev_t *mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_indev_set_display(mouse, disp);
    lv_display_set_default(disp);

    // LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    //  lv_obj_t * cursor_obj;
    //  cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
    //  lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    //  lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

    lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
    lv_indev_set_display(mousewheel, disp);
    lv_indev_set_group(mousewheel, lv_group_get_default());

    lv_indev_t *kb = lv_sdl_keyboard_create();
    lv_indev_set_display(kb, disp);
    lv_indev_set_group(kb, lv_group_get_default());

    return disp;
}
