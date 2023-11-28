#include <map>
#include <Windows.h>
#include "Key.h"

static std::map <Key::Status, int> KMap =
{
	std::pair<Key::Status, int>(Key::Status::UP,'E'),
	std::pair<Key::Status, int>(Key::Status::DOWN,'Q'),
};

void Key::Update(uint8_t status)
{
	switch (status)
	{
	case (uint8_t)Status::DOWN:
		PressKey(KMap[DOWN]);
		break;
	case (uint8_t)Status::UP:
		PressKey(KMap[UP]);
		break;
	default:
		break;
	}
}


void Key::PressKey(int keyCode)
{
	keybd_event(keyCode, 0, 0, 0);
}