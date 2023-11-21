#ifndef _SOCKET_H_
#define _SOCKET_H_

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include "NoneCopyAble.h"

// Server
// 1.create
// 2.bind
// 3.listen
// 4.accept

// Client
// 1.create
// 2.connect

class Socket :private NoneCopyAble
{
public:
	Socket(SOCKET socket = INVALID_SOCKET);
	~Socket();
	void Create(bool tcp = true);
	static bool Startup();
	static void Cleanup();
	bool IsValid() const;
	bool IsReadAble() const;
	bool Bind(const char* ip, unsigned short port);
	bool Listen(int backlog = SOMAXCONN);
	SOCKET Accept();
	bool Connect(const char* ip, unsigned short port);
	void Close();
	int Send(const char* buf, int len);
	int Recv(char* buf, int len);
	int SendN(const char* buf, int len);
	int RecvN(char* buf, int len);
	operator SOCKET() { return socket_; }
	sockaddr_in GetPeerAddr() const;
private:
	SOCKET socket_;
};

#endif // !_SOCKET_H_


