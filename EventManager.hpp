#pragma once
#include <unordered_map>
#include <SFML/Window.hpp>
using namespace std;

// EventInfo is passed into every event callback function (from connectToEvent)
// Ability to provide any necessary information to the callback functions
class EventInfo {
	public:
		EventInfo(string initInputType, int initCode) {
			inputType = initInputType;
			code = initCode;
		}

		string inputType;
		int code;
};

// The following inherited EventInfo classes can also be passed into the callback functions
// These help define info necessary for specific types of input
class DefaultEventInfo : public EventInfo {
	public: DefaultEventInfo() : EventInfo("N/A", -1) { }
};

class KeyboardEventInfo : public EventInfo {
	public: KeyboardEventInfo(int keycode) : EventInfo("Keyboard", keycode) { }
};

class MouseEventInfo : public EventInfo {
	public: MouseEventInfo(int inputcode) : EventInfo("Mouse", inputcode) { }
};

class EventManager {
	public:
		typedef void (*EventFunction)(EventInfo*);
		typedef unordered_multimap<string, EventFunction> EventMap;
		typedef unordered_multimap<int, std::string> BindMap;

		// Run every frame. Handles event polling
		static void run();
		
		// Connect a callback function to some event. Creates event if it doesn't exist
		static void connectToEvent(string eventName, EventFunction fx);
		// Bind an SFML event to one of our events from above
		static void bindInputToEvent(string eventName, int eventType);

		// Execute all functions connected to eventName. 
		// Optional passing of EventInfo pointer, else it will pass DefaultEventInfo
		static void fireEvent(string eventName);
		static void fireEvent(string eventName, EventInfo* info);
	
	private:
		// Maps to store events and input bindings
		static EventMap events;
		static BindMap SFMLBindings;

		// Helper function to fire an event based off of an sfml event
		static void handleSFMLEvent(sf::Event& thisEvent);
};