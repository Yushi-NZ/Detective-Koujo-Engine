#pragma once

#ifdef DK_PLATFORM_WINDOWS

extern DK::Application* DK::CreateApplication();

int main(int argc, char** argv)
{
	DK::Log::Init();
	DK_CORE_WARN("Initialized Log!");
	int a = 5;
	DK_INFO("Hello! Var={0}", a);

	auto app = DK::CreateApplication();
	app->Run();
	delete app;
}

#endif