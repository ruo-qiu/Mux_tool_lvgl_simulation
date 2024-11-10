#include "main_page.h"

#define MAX_APP_NUM 20
app_struct app_admin[MAX_APP_NUM];               //存储所有创建好的页面
int app_num = 0;			            // 记录 app_admin[] 数组中存在多少个页面
lv_style_t app_style;                  // 默认页面背景样式
lv_obj_t * top_obj;
// 描述：设置app默认样式
// 参数：空
// 返回：空
void app_set_default_style(void)
{
    lv_style_init(&app_style);
    lv_style_set_bg_color(&app_style, MAIN_COLOR);//0x020f0f0
    lv_style_set_radius(&app_style, 10);
    lv_style_set_text_color(&app_style, MAIN_COLOR);     //设置样式文本字颜色
    lv_style_set_pad_all(&app_style, 0);
    lv_style_set_border_width(&app_style, 0);
    lv_style_set_border_side(&app_style, LV_BORDER_SIDE_NONE);
}

app_struct *app_search_from_name(char *app_name)
{
    for(int i = 0; i < app_num; i++)
    {
        if(strcmp(app_admin[i].name, app_name) == 0)
        {
            return &app_admin[i];
        }
    }
    return NULL;
}

void init_app_data(     lv_obj_t *parent_obj,
                        char *app_name,
                        lv_style_t* app_style,
                        const void * img,
                        void (*app_callback)(lv_event_t* e))
{
    if(app_num >= MAX_APP_NUM)
    {
        return;
    }
    if(app_search_from_name(app_name) != NULL)
    {
        return;
    }
    strcpy(app_admin[app_num++].name, app_name);
    app_admin[app_num - 1].btn = lv_btn_create(parent_obj);
    app_admin[app_num - 1].label = lv_label_create(parent_obj);;
    app_admin[app_num - 1].app_style = app_style;
    app_admin[app_num - 1].callback = app_callback;

    if(img != NULL)
    {
        lv_obj_t * img_1 = lv_img_create(app_admin[app_num - 1].btn);
        lv_img_set_src(img_1,img);
        lv_obj_set_align(img_1, LV_ALIGN_CENTER);
    }

}

void create_app_to_page(lv_obj_t *parent_obj)
{
    int page_width = lv_obj_get_width(parent_obj);
    for(int i = 0; i < app_num; i++)
    {
        lv_obj_add_event_cb(app_admin[i].btn, app_admin[i].callback, LV_EVENT_CLICKED, NULL);/*设置btn1回调函数*/
        lv_obj_add_style(app_admin[i].btn, app_admin[i].app_style, 0);
        lv_obj_set_size(app_admin[i].btn, (page_width / 7), (page_width / 7));
        lv_obj_set_pos(app_admin[i].btn, (((i+2) % 4) * (int)(page_width / 4) + ((page_width / 4) - (page_width / 7)) / 2 ), (int)(((i+2) / 4) * (page_width / 4.3) + 20));

        lv_label_set_text(app_admin[i].label, app_admin[i].name);
        lv_obj_add_style(app_admin[i].label, app_admin[i].app_style, 0);
        lv_obj_align_to(app_admin[i].label, app_admin[i].btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        lv_obj_update_layout(app_admin[i].btn);
        lv_obj_update_layout(app_admin[i].label);

    }

}


static void event_uart_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("uart_page");
}

static void event_osc_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("osc_page");
}

static void event_iic_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("iic_page");
}

static void event_usbmk_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("usbmk_page");
}

static void event_game2048_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("game2048_page");
}

static void event_audio_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("audio_page");
}

static void event_mlx_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("mlx_page");
}

static void event_elec_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("elec_page");
}

static void event_signal_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("signal_page");
}

static void event_nes_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("nes_page");
}

static void event_enter_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("enter_page");
}

static void event_show_btn_handler(lv_event_t* e)
{
    page_transition_to_page_name("show_page");
}

