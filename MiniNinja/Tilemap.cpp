#include "Tilemap.h"
#include "Draw.h"
#include "Scene.h"

void Tilemap::Render() {
}

std::ostream& Tilemap::Serialize(std::ostream& os) {
	Sprite::Serialize(os);
	return os << tileDim.x << ' ' << tileDim.y;
}

std::istream& Tilemap::Deserialize(std::istream& is) {
	Sprite::Deserialize(is);
	return is >> tileDim.x >> tileDim.y;
}
