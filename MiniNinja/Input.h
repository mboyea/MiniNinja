#ifndef INPUT_H
#define INPUT_H
#pragma once

#include <SDL.h>
#include <string>

void StartTextInput(std::string* target, char ignoreChar = '\a');
void StopTextInput();
void HandleInputEvents();

bool IsKeyDown(SDL_Scancode key);
bool IsKeyPressed(SDL_Scancode key);
// TODO: MouseToWindowPos() & MouseToScenePos()
// TODO: IsMouseDown(mouseButton) & IsMousePressed(int mouseButton)
// TODO: MouseScrollWheelState()

#endif // !INPUT_H