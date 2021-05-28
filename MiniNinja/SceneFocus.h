#ifndef SCENE_FOCUS_H
#define SCENE_FOCUS_H

#include "FocusState.h"
#include "Scene.h"

void HandleSwitchScene();
void UpdateScene();
void RenderScene();
inline const FocusState* FOCUS_SCENE = new FocusState(UpdateScene, RenderScene, HandleSwitchScene);

bool SetFocusScene(Scene* scene);
Scene* GetFocusScene();

#endif // !SCENE_FOCUS_H