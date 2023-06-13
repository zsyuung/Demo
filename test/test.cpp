#include "test.h"
#include "ievent.h"
#include "events.h"
#include "thread_pool.h"
#include "dispatchmsgserver.h"
#include "networkinterface.h"
#include "mysql/mysql.h"
#include <memory>
#include <unistd.h>
#include "sqlconnection.h"
#include "sqlrecords.h"
#include "sqltable.h"
#include <iostream>
#include "handlers.h"
#include "bussinessproc.h"
#include "playingchess.h"
#include "chess_handler.h"

//测试请求响应的描述
void Test::test_get_response_descirbes()
{
    cout << get_response_describe(RESPONSE_ID::ERRC_SUCCESS) << endl;
    cout << get_response_describe(RESPONSE_ID::ERRC_FAILURE) << endl;
    cout << get_response_describe(RESPONSE_ID::ERRC_UNKONWN) << endl;
    cout << get_response_describe(RESPONSE_ID::ERRC_NULL)    << endl;
}

//测试事件
void Test::test_events()
{
    //登录事件
    login_request_event lreqev("chris", "123@456");
    lreqev.dump(cout);
    login_response_event lresev(RESPONSE_ID::ERRC_SUCCESS);
    lresev.dump(cout);

    //选择大厅事件
    Select_hall_request_event shreq(10);
    shreq.dump(cout);
    Select_hall_response_event shares(RESPONSE_ID::ERRC_FAILURE);
    shares.dump(cout);

    //选择桌子事件
    Select_table_request_event streq(20);
    streq.dump(cout);
    Select_table_response_event stres(RESPONSE_ID::ERRC_NULL);
    stres.dump(cout);

    //退出事件
    Quit_event quit;
    quit.dump(cout);
}


//测试事件处理函数
void Test::test_User_info_handler()
{
    Iniconfig* config = Iniconfig::getInstance();
    config->loadfile("./conf/kaohe_chess.ini");

    IEvent* ev = nullptr;

    //登录事件 -> 成功版
    login_request_event lreqev("chris", "123@456");
    //登录事件 -> 失败版
    // login_request_event lreqev("chris", "123@777");

    //创建处理用户信息事件的处理函数对象
    User_info_handler userhandler;
    //处理登录请求事件
    cout << userhandler.getHandlerName() << endl;
    ev = userhandler.handler(&lreqev);
    //打印登录响应事件的信息
    ev->dump(cout);

    //选择大厅事件 -> 成功版
    Select_hall_request_event shreq(2);
    //选择大厅事件 -> 失败版
    // Select_hall_request_event shreq(5);

    //选择桌子事件 -> 成功版
    Select_table_request_event streq(1);
    //选择桌子事件 -> 失败版
    // Select_table_request_event streq(2);

    //创建处理游戏信息事件的处理函数对象
    Game_info_handler gamehandler;

    //处理大厅请求事件
    cout << gamehandler.getHandlerName() << endl;
    ev = gamehandler.handler(&shreq);
    //打印大厅响应事件的信息
    ev->dump(cout);

    //处理桌子请求事件
    ev = gamehandler.handler(&streq);
    //打印桌子响应事件的信息
    ev->dump(cout);

}



//测试事件处理函数的注册机制
void Test::test_register()
{
    DispatchMsgServer* dms = DispatchMsgServer::getInstance();
    cout << dms->getSubscribe_().empty() << endl;

    User_info_handler* uih = new User_info_handler;
    User_info_handler* uih1 = new User_info_handler;

    {
        User_info_handler* uih = new User_info_handler;
        delete uih;
    }

    delete uih1;
    delete uih;

    cout << dms->getSubscribe_().empty() << endl;
}


