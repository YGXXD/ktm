#ifndef _WINDOWS_WINDOW_H_
#define _WINDOWS_WINDOW_H_

#include "Core/Window.h"
#include "EvtWin32Window.h"

namespace keg
{
class WindowsWindow : public Window, public EvtWin32Delegate
{
public:
	WindowsWindow(const WindowProps& props);
	~WindowsWindow();

	virtual LRESULT WindowMsgCallBack(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) override;

	virtual void OnUpdate() override;

    virtual uint32_t GetWidth() const override;
	virtual uint32_t GetHeight() const override;

	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override;

  	virtual void *GetNativeWindow() const override;	
private:
	void InitProps(const WindowProps& props);
	
	std::string title;
	HWND hWindow;
};
}

#endif