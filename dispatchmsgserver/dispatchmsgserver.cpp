#include "dispatchmsgserver.h"
#include <unistd.h>
#include <algorithm>



//单例模式
DispatchMsgServer* DispatchMsgServer::dms_ = nullptr;
//响应事件队列
std::queue<IEvent*> DispatchMsgServer::queue_evs_;
//响应事件队列的锁
pthread_mutex_t DispatchMsgServer::locker_queue_;



//构造函数 属性初始化
DispatchMsgServer::DispatchMsgServer() : is_pool_open(false)
{
    //初始化响应事件队列的锁
    thread_mutex_create(&locker_queue_);
}

DispatchMsgServer::~DispatchMsgServer() 
{
    if(is_pool_open == true)
    {
        close_pool();
    }
    thread_mutex_destroy(&locker_queue_);
    subscribers_.clear();
}


//单例模式
DispatchMsgServer* DispatchMsgServer::getInstance()
{
    if(dms_ == nullptr)
    {
        dms_ = new DispatchMsgServer;
    }
    return dms_;
}


//开启和关闭线程池
bool DispatchMsgServer::open_pool()
{
    if(is_pool_open == false)
    {
        pool_ = thread_pool_init();
        is_pool_open = true;
    }

    return is_pool_open;
}

void DispatchMsgServer::close_pool()
{
    if(is_pool_open == true)
    {
        thread_pool_destroy(pool_);
        is_pool_open = false;
    }
}


//事件处理函数的订阅
void DispatchMsgServer::subscribeHandlers(EVENT_ID eid, IHandler* handler)
{
    if(handler == nullptr)
    {
        LOG_DEBUG("DispatchMsgServer::subscribeHandlers 处理函数为空\n");
    }

    auto iter = subscribers_.find(eid);

    //如果没有找到eid
    if(iter == subscribers_.end())
    {
        subscribers_[eid].push_back(handler);
        // LOG_DEBUG("DispatchMsgServer::subscribeHandlers 处理函数订阅成功\n");
        return;
    }
    else
    {
        auto hdl_iter = std::find(iter->second.begin(), iter->second.end(), handler);
        if(hdl_iter == iter->second.end())
        {
            iter->second.push_back(handler);
            // LOG_DEBUG("DispatchMsgServer::subscribeHandlers 处理函数订阅成功\n");
            return;
        }
        else
        {
            // LOG_DEBUG("DispatchMsgServer::subscribeHandlers 处理函数已经订阅过了\n");
            return;           
        }
    }

    return;
}

//事件处理函数的取消订阅
void DispatchMsgServer::unsubscribeHandlers(EVENT_ID eid, IHandler* handler)
{
    if(handler == nullptr)
    {
        // LOG_DEBUG("DispatchMsgServer::unsubscribeHandlers 处理函数为空\n");
        return;
    }

    auto iter = subscribers_.find(eid);

    if(iter == subscribers_.end())
    {
        // LOG_DEBUG("DispatchMsgServer::unsubscribeHandlers 处理函数没有注册/已经取消订阅\n");
        return;
    }
    else
    {
        handlers_t vec = (*iter).second;
        auto pos = std::find(vec.begin(), vec.end(), handler);
        if(pos != vec.end())
        {
            vec.erase(pos);
            // LOG_DEBUG("DispatchMsgServer::unsubscribeHandlers 处理函数取消订阅成功\n");
            return;
        }
    }
    
    return;
}

//线程回调函数内的处理函数
IEvent* DispatchMsgServer::handler4svrs(IEvent* event)
{
    EVENT_ID eid = event->getEid();

    //其他的不明事件或者退出事件
    if(eid == EVENT_ID::OTHERS || eid == EVENT_ID::QUIT_EVENT)
    {
        return nullptr;
    }

    IEvent* ev = nullptr;
    map_handlers_t::iterator hdl_iter = subscribers_.find(eid);
    if(hdl_iter != subscribers_.end())
    {
        for(auto hdls = (*hdl_iter).second.begin(); hdls != (*hdl_iter).second.end(); hdls++)
        {
            IHandler* handler = (*hdls);
            ev = handler->handler(event);
        }
    }

    return ev;
}

