#include "audio_page.h"

lv_obj_t *audio_chart;
lv_chart_series_t* audio_ser;
lv_style_t audio_style;
lv_timer_t * a_timer;

#define MIC_DATA_LEN    64

int16_t mic_data[MIC_DATA_LEN];
int32_t amp[MIC_DATA_LEN / 2 + 1] = {0};

// void fft(double x[], double y[], int32_t amp[], int N)
// {
// #define M_PI 3.1415926
//     int i, j, k, n1, n2;
//     double c, s, t1, t2;

//     // 位逆序置换
//     j = 0;
//     n2 = N / 2;
//     for(i = 1; i < N - 1; i++)
//     {
//         n1 = n2;
//         while(j >= n1)
//         {
//             j = j - n1;
//             n1 = n1 / 2;
//         }
//         j = j + n1;
//         if(i < j)
//         {
//             t1 = x[i];
//             x[i] = x[j];
//             x[j] = t1;
//             t1 = y[i];
//             y[i] = y[j];
//             y[j] = t1;
//         }
//     }

//     // 蝶形运算
//     n1 = 0;
//     n2 = 1;
//     for(i = 0; i < log2(N); i++)
//     {
//         n1 = n2;
//         n2 = n2 + n2;
//         for(j = 0; j < n1; j++)
//         {
//             c = cos(-M_PI * j / n1);
//             s = sin(-M_PI * j / n1);
//             for(k = j; k < N; k = k + n2)
//             {
//                 t1 = c * x[k + n1] - s * y[k + n1];
//                 t2 = s * x[k + n1] + c * y[k + n1];
//                 x[k + n1] = x[k] - t1;
//                 y[k + n1] = y[k] - t2;
//                 x[k] = x[k] + t1;
//                 y[k] = y[k] + t2;
//             }
//         }
//     }
    
//     for(i = 0; i <= MIC_DATA_LEN / 2 + 1; ++i)
//     {
//         amp[i] = (int32_t)(sqrt(x[i] * x[i] + y[i] * y[i]) / 16);
//     }
// }

void audio_timer(lv_timer_t * timer)
{
    // double re[MIC_DATA_LEN] = {0}, im[MIC_DATA_LEN] = {0};
    // lv_color_t color = lv_color_hex(lv_rand(0, 16777214));
    // HAL_I2S_Receive(&hi2s1, (uint16_t*)mic_data, MIC_DATA_LEN, 0xffff);
    // for(uint8_t i = 0; i < MIC_DATA_LEN; ++i)
    // {
    //     re[i] = (double)mic_data[i];
    // }
    // memset(im, 0, sizeof(im));
    // fft(re, im, amp, MIC_DATA_LEN);
    // lv_chart_set_series_color(audio_chart, audio_ser, color);
    // // lv_obj_set_style_border_color(audio_chart, color, LV_PART_MAIN);
    // lv_chart_set_ext_y_array(audio_chart, audio_ser, amp);
    // lv_chart_refresh(audio_chart);
}

static void event_top_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);    //获取回调事件
    lv_indev_t* indev = lv_indev_get_act(); //获取输入设备
	if (indev == NULL)  return;
    lv_point_t   lv_point;
    lv_indev_get_point(indev, &lv_point);

    static bool down_flag = false;
    static int press_x;
    if (code == LV_EVENT_PRESSING ) //点击事件
    {
        if(!down_flag)
        {
            press_x = lv_point.x;
            down_flag = true;
        }
    }
    if (code == LV_EVENT_RELEASED  ) //点击事件
    {
        if((lv_point.x - press_x) > 80)
        {
            page_transition_to_page_name("main_page");
        }

        down_flag = false;
    }
}


void audio_chart_set_default_style(void)
{
    lv_style_init(&audio_style);
    lv_style_set_bg_color(&audio_style, BACK_COLOR);
    lv_style_set_radius(&audio_style, 5);
    lv_style_set_border_width(&audio_style, 3);
    lv_style_set_border_color(&audio_style, MAIN_COLOR);
    lv_style_set_line_color(&audio_style, MAIN_COLOR);
    lv_style_set_line_opa(&audio_style, 40);
    lv_style_set_text_color(&audio_style, MAIN_COLOR);
    // lv_style_set_bg_grad_color(&audio_style, MAIN_COLOR);
    // lv_style_set_arc_color
}

void audio_page_init(struct page *page)
{
    audio_chart_set_default_style();
    lv_obj_t *body_obj = page->body_obj;

    lv_obj_t * top_obj = lv_obj_create(body_obj);

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


    lv_obj_t * label0 = lv_label_create(top_obj);
    lv_label_set_text(label0, "Audio Show");
    lv_obj_align(label0,  LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label0, BACK_COLOR, LV_PART_MAIN);


    a_timer = lv_timer_create(audio_timer, 100,  NULL);

    audio_chart = lv_chart_create(body_obj);
    lv_obj_set_size(audio_chart, 280, 160);
    lv_obj_align(audio_chart, LV_ALIGN_CENTER, 0, 10);
    lv_obj_add_style(audio_chart, &audio_style, 0);
    lv_chart_set_type(audio_chart, LV_CHART_TYPE_BAR);
    lv_chart_set_div_line_count(audio_chart, 5, 5);
    lv_chart_set_range(audio_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 500);
    lv_chart_set_range(audio_chart, LV_CHART_AXIS_PRIMARY_X, 0, 50);
    // lv_chart_set_range(audio_chart, LV_CHART_AXIS_PRIMARY_Y, 50, 100);
    // lv_chart_set_axis_tick(audio_chart, LV_CHART_AXIS_PRIMARY_Y, 5, 3, 4, 2, true, 40);
    audio_ser = lv_chart_add_series(audio_chart, MAIN_COLOR, LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_set_style_width(audio_chart, 3, LV_PART_INDICATOR);
    lv_obj_set_style_height(audio_chart, 3, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(audio_chart, 2, LV_PART_ITEMS);
    lv_chart_set_all_value(audio_chart, audio_ser, 0);
    lv_chart_set_point_count(audio_chart, 32);
    lv_obj_set_style_pad_column(audio_chart, 2, 0);

    lv_obj_t * audio_obj = lv_obj_create(body_obj);
    lv_obj_set_size(audio_obj, 280, 160);
    lv_obj_align(audio_obj, LV_ALIGN_CENTER, 0, 10);
    lv_obj_add_style(audio_obj, &audio_style, 0);
    lv_obj_set_style_bg_opa(audio_obj, 0, LV_PART_MAIN);
    // lv_obj_set_style_pad_all(audio_chart, 30, LV_PART_ITEMS);
    // lv_obj_set_style_bg_color(audio_chart, BACK_COLOR, LV_PART_ANY);
}

void audio_page_exit(struct page *old_page, struct page *new_page)
{
    lv_obj_clean(old_page->body_obj);
    lv_timer_delete(a_timer);
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 0, 0, false);
}
