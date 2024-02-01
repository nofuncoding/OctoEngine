#pragma once

#include "Event.h"

namespace Octo
{
    class OCTO_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : m_X(x), m_Y(y)
        {
        }

        float GetX() const { return m_X; }
        float GetY() const { return m_Y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << " X: " << m_X << " Y: " << m_Y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_X, m_Y;
    };

    class OCTO_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xoffset, float yoffset)
            : m_XOffset(xoffset), m_YOffset(yoffset)
        {
        }

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << " X: " << m_XOffset << " Y: " << m_YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_XOffset, m_YOffset;
    };

    class OCTO_API MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(int button)
            : m_Button(button)
        {
        }

        int GetButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    protected:
        int m_Button;
    };

    class OCTO_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << " Button: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class OCTO_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << " Button: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}