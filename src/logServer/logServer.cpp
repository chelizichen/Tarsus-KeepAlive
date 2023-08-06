#include <iostream>
#include <boost/asio.hpp>

using namespace std;

struct dbConfig
{
    string host = "127.0.0.1";
    string port = "3306";
    string userName = "root";
    string passowrd = "123456";
};

struct contentStruct
{
    /* data */
};

struct contentConfig
{
    /* data */
};

struct logServerConfig
{
    string serverName;
    dbConfig dbConfig; 
};

/**
 * @details logServer 
 * created by leekus at 2023.8.15
*/
class logServer
{
private:
    string name;
    string date;
    string serverName;
    dbConfig dbConfig;

public:
    logServer(logServerConfig serverConfig);
    ~logServer();
    string getLogName();
    bool Connect2DataBase();
    void Log2DataBase(string dbName,string content);
    contentStruct Log2HTML(contentConfig contentConfig);
    void WatchPort(int port);
};

logServer::logServer(logServerConfig serverConfig)
{
    this->serverName = serverConfig.serverName;
    this->dbConfig = serverConfig.dbConfig;
}

logServer::~logServer()
{
}


string logServer::getLogName(){
    return this->name + this->date;
}

void logServer::Log2DataBase(string dbName,string content){
    
}

bool logServer::Connect2DataBase(){
    
}

void logServer::WatchPort(int port){
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

    try {
        acceptor.accept();
        this->Log2DataBase("tarsus_keep_alive","Port is active and available.");
    } catch (const boost::system::system_error&) {
        this->Log2DataBase("tarsus_keep_alive","Port is not available.");
    }
}



logServer* LogServerFactory(logServerConfig config);
logServer* LogServerFactory(string serverName);

logServer* LogServerFactory(logServerConfig config){
    return new logServer(config);
}

logServer* LogServerFactory(string serverName){
    dbConfig getDbConfig = dbConfig();
    logServerConfig serverConfig = logServerConfig();
    serverConfig.dbConfig = getDbConfig;
    serverConfig.serverName = serverName;
    return new logServer(serverConfig);
}

