#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <SDL.h>
#include <iostream>

class Camera {
private:
	SDL_Rect dest;
	SDL_Texture* renderTexture;
public:
	Camera(SDL_Point dimensions = { 320, 240 });

	void SetPos(SDL_Point position);
	void SetDim(SDL_Point dimensions);
	SDL_Point GetPos();
	SDL_Point GetDim();
	SDL_Rect GetDest();

	// Generate serialized text data for this camera into the stream
	std::ostream& Serialize(std::ostream& os);
	// Populate this camera by deserializing text data from the stream
	std::istream& Deserialize(std::istream& is);

	operator SDL_Texture*() const;
};

#endif // !CAMERA_H