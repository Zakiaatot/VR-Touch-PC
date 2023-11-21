#include <iostream>
#include <cassert>
#include "VRTouchServer.h"
#include "Config.h"
#include "AutoPtr.h"
#include "VRTouchProcessThread.h"

VRTouchServer::VRTouchServer()
{
	assert(Socket::Startup());
}

VRTouchServer::~VRTouchServer()
{
	Socket::Cleanup();
}

int VRTouchServer::Run()
{
	serverSocket_.Create();
	if (!serverSocket_.Bind(NULL, SOCKET_CONFIG::PORT))
	{
		std::cout << "Bind port error!" << std::endl;
		return -1;
	}
	if (!serverSocket_.Listen())
	{
		std::cout << "Listen error!" << std::endl;
		return -2;
	}
	std::cout << "Server started on 0.0.0.0:" << SOCKET_CONFIG::PORT << std::endl;
	while (true)
	{
		AutoPtr<Socket> clientSocket(new Socket(serverSocket_.Accept()));
		Thread* pThread = new VRTouchProcessThread(clientSocket);
		pThread->SetAutoDel();
		pThread->Start();
		pThread->Wait(); // singleton
	}
	return 0;
}