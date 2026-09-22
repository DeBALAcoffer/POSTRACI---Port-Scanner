#include "PortProbe.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

namespace po = boost::program_options;

void displayLogo() {
    std::cout << COLOR_CYAN << R"(
    ____   ___  ____ _____ ____      _    ____ ___ 
 |  _ \ / _ \/ ___|_   _|  _ \    / \  / ___|_ _|
 | |_) | | | \___ \ | | | |_) |  / _ \| |    | | 
 |  __/| |_| |___) || | |  _ <  / ___ \ |___ | | 
 |_|    \___/|____/ |_| |_| \_\/_/   \_\____|___| 
                                          
             by DeBALA
    )" << COLOR_RESET << "\n\n";
}

std::vector<int> extractPorts(const std::string& portInput) {
    std::vector<int> result;
    std::stringstream parser(portInput);
    std::string segment;
    while (std::getline(parser, segment, ',')) {
        if (segment.find('-') != std::string::npos) {
            size_t separator = segment.find('-');
            int begin = std::stoi(segment.substr(0, separator));
            int finish = std::stoi(segment.substr(separator + 1));
            for (int i = begin; i <= finish; ++i) result.push_back(i);
        } else {
            result.push_back(std::stoi(segment));
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    displayLogo();

    po::options_description config(COLOR_CYAN + "POSTRACI Configuration" + COLOR_RESET);
    config.add_options()
        ("help,h", "show help message")
        ("host,H", po::value<std::string>()->default_value("127.0.0.1"),
         "Target hostname or IP")
        ("ports,P", po::value<std::string>()->default_value("1-1024"),
         "Ports to scan (e.g. 1-1024 or 22,80,443)")
        ("workers,W", po::value<int>()->default_value(100),
         "Number of concurrent workers")
        ("delay,D", po::value<int>()->default_value(2),
         "Connection timeout in seconds");

    po::variables_map settings;
    po::store(po::parse_command_line(argc, argv, config), settings);
    po::notify(settings);

    if (settings.count("help")) {
        std::cout << config << "\n";
        std::cout << COLOR_YELLOW << "Usage Examples:" << COLOR_RESET << "\n"
                  << "  Scan localhost ports:\n"
                  << "    ./POSTRACI -H 127.0.0.1 -P 1-1024\n\n"
                  << "  Scan all ports with high concurrency:\n"
                  << "    ./POSTRACI -H scanme.nmap.org -P 1-65535 -W 200\n\n"
                  << "  Scan specific services with custom timeout:\n"
                  << "    ./POSTRACI -H scanme.nmap.org -P 22,80,443 -D 5\n\n"
                  << COLOR_RED << "  Legal Notice:\n" << COLOR_RESET
                  << "  Only scan systems you own or have explicit permission to test.\n\n"
                  << COLOR_CYAN << "  [i] POSTRACI is developed and maintained by DeBALA.\n" << COLOR_RESET;
        return 0;
    }

    std::string targetHost = settings["host"].as<std::string>();
    std::string portInput = settings["ports"].as<std::string>();
    int workerCount = settings["workers"].as<int>();
    int timeoutDelay = settings["delay"].as<int>();

    std::vector<int> portsToScan = extractPorts(portInput);

    std::cout << COLOR_GREEN << "[*] Starting POSTRACI scan..." << COLOR_RESET << "\n";
    std::cout << "    Target:    " << COLOR_YELLOW << targetHost << COLOR_RESET << "\n";
    std::cout << "    Ports:     " << COLOR_YELLOW << portInput
              << " (" << portsToScan.size() << " ports)" << COLOR_RESET << "\n";
    std::cout << "    Workers:   " << COLOR_YELLOW << workerCount << COLOR_RESET << "\n";
    std::cout << "    Timeout:   " << COLOR_YELLOW << timeoutDelay << "s" << COLOR_RESET << "\n\n";

    auto startTime = std::chrono::high_resolution_clock::now();

    PortProbe scanner(targetHost, portsToScan, workerCount, timeoutDelay);
    scanner.runScan();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    std::cout << "\n" << COLOR_GREEN
              << "[+] Scan finished " << duration.count()
              << "." << COLOR_RESET << "\n";

    return 0;
}