//测试线程池结合事件处理函数
void Test::test_thread_pool()
{
    Iniconfig* config = Iniconfig::getInstance();
    config->loadfile("./conf/kaohe_chess.ini");

    //模拟登录的请求事件
    login_request_event lreqev("chris", "123@456");

    //模拟选择大厅请求
    Select_hall_request_event shreq(2);

    //模拟选择桌子请求
    Select_table_request_event streq(1);

    //订阅处理事件的函数
    User_info_handler* uih = new User_info_handler;
    Game_info_handler* gih = new Game_info_handler;

    //创建事件处理分发器
    DispatchMsgServer* dms = DispatchMsgServer::getInstance();
    //开启线程池
    dms->open_pool();

    sleep(1);

    //投递事件
    dms->createAndPostTask((IEvent*)&lreqev);
    //投递事件
    dms->createAndPostTask((IEvent*)&shreq);
    //投递事件
    dms->createAndPostTask((IEvent*)&streq);

    sleep(1);

    //查看响应事件
    queue<IEvent*> queue = dms->getQueue();
    while(!queue.empty())
    {
        cout << "-----------------------------------------------------------------" << endl;
        IEvent* ev = queue.front();
        ev->dump(cout);
        queue.pop();
    }
    cout << "-----------------------------------------------------------------" << endl;
}   


//测试建立网络监听建立及回调
//本次测试 telnet 192.168.124.129 50000
void Test::test_evcent_listener()
{
    DispatchMsgServer* dms = DispatchMsgServer::getInstance();
    dms->open_pool();
    
    NetworkInterface ntf;
    ntf.open_networkinterface();
    
    while(1)
    {
        ntf.network_diapatch();
    }
}


//测试网络接口接受数据后生成事件并处理事件
void Test::test_evcent_DMSNIF()
{
    Iniconfig* config = Iniconfig::getInstance();
    config->loadfile("./conf/kaohe_chess.ini");

    //订阅处理事件的函数
    User_info_handler* uih = new User_info_handler;
    Game_info_handler* gih = new Game_info_handler;

    //创建事件处理分发器
    DispatchMsgServer* dms = DispatchMsgServer::getInstance();
    //开启线程池
    dms->open_pool();

    sleep(1);

    //创建网络接口对象
    NetworkInterface nif;
    //开启网络
    nif.open_networkinterface();
    while(1)
    {
        //开启libevent
        nif.network_diapatch();
#if 1
        //查看结果队列有没有数据
        if(!dms->getQueue().empty())
        {
            //查看响应事件
            while(!dms->getQueue().empty())
            {
                cout << "-----------------------------------------------------------------" << endl;
                IEvent* ev = dms->getQueue().front();
                ev->dump(cout);
                dms->getQueue().pop();
                delete ev;
            }
            cout << "-----------------------------------------------------------------" << endl;
        }
#endif
    }
}


//测试解析文件启动mysql
// void Test::test_iniparser_mysql()
// {
//     #define ini_file_path "../conf/kaohe_chess.ini"

//     Iniconfig* config = Iniconfig::getInstance();
//     config->loadfile(ini_file_path);

//     const string ip = config->getconfig().db_ip; 
//     u32 port = config->getconfig().db_port;
//     const string user = config->getconfig().db_user;
//     const string pwd = config->getconfig().db_pwd;
//     const string db_name = config->getconfig().db_name;

//     MYSQL* mysql;
//     if ((mysql = mysql_init(nullptr)) == NULL)
//     {
//         cout << "数据库初始化失败" << endl;
//         return;
//     }

//     MYSQL* ret = mysql_real_connect(mysql, "127.0.0.1", "root", "12345", nullptr, 3306, nullptr, 0);
//     if(ret == nullptr)
//     {
//         cout << "数据库连接失败" << endl;
//     }
//     else
//     {
//         cout << "数据库连接成功" << endl;
//     }
//     mysql_close(mysql);

// }


