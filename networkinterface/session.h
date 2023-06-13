#ifndef KAOHE_SESSION_H
#define KAOHE_SESSION_H

#include "glo_def.h"
#include "event.h"
#include "ievent.h"
#include "event2/event.h"

#define BUFSIZE 256


//会话状态
enum class SESSION_STAT
{
    REQUEST_SESSION  = 0x01,
    RESPONSE_SESSION = 0x02
};


//会话数据[接受/发送]状态
enum class MESSAGE_STAT
{
    MESSAGE_READING_HEAD       = 0x00,
    MESSAGE_READING_HEAD_DONE  = 0x01,
    MESSAGE_READING            = 0x02,
    MESSAGE_READING_DONE       = 0x03,
    MESSAGE_SENDING            = 0x04,
    MESSAGE_SEND_DONE          = 0x05
};


#define HEAD_LEN    10
#define HEAD_MAEK   "CHES"
#define IP_LEN      16


//会话结构体
typedef struct session_
{
    i32 fd;                     //客户端套接字
    char ip[IP_LEN];            //客户端ip

    struct bufferevent* bev;    //绑定缓冲事件的指针

    EVENT_ID eid;               //事件ID

    SESSION_STAT session_stat;
    IEvent* request_event;      //请求事件的指针
    MESSAGE_STAT message_stat;
    IEvent* response_event;     //响应事件的指针

    char header[HEAD_LEN + 1];  //头部数据
    i32 read_head_len;          //头部已经读取的数据
    
    i32 message_len;            //待读取数据的长度
    i32 message_read_len;       //已经读到的数据长度
    char* read_message;         //读取数据的指针

    i32 send_message_len;       //已经发送的数据
    char* send_message;         //发送数据的指针

}session;













#endif