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
    }
}
