#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Chtholly.h"
#include "Window.h"

namespace xxd
{
class CHTHOLLY_API Application final
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
