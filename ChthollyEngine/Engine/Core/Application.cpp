#include "Application.h"
#include "WindowContext.h"
#include "Window.h"
#include "Render/GraphicsContext.h"
#include "Render/Renderer.h"
#include "Log/Logger.h"
#include "Event/AppEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

bool keg::Application::bIsQuit = false;
std::unique_ptr<keg::Window> keg::Application::mainWindow;
std::unique_ptr<keg::Renderer> keg::Application::mainRenderer;

void keg::Application::Initialize()
{
	WindowContext::Init();
	GraphicsContext::Init();
}

void keg::Application::Destroy()
{
	GraphicsContext::Quit();
	WindowContext::Quit();
}

void keg::Application::Run()
{
    mainWindow = std::unique_ptr<Window>(Window::Create(WindowProps()));
 	mainWindow->eventCallback.BindAnyFunc(&Application::OnEvent);	
	mainRenderer = std::unique_ptr<Renderer>(Renderer::Create(mainWindow->GetNativeWindow()));	

 	while(!bIsQuit)
    {
		WindowContext::PollEvent();
        mainWindow->OnUpdate();
		mainRenderer->SwapBuffer();
    }
	
	mainRenderer.reset();
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
