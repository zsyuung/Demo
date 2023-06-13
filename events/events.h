#ifndef KAOHE_EVENTS_H
#define KAOHE_EVENTS_H

#include "ievent.h"
#include "chess.pb.h"

using namespace chess_protocal;
using namespace std;


/*
    events.h对事件进行了定义
        所有的事件派生于IEvent
        并且关联了事件对应的请求消息
*/

//1.1、登录请求事件
class login_request_event : public IEvent
{
public:
    login_request_event(const std::string& userid, const std::string& password)
         : IEvent(EVENT_ID::LOGIN_REQUEST) 
    {
        logreq_.set_userid(userid.c_str());
        logreq_.set_password(password.c_str());
    }

    //设置获取消息的属性
    string getUserID() const {return logreq_.userid();}
    string getPassWord() const {return logreq_.password();}

    //获取消息的大小
    virtual i32 getMessageSize() {return logreq_.ByteSize();}

    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return logreq_.SerializeToArray(buf, len);}

    //打印测试信息
    virtual std::ostream& dump(std::ostream& os);

protected:
    //关联的消息
    login_request logreq_;
};


//1.2、登录响应事件
class login_response_event : public IEvent
{
public:
    login_response_event(RESPONSE_ID repid) 
        : IEvent(EVENT_ID::LOGIN_RESPONSE)
    {
        logrsp_.set_response_code((i32)repid);
        logrsp_.set_data(get_response_describe(repid));
    }

    //获取及设置消息的属性
    RESPONSE_ID getResponseID() {return (RESPONSE_ID)logrsp_.response_code();}
    string getData() const {return logrsp_.data();}

    //获取消息的大小
    virtual i32 getMessageSize() {return logrsp_.ByteSize();}

    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return logrsp_.SerializeToArray(buf, len);}

    //打印测试信息
    virtual std::ostream& dump(std::ostream& os);

protected:
    //登录响应消息
    login_response logrsp_;
};


//2.1、选择大厅请求事件
class Select_hall_request_event : public IEvent
{
public:
    Select_hall_request_event(u32 hall_no) 
        : IEvent(EVENT_ID::SELECT_HALL_REQUEST) 
    {
        sHall_request_.set_hall_number(hall_no);
    }

    //获取及设置消息的属性
    u32 getHallNo() {return sHall_request_.hall_number();}

    //获取消息的大小
    virtual i32 getMessageSize() {return sHall_request_.ByteSize();}

    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return sHall_request_.SerializeToArray(buf, len);}

    //打印测试信息
    virtual std::ostream& dump(std::ostream& os);

protected:
    //选择大厅的请求消息
    select_hall_request sHall_request_;
};


//2.2、选择大厅响应事件
class Select_hall_response_event : public IEvent
{
public:
    Select_hall_response_event(RESPONSE_ID repid) 
        : IEvent(EVENT_ID::SELECT_HALL_RESPONSE)
    {
        sHall_response_.set_response_code((i32)repid);
        sHall_response_.set_data(get_response_describe(repid));
    }

    //获取及设置消息的属性
    RESPONSE_ID getResponseID() {return (RESPONSE_ID)sHall_response_.response_code();}
    string getData() const {return sHall_response_.data();}

    //获取消息的大小
    virtual i32 getMessageSize() {return sHall_response_.ByteSize();}

    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return sHall_response_.SerializeToArray(buf, len);}

    //打印测试信息
    virtual std::ostream& dump(std::ostream& os);

protected:
    //选择大厅的响应消息
    select_hall_response sHall_response_;
};


//3.1、选择座位请求事件
class Select_table_request_event : public IEvent
{
public:
    Select_table_request_event(u32 table_no) 
        : IEvent(EVENT_ID::SELECT_TABLE_REQUEST) 
    {
        sTable_request_.set_table_number(table_no);
    }

    //获取及设置消息的属性
    u32 getTableNo() {return sTable_request_.table_number();}

    //获取消息的大小
    virtual i32 getMessageSize() {return sTable_request_.ByteSize();}

    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return sTable_request_.SerializeToArray(buf, len);}

    //打印测试信息
    virtual std::ostream& dump(std::ostream& os);

protected:
    //选择大厅的请求消息
    select_table_request sTable_request_;
};


//3.2、选择座位响应事件
class Select_table_response_event : public IEvent
{
public:
    Select_table_response_event(RESPONSE_ID repid) 
        : IEvent(EVENT_ID::SELECT_TABLE_RESPONSE)
    {
        sTable_response_.set_response_code((i32)repid);
        sTable_response_.set_data(get_response_describe(repid));
    }

    //获取及设置消息的属性
    RESPONSE_ID getResponseID() {return (RESPONSE_ID)sTable_response_.response_code();}
    string getData() const {return sTable_response_.data();}

    //获取消息的大小
    virtual i32 getMessageSize() {return sTable_response_.ByteSize();}

    //序列化数据
    virtual bool SerializeToArray(char* buf, i32 len) {return sTable_response_.SerializeToArray(buf, len);}

    //打印测试信息
    virtual std::ostream& dump(std::ostream& os);

protected:
    //选择大厅的响应消息
    select_table_response sTable_response_;
};


//退出事件
class Quit_event : public IEvent
{
public:
    Quit_event() : IEvent(EVENT_ID::QUIT_EVENT) {}
    virtual ~Quit_event() {}
};


//----------------------------------------------------------------------------------

//下棋事件


















#endif