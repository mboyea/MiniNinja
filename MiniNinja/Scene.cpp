#include "Scene.h"
#include "Window.h"
#include "Draw.h"
#include "Log.h"
#include "Textures.h"
#include <algorithm>
#include "FileParameters.h"
#include <fstream>
#include "Files.h"

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

std::vector<Resource> Scene::GetRequiredResources() {
	std::vector<Resource> resources;
	for (Entity* entity : entities) {
		entity->GetRequiredResources(resources);
	}
	std::sort(resources.begin(), resources.end());
	return resources;
}

std::ostream& Scene::Serialize(std::ostream& os, std::string moduleFolderPath) {
	// Serialize Scene Version
	os << SCENE_VERSION << '\n';
	// Serialize Scene Camera
	camera.Serialize(os) << '\n';
	{ // Serialize Required Resources
		int type = 0;
		for (Resource resource : GetRequiredResources()) {
			while (resource.type > type) {
				type++;
				os << '\n';
			}
			os << MakeSerializable(resource.name) << ' ';
			if (type == RESOURCE_MODULE) {
				// TODO: open file and store entity as module
			}
		}
		os << '\n';
	}
	// Serialize Scene Entities
	for (Entity* entity : entities) {
		entity->Serialize(os);
		os << '\n';
	}
	return os;
}

bool Scene::Deserialize(std::istream& is, std::string moduleFolderPath, std::string textureFolderPath, std::string animationFolderPath, std::string fontFolderPath) {
	//TODO: SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE SWITCH TO GETLINE
	// Switch Procedure Based Upon Scene Version
	std::string version;
	is >> version;
	if (version == SCENE_VERSION) {
		// Deserialize Scene Camera
		camera.Deserialize(is);
		// Deserialize Required Resources
		// Deserialize Scene Modules (external & internal Entities)
		
		//return true;
	}
	Log("Scene version unsupported.", WARNING);
	return false;
	/* REFERENCE FOR HOW TO LOOP AND DO SPECIFIC FOLDER ACCESS:
	unsigned int type = 0;
	std::string folder;
	for (Resource resource : GetRequiredResources()) {
		while (resource.type > type) {
			type++;
			os << '\n';
			if (type == RESOURCE_MODULE) {
				folder = moduleFolderPath;
			}
			else if (type == RESOURCE_TEXTURE) {
				folder = textureFolderPath;
			}
			else if (type == RESOURCE_ANIMATION) {
				folder = animationFolderPath;
			}
			else if (type == RESOURCE_FONT) {
				folder = fontFolderPath;
			}
			else {
				folder = "Error";
			}
		}
		os << MakeSerializable(resource.name) << ' ';
	}
	os << '\n';*/
}

Scene* GetActiveScene() {
	if (!activeScene) {
		Log("No active scene.", WARNING);
	}
	return activeScene;
}

bool SaveScene(Scene& scene, std::string filePath, std::string moduleFolderPath) {
	filePath = ForceFileExtension(filePath, "zscne");
	Log("Saving Scene to \"" + filePath + "\" . . .");

	// TODO: Ensure directory exists (std::filesystem)

	std::ofstream ofStream(filePath);
	if (!ofStream) {
		Log("Scene file \"" + filePath + "\" could not be opened.", WARNING);
		Log("Scene save failed.", WARNING);
		return false;
	}

	activeScene = &scene;
	scene.Serialize(ofStream, moduleFolderPath);
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
		Log("Scene load failed.", WARNING);
		return nullptr;
	}

	Scene* scene = new Scene();
	activeScene = scene;
	bool didSucceed = scene->Deserialize(ifStream, moduleFolderPath, textureFolderPath, animationFolderPath, fontFolderPath);
	activeScene = nullptr;

	ifStream.close();
	if (didSucceed) Log("Scene loaded.", SUCCESS);
	else Log("Scene load failed.", WARNING);
	return scene;
}

SDL_Point SceneToViewport(SDL_Point pos, Scene* scene) {
	return { pos.x - scene->camera.GetPos().x, pos.y - scene->camera.GetPos().y };
}

SDL_Rect SceneToViewport(SDL_Rect rect, Scene* scene) {
	return { rect.x - scene->camera.GetPos().x, rect.y - scene->camera.GetPos().y, rect.w, rect.h };
}