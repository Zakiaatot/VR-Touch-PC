#include <process.h>
#include "Thread.h"

Thread::Thread(bool isAutoDel)
	:isAutoDel_(isAutoDel), tHandle_(NULL), tId_(0)
{

}

Thread::~Thread()
{
	if (tHandle_ != NULL)
		CloseHandle(tHandle_);
}

bool Thread::Start()
{
	tHandle_ = (HANDLE)_beginthreadex(NULL, NULL, ThreadFn, (void*)this, NULL, &tId_);
	return tHandle_ != NULL;
}

void Thread::Wait(DWORD waitTime)
{
	WaitForSingleObject(tHandle_, waitTime);
}


unsigned _stdcall Thread::ThreadFn(void* p)
{
	Thread* thread = (Thread*)p;
	thread->Run();
	if (thread->isAutoDel_)
		delete thread;
	return 0;
}
