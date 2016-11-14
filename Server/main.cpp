#include <windows.h>
#include <Winsock.h>
#include <iostream>

using namespace std;

SOCKADDR_IN addr;
int addrlen = sizeof (addr);
int Counter;

SOCKET sConnect;
SOCKET sListen;
SOCKET *Connections;

#pragma comment (lib, "ws2_32.lib")

int initWinSock() {
	
	int Val = 0;
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	Val = WSAStartup(DLLVersion, &wsaData);
	
	return Val;
	
}

int ServerThread(int ID) {
	
	char *buffer = new char[256];
	char *Buffer = new char[256];
	int size = 0;
	
	while (true) {
		ZeroMemory(Buffer, 256);
		
		if ((size = recv(Connections[ID], Buffer, 256, NULL)) > 0) {
			
			for (int a = 0; a < Counter; a++) {
			
			if (Connections[a] == Connections[ID]) {
				
				ZeroMemory(buffer, 256);
				
				sprintf(buffer, "Cliente[%i]: %s", ID, Buffer);
				cout << "Nova Mensagem:" << buffer << endl;
				
			} else {
				
				ZeroMemory(buffer, 256);
				
				sprintf(buffer, "Cliente[%i]: %s", ID, Buffer);
				send(Connections[a], buffer, 256, NULL);
				
			}
			
			}
			
		}
		
	}
	
	
	
}

int main(int argc, char** argv) {
	
	int Val = 0;
	
	system("color 0a");
	cout << "SV Start" << endl;
	
	Val = initWinSock();
	
	if (Val != 0) {
		MessageBoxA(NULL, "Erro na inicialiação do WINSOCK", "ERROR", MB_OK | MB_ICONERROR);
		exit(1);
	}
	
	Connections = (SOCKET*) calloc (64, sizeof(SOCKET));
	
	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);
	
	addr.sin_addr.s_addr = inet_addr("192.168.0.101");
	addr.sin_port 		 = htons(2222);
	addr.sin_family 	 = AF_INET;
	
	bind(sListen, (SOCKADDR*)&addr, sizeof (addr));
	
	listen(sListen, 64);
	
	while (true) {
		
		if (sConnect = accept(sListen, (SOCKADDR*)&addr, &addrlen)) {
			
			Connections[Counter] = sConnect;
			char *Name = new char[64];
			
			ZeroMemory(Name, 64);
			
			sprintf(Name, "%i", Counter);
			
			send(Connections[Counter], Name, 64, NULL);
			send(Connections[Counter], "Seja bem vindo ao CHAT EM C++", 64, NULL);
			
			cout << "Nova Conexão" << endl;
			
			Counter++;
			
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerThread, (LPVOID)(Counter -1), NULL, NULL);
			
		}
		
		Sleep(50);
	
	}
	
	return Val;
	
}


