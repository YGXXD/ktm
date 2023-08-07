#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "XXd.h"
#include "Window.h"
#include "Singleton.h"

namespace xxd
{
class XXD_API Application final
{
	XXD_SINGLETON_FLAG(Application)

public:
	void Run();

private:
	std::unique_ptr<Window> mainWindow;
};

}

#endif
