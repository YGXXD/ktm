#include "Core/EntryPoint.h"

class SandBox : public xxd::Application
{
public:
	SandBox() { };
	~SandBox() { };

	virtual void Run() override
	{
        xxd::Application::Run();
    }
};

xxd::Application* xxd::CreateApplication()
{
	return new SandBox();
}

int main(int argc, const char* argv[])
{
	return EngineMain(argc, argv);
}