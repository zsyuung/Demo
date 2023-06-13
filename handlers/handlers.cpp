#include "handlers.h"
#include "glo_def.h"
#include "events.h"
#include "sqlconnection.h"
#include "userver.h"
#include "dispatchmsgserver.h"
#include "iniconfig.h"
#include <memory>



//用户登录注册等 游戏前的 请求事件的处理函数 [User_info_handler类的函数]
User_info_handler::User_info_handler() : IHandler(std::string("用户信息处理函数"))
{
    //订阅事件处理函数
    DispatchMsgServer::getInstance()->subscribeHandlers(EVENT_ID::LOGIN_REQUEST, this);
}


User_info_handler::~User_info_handler()
{
    //取消订阅事件处理函数
    DispatchMsgServer::getInstance()->unsubscribeHandlers(EVENT_ID::LOGIN_REQUEST, this);
}

IEvent* User_info_handler::handler(IEvent* event)
{
    if(event == nullptr)
    {
        LOG_DEBUG("User_info_handler::handler 传入的参数为空\n");
        return nullptr;
    }
    
    EVENT_ID eid = event->getEid();

    //根据请求事件的id选择处理函数
    if(eid == EVENT_ID::LOGIN_REQUEST)
    {
        return handler_login_req((login_request_event*)event);
    }

    return nullptr;
}

//用户登录请求事件的处理函数
login_response_event* User_info_handler::handler_login_req(login_request_event* ev)
{
    //从请求事件里面获取数据
    std::string user = ev->getUserID();
    std::string password = ev->getPassWord();

    //返回的响应事件指针
    login_response_event* lre = nullptr;

    //获取数据库连接对象
    std::shared_ptr<MysqlConnection> mysqlconn(new MysqlConnection);
    //获取数据库配置文件信息
    Iniconfig* config = Iniconfig::getInstance();
    //连接数据库
    if( mysqlconn->Init(config->getconfig().db_ip.c_str(), config->getconfig().db_port,
                    config->getconfig().db_user.c_str(), config->getconfig().db_pwd.c_str(),
                    config->getconfig().db_name.c_str()) == false)      
    {
        LOG_ERROR("User_info_handler::handler_login_req 处理登录事件时连接数据库失败\n");
        return nullptr;
    }

    //数据库连接成功 查询结果信息
    UserServer us(mysqlconn);
    if(us.user_exsist(user, password))
    {
        lre = new login_response_event(RESPONSE_ID::ERRC_SUCCESS);

        //获取会话事件 修改超时设定
        session* cs = (session*)ev->getSession();
        //设置通信缓冲事件的超时
        bufferevent_settimeout(cs->bev, 300, 10);
        //使能buffervent的自动读写缓冲
        bufferevent_enable(cs->bev, EV_READ);
    }
    else
    {
        lre = new login_response_event(RESPONSE_ID::ERRC_FAILURE);
    }

    return lre;
}


//------------------------------------------------------------------------------------


//用户登录成功后 进入游戏的 请求事件的处理函数 [Game_info_handler类的函数]
Game_info_handler::Game_info_handler() : IHandler(std::string("游戏信息处理函数"))
{
    //订阅事件处理函数
    DispatchMsgServer::getInstance()->subscribeHandlers(EVENT_ID::SELECT_HALL_REQUEST, this);
    DispatchMsgServer::getInstance()->subscribeHandlers(EVENT_ID::SELECT_TABLE_REQUEST, this);
}

Game_info_handler::~Game_info_handler()
{
    //取消订阅事件处理函数
    DispatchMsgServer::getInstance()->unsubscribeHandlers(EVENT_ID::SELECT_HALL_REQUEST, this);
    DispatchMsgServer::getInstance()->unsubscribeHandlers(EVENT_ID::SELECT_TABLE_REQUEST, this);
}

IEvent* Game_info_handler::handler(IEvent* event)
{
    if(event == nullptr)
    {
        LOG_DEBUG("Game_info_handler::handler 传入的参数为空\n");
        return nullptr;
    }

    EVENT_ID eid = event->getEid();

    //根据请求事件的id选择处理函数
    if(eid == EVENT_ID::SELECT_HALL_REQUEST)
    {
        return handler_hall_event((Select_hall_request_event*)event);
    }
    else if(eid == EVENT_ID::SELECT_TABLE_REQUEST)
    {
        return handler_table_event((Select_table_request_event*)event);
    }

    return nullptr;
}


//请求大厅事件的处理函数
Select_hall_response_event* Game_info_handler::handler_hall_event(Select_hall_request_event* ev)
{
    //获取大厅号码
    u32 hall_no = ev->getHallNo();

    std::shared_ptr<MysqlConnection> mysqlconn(new MysqlConnection);
    Iniconfig* config = Iniconfig::getInstance();
    if( mysqlconn->Init(config->getconfig().db_ip.c_str(), config->getconfig().db_port,
                    config->getconfig().db_user.c_str(), config->getconfig().db_pwd.c_str(),
                    config->getconfig().db_name.c_str()) == false)      
    {
        LOG_ERROR("Game_info_handler::handler_hall_event 请求大厅事件时连接数据库失败\n");
        return nullptr;
    }

    GameServer gs(mysqlconn);
    if(gs.hall_exsist(hall_no))
    {
        return new Select_hall_response_event(RESPONSE_ID::ERRC_SUCCESS);
    }
    else
    {
        return new Select_hall_response_event(RESPONSE_ID::ERRC_FAILURE);
    }
}

//请求桌子事件的处理函数
Select_table_response_event* Game_info_handler::handler_table_event(Select_table_request_event* ev)
{
    //获取桌子编号
    u32 table_no = ev->getTableNo();

    std::shared_ptr<MysqlConnection> mysqlconn(new MysqlConnection);
    Iniconfig* config = Iniconfig::getInstance();
    if( mysqlconn->Init(config->getconfig().db_ip.c_str(), config->getconfig().db_port,
                    config->getconfig().db_user.c_str(), config->getconfig().db_pwd.c_str(),
                    config->getconfig().db_name.c_str()) == false)      
    {
        LOG_ERROR("Game_info_handler::handler_hall_event 请求大厅事件时连接数据库失败\n");
        return nullptr;
    }

    GameServer gs(mysqlconn);
    if(gs.table_exsist(table_no))
    {
        return new Select_table_response_event(RESPONSE_ID::ERRC_SUCCESS);
    }
    else
    {
        return new Select_table_response_event(RESPONSE_ID::ERRC_FAILURE);
    }
}


