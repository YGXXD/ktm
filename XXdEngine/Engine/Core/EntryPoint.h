#ifndef _ENTRY_POINT_H_
#define _ENTRY_POINT_H_

#include "Application.h"
#include "Log/Logger.h"

extern xxd::Application* xxd::CreateApplication();

inline int EngineMain(int argc, const char* argv[])
{
	auto App = xxd::CreateApplication();
	App->Run();
	delete App;
	return 0;
}

#endif
