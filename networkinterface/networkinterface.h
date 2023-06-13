#ifndef KAOHE_NETWORKINTERFACE_H
#define KAOHE_NETWORKINTERFACE_H

#include "session.h"
#include "ievent.h"
#include "glo_def.h"
#include "event.h"
#include "event2/event.h"
#include "event2/listener.h"

//设置默认的本地端口号
#define PORT 50000

class NetworkInterface
{
public:
    NetworkInterface();
    virtual ~NetworkInterface();

    //开启网络接口
    bool open_networkinterface(u32 port = PORT);
    //关闭网络接口
    void close_networkinterface();

    //监听事件的回调函数
    static void listenevent_cb(evconnlistener* listener, evutil_socket_t fd
                                , struct sockaddr* addr, i32 len, void* ptr);

    //读事件回调函数
    static void read_bufferevent_cb(bufferevent* bev, void* arg);
    //写事件回调函数
    static void write_bufferevent_cb(bufferevent* bev, void* arg);
    //出现错误事件回调函数
    static void error_bufferenent_cb(bufferevent* bev, short what, void* arg);

    //启动监听 正式开启networkinterface
    void network_diapatch();

    //响应事件发送给客户端
    void send_event_message(session* cs);

protected:
    //创建一个会话
    static session* create_session(evutil_socket_t fd, bufferevent* bev);
    //取消一个会话
    static void close_session(session* cs);
    //重置一个会话
    static void reset_session(session* cs);

private:
    event_base* base_;
    evconnlistener* listener_;
};





#endif