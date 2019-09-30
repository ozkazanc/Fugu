#pragma once

#include "Event.h"

namespace Fugu {

	class FUGU_API KeyEvent : public Event {
	protected:
		KeyEvent(int keyCode)
			:m_KeyCode(keyCode) {}

		int m_KeyCode;

	public:
		inline int GetKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	};

	class FUGU_API KeyPressedEvent : public KeyEvent {
	private:
		int m_RepeatCount;
	
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	};

	class FUGU_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyReleased);
	};

	class FUGU_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keyCode)
			:KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};
}