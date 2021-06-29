#ifndef PAUSE_FOCUS_H
#define PAUSE_FOCUS_H
#pragma once

#include "FocusState.h"
#include "Scene.h"

void HandleSwitchPause();
void OnSwitchPause();
void UpdatePause();
void RenderPause();
inline const FocusState* FOCUS_PAUSE = new FocusState(OnSwitchPause, UpdatePause, RenderPause, HandleSwitchPause);

bool SetPauseScene(Scene* scene);
Scene* GetPauseScene();

#endif // !PAUSE_FOCUS_H