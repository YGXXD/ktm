#include "Application.h"
#include "Window.h"
#include "Renderer/GraphicsContext.h"
#include "Log/Logger.h"
#include "Event/AppEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

bool ktl::Application::bIsQuit = false;
std::unique_ptr<ktl::Window> ktl::Application::mainWindow;
std::unique_ptr<ktl::GraphicsContext> ktl::Application::mainGraphics;

void ktl::Application::Initialize()
{
	Window::Init();
	GraphicsContext::Init();
}

void ktl::Application::Destroy()
{
	GraphicsContext::Quit();
	Window::Quit();
}

void ktl::Application::Run()
{
    mainWindow = std::unique_ptr<Window>(Window::Create(WindowProps()));
 	mainWindow->eventCallback.BindAnyFunc(&Application::OnEvent);	
	mainGraphics = std::unique_ptr<GraphicsContext>(GraphicsContext::Create(mainWindow->GetNativeWindow()));	

 	while(!bIsQuit)
    {
		Window::PollEvent();
        mainWindow->OnUpdate();
		mainGraphics->SwapBuffer();
    }
	
	mainGraphics.reset();
	mainWindow.reset();
}

void ktl::Application::OnEvent(ktl::Event& event)
{
	EventDispatcher ed(event);
	ed.Dispatch<WindowCloseEvent>([](ktl::WindowCloseEvent& event)->bool { bIsQuit = true; return true; });
	ed.Dispatch<WindowResizeEvent>([](ktl::WindowResizeEvent& event)->bool { KTL_DEBUG(event); return true; });
	ed.Dispatch<KeyPressedEvent>([](ktl::KeyPressedEvent& event)->bool { KTL_DEBUG(event); return true; });
}
