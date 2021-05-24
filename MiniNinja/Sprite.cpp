#include "Sprite.h"
#include "FileParameters.h"
#include "Draw.h"
#include "Scene.h"
#include "Log.h"

void Sprite::SetDimensionsByTexture() {
	SDL_Point dimensions = { 0, 0 };
	if (SDL_QueryTexture(texture, NULL, NULL, &dimensions.x, &dimensions.y) < 0) {
		Log("Failed to query texture: " + (std::string)SDL_GetError(), WARNING);
	}
	dim = dimensions;
}

void Sprite::SetDimensions(SDL_Point dimensions) {
	if (dimensions.x == 0 || dimensions.y == 0) {
		SetDimensionsByTexture();
		return;
	}
	dim = dimensions;
}

void Sprite::Update() {}

void Sprite::Render() {
	SDL_Rect rect = SceneToViewport({ pos.x, pos.y, dim.x, dim.y }, GetActiveScene());
	DrawTexture(texture, &rect);
}

void Sprite::OnCollision(Entity* collisionEntity) {}

std::vector<Resource*> Sprite::GetRequiredResources() {
	std::vector<Resource*> resources;
	// TODO: outline required modules, fonts, textures, and animations
	std::vector<Resource*> baseResources = Entity::GetRequiredResources();
	resources.reserve(resources.size() + baseResources.size());
	resources.insert(resources.end(), baseResources.begin(), baseResources.end());
	return resources;
}

std::ostream& Sprite::Serialize(std::ostream& os) {
	Entity::Serialize(os);
	os << ' ' << MakeSerializable(GetKey(texture)) << ' ' << std::to_string(dim.x) << ' ' << std::to_string(dim.y);
	return os;
}

std::istream& Sprite::Deserialize(std::istream& is) {
	Entity::Deserialize(is);
	texture = GetTexture(DeserializeString(is));
	return is >> dim.x >> dim.y;
}
