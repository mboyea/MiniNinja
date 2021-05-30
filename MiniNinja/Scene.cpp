#include "Scene.h"
#include "Window.h"
#include "Draw.h"
#include "Log.h"
#include "Textures.h"
#include <algorithm>
#include "FileParameters.h"
#include <fstream>
#include "Files.h"
#include <sstream>

#include "Sprite.h"

static Scene* activeScene = nullptr;

Scene::~Scene() {
	for (Entity* entity : entities) {
		delete entity;
	}
}

void Scene::Update() {
	activeScene = this;
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
	activeScene = nullptr;
}

void Scene::Render() {
	activeScene = this;

	// TODO: remove test image TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST
	// get img
	SDL_Surface* testSurf = IMG_Load("Resources/Textures/320x240.png");
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
	activeScene = nullptr;
}

int Scene::EntityPointerToIndex(Entity* entity) {
	std::vector<Entity*>::iterator i = std::find(entities.begin(), entities.end(), entity);
	if (i == entities.end()) {
		return -1;
	}
	return i - entities.begin();
}

std::set<Resource> Scene::GetRequiredResources() {
	std::set<Resource> resources;
	for (Entity* entity : entities) {
		entity->GetRequiredResources(resources);
	}
	return resources;
}

std::ostream& Scene::Serialize(std::ostream& os, std::string moduleFolderPath) {
	// Initialize
	if (!DoesPathExist(moduleFolderPath)) {
		Log("Directory \"" + moduleFolderPath + " does not exist.", WARNING);
		if (ForceDirectoryExistence(moduleFolderPath)) {
			Log("Directory Created");
		}
		else {
			Log("Directory could not be created.", WARNING);
			Log("Modules will be saved within the scene.", WARNING);
		}
	}
	// Serialize Scene Version
	os << SCENE_VERSION << '\n';
	// Serialize Scene Camera
	camera.Serialize(os) << '\n';
	{ // Serialize Required Resources
		int type = 0;
		for (Resource resource : GetRequiredResources()) {
			while (type < resource.type) {
				os << '\n';
				type++;
			}
			os << resource << ' ';
		}
		while (type < MAX_RESOURCE_TYPES - 1) {
			type++;
			os << '\n';
		}
		os << '\n';
	}
	// Serialize Scene Entities
	for (Entity* entity : entities) {
		if (entity->saveAsModule) {
			os << MakeSerializable(entity->name);

			std::string filePath = ForceFilePath(entity->name, moduleFolderPath, "zmdle");
			Log("Saving Module to \"" + filePath + "\" . . .");
			std::ofstream ofStream(filePath);
			if (!ofStream) {
				Log("Module file could not be opened.", WARNING);
				Log("Entity data saved after module name.", WARNING);
				os << ' ';
				entity->Serialize(os);
				os << '\n';
				continue;
			}

			entity->Serialize(ofStream);

			ofStream.close();
			Log("Module saved.", SUCCESS);
		}
		else entity->Serialize(os);
		os << '\n';
	}
	return os;
}

bool Scene::Deserialize(std::istream& is, std::string moduleFolderPath, std::string textureFolderPath, std::string animationFolderPath, std::string fontFolderPath) {
	// Switch Procedure Based Upon Scene Version
	std::string line;
	std::getline(is, line);
	if (line == SCENE_VERSION) {
		{ // Deserialize Scene Camera
			std::getline(is, line);
			std::istringstream iStringStream(line);
			camera.Deserialize(iStringStream);
		}
		{ // Deserialize Required Resources
			std::set<Resource> resources;
			for (int type = 0; type < MAX_RESOURCE_TYPES; type++) {
				std::getline(is, line);
				std::istringstream iStringStream(line);
				Resource resource("", (ResourceType)type);
				while (iStringStream >> resource) {
					resources.insert(resource);
				}
			}
			if (!LoadResources(resources, moduleFolderPath, textureFolderPath, animationFolderPath, fontFolderPath)) {
				Log("Some Scene resources failed to load.", FAULT);
			}
		}
		// Deserialize Scene Entities
		// TODO: deserialize scene entities
		Log("TODO: deserialize scene entities . . .", FAULT);
		return true;
	}
	else {
		Log("Scene version unsupported.", WARNING);
		return false;
	}
}

bool Scene::LoadModule(std::string filePath) {
	Log("Loading Module from \"" + filePath + "\" . . .");
	// Ensure File Exists
	if (!DoesPathExist(filePath)) {
		Log("File does not exist.", WARNING);
		Log("Module load failed.", FAULT);
		return false;
	}
	// Open File
	std::ifstream ifStream(filePath);
	if (!ifStream) {
		Log("File could not be opened.", WARNING);
		Log("Module load failed.", FAULT);
		return false;
	}

	// TODO: Load Entity from Module

	/*
	// Load Entity
	std::string line;
	std::getline(ifStream, line);
	std::istringstream iStringStream(line);
	// TODO: Get the entitiy ID and create the correct Enttiy from it
	Entity* entity = new Entity("");
	entity->Deserialize(iStringStream);
	if (!entity) {
		// TODO: log error
		break;
	}
	GetActiveScene()->entities.push_back(entity);
	*/
}

Scene* GetActiveScene() {
	if (!activeScene) {
		Log("No active scene.", WARNING);
	}
	return activeScene;
}

bool SaveScene(Scene* scene, std::string filePath, std::string moduleFolderPath) {
	filePath = ForceFileExtension(filePath, "zscne");
	Log("Saving Scene to \"" + filePath + "\" . . .");

	if (!DoesPathExist(GetFileDirectory(filePath))) {
		Log("Directory \"" + GetFileDirectory(filePath) + "\" does not exist.", WARNING);
		if (ForceDirectoryExistence(GetFileDirectory(filePath))) {
			Log("Directory created.");
		}
		else {
			Log("Directory could not be created.", WARNING);
			Log("Scene save failed.", FAULT);
		}
	}

	std::ofstream ofStream(filePath);
	if (!ofStream) {
		Log("Scene file could not be opened.", WARNING);
		Log("Scene save failed.", FAULT);
		return false;
	}

	activeScene = scene;
	scene->Serialize(ofStream, moduleFolderPath);
	activeScene = nullptr;

	ofStream.close();
	Log("Scene saved.", SUCCESS);
	return true;
}

Scene* LoadScene(std::string filePath, std::string moduleFolderPath, std::string textureFolderPath, std::string animationFolderPath, std::string fontFolderPath) {
	filePath = ForceFileExtension(filePath, "zscne");
	Log("Loading Scene from \"" + filePath + "\" . . .");

	std::ifstream ifStream(filePath);
	if (!ifStream) {
		Log("Scene file \"" + filePath + "\" could not be found.", WARNING);
		Log("Scene load failed.", FAULT);
		return nullptr;
	}

	Scene* scene = new Scene();
	activeScene = scene;
	if (scene->Deserialize(ifStream, moduleFolderPath, textureFolderPath, animationFolderPath, fontFolderPath)) {
		Log("Scene loaded.", SUCCESS);
	}
	else Log("Scene load failed.", FAULT);
	activeScene = nullptr;

	ifStream.close();
	return scene;
}

SDL_Point SceneToViewport(SDL_Point pos, Scene* scene) {
	return { pos.x - scene->camera.GetPos().x, pos.y - scene->camera.GetPos().y };
}

SDL_Rect SceneToViewport(SDL_Rect rect, Scene* scene) {
	return { rect.x - scene->camera.GetPos().x, rect.y - scene->camera.GetPos().y, rect.w, rect.h };
}