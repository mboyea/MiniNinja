#include "Input.h"
#include <array>
#include <vector>
#include <string>

const unsigned short MAX_SCANCODE = 285U;
typedef std::array<bool, MAX_SCANCODE> KeyboardState;

static std::string* ioTextTarget = nullptr;
static bool hasTextUpdated = false;
static char ignoreCharacter = '\n';
static KeyboardState currentKeyState;
static KeyboardState lastKeyState;

void UpdateKey(SDL_KeyboardEvent* event, bool isDown) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_SCANCODE) {
		currentKeyState[event->keysym.scancode] = isDown;
	}
}

void ClearInputBufferText() {
	std::vector<SDL_Event> eventsIgnored;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_TEXTINPUT:
			// throw away event
			break;
		default:
			// ignore all other events
			eventsIgnored.push_back(event);
			break;
		}
	}
	for (SDL_Event event : eventsIgnored) {
		SDL_PushEvent(&event);
	}
}

void StartTextInput(std::string* target, char ignoreChar) {
	SDL_StartTextInput();
	ClearInputBufferText();
	ioTextTarget = target;
	ignoreCharacter = ignoreChar;
	hasTextUpdated = true;
}

void StopTextInput() {
	SDL_StopTextInput();
	ioTextTarget = nullptr;
}

void HandleInputEvents() {
	// record last keyboard state
	lastKeyState = currentKeyState;

	std::vector<SDL_Event> eventsIgnored;
	SDL_Event event;
	if (ioTextTarget == nullptr) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				// update new keyboard state for each key
				UpdateKey(&event.key, true);
				break;
			case SDL_KEYUP:
				// update new keyboard state for each key
				UpdateKey(&event.key, false);
				break;
			default:
				// ignore all other events
				eventsIgnored.push_back(event);
				break;
			}
		}
	}
	else {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				// Backspace
				if (event.key.keysym.sym == SDLK_BACKSPACE && ioTextTarget->size() > 0) {
					hasTextUpdated = true;
					ioTextTarget->pop_back();
				}
				// Copy Buffer Interactions
				else if (SDL_GetModState() & KMOD_CTRL) {
					// Copy
					if (event.key.keysym.sym == SDLK_c) {
						hasTextUpdated = true;
						SDL_SetClipboardText(ioTextTarget->c_str());
					}
					// Paste
					else if (event.key.keysym.sym == SDLK_v) {
						hasTextUpdated = true;
						*ioTextTarget += SDL_GetClipboardText();
					}
					// Cut
					else if (event.key.keysym.sym == SDLK_x) {
						hasTextUpdated = true;
						SDL_SetClipboardText(ioTextTarget->c_str());
						ioTextTarget->erase();
					}
				}
				UpdateKey(&event.key, true);
				break;
			case SDL_KEYUP:
				UpdateKey(&event.key, false);
				break;
			case SDL_TEXTINPUT:
				// Text Input
				if (!(event.text.text[0] == ignoreCharacter || SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V'))) {
					hasTextUpdated = true;
					*ioTextTarget += event.text.text;
				}
				break;
			default:
				// ignore all other events
				eventsIgnored.push_back(event);
				break;
			}
		}
	}
	for (SDL_Event event : eventsIgnored) {
		SDL_PushEvent(&event);
	}
}

bool IsKeyDown(SDL_Scancode key) {
	return currentKeyState[key];
}

bool IsKeyPressed(SDL_Scancode key) {
	return currentKeyState[key] && !lastKeyState[key];
}

bool HasTextInputUpdated() {
	return hasTextUpdated;
}

void SetTextInputUpdated(bool textUpdated) {
	hasTextUpdated = textUpdated;
}