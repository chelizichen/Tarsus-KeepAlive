#include <iostream>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>
#include <string>
#include <mysql/mysql.h>

using namespace std;

namespace logServerParams
{
    struct init {
        unsigned int port;
        db_config dbConfig;
    };

    struct db_config {
        unsigned int port;
        char host;
        char user;
        char password;
        char dbName;
    };
} // namespace logServerParams



class logServer
{
private:
    /* data */
    unsigned int port = 8080;
    logServerParams::init initConfig;
    MYSQL *conn;
public:
    logServer(logServerParams::init initConfig);
    logServer();
    ~logServer();
    void watch_port();
    void watch_port_thread_fn();
    void initDataBase();
};

logServer::logServer(logServerParams::init initConfig){
    this->initConfig = initConfig;
    this->initDataBase();
    
    watch_port_thread_fn();
}

void logServer::initDataBase(){
    conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "mysql_init failed." << std::endl;
    }
    // 连接到本地 MySQL 数据库
    const char *host = &this->initConfig.dbConfig.host;
    const char *user = &this->initConfig.dbConfig.user; // 替换为您的 MySQL 用户名
    const char *password = &this->initConfig.dbConfig.user; // 替换为您的 MySQL 密码
    const char *dbname = &this->initConfig.dbConfig.dbName; // 替换为您的数据库名称
    unsigned int port = this->initConfig.dbConfig.port; // 默认 MySQL 端口号

    if (mysql_real_connect(conn, host, user, password, dbname, port, nullptr, 0) == nullptr) {
        std::cerr << "mysql_real_connect failed: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
    }
}

logServer::logServer(){
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
    std::this_thread::sleep_for(std::chrono::seconds(20)); // 主线程运行 20 秒

    // 停止定时循环线程
    running = false;
    timer.join();
}

void logServer::watch_port()
{

    try {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
        std::cout << "Port is active and available." << std::endl;
    } catch (const boost::system::system_error&) {
        std::cout << "Port is not available." << std::endl;
    }
}

logServer::~logServer()
{
}