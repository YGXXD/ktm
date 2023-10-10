#ifndef _KEY_EVENT_H_
#define _KEY_EVENT_H_

#include "Event.h"

namespace keg
{
class KeyEvent : public Event
{
public:
	uint16_t GetKeyCode() const { return key; }

	EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	KeyEvent(const uint16_t keycode)
		: key(keycode) { }

	uint16_t key;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(const uint16_t keycode, bool isRepeat = false)
		: KeyEvent(keycode), bIsRepeat(isRepeat) { }

	bool IsRepeat() const { return bIsRepeat; }

	std::string ToString() const override
	{
		std::string ss = "KeyPressedEvent: " + std::to_string(key) + " (repeat = " + std::to_string(bIsRepeat) + ")";
		return ss;
	}

	EVENT_TYPE(KeyPressed)
private:
	bool bIsRepeat;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(const uint16_t keycode)
		: KeyEvent(keycode) { }

	std::string ToString() const override
	{
		std::string ss = "KeyReleasedEvent: " + std::to_string(key);
		return ss;
	}

	EVENT_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(const uint16_t keycode)
		: KeyEvent(keycode) { }

	std::string ToString() const override
	{
		std::string ss = "KeyTypedEvent: " + std::to_string(key);
		return ss;
	}

	EVENT_TYPE(KeyTyped)
};
}

#endif
