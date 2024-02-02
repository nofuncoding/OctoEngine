#pragma once

#include "Core.h"

#include "Octo/LayerStack.h"
#include "Octo/Events/Event.h"
#include "Octo/Events/ApplicationEvent.h"
#include "Octo/Window.h"

namespace Octo {

    class OCTO_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    private:
        bool OnWindowClose(WindowCloseEvent& event);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    // To be defined in client
    Application* CreateApplication();
}