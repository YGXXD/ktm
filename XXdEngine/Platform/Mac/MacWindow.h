#ifndef _MAC_WINDOW_H_
#define _MAC_WINDOW_H_

#include "Core/Window.h"

@class NSWindow;

namespace xxd
{
class MacWindow : public Window
{
public:
	MacWindow(const WindowProps& props);
	~MacWindow();

	virtual void OnUpdate() override;

    virtual uint32_t GetWidth() const override;
	virtual uint32_t GetHeight() const override;

	virtual void SetEventCallback(void(* callback)(Event&)) override;
	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override;

  	virtual void *GetNativeWindow() const override;
private:
	void Init(const WindowProps& props);
	
	std::string title;
	uint32_t width;
	uint32_t height;
	::NSWindow* window;
} ;
}

#endif
