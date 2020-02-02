#pragma once

#include "Core.h"
#include "IoPool.h"
#include "Session.h"
namespace Magic{
    class TcpServer{
    public:
        virtual ~TcpServer();
        TcpServer(const std::string& addr,uint16_t port,uint32_t threadCount);
        void run();
        void stop();
    protected:
        virtual void accept();
        virtual void handleFunc(Share<Session> session) =0;
    protected:
        bool m_Stop{false};
        std::string m_Address{};
        uint16_t m_NetworkPort{};
        Safe<IoPool> m_IoPool{};
        Safe<asio::ip::tcp::acceptor> m_Acceptor{};
    };
}