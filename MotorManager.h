#ifndef _MOTOR_MANAGER_H_
#define _MOTOR_MANAGER_H_

#include <fstream>
#include "NoneCopyAble.h"
#include "Singleton.h"
#include "Stream.h"



class MotorManager :private NoneCopyAble
{
	friend class Singleton<MotorManager>;
	friend OutStream& operator<<(OutStream& os, const MotorManager& mm);
public:
	void UpdateMotorData();
private:
	MotorManager();
	~MotorManager();

	bool* data_;
	long long lastUpdateTime_;
	std::ifstream ifs_;
};

#endif // !_MOTOR_MANAGER_H_



