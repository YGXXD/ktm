#include "Application.h"
#include "Window.h"
#include "Renderer/GraphicsContext.h"
#include "Log/Logger.h"
#include "Event/AppEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"
#include "Math/XMath.h"

bool xxd::Application::bIsQuit = false;
std::unique_ptr<xxd::Window> xxd::Application::mainWindow;
std::unique_ptr<xxd::GraphicsContext> xxd::Application::mainGraphics;

void xxd::Application::Initialize()
{
	Window::Init();
	GraphicsContext::Init();
}

void xxd::Application::Destroy()
{
	GraphicsContext::Quit();
	Window::Quit();
}

void xxd::Application::Run()
{
	mathTest();
	return;
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

void xxd::Application::OnEvent(xxd::Event& event)
{
	EventDispatcher ed(event);
	ed.Dispatch<WindowCloseEvent>([](xxd::WindowCloseEvent& event)->bool { bIsQuit = true; return true; });
	ed.Dispatch<WindowResizeEvent>([](xxd::WindowResizeEvent& event)->bool { XXD_DEBUG(event); return true; });
	ed.Dispatch<KeyPressedEvent>([](xxd::KeyPressedEvent& event)->bool { XXD_DEBUG(event); return true; });
}
