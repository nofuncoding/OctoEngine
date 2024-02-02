#pragma once

#include "octo_pch.h"

#include "Octo/Core.h"
#include "Octo/Events/Event.h"

namespace Octo {

    struct WindowProperties
    {
        std::string Title;
        unsigned int Width, Height;
        bool VSync = true; // TODO

        WindowProperties(const std::string& title = "Octo Engine",
                        unsigned int width = 1280,
                        unsigned int height = 720,
                        bool vsync = true)
            : Title(title), Width(width), Height(height), VSync(vsync)
        {
        }
    };

    // Interface representing a desktop system based Window
    class OCTO_API Window
    {
    public:
        using EventCallbackFunc = std::function<void(Event&)>;

        virtual ~Window() {};

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // window attributes
        virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        static Window* Create(const WindowProperties& props = WindowProperties());
    };
}