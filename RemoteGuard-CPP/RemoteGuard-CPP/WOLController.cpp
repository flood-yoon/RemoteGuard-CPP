#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "WOLController.h"
#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

bool WOLController::sendMagicPacket(const std::string& macAddress) {
    std::vector<unsigned char> macBytes = parseMacAddress(macAddress);
    if (macBytes.size() != 6) return false;

    unsigned char packet[102];
    memset(packet, 0xFF, 6);
    for (int i = 1; i <= 16; i++) memcpy(&packet[i * 6], &macBytes[0], 6);

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    BOOL bOpt = TRUE;
    setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9);
    addr.sin_addr.s_addr = INADDR_BROADCAST;

    int result = sendto(s, (char*)packet, sizeof(packet), 0, (sockaddr*)&addr, sizeof(addr));

    closesocket(s);
    WSACleanup();
    return result > 0;
}

void WOLController::sendShutdownCommand(const std::string& ip, const std::string& user, const std::string& pw) {
    // 가장 간편한 윈도우 원격 종료 방식 사용
    std::string cmd = "sshpass -p " + pw + " ssh -o StrictHostKeyChecking=no " + user + "@" + ip + " \"shutdown /s /t 0\"";

    std::cout << "[!] 원격 종료 시도 중...\n";
    if (system(cmd.c_str()) != 0) {
        // 실패 시 윈도우 RPC 방식 차선책
        std::string cmd2 = "shutdown /m \\\\" + ip + " /s /t 0";
        system(cmd2.c_str());
    }
}

std::vector<unsigned char> WOLController::parseMacAddress(const std::string& mac) {
    std::vector<unsigned char> bytes;
    for (size_t i = 0; i < mac.length(); i += 3) {
        bytes.push_back((unsigned char)std::stoul(mac.substr(i, 2), nullptr, 16));
    }
    return bytes;
}