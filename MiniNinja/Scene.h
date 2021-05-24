#ifndef SCENE_H
#define SCENE_H
#pragma once

#include <iostream>
#include <vector>
#include "Entity.h"
#include "Camera.h"
#include "Resource.h"

struct Scene {
	std::vector<Entity*> entities;
	Camera camera;

	~Scene();

	void Update();
	void Render();
	int EntityPointerToIndex(Entity* entity);

	std::vector<Resource*> GetRequiredResources();
	// Generate serialized text data for this scene into the stream
	std::ostream& Serialize(std::ostream& os);
	// Populate this scene by deserializing text data from the stream
	std::istream& Deserialize(std::istream& is);
};

Scene* GetActiveScene();
bool SaveScene(Scene& scene, std::string filePath);
Scene* LoadScene(std::string filePath);

SDL_Point SceneToViewport(SDL_Point pos, Scene* scene);
SDL_Rect SceneToViewport(SDL_Rect rect, Scene* scene);

#endif // !SCENE_H