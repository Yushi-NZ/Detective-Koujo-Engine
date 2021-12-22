#pragma once

#ifdef DK_PLATFORM_WINDOWS

extern DK::Application* DK::CreateApplication();

int main(int argc, char** argv)
{
	DK::Log::Init();
	DK_CORE_WARN("Initalized");
	DK_INFO("Initalized");

	auto app = DK::CreateApplication();
	app->Run();
	delete app;
}

#endif
