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
        //     DEBUG_LOG("Helow", " Chenqiudu");
        //     INFO_LOG("Helow", " Chenqiudu");
        //     WARN_LOG("Helow", " Chenqiudu");
        //     ERROR_LOG("Helow", " Chenqiudu");
        //     FATAL_LOG("Helow", " Chenqiudu");
        //     std::this_thread::sleep_for(std::chrono::milliseconds(300));
        // }
    }
}