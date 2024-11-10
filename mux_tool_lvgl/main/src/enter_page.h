#ifndef __ENTER_PAGE__
#define __ENTER_PAGE__

#include "lvgl_page_ctrl.h"

typedef struct enter
{
    uint16_t enter_num;
    lv_obj_t * enter_btn;                                                 
    char enter_name[32];                                             
    char enter_account[32];                                         
    char enter_password[64];                                              
}enter_struct;

void enter_list_add(lv_obj_t *parent_obj, char *name, char *account, char* password);
void create_enter_list_to_page(lv_obj_t *parent_obj);
void enter_page_init(struct page *page);
void enter_page_exit(struct page *old_page, struct page *new_page);

#endif