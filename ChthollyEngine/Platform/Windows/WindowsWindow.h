#ifndef _WINDOWS_WINDOW_H_
#define _WINDOWS_WINDOW_H_

#include "Core/Window.h"

namespace ktl
{
class WindowsWindow : public Window
{
public:
	static void WindowsWin32Init();
	static void WindowsWin32PollEvent();
	static void WindowsWin32Quit();

	WindowsWindow(const WindowProps& props);
	~WindowsWindow();

	virtual void OnUpdate() override;

    virtual uint32_t GetWidth() const override;
	virtual uint32_t GetHeight() const override;

	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override;

  	virtual void *GetNativeWindow() const override;	
private:
	void InitProps(const WindowProps& props);
	
	std::string title;
	
};
}

#endif