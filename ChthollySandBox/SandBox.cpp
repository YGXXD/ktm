#include "Chtholly.h"

int main(int argc, const char* argv[])
{
	// int i = 0;
	// while (i++ < 100000)
	// {
	//     KEG_DEBUG("Helow", " Chenqiudu");
	//     KEG_INFO("Helow", " Chenqiudu");
	//     KEG_WARN("Helow", " Chenqiudu");
	//     KEG_ERROR("Helow", " Chenqiudu");
	//     KEG_FATAL("Helow", " Chenqiudu");
	//     std::this_thread::sleep_for(std::chrono::milliseconds(300));
	// }
	keg::Application::Initialize();
	keg::Application::Run();
	keg::Application::Destroy();
	return 0;
}