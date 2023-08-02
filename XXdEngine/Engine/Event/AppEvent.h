#ifndef _APP_EVENT_H_
#define _APP_EVENT_H_

#include "Event.h"

namespace xxd
{
class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(uint32_t width, uint32_t height)
		: w(width), h(height) {}

	uint32_t GetWidth() const { return w; }
	uint32_t GetHeight() const { return h; }

	std::string ToString() const override
	{
		std::string ss = "WindowResizeEvent: " +  std::to_string(w) + ", " + std::to_string(h);
		return ss;
	}

	EVENT_TYPE(WindowResize)
	EVENT_CATEGORY(EventCategoryApplication)
private:
	uint32_t w, h;
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
