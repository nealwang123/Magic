#pragma once
#include <atomic>
#include "Core.h"

namespace Magic{
    class IoPool{
    public:
        ~IoPool();
        explicit IoPool(uint32_t poolSize);
        void run();
        void stop();
        asio::io_context& get();
    private:
        uint32_t m_Next{ 0 };
        uint32_t m_PoolSize{0};
        std::vector<Safe<asio::io_context>> m_IOService{};
        std::vector<Safe<asio::io_context::work>> m_IOServiceWork{};
    };
}