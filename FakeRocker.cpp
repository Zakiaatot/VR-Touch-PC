#include <Windows.h>
#include "FakeRocker.h"

static std::map <FakeRocker::Status, int> R2KMap =
{
	std::pair<FakeRocker::Status, int>(FakeRocker::Status::UP,	'W'),
	std::pair<FakeRocker::Status, int>(FakeRocker::Status::DOWN,'S'),
	std::pair<FakeRocker::Status, int>(FakeRocker::Status::LEFT,'A'),
	std::pair<FakeRocker::Status, int>(FakeRocker::Status::RIGHT,'D'),
};

static const uint32_t DOWN_THRESHOLD = 250;
static const uint32_t UP_THRESHOLD = 750;


FakeRocker::FakeRocker()
	:xStatus_(NONE), yStatus_(NONE)
{
}

FakeRocker::~FakeRocker()
{
}

void FakeRocker::Update(uint32_t vrXDeg, uint32_t vrYDeg)
{
	if (xStatus_ != NONE && xStatus_ != CENTER)
	{
		ReleaseKey(R2KMap[xStatus_]);
	}
	if (yStatus_ != NONE && yStatus_ != CENTER)
	{
		ReleaseKey(R2KMap[yStatus_]);
	}


	if (vrXDeg < DOWN_THRESHOLD)
	{
		xStatus_ = LEFT;
	}
	else if (vrXDeg > UP_THRESHOLD)
	{
		xStatus_ = RIGHT;
	}
	else
	{
		xStatus_ = CENTER;
	}

	if (vrYDeg < DOWN_THRESHOLD)
	{
		yStatus_ = DOWN;
	}
	else if (vrYDeg > UP_THRESHOLD)
	{
		yStatus_ = UP;
	}
	else
	{
		yStatus_ = CENTER;
	}

	if (xStatus_ != NONE && xStatus_ != CENTER)
	{
		PressKey(R2KMap[xStatus_]);
	}
	if (yStatus_ != NONE && yStatus_ != CENTER)
	{
		PressKey(R2KMap[yStatus_]);
	}
}

void FakeRocker::PressKey(int keyCode)
{
	keybd_event(keyCode, 0, 0, 0);
}

void FakeRocker::ReleaseKey(int keyCode)
{
	keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0);
}