//线程回调函数
void DispatchMsgServer::svrs4pool(void* param)
{
    DispatchMsgServer* dms = DispatchMsgServer::getInstance();

    IEvent* event = nullptr;
    IEvent* old_event = (IEvent*)param;

    event = dms->handler4svrs(old_event);
    
    if(event == nullptr)
    {
        event = new Quit_event;
    }

    event->setSession(old_event->getSession());

    //释放请求事件的资源
    session *cs = (session*)old_event->getSession();
    if(cs->request_event)
    {
        delete cs->request_event;
        cs->request_event = nullptr;
        // LOG_DEBUG("DispatchMsgServer::svrs4pool 释放请求事件的资源\n");
    }

    //把处理后得到的响应事件投递到响应事件队列
    pthread_mutex_lock(&locker_queue_);
    queue_evs_.push(event);
    pthread_mutex_unlock(&locker_queue_);
}

//创建任务并投递到线程池
void DispatchMsgServer::createAndPostTask(IEvent* event)
{
    if(is_pool_open == false)
    {
        // open_pool()
        LOG_DEBUG("DispatchMsgServer::createAndPostTask 线程池未开启\n");
        return;
    }

    //创建任务
    thread_task_t* task = thread_task_alloc(0);
    task->handler = DispatchMsgServer::svrs4pool;
    task->ctx = (void*)event;

    //投递任务
    thread_task_post(pool_, task);
    // LOG_DEBUG("DispatchMsgServer::createAndPostTask 创建任务并投递到线程池成功\n");
}

//提供给networkinterface接口 用来处理发送过来的数据
IEvent* DispatchMsgServer::handler_message(EVENT_ID eid, const char* buf, i32 len)
{
    if(eid == EVENT_ID::LOGIN_REQUEST)
    {
        login_request lr;
        lr.ParseFromArray(buf, len);

        login_request_event* lre = new login_request_event(lr.userid(), lr.password());

        return lre;
    }
    else if(eid == EVENT_ID::SELECT_HALL_REQUEST)
    {
        select_hall_request shr;
        shr.ParseFromArray(buf, len);

        Select_hall_request_event* shre = new Select_hall_request_event(shr.hall_number());

        return shre;
    }
    else if(eid == EVENT_ID::SELECT_TABLE_REQUEST)
    {
        select_table_request str;
        str.ParseFromArray(buf, len);

        Select_table_request_event* stre = new Select_table_request_event(str.table_number());

        return stre;
    }
    else if(eid == EVENT_ID::PLAYING_CHESS_REQUEST)
    {
        playing_chess_request chess_request;
        chess_request.ParseFromArray(buf, len);

        chess_playing_request* chess_request_event = new chess_playing_request(chess_request.hall_number(), 
                chess_request.table_number(), chess_request.game_stat(), chess_request.x_pos(), chess_request.y_pos());

        return chess_request_event;
    }

    return nullptr;
}


