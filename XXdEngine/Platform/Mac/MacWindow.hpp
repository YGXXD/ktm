#ifndef MAC_WINDOW_HPP
#define MAC_WINDOW_HPP

#include "Core/Window.hpp"

namespace xxd
{
class MacWindow : public Window
{
public:
	virtual void OnUpdate() override;

    virtual uint32_t GetWidth() const override;
	virtual uint32_t GetHeight() const override;

	virtual void SetEventCallback(void(* callback)(Event&)) override;
	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override;

  	virtual void *GetNativeWindow() const override;
} ;
}

#endif
