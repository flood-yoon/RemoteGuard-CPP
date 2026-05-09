#include <iostream>
#include "WOLController.h"

using namespace std;

int main() {
    string ip, mac, user, pw;
    int menu;

    cout << "=== 원격 PC 제어 (WOL/SSH) ===\n";
    cout << "IP 주소: "; cin >> ip;
    cout << "맥 주소: "; cin >> mac;
    cout << "사용자명: "; cin >> user;
    cout << "비밀번호: "; cin >> pw;

    while (true) {
        cout << "\n[1] 켜기(WOL) [2] 끄기(SSH) [3] 정보 재설정 [4] 종료 : ";
        cin >> menu;

        if (menu == 1) {
            if (WOLController::sendMagicPacket(mac)) cout << "-> WOL 패킷 전송 성공!\n";
            else cout << "-> 패킷 전송 실패.\n";
        }
        else if (menu == 2) {
            WOLController::sendShutdownCommand(ip, user, pw);
            cout << "-> 종료 명령 실행됨.\n";
        }
        else if (menu == 3) {
            cout << "IP 다시 입력: "; cin >> ip;
            cout << "맥 다시 입력: "; cin >> mac;
        }
        else if (menu == 4) break;
    }

    return 0;
}