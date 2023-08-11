#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Chtholly.h"
#include "Event/Event.h"
#include "Delegate.h"

namespace xxd
{
struct WindowProps
{
    std::string title;
    uint32_t width;
    uint32_t height;

    WindowProps(const std::string& title = "XXd Engine", uint32_t width = 1280, uint32_t height = 720)
        : title(title), width(width), height(height)
    {
    }
};

class CHTHOLLY_API Window
{
public: 	
	static Window* Create(const WindowProps &props = WindowProps());
	static void Init();
	static void PollEvent();
	static void Quit();

  	virtual ~Window() { };

  	virtual void OnUpdate() = 0;

  	virtual uint32_t GetWidth() const = 0;
  	virtual uint32_t GetHeight() const = 0;

 	virtual void SetVSync(bool enabled) = 0; // 垂直同步
 	virtual bool IsVSync() const = 0;
 	virtual void* GetNativeWindow() const = 0;
	
	SingleDelegate<void, Event&> eventCallback;

private:
	static bool bisInitialized;
};
}

#endif