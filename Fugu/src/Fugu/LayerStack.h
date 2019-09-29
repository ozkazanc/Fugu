#pragma once

#include "Fugu/Core.h"
#include "Layer.h"

//#include <vector>

namespace Fugu {

	class FUGU_API LayerStack {
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_InsertLayer;

	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	};
}
