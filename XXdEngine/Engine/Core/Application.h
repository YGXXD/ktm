#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "XXd.h"
#include "Window.h"

namespace xxd
{
class XXD_API Application final
{
public:
	static void Initialize();
	static void Destroy();
	static void Run();

	static void OnEvent(Event& event);
private:
	static bool bIsQuit;
	static std::unique_ptr<Window> mainWindow;
};

}

#endif
