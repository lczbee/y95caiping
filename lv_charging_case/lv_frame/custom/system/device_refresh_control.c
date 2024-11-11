#include "custom.h"

static lv_timer_t *screen_refresh_timer = NULL;

static OS_MUTEX screen_list_mutex;

//-------------------------------------------------------------------------------------------
//-----------------------------------抢断页面管理链表----------------------------------------
//-------------------------------------------------------------------------------------------

typedef struct ScreenNode {
    lv_obj_t *screen;
    int Screen_Id;
    int init_flag;
    void (*Init)();
    void (*Deinit)();
    void (*Load)();
    void (*Refresh)();
    struct ScreenNode * next;
} ScreenNode;

static ScreenNode * head = NULL;

static bool node_exist(int Screen_Id) 
{
    ScreenNode * cur_node = head;
    while (cur_node != NULL) {
        if (cur_node->Screen_Id == Screen_Id) {
            return true;
        }
        cur_node = cur_node->next;
    }
    return false;
}


static void node_add(void (*Init)(), void (*Deinit)(), void (*Load)(), void (*Refresh)(),int Screen_Id) 
{
    ScreenNode * new_node = (ScreenNode *)malloc(sizeof(ScreenNode));
    new_node->Screen_Id = Screen_Id;
    new_node->init_flag = false;
    new_node->Init = Init;
    new_node->Deinit = Deinit;
    new_node->Load = Load;
    new_node->Refresh = Refresh;
    new_node->next = NULL;

    if (head == NULL || head->Screen_Id < Screen_Id) {
        // 插入到链表头部
        new_node->next = head;
        head = new_node;
    } else {
        // 找到插入点
        ScreenNode * cur_node = head;
        while (cur_node->next != NULL && cur_node->next->Screen_Id >= Screen_Id) {
            cur_node = cur_node->next;
        }
        new_node->next = cur_node->next;
        cur_node->next = new_node;
    }
}


static void node_del(int Screen_Id) 
{
    ScreenNode * cur_node = head;
    ScreenNode * prev = NULL;

    while (cur_node != NULL) {
        if (cur_node->Screen_Id == Screen_Id) {
            if (prev == NULL) {
                head = cur_node->next;
            } else {
                prev->next = cur_node->next;
            }
            free(cur_node);
            return;
        }
        prev = cur_node;
        cur_node = cur_node->next;
    }
}

static void node_all_clean() {
    ScreenNode * cur_node = head;
    while (cur_node != NULL) {
        ScreenNode * next = cur_node->next;
        free(cur_node);
        cur_node = next;
    }
    head = NULL;
}

static void node_printf()
{
    printf("-----------------------\n");
    ScreenNode * cur_node = head;
    int count = 0;
    while (cur_node != NULL) {
        printf("[node:%d]:screen:%d   init:%d\n", count, cur_node->Screen_Id, cur_node->init_flag);
        count++;
        ScreenNode * next = cur_node->next;
        cur_node = next;
    }
    printf("-----------------------\n");
}

//-------------------------------------------------------------------------------------------
//-----------------------------------对外接口------------------------------------------------
//-------------------------------------------------------------------------------------------
void screen_list_clean()
{
    os_mutex_pend(&screen_list_mutex, 0);

    // 释放所有页面
    ScreenNode * temp = head;
    while (temp != NULL) {
        if(temp->init_flag){
            if(temp->Deinit){
                temp->Deinit();
                temp->init_flag = false;
            }
        }

        ScreenNode * next = temp->next;
        temp = next;
    }

    node_all_clean();

_exit:
    os_mutex_post(&screen_list_mutex);
}


void screen_list_add(void (*Init)(), void (*Deinit)(), void (*Load)(), void (*Refresh)(), int Screen_Id)
{
    os_mutex_pend(&screen_list_mutex, 0);

    if(Screen_Id < 0 || Screen_Id >= SCREEN_PRIO_MAX){
        r_printf("[error] screen_list_add : Screen_Id not match\n");
        goto _exit;
    }

    if (node_exist(Screen_Id)) {
        r_printf("[error] screen_list_add : Screen_Id existed\n");
        goto _exit;
    }

    ScreenNode * pre_head = head;
    node_add(Init, Deinit, Load, Refresh, Screen_Id);
    ScreenNode * cur_head = head;

    if(cur_head == NULL){
        r_printf("[error] screen_list_add : cur_head == NULL\n");
        goto _exit;
    }

    if(cur_head->Screen_Id == Screen_Id){
        // 初始化新页面
        if(!cur_head->init_flag){
            if(cur_head->Init){
                cur_head->Init();
                cur_head->init_flag = true;
                if(cur_head->Refresh){
                    cur_head->Refresh();
                }
            }
        }

        // 显示新页面
        if(cur_head->Load){
            cur_head->Load();
        }

        // 把其他页面释放
        if(pre_head){
            if(pre_head->init_flag){
                if(pre_head->Deinit){
                    pre_head->Deinit();
                    pre_head->init_flag = false;
                }
            }
        }
    }

    node_printf();

_exit:
    os_mutex_post(&screen_list_mutex);
}


void screen_list_del(int Screen_Id)
{
    os_mutex_pend(&screen_list_mutex, 0);

    if(Screen_Id < 0 || Screen_Id >= SCREEN_PRIO_MAX){
        r_printf("[error] screen_list_del : Screen_Id not match\n");
        goto _exit;
    }

    if (!node_exist(Screen_Id)) {
        r_printf("[error] screen_list_del : Screen_Id not exist\n");
        goto _exit;
    }

    ScreenNode * cur_node = head;
    if(cur_node == NULL){
        r_printf("[error] screen_list_del : cur_node == NULL\n");
        goto _exit;
    }

    if(cur_node->Screen_Id == Screen_Id){

        if(cur_node->next){
            // 初始化下一个页面
            if(!cur_node->next->init_flag){
                if(cur_node->next->Init){
                    cur_node->next->Init();
                    cur_node->next->init_flag = true;
                }
            }

            // 显示下一个页面
            if(cur_node->next->Load){
                if(cur_node->next->Refresh){
                    cur_node->next->Refresh();
                }
                cur_node->next->Load();
            }
        }

        // 把当前页面释放
        if(cur_node->init_flag){
            if(cur_node->Deinit){
                cur_node->Deinit();
                cur_node->init_flag = false;
            }
        }
    }

    node_del(Screen_Id);

    node_printf();

_exit:
    os_mutex_post(&screen_list_mutex);
}

void screen_list_refresh()
{
    os_mutex_pend(&screen_list_mutex, 0);

    ScreenNode * cur_node = head;
    if(cur_node){
        if(cur_node->Refresh){
            cur_node->Refresh();
        }
    }

    os_mutex_post(&screen_list_mutex);
}



static void screen_refresh_timer_cb()
{
    screen_call_check();
    screen_charging_check();
    screen_upgrade_check();
    // screen_pop_up_check();

    screen_list_refresh();

	//全屏刷新,确保DISABLE状态能够刷新
	lv_obj_invalidate(lv_scr_act()); 
}

void lv_screen_refresh_start()
{
    os_mutex_create(&screen_list_mutex);

    if (!screen_refresh_timer) {
        screen_refresh_timer_cb();
        screen_refresh_timer = lv_timer_create(screen_refresh_timer_cb, SCREEN_REFRESH_INTERVAL, NULL);
    }
}