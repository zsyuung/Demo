#ifndef KAOHE_INICONFIG_H
#define KAOHE_INICONFIG_H

#include <cstring>
#include "configdef.h"

/*
    对配置文件进行解析 -> 单例
*/
class Iniconfig
{
protected:
    Iniconfig();

public:
    ~Iniconfig();
    static Iniconfig* getInstance();
    bool loadfile(const std::string& path);
    const st_env_config& getconfig();

private:
    st_env_config config_;
    bool is_loaded_;
    static Iniconfig* config;
};





#endif