void Test::test_dml_ddl_mysql()
{
    // #define ini_file_path "./conf/kaohe_chess.ini"

    Iniconfig* config = Iniconfig::getInstance();
    // config->loadfile(ini_file_path);

    const string ip = config->getconfig().db_ip; 
    u32 port = config->getconfig().db_port;
    const string user = config->getconfig().db_user;
    const string pwd = config->getconfig().db_pwd;
    const string db_name = config->getconfig().db_name;

    //创建连接数据库对象
    shared_ptr<MysqlConnection> sqlconn(new MysqlConnection);
    //初始化数据库
    sqlconn->Init(ip.c_str(), port, user.c_str(), pwd.c_str(), db_name.c_str());
    //数据库表加载
    SqlTable sqt = SqlTable(sqlconn);
    sqt.CreateGameInfo();
    sqt.CreateTableInfo();
    sqt.CreateUserInfo();

#if 0
    //插入数据测试
    const char* insert_data = "\
                INSERT INTO userinfo (mobile, username, password) values('15678945600', 'chris', '123@456');  \
                ";
    if(sqlconn->Execute(insert_data) == false)
    {
        LOG_ERROR("插入数据失败\n");
        return;
    }

    //插入数据测试
    const char* insert_hall_data = "\
                INSERT INTO hallinfo (onlines, hallname, gamename) values('123', 'WZQ', 'wuziqi');  \
                ";
    if(sqlconn->Execute(insert_hall_data) == false)
    {
        LOG_ERROR("插入数据失败\n");
        return;
    }

    //插入数据测试
    const char* insert_table_data = "\
                INSERT INTO tableinfo (tablename, onlines) values('XZZ', '012');  \
                ";
    if(sqlconn->Execute(insert_table_data) == false)
    {
        LOG_ERROR("插入数据失败\n");
        return;
    }
#endif

    //获取数据测试
    const char* select_data = "\
                select id, username, password, mobile, time(registertm) date from userinfo;  \
                ";
    //数据结果操作对象
    MysqlRecords record_set;

    //查询数据
    if(sqlconn->Execute(select_data, record_set) == false)
    {
        LOG_ERROR("获取数据失败\n");
        return;
    }

    //结果集的列名
    MYSQL_FIELD* filds = record_set.getFiles();
    for(int i = 0; i < record_set.GetFildsNum(); i++)
    {
        cout << filds[i].name << "   ";
    }
    cout << endl;

    cout << "------------------------------------------------------" << endl;;

    //获取每一行的所有列的数据
    MYSQL_ROW mRow1;
    for(int i = 0; i < record_set.GetRowCount(); i++)
    {
        record_set.FetchRow(mRow1);
        for(int j = 0; j < record_set.GetFildsNum(); j++)
        {
            cout << mRow1[j] << " ";
        }
        cout << endl;
    }
}

//测试整个服务器的运行
void Test::test_bussiness_processor()
{
    #define ini_file_path "../conf/kaohe_chess.ini"
    
    //初始化配置文件
    Iniconfig* config = Iniconfig::getInstance();
    if(config->loadfile(ini_file_path) == false)
    {
        cout << "初始化配置文件失败" << endl;
    }

    //启动mysql
    shared_ptr<MysqlConnection> mysqlconn(new MysqlConnection);
    mysqlconn->Init(config->getconfig().db_ip.c_str(), config->getconfig().db_port,
                    config->getconfig().db_user.c_str(), config->getconfig().db_pwd.c_str(),
                    config->getconfig().db_name.c_str());


    //初始化mysql数据库、注册客户端请求处理函数
    BussinessProc bussiness(mysqlconn);
    bussiness.init();

    //创建事件处理分发器
    DispatchMsgServer* dms = DispatchMsgServer::getInstance();
    //开启线程池
    dms->open_pool();

    //创建网络接口对象
    NetworkInterface nif;
    //开启网络
    nif.open_networkinterface();
    while(1)
    {
        //开启libevent
        nif.network_diapatch();
    }

    nif.close_networkinterface();
    dms->close_pool();
}


//测试下棋事件
void Test::test_chess_events()
{
    chess_playing_request chess_play_req(1, 2);
    chess_play_req.dump(cout);

    chess_playing_response chess_play_rsp(RESPONSE_ID::ERRC_SUCCESS, 0);
    chess_play_rsp.dump(cout);

    Chess_battle_handler chess_hander;
    chess_hander.handler((IEvent*)&chess_play_req);
}


