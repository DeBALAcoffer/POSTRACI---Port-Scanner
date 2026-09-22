<div align="center">

# POSTRACI


** multi-threaded TCP port scanner in C++17**

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Boost](https://img.shields.io/badge/Boost-Asio-orange.svg)](https://www.boost.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14+-green.svg)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Author:** [DeBALA](https://github.com/DeBALAcoffer)

</div>

---

## 📖 About

POSTRACI is a vibecoded, high-performance TCP port scanner that leverages **Boost.Asio** for network operations and **multi-threading** for blazing-fast concurrent port scanning. Built from the ground up with clean C++17, it features a professional CMake build system, color-coded terminal output, and flexible targeting options.

Whether you're doing network reconnaissance, security auditing, or just exploring open ports, POSTRACI delivers speed, reliability, and style.

## ✨ Features

- ⚡ **Multi-threaded scanning** — Scan hundreds of ports concurrently with customizable worker pools
- 🎨 **Color-coded output** — Clean, readable terminal output with ANSI colors
- 🔧 **Flexible configuration** — Custom timeouts, thread counts, and port ranges
- 📊 **Built-in timer** — Track exactly how long your scans take
- 🎯 **Multiple input formats** — Support for port ranges (`1-1024`) and lists (`22,80,443`)
- 🛡️ **Professional architecture** — CMake build system, modular code structure
- 🚫 **No dependencies hell** — Just Boost and a C++17 compiler

## 🛠️ Tech Stack

| Component | Technology |
|-----------|-----------|
| Language | C++17 |
| Networking | Boost.Asio |
| CLI Parsing | Boost.Program_options |
| Build System | CMake 3.14+ |
| Threading | std::thread (C++11) |

## 📦 Installation

### Prerequisites

```bash
# Ubuntu / Kali Linux
sudo apt update
sudo apt install build-essential cmake libboost-all-dev

# macOS (with Homebrew)
brew install cmake boost
