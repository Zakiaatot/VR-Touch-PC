#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <cstdint>
#include "DtmMap.h"

namespace SOCKET_CONFIG
{
	extern const uint16_t PORT;
}

namespace MOTOR_MANAGER_CONFIG
{
	extern const uint32_t MOTOR_NUM;
	extern const char* DATA_FILE_PATH;
	extern const uint32_t MAP_SIZE;
	extern DtmMap DTM_MAP;
}

#endif // !_CONFIG_H_


