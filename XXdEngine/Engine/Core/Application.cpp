#include "Application.h"
#include "Log/Logger.h"

void WindowEventCallback(xxd::Event& event)
{
	XXD_DEBUG(event)
}

xxd::Application::Application()
{
	Window::Init();
    
}

xxd::Application::~Application()
{
	Window::Quit();
}

void xxd::Application::Run()
{
    mainWindow = std::unique_ptr<Window>(Window::Create(WindowProps()));
 	mainWindow->SetEventCallback(&WindowEventCallback);	
 	while(1)
    {
		Window::PollEvent();
        mainWindow->OnUpdate();
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
    }
}
