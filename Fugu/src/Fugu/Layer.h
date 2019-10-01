#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Fugu {

	class FUGU_API Layer {

	protected:
		const std::string m_DebugName;

	public:
		Layer(const std::string& name = "Layer")
			:m_DebugName(name) {}

		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_DebugName; }
	};
}