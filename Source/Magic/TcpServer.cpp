#include "Macro.h"
#include "TcpServer.h"


namespace Magic{


    TcpServer::~TcpServer(){
    }
    TcpServer::TcpServer(const std::string& addr,uint16_t port,uint32_t threadCount)
        :m_Address{addr}
        ,m_NetworkPort{port}
        ,m_IoPool{new IoPool{threadCount}}{
        auto endpoint = asio::ip::tcp::endpoint{asio::ip::address::from_string(addr),port};
        m_Acceptor.reset(new asio::ip::tcp::acceptor{m_IoPool->get(),endpoint});

    }
    void TcpServer::run(){
        if(m_Stop){
            return;
        }
        //TODO: ...
        MAGIC_LOG(LogLevel::LogInfo)  << "Server running";
        accept();
        m_IoPool->run();
    }
    void TcpServer::stop(){
        //TODO: ...
        MAGIC_LOG(LogLevel::LogInfo)  << "Server stoping";
        m_Stop = true;
    }
                
    void TcpServer::accept(){
        std::shared_ptr<Session> session = std::make_shared<Session>(m_IoPool->get());
        auto& socket = session->socket();
        m_Acceptor->async_accept(*socket,[this, session](const asio::error_code& err){
            if(err){
                //TODO: ...
                MAGIC_LOG(LogLevel::LogWarn) << err.message();
                return;
            }
            this->handleFunc(session);
            if(!m_Stop){
                accept();
            }
        });
    }

    void TcpServer::handleFunc(std::shared_ptr<Session> session){
    }
}