#pragma once

#ifdef DK_PLATFORM_WINDOWS

extern DK::Application* DK::CreateApplication();

int main(int argc, char** argv)
{
	auto app = DK::CreateApplication();
	app->Run();
	delete app;
}

#endif
