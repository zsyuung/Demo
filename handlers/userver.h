#ifndef KAOHE_USER_H
#define KAOHE_USER_H

#include <memory>
#include "sqlrecords.h"
#include "sqlconnection.h"

class UserServer
{
public:
    UserServer(std::shared_ptr<MysqlConnection> sqlconn) : sqlconn_(sqlconn) {};
    ~UserServer() {}

    bool user_exsist(std::string user, std::string password)
    {
        MysqlRecords mRes;
        
        char sql[1024] = {0};
        sprintf(sql, "\
                select id from userinfo where username = '%s' and password = '%s';", 
                user.c_str(), password.c_str());
        
        if(sqlconn_->Execute(sql, mRes) == false)
        {
            LOG_DEBUG("查询结果失败\n");
            return false;
        }

        return (mRes.GetRowCount() != 0);
    }   

public:
    std::shared_ptr<MysqlConnection> sqlconn_;
};


class GameServer
{
public:
    GameServer(std::shared_ptr<MysqlConnection> sqlconn) : sqlconn_(sqlconn) {};
    ~GameServer() {}

    bool hall_exsist(u32& hall_no)
    {
        MysqlRecords mRes;
        
        char sql[1024] = {0};
        sprintf(sql, "\
                select hallname from hallinfo where hallid = %d;", 
                hall_no);
        
        if(sqlconn_->Execute(sql, mRes) == false)
        {
            LOG_DEBUG("查询结果失败\n");
            return false;
        }

        return (mRes.GetRowCount() != 0);
    }   

    bool table_exsist(u32& table_no)
    {
        MysqlRecords mRes;
        
        char sql[1024] = {0};
        sprintf(sql, "\
                select tablename from tableinfo where tableid = %d;", 
                table_no);
        
        if(sqlconn_->Execute(sql, mRes) == false)
        {
            LOG_DEBUG("查询结果失败\n");
            return false;
        }

        return (mRes.GetRowCount() != 0);
    }   

public:
    std::shared_ptr<MysqlConnection> sqlconn_;
};






#endif