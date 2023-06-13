#include "networkinterface.h"
#include "dispatchmsgserver.h"
#include "events.h"
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>


NetworkInterface::NetworkInterface() : base_(nullptr), listener_(nullptr) {}

NetworkInterface::~NetworkInterface()
{
    close_networkinterface();
}

//开启网络接口
bool NetworkInterface::open_networkinterface(u32 port)
{
    if(port < 50000 || port > 65535)
    {
        port = PORT;
    }

    //创建一个sockaddr_in结构体后一定要清零处理
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    base_ = event_base_new();
    if(base_ == nullptr)
    {
        LOG_DEBUG("NetworkInterface::event_base_new 创建事件集合失败\n");
        return false;
    }

    //创建链接监听器 接受一个tcp连接
    listener_ = evconnlistener_new_bind(base_, listenevent_cb, base_
                    , LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE
                    , 512, (sockaddr*)&addr, sizeof(addr));
    if(listener_ == nullptr)
    {
        LOG_DEBUG("NetworkInterface::evconnlistener_new_bind 创建链接监听器 接受一个tcp连接 失败\n");
        return false;
    }

    return true;
}

//关闭网络接口
void NetworkInterface::close_networkinterface()
{
    if(base_)
    {
        event_base_free(base_);
    }

    if(listener_)
    {
        evconnlistener_free(listener_);
    }
}


//创建一个会话
session* NetworkInterface::create_session(evutil_socket_t fd, bufferevent* bev)
{
    if(bev == nullptr)
    {
        LOG_DEBUG("NetworkInterface::create_session 传入缓冲事件为空\n");
        return nullptr;
    }

    if(fd < 0)
    {
        LOG_DEBUG("NetworkInterface::create_session 传入客户端套接字文件描述符为负数\n");
        return nullptr;
    }

    session* cs = new session;
    if(cs == nullptr)
    {
        LOG_DEBUG("NetworkInterface::create_session 创建一个会话失败\n");
        return nullptr;
    }
    memset(cs, '\0', sizeof(session));
    cs->request_event = nullptr;
    cs->response_event = nullptr;

    //会话绑定套接字描述符
    cs->fd = fd;
    //会话绑定缓冲事件
    cs->bev = bev;
    //监听事件为请求事件
    cs->session_stat = SESSION_STAT::REQUEST_SESSION;
    //信息状态为读头部状态
    cs->message_stat = MESSAGE_STAT::MESSAGE_READING_HEAD;

    return cs;
}

//取消一个会话
void NetworkInterface::close_session(session* cs)
{
    if(cs)
    {
        if(cs->read_message)
        {
            delete[] cs->read_message;
            cs->read_message = nullptr;
        }
        
        if(cs->send_message)
        {
            delete[] cs->send_message;
            cs->send_message = nullptr;
        }
    }

    delete cs;
    cs = nullptr;
}

//重置一个会话
void NetworkInterface::reset_session(session* cs)
{
    if(cs)
    {
        if(cs->read_message)
        {
            delete[] cs->read_message;
            cs->read_message = nullptr;
        }

        if(cs->send_message)
        {
            delete[] cs->send_message;
            cs->send_message = nullptr;
        }
        
        cs->message_len = 0;
        cs->message_read_len = 0;
        cs->send_message_len = 0;

        cs->session_stat = SESSION_STAT::REQUEST_SESSION;
        cs->message_stat = MESSAGE_STAT::MESSAGE_READING_HEAD;
    }
}

//监听事件的回调函数
void NetworkInterface::listenevent_cb(evconnlistener* listener, evutil_socket_t fd, struct sockaddr* addr, i32 len, void* arg)
{
    // std::cout << "listenevent_cb回调" << std::endl;
    if(arg == nullptr)
    {
        LOG_DEBUG("NetworkInterface::listenevent_cb 传入的参数为空 监听回调结束\n");
        return;
    }

    event_base* base = (event_base*)arg;
    //创建一个socket套接字的缓冲事件
    bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if(bev == nullptr)
    {
        LOG_DEBUG("NetworkInterface::bufferevent_socket_new 创建一个socket套接字的缓冲事件失败\n");
        return;
    }

    //创建会话与缓冲事件进行绑定
    session* cs = create_session(fd, bev);
    if(cs == nullptr)
    {
        LOG_DEBUG("NetworkInterface::create_session 创建一个创建会话 并对事件进行绑定失败\n");
        return;
    }
    inet_ntop(AF_INET, &((sockaddr_in*)addr)->sin_addr.s_addr, cs->ip, len);

    //设置通信缓冲事件的回调
    bufferevent_setcb(bev, read_bufferevent_cb, write_bufferevent_cb, error_bufferenent_cb, (void*)cs);
    //设置通信缓冲事件的超时
    bufferevent_settimeout(bev, 10, 0);
    //使能buffervent的自动读写缓冲
    bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);

    LOG_DEBUG("远程客户端已经连接 来自：%s\n", cs->ip);
}

