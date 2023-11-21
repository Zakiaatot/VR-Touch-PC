#ifndef _THREAD_H_
#define _THREAD_H_

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "NoneCopyAble.h"

class Thread :private NoneCopyAble
{
public:
	Thread(bool isAutoDel = false);
	virtual ~Thread();
	bool Start();
	void Wait(DWORD waitTime = INFINITE);
	void SetAutoDel(bool isAutoDel = true) { isAutoDel_ = isAutoDel; }
private:
	HANDLE tHandle_;
	unsigned tId_;
	bool isAutoDel_;
	static unsigned _stdcall ThreadFn(void* p);
	virtual void Run() = 0;
};

#endif // !_THREAD_H_


