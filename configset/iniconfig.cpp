#include "iniconfig.h"
#include "iniparser.h"
#include "dictionary.h"
#include "glo_def.h"


Iniconfig* Iniconfig::config = nullptr;

Iniconfig::Iniconfig():is_loaded_(false)
{
}

Iniconfig::~Iniconfig() 
{
}

Iniconfig* Iniconfig::getInstance()
{
    if(config == nullptr)
    {
        config = new Iniconfig;
    }
    return config;
}

bool Iniconfig::loadfile(const std::string& path)
{
    if(is_loaded_ == false)
    {
        dictionary* ini = nullptr;

        ini = iniparser_load(path.c_str());
        if(ini == nullptr)
        {
            fprintf(stderr, "iniparser_load初始化配置文件<%s>失败\n", path.c_str());
            return false ;
        }

        const char* ip    = iniparser_getstring(ini, "database:ip", "127.0.0.1");
        const u32   port  = iniparser_getint(ini, "database:port", 3306);
        const char* user  = iniparser_getstring(ini, "database:user", "root");
        const char* pwd   = iniparser_getstring(ini, "database:pwd", "12345");
        const char* db    = iniparser_getstring(ini, "database:db", "kaohe_chess");
        const i32   sport = iniparser_getint(ini, "server:port", 50000);

        config_ = st_env_config(ip, port, user, pwd, db, sport);

        iniparser_freedict(ini);

        is_loaded_ = true;
    }

    return is_loaded_;
}

const st_env_config& Iniconfig::getconfig()
{
    return config_;
}
