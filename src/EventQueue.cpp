#include "EventQueue.h"
#include <SDL.h>

struct EventNode {
	void (*func)();
	uint32_t timeOf;
	EventNode* next;

	EventNode(void(*func)(), uint32_t timeOf, EventNode* next)
		: func(func), timeOf(timeOf), next(next) {}
};

static EventNode* eventHead = nullptr;

// recursive function to crawl for the proper location of an event at time timeOfEvent,
// beginning at prev (to crawl whole tree, prev=eventHead)
EventNode* GetEventLocation(EventNode* prev, size_t timeOfEvent) {
	if (prev == nullptr || prev->timeOf >= timeOfEvent) {
		return nullptr;
	}
	if (prev->timeOf <= timeOfEvent) {
		return prev;
	}
	return GetEventLocation(prev->next, timeOfEvent);
}

void InsertEvent(EventNode* prev, void (*func)(), size_t timeOfEvent) {
	if (prev == nullptr) {
		eventHead = new EventNode(func, timeOfEvent, nullptr);
		return;
	}
	EventNode* eventNode = new EventNode(func, timeOfEvent, prev->next);
	prev->next = eventNode;
}

void PushEvent(void(*func)(), uint32_t msToEvent) {
	uint32_t timeOfEvent = SDL_GetTicks() + msToEvent;
	InsertEvent(GetEventLocation(eventHead, timeOfEvent), func, timeOfEvent);
}

void DeleteEventHead() {
	EventNode* temp = eventHead;
	eventHead = eventHead->next;
	delete temp;
}

void HandleEventQueue() {
	if (eventHead == nullptr) {
		return;
	}
	if (SDL_GetTicks() >= eventHead->timeOf) {
		eventHead->func();
		DeleteEventHead();
		HandleEventQueue();
	}
}