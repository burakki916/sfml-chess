#include "Window.hpp"
#include "EventManager.hpp"
using namespace std;

EventInfo::EventInfo(sf::Event& thisEvent) {
	type = thisEvent.type;
	switch (thisEvent.type) {
	case sf::Event::Resized:
		size = thisEvent.size;
		break;
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
		key = thisEvent.key;
		break;
	case sf::Event::TextEntered:
		text = thisEvent.text;
		break;
	case sf::Event::MouseMoved:
		mouseMove = thisEvent.mouseMove;
		break;
	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased:
		mouseButton = thisEvent.mouseButton;
		break;
	case sf::Event::MouseWheelScrolled:
		mouseWheelScroll = thisEvent.mouseWheelScroll;
		break;
	case sf::Event::JoystickMoved:
		joystickMove = thisEvent.joystickMove;
		break;
	case sf::Event::JoystickButtonPressed:
	case sf::Event::JoystickButtonReleased:
		joystickButton = thisEvent.joystickButton;
		break;
	case sf::Event::JoystickConnected:
	case sf::Event::JoystickDisconnected:
		joystickConnect = thisEvent.joystickConnect;
		break;
	case sf::Event::TouchBegan:
	case sf::Event::TouchMoved:
	case sf::Event::TouchEnded:
		touch = thisEvent.touch;
		break;
	case sf::Event::SensorChanged:
		sensor = thisEvent.sensor;
		break;
	}
}

EventInfo::EventInfo(int initType) { type = initType; }
EventInfo::EventInfo() { }

// -- -- -- -- -- -- -- -- -- -- //

EventManager::EventMap EventManager::events;
EventManager::BindMap EventManager::SFMLBindings;

void EventManager::run() {
	sf::Event thisEvent;
	while (Window::pollEvent(thisEvent)) {
		handleSFMLEvent(thisEvent);
	}
}

void EventManager::handleSFMLEvent(sf::Event &thisEvent) {
	EventInfo* thisEventInfo = new EventInfo(thisEvent);

	auto range = EventManager::SFMLBindings.equal_range(thisEvent.type);
	for (auto i = range.first; i != range.second; i++) {
		EventManager::fireEvent(i->second, thisEventInfo);
	}

	delete thisEventInfo;
}

void EventManager::connectToEvent(string eventName, EventManager::EventFunction fx) {
	EventManager::events.emplace(eventName, fx);
}

void EventManager::bindInputToEvent(string eventName, int eventType) {
	EventManager::SFMLBindings.emplace(eventType, eventName);
}

void EventManager::fireEvent(string eventName) {
	auto range = EventManager::events.equal_range(eventName);
	for (auto i = range.first; i != range.second; ++i) {
		EventInfo* defaultInfo = new DefaultEventInfo;
		i->second(defaultInfo);
		delete defaultInfo;
	}
}

void EventManager::fireEvent(string eventName, EventInfo* info) {
	auto range = EventManager::events.equal_range(eventName);
	for (auto i = range.first; i != range.second; ++i) {
		i->second(info);
	}
}