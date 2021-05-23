#include "Sprite.h"
#include "FileParameters.h"

void Sprite::Update() {}
void Sprite::Render() {}
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
	os << ' ' << MakeSerializable(GetKey(texture));
	return os;
}

std::istream& Sprite::Deserialize(std::istream& is) {
	Entity::Deserialize(is);
	texture = GetTexture(DeserializeString(is));
	return is;
}
