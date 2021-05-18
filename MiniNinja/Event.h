#ifndef EVENT_H
#define EVENT_H
#pragma once

void PushEvent(void (*Function)(), size_t msDifference = 0);
void HandleEvents();

#endif // !EVENT_H