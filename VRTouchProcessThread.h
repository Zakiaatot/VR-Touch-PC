#ifndef _VRTOUCH_PROCESS_THREAD_H_
#define _VRTOUCH_PROCESS_THREAD_H_

#include "Thread.h"
#include "AutoPtr.h"
#include "Socket.h"

class VRTouchProcessThread :public Thread
{
public:
	VRTouchProcessThread(AutoPtr<Socket>& socket);
private:
	AutoPtr<Socket> socket_;
	long long lastRecvTime_;

	void Run();
	void UpdateLastRecvTime();
	bool IsConnect() const;
};

#endif // !_VRTOUCH_PROCESS_THREAD_H_

