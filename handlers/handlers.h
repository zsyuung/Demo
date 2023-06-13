#ifndef KAOHE_HANDLER_H
#define KAOHE_HANDLER_H

#include "events.h"
#include "handlers.h"
#include "ihandlers.h"


//用户登录注册等 游戏前的 请求事件的处理函数
class User_info_handler : public IHandler
{
public:
    User_info_handler();
    virtual ~User_info_handler();

    //具体的处理函数
    virtual IEvent* handler(IEvent* event);    

private:
    //用户登录请求事件的处理函数
    login_response_event* handler_login_req(login_request_event* ev);
};


//用户登录成功后 进入游戏的 请求事件的处理函数
class Game_info_handler : public IHandler
{
public:
    Game_info_handler();
    virtual ~Game_info_handler();

    //具体的处理函数
    virtual IEvent* handler(IEvent* event);    

private:
    //请求大厅事件的处理函数
    Select_hall_response_event* handler_hall_event(Select_hall_request_event* ev);
    //请求桌子事件的处理函数
    Select_table_response_event* handler_table_event(Select_table_request_event* ev);
};




#endif