#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <SDL.h>

class Camera {
private:
	SDL_Rect dest;
	SDL_Texture* renderTexture;
public:
	Camera(SDL_Point dimensions = { 320, 240 });

	void Resize(SDL_Point dimensions);
	SDL_Point GetPos();
	SDL_Point GetDim();
	SDL_Rect GetDest();

	operator SDL_Texture*() const;
};

#endif // !CAMERA_H