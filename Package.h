#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include <cstdint>

enum class PACKAGE_CMD : uint16_t
{
	PING = 0x00,
	REPORT_ROCKER = 0x01,
	CHANGE_MOTOR = 0x02,
};

struct PackageHead
{
	uint16_t cmd_;
	uint16_t len_;
};

struct Package
{
	PackageHead head_;
	char* body_;
};

#endif //!_PACKAGE_H_
