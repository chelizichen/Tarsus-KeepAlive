cmake_minimum_required(VERSION 3.26)
project(Tarsus_KeepAlive)

set(CMAKE_CXX_STANDARD 11)

#set(MYSQL_HEADER "/usr/local/mysql-8.0.33-macos13-arm64/include")
#set(MYSQL_LIB "/usr/local/mysql-8.0.33-macos13-arm64/lib")

set(BOOST_ROOT "/usr/local/include/boost")


# 添加头文件搜索路径
include_directories(/usr/local/include)
include_directories(/usr/local/mysql/include)

# 添加库文件搜索路径
link_directories(/usr/local/lib)
link_directories(/usr/local/mysql/lib)


add_executable(Tarsus_KeepAlive
        src/logServer.h
        main.cpp)
target_link_libraries(Tarsus_KeepAlive mysqlclient)