#include "DtmMap.h"
#include "Config.h"

const bool* DtmMap::operator[](int name)
{
	if (dtms_.size() < name && name <= 0)
		return 0;
	return dtms_[name - 1];
}

void DtmMap::Push(bool* dtm)
{
	dtms_.push_back(dtm);
}

DtmMap::~DtmMap()
{
}

DtmMap::DtmMap(bool* dtms)
{
	for (size_t i = 0;i < MOTOR_MANAGER_CONFIG::MAP_SIZE;++i)
		dtms_.push_back(dtms + i * MOTOR_MANAGER_CONFIG::MOTOR_NUM);
}
