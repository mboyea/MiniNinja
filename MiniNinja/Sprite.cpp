#include "Sprite.h"
#include "FileParameters.h"
#include "Draw.h"
#include "Scene.h"
#include "Log.h"
#include "Input.h"

SDL_Point Sprite::GetTextureDimensions() {
	SDL_Point dimensions = { 0, 0 };
	if (SDL_QueryTexture(texture, NULL, NULL, &dimensions.x, &dimensions.y) < 0) {
		Log("Failed to query texture: " + (std::string)SDL_GetError(), WARNING);
	}
	return dimensions;
}

void Sprite::SetDimensionsByTexture() {
	dim = GetTextureDimensions();
}

void Sprite::SetDimensions(SDL_Point dimensions) {
	dim = dimensions;
}

void Sprite::Update() {
	if (IsKeyDown(SDL_SCANCODE_W)) {
		pos.y--;
	}
	if (IsKeyDown(SDL_SCANCODE_S)) {
		pos.y++;
	}
	if (IsKeyDown(SDL_SCANCODE_A)) {
		pos.x--;
	}
	if (IsKeyDown(SDL_SCANCODE_D)) {
		pos.x++;
	}
	if (IsKeyPressed(SDL_SCANCODE_SPACE)) {
		Log(GetKey(texture));
		colliders.push_back(new AABBCollider({ 0, 0, 12, 12 }));
		Log(GetKey(texture));
	}
}

void Sprite::Render() {
	SDL_Rect rect = SceneToViewport({ pos.x, pos.y, dim.x, dim.y }, GetActiveScene());
	DrawTexture(texture, &rect);
}

void Sprite::OnCollision(Entity* collisionEntity) {}

std::set<Resource>& Sprite::GetRequiredResources(std::set<Resource>& resourcesOut) {
	Entity::GetRequiredResources(resourcesOut);
	std::string key = GetKey(texture);
	if (key != "") {
		resourcesOut.insert(Resource(key, RESOURCE_TEXTURE));
	}
	return resourcesOut;
}

std::ostream& Sprite::Serialize(std::ostream& os) {
	Entity::Serialize(os);
	os << ' ' << MakeSerializable(GetKey(texture)) << ' ' << dim.x << ' ' << dim.y;
	return os;
}

std::istream& Sprite::Deserialize(std::istream& is) {
	Entity::Deserialize(is);
	texture = GetTexture(DeserializeString(is));
	return is >> dim.x >> dim.y;
}