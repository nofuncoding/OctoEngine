#include <Octo.h>


class Sandbox : public Octo::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

Octo::Application* Octo::CreateApplication()
{
    return new Sandbox();
}