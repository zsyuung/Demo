#ifndef KAOHE_CHESS_H
#define KAOHE_CHESS_H

// #include "eventtype.h"
// #include "events.h"
// #include "ievent.h"
// #include "handlers.h"
// #include "ihandlers.h"
#include "iniconfig.h"


using namespace std;


class Test
{
public:
    Test() {}
    virtual ~Test() {}

    //测试请求响应的描述
    static void test_get_response_descirbes();

    //测试事件
    static void test_events();

    //测试事件处理函数
    static void test_User_info_handler();

    //测试事件处理函数的注册机制
    static void test_register();

    //测试线程池结合事件处理函数
    static void test_thread_pool();

    //测试建立网络监听建立及回调
    static void test_evcent_listener();

    /*
        测试网络接口接受数据后生成事件并处理事件
        需要客户端进行配合验证
        测试内容：
                1、登录验证
                2、选择大厅
                3、选择桌子
    */
    static void test_evcent_DMSNIF();

    //测试mysql创建表、插入表及查询表
    static void test_dml_ddl_mysql();

    //测试业务处理类
    static void test_bussiness_processor();

    //测试下棋事件
    static void test_chess_events();

    //测试两个客户端进行下棋
    static void test_chess();


};







#endif