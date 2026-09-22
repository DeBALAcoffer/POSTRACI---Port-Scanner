#pragma once

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

// Terminal color definitions
const std::string COLOR_RESET   = "\033[0m";
const std::string COLOR_RED     = "\033[1;31m";
const std::string COLOR_GREEN   = "\033[1;32m";
const std::string COLOR_YELLOW  = "\033[1;33m";
const std::string COLOR_CYAN    = "\033[1;36m";

class PortProbe {
public:
    PortProbe(const std::string& host,
              const std::vector<int>& portList,
              int threadCount,
              int waitSeconds)
        : host_(host),
          portList_(portList),
          threadCount_(threadCount),
          waitSeconds_(waitSeconds) {}

    void runScan() {
        std::vector<std::thread> workerPool;

        for (int portNum : portList_) {
            workerPool.emplace_back(&PortProbe::checkPort, this, portNum);

            if (static_cast<int>(workerPool.size()) >= threadCount_) {
                for (auto& worker : workerPool) worker.join();
                workerPool.clear();
            }
        }
        for (auto& worker : workerPool) worker.join();
    }

private:
    void checkPort(int portNum) {
        try {
            boost::asio::io_context networkContext;
            boost::asio::ip::tcp::socket connection(networkContext);
            boost::asio::ip::tcp::endpoint targetEndpoint(
                boost::asio::ip::make_address(host_), portNum);

            boost::system::error_code errorCode;
            connection.async_connect(targetEndpoint,
                [&errorCode](const boost::system::error_code& err) { errorCode = err; });

            networkContext.run_for(std::chrono::seconds(waitSeconds_));

            if (!errorCode && connection.is_open()) {
                std::lock_guard<std::mutex> lock(outputMutex_);
                std::cout << COLOR_GREEN << "[+] Port " << portNum
                          << " is OPEN" << COLOR_RESET << "\n";
            }
        } catch (...) {
            // Skip unreachable ports silently
        }
    }

    std::string host_;
    std::vector<int> portList_;
    int threadCount_;
    int waitSeconds_;
    std::mutex outputMutex_;
};
