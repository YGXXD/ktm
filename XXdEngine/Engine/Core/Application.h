#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "XXd.h"
#include "Window.h"

namespace xxd
{
class XXD_API Application
{
public:
	Application();
	virtual ~Application();
	virtual void Run() = 0;

private:
	std::unique_ptr<Window> mainWindow;
};

Application* CreateApplication();

}

#endif
