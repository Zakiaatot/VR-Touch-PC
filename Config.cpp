#include "Config.h"

const uint16_t SOCKET_CONFIG::PORT = 3456;

const char* MOTOR_MANAGER_CONFIG::DATA_FILE_PATH = "C:\\VR Project\\Test Data\\Test.txt";
const uint32_t MOTOR_MANAGER_CONFIG::MOTOR_NUM = 5;
const uint32_t MOTOR_MANAGER_CONFIG::MAP_SIZE = 3;

bool data[MOTOR_MANAGER_CONFIG::MAP_SIZE][MOTOR_MANAGER_CONFIG::MOTOR_NUM] =
{
	{0,0,0,0,0},
	{1,0,1,0,1},
	{1,1,1,1,1}
};

DtmMap MOTOR_MANAGER_CONFIG::DTM_MAP((bool*)data);
