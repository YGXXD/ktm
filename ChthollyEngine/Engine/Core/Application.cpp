#include "Application.h"
#include "Window.h"
#include "Renderer/GraphicsContext.h"
#include "Log/Logger.h"
#include "Event/AppEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

bool keg::Application::bIsQuit = false;
std::unique_ptr<keg::Window> keg::Application::mainWindow;
std::unique_ptr<keg::GraphicsContext> keg::Application::mainGraphics;

void keg::Application::Initialize()
{
	Window::Init();
	GraphicsContext::Init();
}

void keg::Application::Destroy()
{
	GraphicsContext::Quit();
	Window::Quit();
}

void keg::Application::Run()
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

void keg::Application::OnEvent(keg::Event& event)
{
	EventDispatcher ed(event);
	ed.Dispatch<WindowCloseEvent>([](WindowCloseEvent& event)->bool { bIsQuit = true; return true; });
	ed.Dispatch<WindowResizeEvent>([](WindowResizeEvent& event)->bool { KEG_DEBUG(event); return true; });
	ed.Dispatch<KeyPressedEvent>([](KeyPressedEvent& event)->bool { KEG_DEBUG(event); return true; });
	ed.Dispatch<MouseButtonPressedEvent>([](MouseButtonPressedEvent& event)->bool { KEG_DEBUG(event); return true; });
}
