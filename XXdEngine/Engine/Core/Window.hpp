#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <XXd.h>
#include "Event/Event.hpp"

namespace xxd
{
struct WindowProps
{
    std::string title;
    uint32_t width;
    uint32_t height;

    WindowProps(const std::string &title = "XXd Engine", uint32_t width = 1600, uint32_t height = 900)
        : title(title), width(width), height(height)
    {
    }
};

class XXD_API Window
{
public:
  virtual ~Window() = default;

  virtual void OnUpdate() = 0;

  virtual uint32_t GetWidth() const = 0;
  virtual uint32_t GetHeight() const = 0;

  virtual void SetEventCallback(void(* callback)(Event&)) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;

  virtual void *GetNativeWindow() const = 0;

  static Window* Create(const WindowProps &props = WindowProps());
};
}

#endif