//调用networkinterface接口 把处理过的事件队列发送
void DispatchMsgServer::handle_response_event(NetworkInterface* nif)
{
    bool done = false;
    
    while(!done)
    {
        //从队列里面拿出一个事件
        IEvent* ev = nullptr;
        pthread_mutex_lock(&locker_queue_);
        if(!queue_evs_.empty())
        {
            ev = queue_evs_.front();
            queue_evs_.pop();
            pthread_mutex_unlock(&locker_queue_);
        }
        else
        {
            pthread_mutex_unlock(&locker_queue_);
            done = true;
        }

        //对事件进行拼装
        if(!done)
        {
            // LOG_DEBUG("DispatchMsgServer::handle_response_event 处理响应事假队列\n");

            if(ev->getSession() == nullptr)
            {
                cout << "ev is nullptr" << endl;
                return;
            }

            //把事件的会话拿出来
            session* cs = (session*)ev->getSession();

            //设置会话为响应事件
            cs->session_stat = SESSION_STAT::RESPONSE_SESSION;

            //设置会话的事件id
            cs->eid = ev->getEid();

            //获取事件的eid
            EVENT_ID eid = ev->getEid();

            if(eid == EVENT_ID::QUIT_EVENT)
            {
                cs->response_event = nullptr;
                nif->send_event_message(cs);
            }
            else if(eid == EVENT_ID::LOGIN_RESPONSE)
            {
                //把事件的属性赋值给消息
                login_response_event* le = (login_response_event*)ev;

                //设置会话对应的事件
                cs->response_event = le;

                //发送数据的字符数组
                cs->send_message_len = ev->getMessageSize();
                cs->send_message = new char[cs->send_message_len + HEAD_LEN];

                //组装头部
                memcpy(cs->send_message, HEAD_MAEK, strlen(HEAD_MAEK));
                *(i16*)(cs->send_message + 4) = (i16)eid;
                *(i32*)(cs->send_message + 6) = cs->send_message_len;

                //序列化数据
                ev->SerializeToArray(cs->send_message + HEAD_LEN, cs->send_message_len);
                //发送数据
                nif->send_event_message(cs);
            }
            else if(eid == EVENT_ID::SELECT_HALL_RESPONSE)
            {
                //把事件的属性赋值给消息
                Select_hall_response_event* le = (Select_hall_response_event*)ev;
                
                //设置会话对应的事件
                cs->response_event = le;

                //发送数据的字符数组
                cs->send_message_len = ev->getMessageSize();
                cs->send_message = new char[cs->send_message_len + HEAD_LEN];

                //组装头部
                memcpy(cs->send_message, HEAD_MAEK, strlen(HEAD_MAEK));
                *(i16*)(cs->send_message + 4) = (i16)eid;
                *(i32*)(cs->send_message + 6) = cs->send_message_len;

                //序列化数据
                ev->SerializeToArray(cs->send_message + HEAD_LEN, cs->send_message_len);
                //发送数据
                nif->send_event_message(cs);
            }
            else if(eid == EVENT_ID::SELECT_TABLE_RESPONSE)
            {
                //把事件的属性赋值给消息
                Select_table_response_event* le = (Select_table_response_event*)ev;
                
                //设置会话对应的事件
                cs->response_event = le;

                //发送数据的字符数组
                cs->send_message_len = ev->getMessageSize();
                cs->send_message = new char[cs->send_message_len + HEAD_LEN];

                //组装头部
                memcpy(cs->send_message, HEAD_MAEK, strlen(HEAD_MAEK));
                *(i16*)(cs->send_message + 4) = (i16)eid;
                *(i32*)(cs->send_message + 6) = cs->send_message_len;

                //序列化数据
                ev->SerializeToArray(cs->send_message + HEAD_LEN, cs->send_message_len);
                //发送数据
                nif->send_event_message(cs);
            }
            else if(eid == EVENT_ID::PLAYING_CHESS_RESPONSE)
            {
                chess_playing_response* pcresp = (chess_playing_response*)ev;

                //设置会话对应的事件
                cs->response_event = pcresp;

                //发送数据的字符数组
                cs->send_message_len = ev->getMessageSize();
                cs->send_message = new char[cs->send_message_len + HEAD_LEN];

                //组装头部
                memcpy(cs->send_message, HEAD_MAEK, strlen(HEAD_MAEK));
                *(i16*)(cs->send_message + 4) = (i16)eid;
                *(i32*)(cs->send_message + 6) = cs->send_message_len;

                //序列化数据
                ev->SerializeToArray(cs->send_message + HEAD_LEN, cs->send_message_len);
                //发送数据
                nif->send_event_message(cs);

                //查看是几个用户
                u32 player_num = pcresp->getRival().size();            

                //如果是两个人
                if(player_num == 2)
                {
                    //双方第一次绑定成功
                    if(pcresp->getGamestat() == CHESS_CODE::BEGGING)
                    {
                        //从响应事件里面拿到对战双方的会话
                        players_ css = pcresp->getRival();
                        //向玩家传输数据
                        for(int i = 0; i < css.size(); i++)
                        {
                            if(css[i] != cs)
                            {
                                string str = string("游戏开始！");
                                write(css[i]->fd, str.c_str(), strlen(str.c_str()));
                            }
                        }
                    }

                    //双方已经绑定了
                    if(pcresp->getGamestat() == CHESS_CODE::PLAYING)
                    {
                        //从响应事件里面拿到对战双方的会话
                        players_ css = pcresp->getRival();
                        //向玩家传输数据
                        for(int i = 0; i < css.size(); i++)
                        {
                            if(css[i] != cs)
                            {
                                // string str = string("nihao");
                                // write(css[i]->fd, str.c_str(), strlen(str.c_str()));

                                //发一个响应事件
                                int len = pcresp->getMessageSize();
                                char msg[512] = {0};
                                memcpy(msg, "CHES", 4);
                                *(u16*)(msg + 4) = (u16)EVENT_ID::PLAYING_CHESS_RESPONSE;
                                *(i32*)(msg + 6) = len;
                                pcresp->SerializeToArray(msg+10, len);
                                write(css[i]->fd, msg, len + 10);
                            }
                        }
                    }
                }

            }

            //把响应事件的资源释放掉
            delete ev;
            cs->response_event = nullptr;
        }
    }

}
