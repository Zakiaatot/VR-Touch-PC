#ifndef _FAKE_ROCKER_H_
#define _FAKE_ROCKER_H_

#include <cstdint>
#include <map>
#include "NoneCopyAble.h"
#include "Singleton.h"


class FakeRocker : private NoneCopyAble
{
	friend class Singleton<FakeRocker>;
public:
	// rocker status
	enum Status
	{
		NONE = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4,
		CENTER = 5
	};
	void Update(uint32_t vrXDeg, uint32_t vrYDeg);
private:
	FakeRocker();
	~FakeRocker();

	void PressKey(int keyCode);
	void ReleaseKey(int keyCode);

	Status xStatus_;
	Status yStatus_;
};

#endif // !_FAKE_ROCKER_H_

