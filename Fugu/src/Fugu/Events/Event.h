#pragma once

#include "fgpch.h"
#include "Fugu/Core.h"

namespace Fugu {
	// Events are blocking, meaning when an event ocurrs
	// it immediately gets dispatched and must be dealt.
	// For future, a better strategy might be to buffer events
	// in an event bus and process them during the "event" part of the update stage

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class FUGU_API Event {
		friend class EventDispatcher;
	protected:

	public:
		bool Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher {
		template<typename T>
		using EventFc = std::function<bool(T&)>;

	private:
		Event& m_Event;

	public:
		EventDispatcher(Event& event)
			:m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFc<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<< (std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}
