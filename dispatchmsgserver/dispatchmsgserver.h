#ifndef KAOHE_DISPATCHMSGSERVER_H
#define KAOHE_DISPATCHMSGSERVER_H


#include <map>
#include <vector>
#include <queue>
#include "ihandlers.h"
#include "events.h"
#include "networkinterface.h"
#include "thread_pool.h"
#include "playingchess.h"
#include "chess_handler.h"


//事件分发器 所有与事件处理有关的函数交由这个类处理
class DispatchMsgServer
{
public:
    typedef vector<IHandler*> handlers_t;
    typedef map<EVENT_ID, handlers_t> map_handlers_t;

protected:
    //构造函数 属性初始化
    DispatchMsgServer();
public:
    virtual ~DispatchMsgServer();

    //单例模式
    static DispatchMsgServer* getInstance();

    //开启和关闭线程池
    bool open_pool();
    void close_pool();

    //事件处理函数的订阅
    void subscribeHandlers(EVENT_ID eid, IHandler* handler);
    //事件处理函数的取消订阅
    void unsubscribeHandlers(EVENT_ID eid, IHandler* handler);

    //提供给networkinterface接口 用来处理发送过来的数据
    IEvent* handler_message(EVENT_ID eid, const char* buf, i32 len);

    //调用networkinterface接口 把处理过的事件队列发送
    void handle_response_event(NetworkInterface* nif);


#if 1
    //检查是否订阅成功
    map_handlers_t getSubscribe_() {return subscribers_;}
    //检查线程池是否正常运行
    std::queue<IEvent*>& getQueue() {return queue_evs_;}
#endif

    //创建任务并投递到线程池
    void createAndPostTask(IEvent* event);
    //线程回调函数
    static void svrs4pool(void* param);
private:
    //线程回调函数内的处理函数
    IEvent* handler4svrs(IEvent* event);

private:
    //标记线程池是否开启
    bool is_pool_open;
    //线程池
    thread_pool_t* pool_;

    //单例模式
    static DispatchMsgServer* dms_;

    //响应事件队列的锁
    static pthread_mutex_t locker_queue_;
    //响应事件队列
    static std::queue<IEvent*> queue_evs_;

    //注册事件的函数
    map_handlers_t subscribers_;
};






#endif