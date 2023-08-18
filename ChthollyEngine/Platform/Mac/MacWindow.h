#ifndef _MAC_WINDOW_H_
#define _MAC_WINDOW_H_

#include "Core/Window.h"
#include "EvtNSWindow.h"

namespace ktl
{
class MacWindow : public Window, public EvtNSDelegate
{
public:
	static void MacCocoaInit();
	static void MacCocoaPollEvent();
	static void MacCocoaQuit();

	MacWindow(const WindowProps& props);
	~MacWindow();

	virtual SingleDelegate<void, Event&>& GetEventCallback() override;

	virtual void OnUpdate() override;

    virtual uint32_t GetWidth() const override;
	virtual uint32_t GetHeight() const override;

	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override;

  	virtual void *GetNativeWindow() const override;	
private:
	void InitProps(const WindowProps& props);
	
	std::string title;
	::EvtNSWindow* window;
} ;
}

#endif