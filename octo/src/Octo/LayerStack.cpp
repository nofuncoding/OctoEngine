#include "octo_pch.h"
#include "LayerStack.h"

namespace Octo {

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* layer)
    {
        m_Layers.emplace_back(layer);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto layerIterator = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);

        if (layerIterator != m_Layers.begin() + m_LayerInsertIndex)
        {
            layer->OnDetach();
            m_Layers.erase(layerIterator);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* layer)
    {
        auto layerIterator = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), layer);

        if (layerIterator != m_Layers.end())
        {
            layer->OnDetach();
            m_Layers.erase(layerIterator);
        }
    }
}