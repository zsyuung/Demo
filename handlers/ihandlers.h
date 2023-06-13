#ifndef KAOHE_IHANDLER_H
#define KAOHE_IHANDLER_H

#include "glo_def.h"
#include "ievent.h"

/*
    ihandler是所有处理事件类的基类 
        所有处理事件基类派生于ihandler类
*/

class IHandler
{
public:
    IHandler(std::string name) : name_(name) {}
    virtual ~IHandler() {}

    //设置获取处理函数的名字
    std::string getHandlerName() const {return name_;}

    //处理请求事件 得到响应事件
    virtual IEvent* handler(IEvent* event) {return nullptr;}  

protected:
    std::string name_;
};





#endif