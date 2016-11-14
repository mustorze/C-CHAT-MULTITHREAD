#include <iostream>
#include <WinSock.h>
#include <Windows.h>

#pragma comment (lib, "w2_32.lib")

using namespace std;

SOCKET sConnect;
SOCKADDR_IN addr;

int Startup_WinSock () {
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	
	int Val = WSAStartup(DLLVersion, &wsaData);
	
	
	
	return Val;
}

int ClienteThread() {
	
	char *Buffer = new char[256];
	int size = 0;
	
	while (true) {
		
		ZeroMemory(Buffer, 256);
		
		if ((size = recv(sConnect, Buffer, 256, NULL)) > 0) {
			
			cout << Buffer << endl;
			
		}
		
		Sleep(50);
		
	}
	
	
}

int main() {
	
	system("color 0a");
	int Val = Startup_WinSock();
	
	if (Val != 0) {
		cout << "Erro na inicialização do WinSock" << endl;
		exit(1);
	}
	
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);
	
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(2222);
	addr.sin_family = AF_INET;
	
	cout << "POR FAVOR APERTE [ENTER]" << endl;
	cin.get();
	
	Val = connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
	
	if (Val != 0) {
		cout << "Erro na conexão" << endl;
		main();
		} else {
		system("cls");
	}
	
	int ID;
	char *nID = new char[64];
	char *hello = new char[64];
	
	ZeroMemory(nID, 64);
	ZeroMemory(hello, 64);
	
	recv(sConnect, nID, 64, NULL);
	recv(sConnect, hello, 64, NULL);
	
	ID = atoi(nID);
	cout << hello << endl;
	cout << "Seu ID:" << ID << endl;
	cout << "Se esta pronto aperte [ENTER]" << endl;
	cin.get();
	
	system("cls");
	
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClienteThread, NULL, NULL, NULL);
	
	while(true) {
		
		char *MSG = new char[256];
		
		ZeroMemory(MSG, 256);
		
		
		cin.getline(MSG, 256);
		
		send(sConnect, MSG, 256, NULL);
		Sleep(50);
		
	}
	
	return Val;
}
