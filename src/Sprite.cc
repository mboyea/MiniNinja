#include "Sprite.h"
#include "FileParameters.h"
#include "Draw.h"
#include "Scene.h"
#include "Log.h"

SDL_Point Sprite::GetTextureDimensions() {
	SDL_Point dimensions = { 0, 0 };
	if (SDL_QueryTexture(texture, NULL, NULL, &dimensions.x, &dimensions.y) < 0) {
		Log("Failed to query texture: " + (std::string)SDL_GetError(), WARNING);
	}
	return dimensions;
}

void Sprite::Render() {
	SDL_Rect rect = SceneToViewport({ pos.x, pos.y, dim.x, dim.y }, GetActiveScene());
	DrawTexture(texture, &rect);
}

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
	return os << ' ' << MakeSerializable(GetKey(texture)) << ' ' << dim.x << ' ' << dim.y;
}

std::istream& Sprite::Deserialize(std::istream& is) {
	Entity::Deserialize(is);
	texture = GetTexture(DeserializeString(is));
	return is >> dim.x >> dim.y;
}