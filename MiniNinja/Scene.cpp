#include "Scene.h"
#include "Window.h"
#include "Draw.h"
#include "Log.h"

Scene::~Scene() {
	for (Entity* entity : entities) {
		delete entity;
	}
}

void Scene::Update() {
}

void Scene::Render() {
	// TODO: remove test image TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
	// get img
	SDL_Surface* testSurf = IMG_Load("Textures/320x240.png");
	SDL_Texture* testTex = SDL_CreateTextureFromSurface(Game::renderer, testSurf);
	SDL_FreeSurface(testSurf);
	// draw img
	DrawTexture(testTex, NULL);
	SDL_DestroyTexture(testTex);
	// End the test TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
}

int Scene::EntityPointerToIndex(Entity* entity) {
	std::vector<Entity*>::iterator i = std::find(entities.begin(), entities.end(), entity);
	if (i == entities.end()) {
		return -1;
	}
	return i - entities.begin();
}

std::ostream& Scene::Serialize(std::ostream& os) {
	return os;
}

std::istream& Scene::Deserialize(std::istream& is) {
	return is;
}

bool SaveScene(const Scene& scene, std::string filePath) {
	return false;
}

Scene* LoadScene(std::string filePath) {
	Log("Failed to load scene \"" + filePath + "\"", WARNING);
	return nullptr;
}

SDL_Point SceneToViewport(SDL_Point pos, Scene* scene) {
	return { pos.x - scene->camera.GetPos().x, pos.y - scene->camera.GetPos().y };
}

SDL_Rect SceneToViewport(SDL_Rect rect, Scene* scene) {
	return { rect.x - scene->camera.GetPos().x, rect.y - scene->camera.GetPos().y, rect.w, rect.h };
}
