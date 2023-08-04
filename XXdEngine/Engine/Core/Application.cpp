#include "Application.h"
#include "Log/Logger.h"

xxd::Application::Application()
{
    mainWindow = std::unique_ptr<Window>(Window::Create(WindowProps()));
}

xxd::Application::~Application()
{

}

void xxd::Application::Run()
{
    while(1)
    {
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