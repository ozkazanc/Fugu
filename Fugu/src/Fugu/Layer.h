#pragma once

#include "Core.h"
#include "Timestep.h"
#include "Events/Event.h"

namespace Fugu {

	class Layer {

	protected:
		const std::string m_DebugName;

	public:
		Layer(const std::string& name = "Layer")
			:m_DebugName(name) {}

		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_DebugName; }
	};
}