#include "mlx_page.h"

lv_style_t mlx_style;
static lv_img_dsc_t img_dsc;
lv_timer_t* mlx_timer;
lv_obj_t* mlx_img;
void mlx_timer_handle(lv_timer_t* timer)
{
//   for(uint16_t i = 0; i < sizeof(mlx_imgs)/2; i++)
//   {
//       mlx_imgs[i] = lv_rand(10, 65535);
//   }
    // mlx_get_img();
    lv_img_set_src(mlx_img, &img_dsc);
}

static void event_top_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    lv_indev_t* indev = lv_indev_get_act(); //获取输入设备
    if(indev == NULL)  return;
    lv_point_t   lv_point;
    lv_indev_get_point(indev, &lv_point);

    static bool down_flag = false;
    static int press_x;
    if(code == LV_EVENT_PRESSING)   //点击事件
    {
        if(!down_flag)
        {
            press_x = lv_point.x;
            down_flag = true;
        }
    }
    if(code == LV_EVENT_RELEASED)    //点击事件
    {
        if((lv_point.x - press_x) > 80)
        {
            page_transition_to_page_name("main_page");
        }

        down_flag = false;
    }
}


void mlx_text_set_default_style(void)
{
    lv_style_init(&mlx_style);
    lv_style_set_bg_color(&mlx_style, BACK_COLOR);
    lv_style_set_radius(&mlx_style, 5);
    lv_style_set_border_width(&mlx_style, 3);
    lv_style_set_border_color(&mlx_style, MAIN_COLOR);
    lv_style_set_line_color(&mlx_style, MAIN_COLOR);
    lv_style_set_line_opa(&mlx_style, 40);
    lv_style_set_text_color(&mlx_style, MAIN_COLOR);
    lv_style_set_pad_left(&mlx_style, 0);
    lv_style_set_pad_right(&mlx_style, 0);
    lv_style_set_pad_top(&mlx_style, 5);
    lv_style_set_pad_bottom(&mlx_style, 5);
}

void mlx_page_init(struct page* page)
{
    mlx_text_set_default_style();

    lv_obj_t* body_obj = page->body_obj;

    lv_obj_t* top_obj = lv_obj_create(body_obj);
    lv_obj_add_event_cb(top_obj, event_top_handler, LV_EVENT_ALL, NULL);/*设置btn1回调函数*/
    lv_obj_add_style(top_obj, &app_style, 0);
    lv_obj_set_size(top_obj, lv_obj_get_width(body_obj), 25);
    lv_obj_set_pos(top_obj, 0, -25);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, top_obj);
    lv_anim_set_values(&a, -25, 0);
    lv_anim_set_duration(&a, 500);
    lv_anim_set_exec_cb(&a, anim_y_cb);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
    lv_anim_start(&a);
    mlx_timer = lv_timer_create(mlx_timer_handle, 200,  NULL);
    lv_obj_t* label0 = lv_label_create(top_obj);
    lv_label_set_text(label0, "Thermal Imaging");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);

    mlx_img = lv_img_create(body_obj);
    lv_obj_add_style(mlx_img, &mlx_style, 0);
    lv_obj_set_size(mlx_img, 256, 192);
    lv_obj_align(mlx_img, LV_ALIGN_CENTER, 0, 13);
    lv_image_set_scale_x(mlx_img, 2048);
    lv_image_set_scale_y(mlx_img, 2048);
    img_dsc.header.cf = LV_COLOR_FORMAT_RGB565;
    // img_dsc.data = (uint8_t*)mlx_imgs;
    img_dsc.header.w = 32;
    img_dsc.header.h = 24;

    // mlx90640_init();
}

void mlx_page_exit(struct page* old_page, struct page* new_page)
{
    lv_obj_clean(old_page->body_obj);
    // mlx90640_deinit();
    lv_timer_delete(mlx_timer);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
