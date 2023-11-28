#ifndef _KEY_H_
#define _KEY_H_

#include <cstdint>
#include "NoneCopyAble.h"
#include "Singleton.h"


class Key : private NoneCopyAble
{
	friend class Singleton<Key>;
public:
	// Key status
	enum Status
	{
		NONE = 0,
		UP = 1,
		DOWN = 2,
	};
	void Update(uint8_t status);
private:
	Key() = default;
	~Key() = default;
	void PressKey(int keyCode);
};

#endif // !_KEY_H_

