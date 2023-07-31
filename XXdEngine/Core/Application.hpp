#ifndef APPLICATION_HPP
#define APPLICATION_HPP

namespace xxd
{
class Application
{
public:
	Application();
	virtual ~Application();
	virtual void Run() = 0;
};

Application* CreateApplication();

}

#endif
