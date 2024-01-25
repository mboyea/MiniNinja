#include "Camera.h"
#include "Window.h"

Camera::Camera(SDL_Point dim)
	: dest({ 0, 0, dim.x, dim.y }), renderTexture(SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dim.x, dim.y)) {}

void Camera::SetPos(SDL_Point pos) {
	dest.x = pos.x;
	dest.y = pos.y;
}

void Camera::SetDim(SDL_Point dim) {
	SDL_DestroyTexture(renderTexture);
	renderTexture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dim.x, dim.y);
	dest.w = dim.x;
	dest.h = dim.y;
}

SDL_Point Camera::GetPos() {
	return { dest.x, dest.y };
}

SDL_Point Camera::GetDim() {
	return { dest.w, dest.h };
}

SDL_Rect Camera::GetDest() {
	return dest;
}

std::ostream& Camera::Serialize(std::ostream& os) {
	return os << dest.x << ' ' << dest.y << ' ' << dest.w << ' ' << dest.h;
}

std::istream& Camera::Deserialize(std::istream& is) {
	return is >> dest.x >> dest.y >> dest.w >> dest.h;
}

Camera::operator SDL_Texture* () const {
	return renderTexture;
}