#include "eventtype.h"

//结构体数组
response_describe RSPD_ESC[] =
{
    {RESPONSE_ID::ERRC_SUCCESS, "处理请求成功"},
    {RESPONSE_ID::ERRC_FAILURE, "处理请求失败"},
    {RESPONSE_ID::ERRC_UNKONWN, "未知请求 处理响应失败"},
    {RESPONSE_ID::ERRC_NULL,    "退出事件"},
};

//获取响应结果编号
const std::string get_response_describe(RESPONSE_ID rid)
{
    u32 len = sizeof(RSPD_ESC) / sizeof(RSPD_ESC[0]);
    int i = 0;
    for(; i < len; i++)
    {
        if(RSPD_ESC[i].rid_ == rid)
        {
            return std::string(RSPD_ESC[i].describe_);
        }
    }
    return std::string(RSPD_ESC[i].describe_);
}