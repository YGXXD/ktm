#ifndef MOUSE_EVENT_HPP
#define MOUSE_EVENT_HPP

#include "Event.hpp"

namespace xxd
{
class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(const float x, const float y)
		: mouseX(x), mouseY(y) { }

	float GetX() const { return mouseX; }
	float GetY() const { return mouseY; }

	std::string ToString() const override
	{
		std::string ss = "MouseMovedEvent: " + std::to_string(mouseX) + ", " + std::to_string(mouseY);
		return ss;
	}

	EVENT_TYPE(MouseMoved)
	EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float mouseX, mouseY;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(const float xOffset, const float yOffset)
		: offsetX(xOffset), offsetY(yOffset) { }

	float GetXOffset() const { return offsetX; }
	float GetYOffset() const { return offsetY; }

	std::string ToString() const override
	{
		std::string ss = "MouseScrolledEvent: " + std::to_string(offsetX) + ", " + std::to_string(offsetY);
		return ss;
	}

	EVENT_TYPE(MouseScrolled)
	EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float offsetX, offsetY;
};

class MouseButtonEvent : public Event
{
public:
	uint16_t GetMouseButton() const { return btn; }

	EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
protected:
	MouseButtonEvent(const uint16_t button)
		: btn(button) { }

	uint16_t btn;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(const uint16_t button)
		: MouseButtonEvent(button) { }

	std::string ToString() const override
	{
		std::string ss = "MouseButtonPressedEvent: " + std::to_string(btn);
		return ss;
	}

	EVENT_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(const uint16_t button)
		: MouseButtonEvent(button) { }

	std::string ToString() const override
	{
		std::string ss = "MouseButtonReleasedEvent: " + std::to_string(btn);
		return ss;
	}

	EVENT_TYPE(MouseButtonReleased)
};

}
#endif
