#include "Application.h"

#include "DK/Events/ApplicationEvent.h"
#include "DK/Log.h"

namespace DK {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		DK_TRACE(e);

		while (true);
	}
}
