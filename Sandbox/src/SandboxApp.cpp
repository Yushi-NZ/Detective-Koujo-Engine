#include <DK.h>

class ExampleLayer : public DK::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		DK_INFO("ExampleLayer::Update");
	}

	void OnEvent(DK::Event& event) override
	{
		DK_TRACE("{0}", event);
	}

};

class Sandbox : public DK::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new DK::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

DK::Application* DK::CreateApplication()
{
	return new Sandbox();
}