#pragma once
#include <unordered_map>
#include <SFML/Window.hpp>

using namespace std;

class TestEventInfo : public sf::Event {
	public:

};

// EventInfo is passed into every event callback function (from connectToEvent)
// Ability to provide any necessary information to the callback functions
class EventInfo {
	public:
		int type = -1;

		union {
			sf::Event::SizeEvent size;
			sf::Event::KeyEvent key;
			sf::Event::TextEvent text;
			sf::Event::MouseMoveEvent mouseMove;
			sf::Event::MouseButtonEvent mouseButton;
			sf::Event::MouseWheelScrollEvent mouseWheelScroll;
			sf::Event::JoystickMoveEvent joystickMove;
			sf::Event::JoystickButtonEvent joystickButton;
			sf::Event::JoystickConnectEvent joystickConnect;
			sf::Event::TouchEvent touch;
			sf::Event::SensorEvent sensor;
		};

		EventInfo(sf::Event& thisEvent);
		EventInfo(int initType);
		EventInfo();
};

class DefaultEventInfo : public EventInfo {
	public: DefaultEventInfo() : EventInfo(-1) { }
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