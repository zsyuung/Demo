#cmake版本
cmake_minimum_required(VERSION 3.0.0)

#项目名字
project(chess)

#设置编译器的标准
set("${CMAKE_CXX_FLAGS} -std=c++11")

#包含头文件
include_directories(${PROJECT_SOURCE_DIR}/events)
include_directories(${PROJECT_SOURCE_DIR}/protodir)
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/handlers)
include_directories(${PROJECT_SOURCE_DIR}/threadpool)
include_directories(${PROJECT_SOURCE_DIR}/dispatchmsgserver)
include_directories(${PROJECT_SOURCE_DIR}/networkinterface)
include_directories(${PROJECT_SOURCE_DIR}/configset)
include_directories(${PROJECT_SOURCE_DIR}/include/iniparser)
include_directories(${PROJECT_SOURCE_DIR}/mysqlconn)
include_directories(${PROJECT_SOURCE_DIR}/bussiness)
include_directories(${PROJECT_SOURCE_DIR}/test)   #测试使用

#搜索源文件保存到src里面
aux_source_directory(${PROJECT_SOURCE_DIR} src)
aux_source_directory(${PROJECT_SOURCE_DIR}/protodir src)
aux_source_directory(${PROJECT_SOURCE_DIR}/events src)
aux_source_directory(${PROJECT_SOURCE_DIR}/handlers src)
aux_source_directory(${PROJECT_SOURCE_DIR}/threadpool src)
aux_source_directory(${PROJECT_SOURCE_DIR}/dispatchmsgserver src)
aux_source_directory(${PROJECT_SOURCE_DIR}/networkinterface src)
aux_source_directory(${PROJECT_SOURCE_DIR}/configset src)
aux_source_directory(${PROJECT_SOURCE_DIR}/bussiness src)
aux_source_directory(${PROJECT_SOURCE_DIR}/test src)  #测试使用

#连接三方静态库
link_directories(${PROJECT_SOURCE_DIR}/libs/iniparser)
link_directories(/usr/include/mysql)

set(MYSQL_LIBS mysqlclient pthread dl ssl crypto resolv m rt)

#生成可执行程序
add_executable(chess ${src})

#连接到库
target_link_libraries(chess protobuf iniparser event pthread)
target_link_libraries(chess ${MYSQL_LIBS})
