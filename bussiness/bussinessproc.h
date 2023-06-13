#ifndef KAOHE_BUSSNESSPROCESS_H
#define KAOHE_BUSSNESSPROCESS_H

#include "sqlconnection.h"
#include "handlers.h"
#include "sqltable.h"
#include <memory>


/*
    该类负责业务的初始化工作：
        1、负责初始化业务相关的表信息
        2、负责事件处理函数的注册
*/

class BussinessProc
{
public:

    //完成事件处理函数的注册
    BussinessProc(std::shared_ptr<MysqlConnection> sqlconn) : sqlconn_(sqlconn), 
            uih_(new User_info_handler), gih_(new Game_info_handler), cbh_(new Chess_battle_handler) {}

    //时间处理函数的注销
    ~BussinessProc() 
    {
        //智能指针的释放
        uih_.reset();
        gih_.reset();
    }

    //数据库表的初始化
    void init()
    {
        SqlTable table(sqlconn_);
        table.CreateUserInfo();
        table.CreateGameInfo();
        table.CreateTableInfo();
    }


private:
    //数据库的智能指针
    std::shared_ptr<MysqlConnection> sqlconn_;
    //客户端处理用户请求事件的智能指针
    std::shared_ptr<User_info_handler> uih_;
    //客户端处理游戏请求事件的智能指针
    std::shared_ptr<Game_info_handler> gih_;
    //处理下棋事件的智能指针
    std::shared_ptr<Chess_battle_handler> cbh_;
};









#endif