#include "octo_pch.h"
#include "Application.h"

namespace Octo {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

        OCTO_CORE_TRACE("{0}", event);

        for (auto iterator = m_LayerStack.rbegin(); iterator != m_LayerStack.rend(); ++iterator)
        {
            if (event.Handled)
                break;

            (*iterator)->OnEvent(event);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run()
    {
        while (m_Running)
        {
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }
}