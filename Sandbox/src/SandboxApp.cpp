#include <DK.h>

class Sandbox : public DK::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

DK::Application* DK::CreateApplication()
{
	return new Sandbox();
}