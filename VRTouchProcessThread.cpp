#include <iostream>
#include <WS2tcpip.h>
#include <chrono>
#include "VRTouchProcessThread.h"
#include "Stream.h"
#include "Package.h"
#include "FakeRocker.h"
#include "Key.h"
#include "MotorManager.h"

const size_t BUFFER_SIZE = 64;
const long long OFFLINE_TIME = 3;
const long long MOTOR_PACKAGE_SEND_SPACE = 500;

VRTouchProcessThread::VRTouchProcessThread(AutoPtr<Socket>& socket)
	:socket_(socket), lastRecvTime_(0), lastSendMotorDataTime_(0)
{

}

void VRTouchProcessThread::UpdateLastRecvTime()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::seconds timestamp =
		std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
	lastRecvTime_ = timestamp.count();
}

bool VRTouchProcessThread::IsConnect() const
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::seconds timestamp =
		std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
	long long nowTime = timestamp.count();
	if (nowTime - lastRecvTime_ > OFFLINE_TIME)
		return false;
	else
		return true;
}

void VRTouchProcessThread::SendMotorData()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::milliseconds timestamp =
		std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	long long nowTime = timestamp.count();
	if (nowTime - lastSendMotorDataTime_ > MOTOR_PACKAGE_SEND_SPACE)
	{
		OutStream os;
		os << (uint16_t)PACKAGE_CMD::CHANGE_MOTOR;
		os.Skip(sizeof(PackageHead::len_));
		os << Singleton<MotorManager>::Instance();
		os.RePosition(sizeof(PackageHead::cmd_));
		uint16_t len = (uint16_t)(os.Len() - sizeof(PackageHead));
		os << len;
		socket_->SendN(os.Data(), (int)os.Len());
		lastSendMotorDataTime_ = nowTime;
	}
}

void VRTouchProcessThread::Run()
{
	// Todo 
	// 1.recv and parse package
	// 2.exec cmd 

	// info
	sockaddr_in addr = socket_->GetPeerAddr();
	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(addr.sin_addr), ip, INET_ADDRSTRLEN);
	std::cout << "Client: " << ip << ":" << ntohs(addr.sin_port) << " connected!" << std::endl;

	char buf[BUFFER_SIZE];
	int recvN;

	UpdateLastRecvTime();
	while (IsConnect())
	{
		// recv
		if (socket_->IsReadAble())
		{
			recvN = socket_->RecvN(buf, sizeof(PackageHead));
			if (recvN == sizeof(PackageHead))
			{
				InStream is(buf);

				// head
				uint16_t cmd;
				uint16_t packLen;
				is >> cmd >> packLen;

				// body
				if (packLen > 0 &&
					socket_->RecvN(buf + sizeof(PackageHead), (int)packLen) != (int)packLen)
					goto Exit;

				// exec
				switch (cmd)
				{
				case (uint16_t)PACKAGE_CMD::REPORT_ROCKER:
					uint32_t x, y;
					is >> x >> y;
					std::cout << x << " " << y << std::endl;
					Singleton<FakeRocker>::Instance().Update(x, y);
					break;
				case(uint16_t)PACKAGE_CMD::CHANGE_MOTOR: // never reach here
					break;
				case(uint16_t)PACKAGE_CMD::PING:
					UpdateLastRecvTime();
					break;
				case(uint16_t)PACKAGE_CMD::REPORT_KEY:
					uint8_t status;
					is >> status;
					std::cout << "KEY:" << (int)status << std::endl;
					Singleton<Key>::Instance().Update(status);
					break;
				default:
					goto Exit;
				}
			}
			else
			{
				goto Exit;
			}
		}

		// send
		Singleton<MotorManager>::Instance().UpdateMotorData();
		SendMotorData();
		Sleep(1);
	}

Exit:
	std::cout << "Client: " << ip << ":" << ntohs(addr.sin_port) << " disconnected!" << std::endl;
}
