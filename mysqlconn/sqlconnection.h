#ifndef KAOHE_SQLCONNECTION_H
#define KAOHE_SQLCONNECTION_H

#include "glo_def.h"
#include <mysql/mysql.h>
#include <cstring>
#include <mysql/errmsg.h>
#include "sqlrecords.h"


class MysqlConnection
{
public:
    MysqlConnection():mysql_(nullptr) 
    {
        mysql_ = new MYSQL;
    }

    virtual ~MysqlConnection()
    {
        if(mysql_ == nullptr)
        {
            mysql_close(mysql_);
            delete mysql_;
            mysql_ = nullptr;
        }
    }

    //返回数据库句柄
    MYSQL* MySql() 
    {
        return mysql_;
    }
    
    //初始化句柄并连接数据库
    bool Init(const char* host, i32 port, const char* user, const char* pwd, const char* dbname)
    {
        //初始化句柄 否则出现段错误
        if ((mysql_ = mysql_init(mysql_)) == NULL)
        {
            LOG_ERROR("MysqlConnection::Init 数据库句柄初始化失败 %s, %d\n", this->GetErrInfo(), errno);
            return false;
        }

        //设置字符集
        if(mysql_options(mysql_, MYSQL_SET_CHARSET_NAME, "gbk") != 0)
        {
            LOG_ERROR("MysqlConnection::mysql_options 数据库设置字符集失败 %s, %d\n", this->GetErrInfo(), errno);
            return false;
        }

        //设置重新连接
        if(mysql_options(mysql_, MYSQL_OPT_RECONNECT, "1") != 0)
        {
            LOG_ERROR("MysqlConnection::mysql_options 数据库设置重新连接失败 %s, %d\n", this->GetErrInfo(), errno);
            return false;
        }

        //连接数据库
        if(mysql_real_connect(mysql_, host, user, pwd, dbname, port, nullptr, 0) == nullptr)
        {
            LOG_ERROR("MysqlConnection::mysql_real_connect 数据库连接失败 %s, %d\n", this->GetErrInfo(), errno);
            return false;
        }

        return true;
    }

    //关闭MySql
    bool Close()
    {
        if(mysql_)
        {
            mysql_close(mysql_);
            delete mysql_;
            mysql_ == nullptr;
        }
        return mysql_ == nullptr;
    }

    //更新语句
    bool Execute(const char* sql)
    {
        if(mysql_real_query(mysql_, sql, strlen(sql)) != 0)
        {
            if(mysql_errno(mysql_) == CR_SERVER_GONE_ERROR)
            {
                Reconnection();
            }
            LOG_ERROR("MysqlConnection::Execute 数据库更新失败\n");
            return false;
        }
        return true;
    }

    //查询语句
    bool Execute(const char* sql, MysqlRecords& mRes)
    {
        if(mysql_real_query(mysql_, sql, strlen(sql)) != 0)
        {
            if(mysql_errno(mysql_) == CR_SERVER_GONE_ERROR)
            {
                Reconnection();
            }
            LOG_ERROR("MysqlConnection::Execute 数据库查询失败\n");
            return false;
        }

        MYSQL_RES* res = mysql_store_result(mysql_);
        if(res == nullptr)
        {
            LOG_ERROR("MysqlConnection::mysql_store_result 数据库获取结果失败\n");
            return false;
        }
        
        mRes.SetResult(res);

        return true;
    }

    //报告错误信息
    const char* GetErrInfo()
    {
        return mysql_error(mysql_);
    }

    //重新连接MySql
    bool Reconnection()
    {
        return mysql_reset_connection(mysql_);
    }

    //转义语句
    int EscapeString(const char* src, u32 len, char* dst)
    {
        return mysql_escape_string(dst, src, len);
    }

private:
    MYSQL* mysql_;
};











#endif