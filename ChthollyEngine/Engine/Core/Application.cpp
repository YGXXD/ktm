#include "Application.h"
#include "WindowContext.h"
#include "Window.h"
#include "Render/GraphicsContext.h"
#include "Render/Renderer.h"
#include "Log/Logger.h"
#include "Event/AppEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"
#include "Math/KTMTest.h"

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

const char* a = "sss";

void keg::Application::Run()
{
	// const char* b = "sss";
	// const std::string c = "sss";
	// const std::string d = "sss";

	// int a[3][4] = {1, 2, 3 ,4 ,5 , 6, 7 , 8, 9, 10, 11, 12};
	// int (*p)[4] = (int (*) [4])a;
	// std::cout << ((int*)a)[14] << ", " << p[3][2] <<std::endl;
	test::MatTest();
	return;
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
