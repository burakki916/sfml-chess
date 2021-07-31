#pragma once
#include "Window.hpp"
#include "EventManager.hpp"
using namespace std;

EventManager::EventMap EventManager::events;
EventManager::BindMap EventManager::SFMLBindings;

void EventManager::run() {
	sf::Event thisEvent;
	while (Window::pollEvent(thisEvent)) {
		handleSFMLEvent(thisEvent);
	}
}

void EventManager::handleSFMLEvent(sf::Event &thisEvent) {
	EventInfo* thisEventInfo = new DefaultEventInfo;
	switch (thisEvent.type) {
		// Set EventInfo for specific events
	}

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