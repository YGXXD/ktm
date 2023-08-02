#include "Core/EntryPoint.h"

class AppTest : public xxd::Application
{
public:
	AppTest() { };
	~AppTest() { };

	virtual void Run() override
	{
        xxd::Application::Run();
    }
};

xxd::Application* xxd::CreateApplication()
{
	return new AppTest();
}

int main(int argc, const char* argv[])
{
	return EngineMain(argc, argv);
}