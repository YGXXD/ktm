#ifndef APP_EVENT_HPP
#define APP_EVENT_HPP

#include "Event.hpp"

namespace xxd
{
class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(unsigned int width, unsigned int height)
		: w(width), h(height) {}

	unsigned int GetWidth() const { return w; }
	unsigned int GetHeight() const { return h; }

	std::string ToString() const override
	{
		std::string ss = "WindowResizeEvent: " +  std::to_string(w) + ", " + std::to_string(h);
		return ss;
	}

	EVENT_TYPE(WindowResize)
	EVENT_CATEGORY(EventCategoryApplication)
private:
	unsigned int w, h;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_TYPE(WindowClose)
	EVENT_CATEGORY(EventCategoryApplication)
};

class AppTickEvent : public Event
{
public:
	AppTickEvent() = default;

	EVENT_TYPE(AppTick)
	EVENT_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() = default;

	EVENT_TYPE(AppUpdate)
	EVENT_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event
{
public:
	AppRenderEvent() = default;

	EVENT_TYPE(AppRender)
	EVENT_CATEGORY(EventCategoryApplication)
};

}

#endif
