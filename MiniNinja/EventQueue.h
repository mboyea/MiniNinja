#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#pragma once

#include <cstdint>

void PushEvent(void (*func)(), uint32_t msToEvent);
void HandleEventQueue();

#endif // !EVENT_QUEUE_H