#include "Scene.h"
#include "Window.h"
#include "Draw.h"
#include "Log.h"
#include "Textures.h"
#include <algorithm>

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
				collider->RenderNarrowCollider();
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