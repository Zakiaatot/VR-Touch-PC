#include <cassert>
#include <WS2tcpip.h>
#include "Socket.h"


Socket::Socket(SOCKET socket)
	:socket_(socket)
{

}

Socket::~Socket()
{
	if (socket_ != INVALID_SOCKET)
	{
		Close();
	}
}

void Socket::Create(bool tcp)
{
	if (tcp)
		socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	else
		socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	assert(socket_ != INVALID_SOCKET);
	int optvalue = 1;
	setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (const char*)&optvalue, sizeof(optvalue));
}

bool Socket::Startup()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return false;
	}
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		WSACleanup();
		return false;
	}
	return true;
}

void Socket::Cleanup()
{
	WSACleanup();
}

bool Socket::IsValid() const
{
	return socket_ != INVALID_SOCKET;
}

bool Socket::Bind(const char* ip, unsigned short port)
{
	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (ip == NULL)
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	else
		inet_pton(AF_INET, ip, &(addr.sin_addr));
	if (SOCKET_ERROR == bind(socket_, (sockaddr*)&addr, sizeof(addr)))
		return false;
	return true;
}


bool Socket::Listen(int backlog)
{
	if (listen(socket_, backlog) == SOCKET_ERROR)
		return false;
	return true;
}

SOCKET Socket::Accept()
{
	sockaddr_in peerAddr = { 0 };
	int addrSize = sizeof(peerAddr);
	SOCKET socket = accept(socket_, (sockaddr*)&peerAddr, &addrSize);
	return socket;
}

bool Socket::Connect(const char* ip, unsigned short port)
{
	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &addr.sin_addr);

	if (SOCKET_ERROR == connect(socket_, (sockaddr*)&addr, sizeof(addr)))
	{
		return false;
	}
	return true;
}

void Socket::Close()
{
	closesocket(socket_);
	socket_ = INVALID_SOCKET;
}

int Socket::Send(const char* buf, int len)
{

	return send(socket_, buf, len, 0);
}

int Socket::Recv(char* buf, int len)
{
	return recv(socket_, buf, len, 0);
}

int Socket::SendN(const char* buf, int len)
{
	int leftLen = len;
	int sendLen = 0;

	while (leftLen > 0)
	{
		sendLen = Send(buf, leftLen);
		if (sendLen == SOCKET_ERROR)
			return sendLen;
		leftLen -= sendLen;
		buf += sendLen;
	}

	return len - leftLen;
}

int Socket::RecvN(char* buf, int len)
{
	int leftLen = len;
	int recvLen = 0;

	while (leftLen > 0)
	{
		recvLen = Recv(buf, len);
		if (recvLen == SOCKET_ERROR)
			return recvLen;
		leftLen -= recvLen;
		buf += recvLen;
	}

	return len - leftLen;
}

sockaddr_in Socket::GetPeerAddr() const
{
	sockaddr_in addr = { 0 };
	int addrSize = sizeof(addr);
	getpeername(socket_, (sockaddr*)&addr, &addrSize);
	return addr;
}

bool Socket::IsReadAble() const
{
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(socket_, &readSet);

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	int result = select((int)socket_ + 1, &readSet, NULL, NULL, &timeout);
	if (result == -1)
	{
		// Error occurred during select()
		return false;
	}
	else if (result == 0)
	{
		// Timeout occurred, socket is not ready for reading
		return false;
	}
	else
	{
		// Socket is ready for reading
		return true;
	}
}
