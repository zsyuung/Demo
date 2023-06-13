#ifndef KAOHE_EVENTTYPE_H
#define KAOHE_EVENTTYPE_H

#include <iostream>
#include "glo_def.h"

//事件编号
enum class EVENT_ID
{
    //未定义
    NO_DEFINED_EVENT       =   0x00,

    //登录事件
    LOGIN_REQUEST          =   0x01,
    LOGIN_RESPONSE         =   0x02,

    //选择大厅事件
    SELECT_HALL_REQUEST    =   0x03,
    SELECT_HALL_RESPONSE   =   0x04,

    //选择桌子事件
    SELECT_TABLE_REQUEST   =   0x05,
    SELECT_TABLE_RESPONSE  =   0x06,

    //下棋事件
    PLAYING_CHESS_REQUEST  =   0x07,
    PLAYING_CHESS_RESPONSE =   0x08,

    //其他事件
    OTHERS                 =   0xfe,

    //退出事件
    QUIT_EVENT             =   0xff
};

//客户端接受请求之后对事件[响应结果的编号]
enum class RESPONSE_ID
{
    ERRC_SUCCESS = 200,
    ERRC_FAILURE = 300,
    ERRC_UNKONWN = 400,
    ERRC_NULL    = 0
};

//对[响应结果的编号]的描述
typedef struct response_describe_
{
    RESPONSE_ID rid_;
    const std::string describe_;
}response_describe;

//获取响应结果编号的描述
const std::string get_response_describe(RESPONSE_ID rid);




#endif