//读事件回调函数
void NetworkInterface::read_bufferevent_cb(bufferevent* bev, void* arg)
{
    session* cs = (session*)arg;

    //检查事件的状态
    if(cs->session_stat == SESSION_STAT::RESPONSE_SESSION)
    {
        LOG_DEBUG("NetworkInterface::read_bufferevent_cb 读事件回调函数的会话状态不是请求状态\n");
        return;
    }

    //检查事件的消息状态 -> 为读头标记
    if(cs->message_stat == MESSAGE_STAT::MESSAGE_READING_HEAD)
    {
        i32 len = bufferevent_read(bev, cs->header + cs->read_head_len, HEAD_LEN - cs->read_head_len);
        cs->read_head_len += len;
        cs->header[cs->read_head_len] = '\0';

        //头部数据读取完成
        if(cs->read_head_len == HEAD_LEN)
        {
            cs->message_stat = MESSAGE_STAT::MESSAGE_READING_HEAD_DONE;

            //头部数据标记正确
            if(strncmp(cs->header, HEAD_MAEK, strlen(HEAD_MAEK)) == 0)
            {
                cs->eid =  (EVENT_ID)(*(i16*)(cs->header + 4));
                cs->message_len = *(i32*)(cs->header + 6);

                if(cs->message_len > 1450 || cs->message_len < 0)
                {
                    LOG_DEBUG("NetworkInterface::read_bufferevent_cb 读事件回调函数接受数据长度不合法\n");
                    bufferevent_free(cs->bev);
                    close_session(cs);
                    return;
                }

                cs->read_message = new char[cs->message_len];                
                cs->message_stat = MESSAGE_STAT::MESSAGE_READING;
                cs->read_head_len = 0;
            }
            else
            {
                bufferevent_free(cs->bev);
                close_session(cs);
                return;
            }
        }
    }

    //检查事件的消息状态 -> 为读消息
    if(cs->message_stat == MESSAGE_STAT::MESSAGE_READING && evbuffer_get_length(bufferevent_get_input(bev)) > 0)
    {
        i32 len = bufferevent_read(bev, cs->read_message + cs->message_read_len, cs->message_len - cs->message_read_len);
        cs->message_read_len += len;

        if(cs->message_read_len == cs->message_len)
        {
            cs->message_stat = MESSAGE_STAT::MESSAGE_READING_DONE;

            IEvent* request_event = nullptr;

            //调用DispatchMsgServer解析消息为事件
            request_event = DispatchMsgServer::getInstance()->handler_message(cs->eid, cs->read_message, cs->message_len);
            
            if(request_event != nullptr)
            {
                delete[] cs->read_message;
                cs->read_message = nullptr;
                cs->message_len = 0;
                cs->message_read_len = 0;
                cs->message_stat = MESSAGE_STAT::MESSAGE_READING_DONE;

                //把创建的事件绑定会话
                request_event->setSession(cs);
                //把事件绑定给会话 用于释放资源
                cs->request_event = request_event;

                //投递请求至线程池
                DispatchMsgServer::getInstance()->createAndPostTask(request_event);
            }
            else
            {
                LOG_DEBUG("客户端[%s]发送的数据解析失败\n", cs->ip);
                bufferevent_free(cs->bev);
                close_session(cs);
            }
        }
    }
}

//写事件回调函数
void NetworkInterface::write_bufferevent_cb(bufferevent* bev, void* arg)
{
    // std::cout << "write_bufferevent_cb回调:服务器发送数据..." << std::endl;
}

//出现错误事件回调函数
void NetworkInterface::error_bufferenent_cb(bufferevent* bev, short what, void* arg)
{
    session* cs = (session*)arg;

    if((what & BEV_EVENT_EOF))
    {
        LOG_DEBUG("客户端[%s]正常会话结束\n", cs->ip);
    }
    if((what & BEV_EVENT_READING) && (what & BEV_EVENT_TIMEOUT))
    {
        LOG_DEBUG("读连接超时 与客户端[%s]会话结束\n", cs->ip);
    }
    else if((what & BEV_EVENT_TIMEOUT) && (what & BEV_EVENT_WRITING))
    {
        LOG_DEBUG("写连接超时 与客户端[%s]会话结束\n", cs->ip);
    }
    else if(what & BEV_EVENT_ERROR)
    {
        LOG_DEBUG("出现未知错误 与客户端[%s]会话结束\n", cs->ip);
    }

    bufferevent_free(bev);
    close_session(cs);
}

//响应事件发送给客户端
void NetworkInterface::send_event_message(session* cs)
{
    // LOG_DEBUG("NetworkInterface::send_event_message 响应事件发送给客户端\n");

    if(cs->response_event == nullptr)
    {
        bufferevent_free(cs->bev);
        if(cs->request_event)
        {
            delete cs->request_event;
        }
        close_session(cs);
    }

    if(cs->eid == EVENT_ID::LOGIN_RESPONSE || cs->eid == EVENT_ID::SELECT_HALL_RESPONSE || cs->eid == EVENT_ID::SELECT_TABLE_RESPONSE)
    {
        bufferevent_write(cs->bev, cs->send_message, cs->send_message_len + HEAD_LEN);
        reset_session(cs);
    }
    else if(cs->eid == EVENT_ID::PLAYING_CHESS_RESPONSE)
    {
        bufferevent_write(cs->bev, cs->send_message, cs->send_message_len + HEAD_LEN);
        reset_session(cs);
    }

}


//启动监听 正式开启networkinterfac
void NetworkInterface::network_diapatch()
{
    //启动监听事件循环
    event_base_loop(base_, EVLOOP_NONBLOCK);
    //启动响应事件发送
    DispatchMsgServer::getInstance()->handle_response_event(this);
}



