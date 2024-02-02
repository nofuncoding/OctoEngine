#include <Octo.h>

class ExampleLayer : public Octo::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {

    }

    void OnUpdate() override
    {
        OCTO_INFO("ExampleLayer::OnUpdate");
    }

    void OnEvent(Octo::Event& event) override
    {
        OCTO_TRACE("ExampleLayer::OnEvent {0}", event);
    }
};

class Sandbox : public Octo::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Octo::Application* Octo::CreateApplication()
{
    return new Sandbox();
}