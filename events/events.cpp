#include "events.h"


//1.1、选择登录请求的测试
std::ostream& login_request_event::dump(std::ostream& os)
{
    IEvent::dump(os);
    os << "登录请求：" << std::endl
       << "账号：" << logreq_.userid() << " "
       << "密码：" << logreq_.password();
    os << std::endl;
    return os;
}

//1.2、选择登录响应的测试
std::ostream& login_response_event::dump(std::ostream& os)
{
    IEvent::dump(os);
    os << "响应的类型 RESPONSE_ID:" << (u32)logrsp_.response_code() << " " << logrsp_.data();
    os << std::endl;
    return os;
}

//2.1、选择大厅请求的测试
std::ostream& Select_hall_request_event::dump(std::ostream& os)
{
    IEvent::dump(os);
    os << "选择的大厅：" << sHall_request_.hall_number() << std::endl;
    return os;
}

//2.2、选择大厅响应的测试
std::ostream& Select_hall_response_event::dump(std::ostream& os)
{
    IEvent::dump(os);
    os << "响应的类型 RESPONSE_ID:" << (u32)sHall_response_.response_code() << " " << sHall_response_.data();
    os << std::endl;
    return os;
}

//3.1、选择座位请求的测试
std::ostream& Select_table_request_event::dump(std::ostream& os)
{
    IEvent::dump(os);
    os << "选择的座位：" << sTable_request_.table_number() << std::endl;
    return os;
}

//3.2、选择座位响应的测试
std::ostream& Select_table_response_event::dump(std::ostream& os)
{
    IEvent::dump(os);
    os << "响应的类型 RESPONSE_ID:" << (i32)sTable_response_.response_code() << " " << sTable_response_.data();
    os << std::endl;
    return os;
}

