#ifndef KAOHE_SQLRECORD_H
#define KAOHE_SQLRECORD_H

#include "glo_def.h"
#include <mysql/mysql.h>
#include <assert.h>


class MysqlRecords
{
public:
    MysqlRecords() : mRes_(nullptr) {}
    
    MysqlRecords(MYSQL_RES* mRes) : mRes_(mRes) {}

    ~MysqlRecords() 
    {
        if(mRes_)
        {
            mysql_free_result(mRes_);
        }
    }

    //获取/设置数据库结果集
    MYSQL_RES* MysqlRes()
    {
        return mRes_;
    }

    void SetResult(MYSQL_RES* mRes)
    {
        if(mRes_)
        {
            LOG_ERROR("MysqlRecords::SetResult 结果集已经设置 不为空\n");
            return;
        }
        mRes_ = mRes;
    }

    //获取数据库结果集
    void FetchRow(MYSQL_ROW& row)
    {
        row = mysql_fetch_row(mRes_);
    }

    //获取数据库查询结果数量
    i32  GetRowCount()
    {
        return mRes_->row_count;
    }

    //获取结果集的列数
    i32 GetFildsNum()
    {
        return mysql_num_fields(mRes_);
    }

    //获取结果集的所有列的名字
    MYSQL_FIELD* getFiles()
    {
        MYSQL_FIELD* fields = mysql_fetch_fields(mRes_);
        return fields;
    }

private:
    //结果结构体
    MYSQL_RES* mRes_;    
};






#endif