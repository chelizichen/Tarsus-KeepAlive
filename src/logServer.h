#include <iostream>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>
#include <mysql.h>

using namespace std;

namespace logServerParams
{
    struct db_config {
        unsigned int port;
        char host;
        char user;
        char password;
        char dbName;
    };

    struct init {
        unsigned int port;
        db_config dbConfig;
    };
} // namespace logServerParams

#ifndef logServer_H
#define logServer_H

class logServer
{
private:
    /* data */
    unsigned int listen_port = 8080;
    logServerParams::init initConfig;

public:
    logServer(logServerParams::init initConfig);
    logServer();
    ~logServer();
    void watch_port();
    void watch_port_thread_fn();
    void initDataBase();
};
//
logServer::logServer(logServerParams::init initConfig){
    this->initConfig = initConfig;
    this->initDataBase();

    watch_port_thread_fn();
}

void logServer::initDataBase(){
    MYSQL *conn = mysql_init(nullptr);
    MYSQL *conn_ptr;

    conn_ptr = mysql_init(NULL);

    if (!conn_ptr) {
        fprintf(stderr, "init failed\n");
    }

    conn_ptr = mysql_real_connect(conn_ptr,//mysql
                                  "localhost", //host
                                  "root",//user
                                  "12345678",//password : 你的数据库密码
                                  "test_db",//db : 你的数据库名称
                                  3306,//port （default）
                                  NULL,//unix_socket
                                  0//clientflag (最后两个参数填写NULL,0即可)
    );//连接数据库
    if (conn_ptr) {
        printf("connection success\n");

        // 执行查询
        const char *query = "SELECT * FROM table1";
        if (mysql_query(conn_ptr, query) == 0) {
            MYSQL_RES *result = mysql_store_result(conn_ptr);
            if (result != nullptr) {
                int numFields = mysql_num_fields(result);
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result))) {
                    for (int i = 0; i < numFields; ++i) {
                        if (row[i]) {
                            std::cout << row[i] << " ";
                        } else {
                            std::cout << "NULL ";
                        }
                    }
                    std::cout << std::endl;
                }
                mysql_free_result(result);
            }
        } else {
            std::cerr << "Query error: " << mysql_error(conn_ptr) << std::endl;
        }
    } else {
        printf("connection failed\n");
    }

    mysql_close(conn_ptr);
}

logServer::logServer(){
    initDataBase();
    watch_port_thread_fn();
}

void logServer::watch_port_thread_fn(){
    // 创建并启动定时循环线程
    bool running = true;
    std::thread timer([&running, this]() {
        while (running) {
            watch_port(); // 定时执行 watch_port 方法
            std::this_thread::sleep_for(std::chrono::seconds(5)); // 定时间隔为 5 秒
        }
    });

    // 主线程运行一段时间
    std::this_thread::sleep_for(std::chrono::seconds(10)); // 主线程运行 20 秒

    // 停止定时循环线程
    running = false;
    timer.join();
}

void logServer::watch_port()
{

    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), listen_port));
        std::cout << "Port is active and available." << std::endl;
    } catch (const boost::system::system_error&) {
        std::cout << "Port is not available." << std::endl;
    }
}

logServer::~logServer()
{
}

#endif

