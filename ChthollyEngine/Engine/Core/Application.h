#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Basic/SetupBase.h"

namespace keg
{
class Event;
class Window;
class GraphicsContext;
class CHTHOLLY_ENGINE_API Application final
{
public:
	static void Initialize();
	static void Destroy();
	static void Run();

	static void OnEvent(Event& event);
private:
	static bool bIsQuit;
	static std::unique_ptr<Window> mainWindow;
	static std::unique_ptr<GraphicsContext> mainGraphics;
};

}

#endif
