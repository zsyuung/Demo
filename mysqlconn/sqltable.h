#ifndef KAOHE_SQLTABLE_H
#define KAOHE_SQLTABLE_H

#include <memory>
#include "sqlconnection.h"


class SqlTable
{
public:
    SqlTable(std::shared_ptr<MysqlConnection> sqlconn) : sqlconn_(sqlconn) {}
    ~SqlTable() {}

    //创建用户表
    bool CreateUserInfo()
    {
        const char* pUserInfoTable = "\
                        CREATE TABLE IF NOT EXISTS userinfo(                                \
                        id          int(16)         NOT NULL primary key auto_increment,    \
                        mobile      varchar(16)     NOT NULL default '18000000000',         \
                        username    varchar(128)    NOT NULL default '',                    \
                        password    varchar(128)    NOT NULL default '',                    \
                        registertm  timestamp       NOT NULL default CURRENT_TIMESTAMP      \
                        );";

        if(sqlconn_->Execute(pUserInfoTable) == false)
        {
            LOG_ERROR("SqlTable::CreateUserInfo 创建用户信息表失败\n");
            return false;
        }

        return true;
    }

    //创建游戏大厅内容表
    bool CreateGameInfo()
    {
        const char* pGameInfoTable = "\
                        CREATE TABLE IF NOT EXISTS hallinfo(                                \
                        hallid          int(16)     NOT NULL primary key auto_increment,    \
                        hallname    varchar(128)    NOT NULL default '',                    \
                        gamename    varchar(128)    NOT NULL default '',                    \
                        onlines     varchar(128)    NOT NULL default ''                     \
                        );";

        if(sqlconn_->Execute(pGameInfoTable) == false)
        {
            LOG_ERROR("SqlTable::CreateUserInfo 创建游戏大厅信息表失败\n");
            return false;
        }

        return true;
    }

    //创建游戏桌子内容表
    bool CreateTableInfo()
    {
        const char* pTableInfoTable = "\
                        CREATE TABLE IF NOT EXISTS tableinfo(                                \
                        tableid          int(16)     NOT NULL primary key auto_increment,    \
                        tablename    varchar(128)    NOT NULL default '',                    \
                        onlines      varchar(128)    NOT NULL default ''                     \
                        );";

        if(sqlconn_->Execute(pTableInfoTable) == false)
        {
            LOG_ERROR("SqlTable::CreateUserInfo 创建游戏桌子信息表失败\n");
            return false;
        }

        return true;
    }

private:
    std::shared_ptr<MysqlConnection> sqlconn_;
};



#endif