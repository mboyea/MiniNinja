#include "Scene.h"
#include "Window.h"
#include "Draw.h"
#include "Log.h"
#include "Textures.h"
#include <algorithm>
#include "FileParameters.h"
#include <fstream>
#include "Files.h"

static Scene* currentSavingScene = nullptr;
static Scene* currentLoadingScene = nullptr;

Scene::~Scene() {
	for (Entity* entity : entities) {
		delete entity;
	}
}

void Scene::Update() {
	// Updates
	for (Entity* entity : entities) {
		entity->lastPos = entity->pos;
		entity->Update();
	}

	// Children
	for (Entity* entity : entities) {
		SDL_Point offset = { entity->pos.x - entity->lastPos.x, entity->pos.y - entity->lastPos.y };
		if (offset.x != 0 || offset.y != 0) {
			for (Entity* child : entity->children) {
				child->pos.x += offset.x;
				child->pos.y += offset.y;
			}
			for (Collider* collider : entity->colliders) {
				collider->SetPosition(
					{ collider->GetPosition().x + offset.x, collider->GetPosition().y + offset.y }
				);
			}
		}
	}

	// Collisions
	for (Entity* entity : entities) {
		entity->lastPos = entity->pos;
		// TODO: detect collisions
	}

	// Children
	for (Entity* entity : entities) {
		SDL_Point offset = { entity->pos.x - entity->lastPos.x, entity->pos.y - entity->lastPos.y };
		if (offset.x != 0 || offset.y != 0) {
			for (Entity* child : entity->children) {
				child->pos.x += offset.x;
				child->pos.y += offset.y;
			}
			for (Collider* collider : entity->colliders) {
				collider->SetPosition(
					{ collider->GetPosition().x + offset.x, collider->GetPosition().y + offset.y }
				);
			}
		}
	}
}

void Scene::Render() {
	// TODO: remove test image TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
	// get img
	SDL_Surface* testSurf = IMG_Load("Textures/320x240.png");
	SDL_Texture* testTex = SDL_CreateTextureFromSurface(Game::renderer, testSurf);
	SDL_FreeSurface(testSurf);
	// draw img
	DrawTexture(testTex);
	SDL_DestroyTexture(testTex);
	// End the test TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST

	// sort entities by layer so that they render on top of eachother in the expected order
	std::sort(entities.begin(), entities.end());

	for (Entity* entity : entities) {
		entity->Render();
	}
	if (Game::doRenderColliders) {
		for (Entity* entity : entities) {
			for (Collider* collider : entity->colliders) {
				SetDrawColor(Colors::GREEN);
				collider->RenderNarrowCollider();
				SetDrawColor(Colors::LIGHT_GREY);
				collider->RenderBroadCollider();
			}
		}
	}
}

int Scene::EntityPointerToIndex(Entity* entity) {
	std::vector<Entity*>::iterator i = std::find(entities.begin(), entities.end(), entity);
	if (i == entities.end()) {
		return -1;
	}
	return i - entities.begin();
}

std::vector<Resource*> Scene::GetRequiredResources() {
	std::vector<Resource*> resources;
	// TODO: outline required modules, fonts, textures, and animations
	
	//	std::vector<Resource*> baseResources = Entity::GetRequiredResources();
	//	resources.reserve(resources.size() + baseResources.size());
	//	resources.insert(resources.end(), baseResources.begin(), baseResources.end());
	return resources;
}

std::ostream& Scene::Serialize(std::ostream& os) {
	// Serialize Scene Version
	// Serialize Scene Camera
	// Serialize Required Resources
	// Serialize Scene Modules (external & internal Entities)
	return os;
}

std::istream& Scene::Deserialize(std::istream& is) {
	// Switch Procedure Based Upon Scene Version
	// Deserialize Scene Camera
	// Deserialize Required Resources
	// Deserialize Scene Modules (external & internal Entities)
	return is;
}

Scene* GetCurrentSavingScene() {
	if (!currentSavingScene) {
		Log("No scene currently saving.", WARNING);
	}
	return currentSavingScene;
}

Scene* GetCurrentLoadingScene() {
	if (!currentLoadingScene) {
		Log("No scene currently loading.", WARNING);
	}
	return currentLoadingScene;
}

bool SaveScene(Scene& scene, std::string filePath) {
	filePath = ForceFileExtension(filePath, "zscne");
	Log("Saving Scene to \"" + filePath + "\"");

	std::ofstream ofStream(filePath);
	if (!ofStream) {
		Log("Scene file \"" + filePath + "\" could not be opened.", WARNING);
		Log("Scene save failed.", WARNING);
		return false;
	}

	currentSavingScene = &scene;
	scene.Serialize(ofStream);
	currentSavingScene = nullptr;

	ofStream.close();
	Log("Scene saved.");
	return true;
}

Scene* LoadScene(std::string filePath) {
	filePath = ForceFileExtension(filePath, "zscne");
	Log("Loading Scene from \"" + filePath + "\" . . .");

	std::ifstream ifStream(filePath);
	if (!ifStream) {
		Log("Scene file \"" + filePath + "\" could not be found.", WARNING);
		Log("Scene load failed.", WARNING);
		return nullptr;
	}

	Scene* scene = new Scene();
	currentLoadingScene = scene;
	scene->Deserialize(ifStream);
	currentLoadingScene = nullptr;

	ifStream.close();
	Log("Scene loaded.");
	return scene;
}

SDL_Point SceneToViewport(SDL_Point pos, Scene* scene) {
	return { pos.x - scene->camera.GetPos().x, pos.y - scene->camera.GetPos().y };
}

SDL_Rect SceneToViewport(SDL_Rect rect, Scene* scene) {
	return { rect.x - scene->camera.GetPos().x, rect.y - scene->camera.GetPos().y, rect.w, rect.h };
}