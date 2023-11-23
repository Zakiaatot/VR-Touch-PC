#include <chrono>
#include "MotorManager.h"
#include "Config.h"

const long long UPDATE_TIME_SPACE = 300;

MotorManager::MotorManager()
	:data_(0), lastUpdateTime_(0),
	ifs_(std::ifstream(MOTOR_MANAGER_CONFIG::DATA_FILE_PATH))
{
	data_ = new bool[MOTOR_MANAGER_CONFIG::MOTOR_NUM] {0};
}

MotorManager::~MotorManager()
{
	delete[] data_;
}


OutStream& operator<<(OutStream& os, const MotorManager& mm)
{
	os.Append((char*)mm.data_, MOTOR_MANAGER_CONFIG::MOTOR_NUM);
	return os;
}

void MotorManager::UpdateMotorData()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::milliseconds timestamp =
		std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	long long nowTime = timestamp.count();
	if (nowTime - lastUpdateTime_ > UPDATE_TIME_SPACE)
	{
		int degree = 0;
		if (ifs_.is_open())
		{
			ifs_.seekg(std::ios::beg);
			ifs_ >> degree;
			const bool* data = 0;
			data = MOTOR_MANAGER_CONFIG::DTM_MAP[degree];
			if (data)
			{
				for (unsigned int i = 0;i < MOTOR_MANAGER_CONFIG::MOTOR_NUM;++i)
				{
					data_[i] = data[i];
				}
			}
		}
		else
		{
			ifs_.open(MOTOR_MANAGER_CONFIG::DATA_FILE_PATH);
		}
		lastUpdateTime_ = nowTime;
	}
}