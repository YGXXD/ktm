#include "Application.h"
#include "Log/Logger.h"
#include "Event/AppEvent.h"
#include "Event/MouseEvent.h"

bool xxd::Application::bIsQuit = false;
std::unique_ptr<xxd::Window> xxd::Application::mainWindow;

void xxd::Application::Initialize()
{
	Window::Init();
}

void xxd::Application::Destroy()
{
	Window::Quit();
}

void xxd::Application::Run()
{
    mainWindow = std::unique_ptr<Window>(Window::Create(WindowProps()));
 	mainWindow->SetEventCallback(&Application::OnEvent);	
 	while(!bIsQuit)
    {
		Window::PollEvent();
        mainWindow->OnUpdate();
    }
}

void xxd::Application::OnEvent(xxd::Event& event)
{
	EventDispatcher ed(event);
	ed.Dispatch<WindowCloseEvent>([](xxd::WindowCloseEvent& event)->bool { bIsQuit = true; return true; });
	ed.Dispatch<WindowResizeEvent>([](xxd::WindowResizeEvent& event)->bool { XXD_DEBUG(event); return true; });
	ed.Dispatch<MouseMovedEvent>([](xxd::MouseMovedEvent& event)->bool { XXD_DEBUG(event); return true; });
}