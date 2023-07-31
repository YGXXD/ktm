#include "Core/Core.hpp"

class AppTest : public xxd::Application
{
public:
	AppTest() { };
	~AppTest() { };

	virtual void Run() override
	{
        int i = 0;
        while (i++ < 100000)
        {
            DEBUG_LOG("Helow", " Chenqiudu");
            INFO_LOG("Helow", " Chenqiudu");
            WARN_LOG("Helow", " Chenqiudu");
            ERROR_LOG("Helow", " Chenqiudu");
            FATAL_LOG("Helow", " Chenqiudu");
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
};

xxd::Application* xxd::CreateApplication()
{
	return new AppTest();
}
