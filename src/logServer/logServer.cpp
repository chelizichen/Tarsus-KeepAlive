#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>

using namespace std;

namespace LogServerParams {
    struct DbConfig {
        string host = "127.0.0.1";
        string port = "3306";
        string userName = "root";
        string password = "123456"; // 修正拼写错误
    };

    struct logServerConfig {
        string serverName;
        DbConfig dbConfig;
    };

    struct contentStruct {
        /* data */
    };

    struct contentConfig {
        /* data */
    };
};

class logServer {
private:
    string name;
    string date;
    string serverName;
    LogServerParams::DbConfig dbConfig;
    bool running_ = false;
    std::thread timer_;

public:
    logServer(LogServerParams::logServerConfig serverConfig);
    ~logServer();
    string getLogName();
    bool Connect2DataBase();
    void Log2DataBase(const std::string& tag, const std::string& message);
    LogServerParams::contentStruct Log2HTML(LogServerParams::contentConfig contentConfig);
    void WatchPort(int port, int intervalSeconds);
    void StartWatchPort(int port, int intervalSeconds);
};

logServer::logServer(LogServerParams::logServerConfig serverConfig)
    : serverName(serverConfig.serverName), dbConfig(serverConfig.dbConfig) {} // 使用成员初始化列表初始化成员变量

logServer::~logServer() {
    running_ = false;
    if (timer_.joinable()) {
        timer_.join();
    }
}

string logServer::getLogName() {
    return this->name + this->date;
}

bool logServer::Connect2DataBase() {
    // 实现数据库连接逻辑
    return true; // 根据实际情况返回连接结果
}

void logServer::WatchPort(int port, int intervalSeconds) {
    std::cout << "-------- START_2_WATCH_PORT --------- "<< std::endl;
    std::chrono::milliseconds interval(intervalSeconds); // 转换为毫秒
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
    std::cout << "-------- AFTER_CREATED_SERVICE --------- "<< std::endl;
    while (running_) {
        std::cout << "-------- BEFORE_LISITENING --------- "<< std::endl;
        try {
            acceptor.accept();
            Log2DataBase("tarsus_keep_alive", "Port is active and available.");
        } catch (const boost::system::system_error&) {
            Log2DataBase("tarsus_keep_alive", "Port is not available.");
        }
        std::cout << "-------- AFTER_LISITENING --------- "<< std::endl;
        std::this_thread::sleep_for(interval);
        
    }
}

void logServer::StartWatchPort(int port, int intervalSeconds) {
    running_ = true;
    timer_ = std::thread(&logServer::WatchPort, this, port, intervalSeconds);
}

void logServer::Log2DataBase(const std::string& tag, const std::string& message) {
    // 实现将日志写入数据库的逻辑
    // 这里只是示例，您需要根据实际情况实现该函数
    std::cout << "-------- Log_START_2_PRINT --------- "<< std::endl;
    std::cout << "[" << tag << "] " << message << std::endl;
}

logServer* LogServerFactory(LogServerParams::logServerConfig config) {
    return new logServer(config);
}

logServer* LogServerFactory(string serverName) {
    LogServerParams::DbConfig getDbConfig = LogServerParams::DbConfig();
    LogServerParams::logServerConfig serverConfig;
    serverConfig.dbConfig = getDbConfig;
    serverConfig.serverName = serverName;
    return new logServer(serverConfig);
}