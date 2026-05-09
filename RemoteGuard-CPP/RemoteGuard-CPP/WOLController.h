#pragma once
#include <string>
#include <vector>

class WOLController {
public:
    // 매직 패킷 전송 (맥 주소 기반)
    static bool sendMagicPacket(const std::string& macAddress);

    // SSH 종료 명령 실행 (아이피, 아이디, 비번 기반)
    static void sendShutdownCommand(const std::string& ip, const std::string& user, const std::string& pw);

private:
    static std::vector<unsigned char> parseMacAddress(const std::string& mac);
};