#include "Core/Application.h"

int main(int argc, const char* argv[])
{
	// int i = 0;
	// while (i++ < 100000)
	// {
	//     XXD_DEBUG("Helow", " Chenqiudu");
	//     XXD_INFO("Helow", " Chenqiudu");
	//     XXD_WARN("Helow", " Chenqiudu");
	//     XXD_ERROR("Helow", " Chenqiudu");
	//     XXD_FATAL("Helow", " Chenqiudu");
	//     std::this_thread::sleep_for(std::chrono::milliseconds(300));
	// }
	ktl::Application::Initialize();
	ktl::Application::Run();
	ktl::Application::Destroy();
	return 0;
}