void main_page_init(struct page *page)
{
    app_set_default_style();
    lv_obj_t *body_obj = page->body_obj;
    // lv_obj_add_event_cb(body_obj, event_app_handler, LV_EVENT_ALL, NULL);/*设置btn1回调函数*/

    top_obj = lv_obj_create(body_obj);
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

    lv_obj_t *bg_obj = lv_obj_create(body_obj);
    lv_obj_set_size(bg_obj, lv_obj_get_width(body_obj), lv_obj_get_height(body_obj) - 25);
    lv_obj_set_pos(bg_obj, 0, 25);
    lv_obj_add_style(bg_obj, &page_style, 0);
    lv_obj_update_layout(bg_obj);

    lv_obj_t *title_obj = lv_obj_create(bg_obj);
    lv_obj_set_size(title_obj, (lv_obj_get_width(body_obj) / 7) * 2 + ((lv_obj_get_width(body_obj) / 4) - (lv_obj_get_width(body_obj) / 7)), (lv_obj_get_width(body_obj) / 7));
    lv_obj_set_pos(title_obj, ((lv_obj_get_width(body_obj) / 4) - (lv_obj_get_width(body_obj) / 7)) / 2, 20);
    lv_obj_add_style(title_obj, &app_style, 0);

    lv_obj_t * title_img = lv_img_create(title_obj);
	lv_img_set_src(title_img,&imgimage);
    lv_obj_set_align(title_img, LV_ALIGN_CENTER);

    lv_obj_update_layout(title_obj);
    lv_obj_set_pos(title_obj, lv_obj_get_x(title_obj), -100);
    lv_anim_t app_anim;
    lv_anim_init(&app_anim);
    lv_anim_set_var(&app_anim, title_obj);
    lv_anim_set_values(&app_anim, -100, lv_obj_get_y(title_obj));
    lv_anim_set_duration(&app_anim, 500);
    lv_anim_set_delay(&app_anim, 500);
    lv_anim_set_path_cb(&app_anim, lv_anim_path_ease_in_out);
    lv_anim_set_exec_cb(&app_anim, anim_y_cb);
    lv_anim_start(&app_anim);

    init_app_data(bg_obj, "uart", &app_style, &imguart, event_uart_btn_handler);
    init_app_data(bg_obj, "osc", &app_style, &imgshiboq, event_osc_btn_handler);
    init_app_data(bg_obj, "iic", &app_style, &imgiicsearch, event_iic_btn_handler);
    init_app_data(bg_obj, "ptg", &app_style, &imghot, event_mlx_btn_handler);
    init_app_data(bg_obj, "elec", &app_style, &imgelec, event_elec_btn_handler);
    init_app_data(bg_obj, "enter", &app_style, &imgenter, event_enter_btn_handler);
    init_app_data(bg_obj, "sign", &app_style, &imgsignal, event_signal_btn_handler);
    init_app_data(bg_obj, "umk", &app_style, &imgusbmk, event_usbmk_btn_handler);
    init_app_data(bg_obj, "mic", &app_style, &imgmic, event_audio_btn_handler);
    init_app_data(bg_obj, "self", &app_style, &imgself, event_show_btn_handler);
    init_app_data(bg_obj, "2048", &app_style, &imggame2048, event_game2048_btn_handler);
    init_app_data(bg_obj, "nes", &app_style, &imggame, event_nes_btn_handler);

    // init_app_data(bg_obj, "t11", &app_style, &img_7, event_btn1_handler);
    // init_app_data(bg_obj, "t12", &app_style, &img_7, event_btn1_handler);
    // init_app_data(bg_obj, "t13", &app_style, &img_7, event_btn1_handler);
    create_app_to_page(bg_obj);

    for(int i = 0; i < app_num; i++)
    {
        lv_obj_set_pos(app_admin[i].btn, lv_obj_get_width(body_obj) / 2 - lv_obj_get_width(app_admin[i].btn) / 2, lv_obj_get_height(body_obj) / 2);
        // lv_obj_set_pos(app_admin[i].btn, lv_obj_get_width(body_obj) / 2 - lv_obj_get_width(app_admin[i].btn) / 2, lv_obj_get_height(body_obj) / 2);
        lv_anim_t app_anim;
        lv_anim_init(&app_anim);
        lv_anim_set_var(&app_anim, app_admin[i].btn);
        lv_anim_set_values(&app_anim, lv_obj_get_height(body_obj) / 2, lv_obj_get_y(app_admin[i].btn));
        lv_anim_set_duration(&app_anim, 500);
        lv_anim_set_path_cb(&app_anim, lv_anim_path_ease_in_out);
        lv_anim_set_exec_cb(&app_anim, anim_y_cb);
        lv_anim_start(&app_anim);
        lv_anim_set_values(&app_anim, lv_obj_get_width(body_obj) / 2- lv_obj_get_width(app_admin[i].btn) / 2, lv_obj_get_x(app_admin[i].btn));
        lv_anim_set_exec_cb(&app_anim, anim_x_cb);
        lv_anim_start(&app_anim);

        lv_anim_set_var(&app_anim, app_admin[i].label);
        lv_anim_set_values(&app_anim, lv_obj_get_height(body_obj) / 2, lv_obj_get_y(app_admin[i].label));
        lv_anim_set_duration(&app_anim, 500);
        lv_anim_set_path_cb(&app_anim, lv_anim_path_ease_in_out);
        lv_anim_set_exec_cb(&app_anim, anim_y_cb);
        lv_anim_start(&app_anim);
        lv_anim_set_values(&app_anim, lv_obj_get_width(body_obj) / 2- lv_obj_get_width(app_admin[i].btn) / 2, lv_obj_get_x(app_admin[i].label));
        lv_anim_set_exec_cb(&app_anim, anim_x_cb);
        lv_anim_start(&app_anim);
    }
}

void main_page_exit(struct page *old_page, struct page *new_page)
{
    lv_obj_clean(old_page->body_obj);
    memset((char*)app_admin, 0, sizeof(app_admin));
    app_num = 0;
    lv_scr_load_anim(new_page->body_obj, LV_SCR_LOAD_ANIM_FADE_IN, 500, 0, false);

}
