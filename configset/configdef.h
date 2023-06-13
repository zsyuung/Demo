#ifndef KAOHE_CONFIGDEF_H
#define KAOHE_CONFIGDEF_H

#include "glo_def.h"
#include <string>

/*
    项目配置的结构体
*/

typedef struct st_env_config_
{
    //数据库的配置
    std::string db_ip;
    u16         db_port;
    std::string db_user;
    std::string db_pwd;
    std::string db_name;

    //服务器的配置
    u16         svr_port;

    st_env_config_() {}

    st_env_config_(const std::string& db_ip, const u16 db_port, const std::string& db_user, \
                   const std::string& db_pwd, const std::string& db_name, u16 svr_port) 
    {
        this->db_ip    = db_ip;
        this->db_port  = db_port;
        this->db_user  = db_user;
        this->db_pwd   = db_pwd;
        this->db_name  = db_name;
        this->svr_port = svr_port;
    }

    st_env_config_& operator=(const st_env_config_& config)
   {
       if (this != &config)
       {
                   this->db_ip    = config.db_ip;
                   this->db_port  = config.db_port;
                   this->db_user  = config.db_user;
                   this->db_pwd   = config.db_pwd;
                   this->db_name  = config.db_name;
                   this->svr_port = config.svr_port;

        }
        return *this;
    }


}st_env_config;





#endif