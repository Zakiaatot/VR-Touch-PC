#include "VRTouchServer.h"

int main(void)
{
	return Singleton<VRTouchServer>::Instance().Run();
}