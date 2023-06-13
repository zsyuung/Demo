#ifndef KAOHE_IEVENT_H
#define KAOHE_IEVENT_H

#include "glo_def.h"
#include "eventtype.h"

/*
    ievent是所有事件的基类 
        所有事件派生于ievent类
*/

class IEvent
{
public:
    IEvent(EVENT_ID eid = EVENT_ID::NO_DEFINED_EVENT):eid_(eid), argv_(nullptr)
    { 
        generateOnlyID(); 
    }

    virtual ~IEvent() {}

    //获取事件的编号
    EVENT_ID getEid() const {return eid_;}
    void setEid(EVENT_ID eid) {eid_ = eid;}
    u32 getSid() const {return sid_;}

    //设置和获取事件的会话
    void setSession(void* argv) {argv_ = argv;}
    void* getSession() const {return argv_;}

    //获取事件大小
    virtual i32 getMessageSize() {return 0;}    
    
    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return true;};

    //给每个事件单独设置一个编号
    void generateOnlyID()
    {
        static u32 sid = 0;
        sid_ = ++sid;
    }

    virtual std::ostream& dump(std::ostream& os)
    {
        os << "事件sid:" << sid_ << " - "
           << "事件类型eid:" << (u32)eid_ << " - ";
        return os;
    }

protected:
    //事件的id
    u32 sid_;
    //事件类型的编号
    EVENT_ID eid_;
    //用来保存连接的会话
    void* argv_;
};





#endif