#pragma once

#include "Core.h"

namespace DK {

	class DK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


