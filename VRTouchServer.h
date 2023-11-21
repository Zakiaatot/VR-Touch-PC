#ifndef _VRTOUCH_SERVER_H_
#define _VRTOUCH_SERVER_H_

#include "NoneCopyAble.h"
#include "Singleton.h"
#include "Socket.h"

class VRTouchServer
{
	friend class Singleton<VRTouchServer>;
private:
	VRTouchServer();
	~VRTouchServer();
public:
	int Run();
private:
	Socket serverSocket_;
};

#endif // !_VRTOUCH_SERVER_H_



