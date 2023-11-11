#ifndef _EVENT_H_
#define _EVENT_H_

#include "Basic/Basic.h"

namespace keg
{
enum class EventType : unsigned char
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory : unsigned char
{
	None = 0,
	EventCategoryApplication    = 1,
	EventCategoryInput          = 1 << 1,
	EventCategoryKeyboard       = 1 << 2,
	EventCategoryMouse          = 1 << 3,
	EventCategoryMouseButton    = 1 << 4
};

#define EVENT_TYPE(type) \
static CHTHOLLY_INLINE EventType GetStaticType() { return keg::EventType::type; } \
virtual EventType GetEventType() const override { return keg::EventType::type; } \
virtual const char* GetName() const override { return #type; }

#define EVENT_CATEGORY(category) \
virtual unsigned char GetCategoryFlags() const override { return keg::category; }

class Event
{
public:
	friend class EventDispatcher;
	
	virtual ~Event() = default;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual unsigned char GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); };

	CHTHOLLY_INLINE bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

private:
	bool handled = false;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event)
		: eventRef(event)
	{
	}

	template<typename T, typename F>
	bool Dispatch(F&& func)
	{
		if (eventRef.GetEventType() == T::GetStaticType())
		{
			eventRef.handled = func(static_cast<T&>(eventRef));
			return true;
		}
		return false;
	}
private:
	Event& eventRef;
};

CHTHOLLY_INLINE std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}

}

#endif
