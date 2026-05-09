# 🖥️ RemoteGuard-CPP: Remote Power & Resource Monitor

A high-performance C++ system utility designed for remote hardware management. This tool enables users to wake up remote machines via **WOL (Wake-on-LAN)**, monitor system resources (CPU/RAM/Disk) in real-time via **SSH**, and execute power commands or custom scripts remotely.

---

## 🎯 Project Objectives
The goal of this project is to build a lightweight, low-level remote management tool that bypasses the need for heavy third-party software. It demonstrates:
- **Low-level Networking:** Manual construction of UDP Magic Packets for WOL.
- **Secure Communication:** Implementing SSH protocols for remote command execution and data retrieval.
- **System Programming:** Efficient resource monitoring and asynchronous task management in C++.

---

## ✨ Key Features

### ⚡ Power Management (Wake-on-LAN)
- Direct implementation of **UDP Magic Packet** (102-byte frame) to power on remote machines.
- Broadcasts to local networks via `Winsock2` socket programming.

### 📊 Real-time Resource Monitoring
- Connects to remote hosts via **libssh2** to fetch system statistics.
- Parses output from `top`, `free`, and `df` to display:
  - **CPU Usage:** Real-time load percentage.
  - **Memory:** Total vs. Used RAM.
  - **Storage:** Disk health and remaining capacity.

### 🕹️ Remote Execution & Power Control
- Execute local batch files (`.bat`) or shell scripts for automated workflows.
- Immediate power control: `Shutdown`, `Restart`, and `Sleep` via secure SSH channels.
- Process management: Capability to terminate specific tasks remotely.

---

## 🛠️ Tech Stack
- **Language:** C++17 or higher
- **Libraries:**
  - `Winsock2` (Windows Socket API for WOL)
  - `libssh2` (SSH-2 protocol implementation)
  - `std::thread` / `std::future` (Asynchronous monitoring)
- **Environment:** Visual Studio / Windows (Targeting cross-platform SSH execution)

---

## 📂 System Architecture
```text
RemoteGuard_CPP/
├── include/
│   ├── WOLController.h     # UDP Packet construction & Broadcast logic
│   ├── SSHManager.h        # SSH Session & Command execution handling
│   └── SystemMonitor.h     # Resource data parsing & structures
├── src/
│   ├── main.cpp            # Application Entry & Loop
│   ├── WOLController.cpp
│   ├── SSHManager.cpp
│   └── SystemMonitor.cpp
└── README.md
