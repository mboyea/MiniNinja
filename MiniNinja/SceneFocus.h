#ifndef SCENE_FOCUS_H
#define SCENE_FOCUS_H

#include "FocusState.h"
#include "Scene.h"

void HandleSwitchScene();
void UpdateScene();
void RenderScene();
inline const FocusState* FOCUS_SCENE = new FocusState(UpdateScene, RenderScene, HandleSwitchScene);

bool SetCurrentScene(Scene* scene);
Scene* GetCurrentScene();

#endif // !SCENE_FOCUS_H