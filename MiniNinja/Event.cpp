#include "Event.h"
#include <SDL.h>

struct EventLink {
	void (*Function)();
	size_t timeOf;
	EventLink* next;

	EventLink(void(*Function)(), size_t timeOf, EventLink* nextEvent)
		: Function(Function), timeOf(timeOf), next(nextEvent) {}
};

static EventLink* eventHead = nullptr;

void InsertEvent(EventLink* prev, void (*Function)(), size_t timeOf) {
    if (prev == nullptr) {
		eventHead = new EventLink(Function, timeOf, nullptr);
        return;
    }
    EventLink* eventLink = new EventLink(Function, timeOf, prev->next);
    prev->next = eventLink;
}
EventLink* GetEventLocation(EventLink* prev, size_t timeOf) {
	if (prev == nullptr || prev->timeOf >= timeOf) {
		return nullptr;
	}
	if (prev->next->timeOf >= timeOf) {
		return prev;
	}
	return GetEventLocation(prev->next, timeOf);
}
void PushEvent(void (*Function)(), size_t msDifference) {
	size_t timeOf = SDL_GetTicks() + msDifference;
	InsertEvent(GetEventLocation(eventHead, timeOf), Function, timeOf);
}
void DeleteHead() {
	EventLink* temp = eventHead;
	eventHead = eventHead->next;
	delete temp;
}
void HandleEvents() {
	if (eventHead == nullptr) {
		return;
	}
	if (SDL_GetTicks() >= eventHead->timeOf) {
		eventHead->Function();
		DeleteHead();
		HandleEvents();
	}
}