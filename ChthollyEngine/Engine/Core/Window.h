#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Basic/Basic.h"
#include "Event/Event.h"

namespace keg
{
struct WindowProps
{
    std::string title;
    uint32_t width;
    uint32_t height;

    WindowProps(const std::string& title = "Chtholly Engine", uint32_t width = 1280, uint32_t height = 720)
        : title(title), width(width), height(height)
    {
    }
};

DECLARE_FUNCTION_DELEGATE(EventCallbackDelegate, void, keg::Event&)

class CHTHOLLY_ENGINE_API Window
{
public: 	
	static Window* Create(const WindowProps &props = WindowProps());

  	virtual ~Window() { };
  	virtual void OnUpdate() = 0;

  	virtual uint32_t GetWidth() const = 0;
  	virtual uint32_t GetHeight() const = 0;

 	virtual void SetVSync(bool enabled) = 0; // 垂直同步
 	virtual bool IsVSync() const = 0;
 	virtual void* GetNativeWindow() const = 0;
	
	EventCallbackDelegate eventCallback;
};
}

#endif