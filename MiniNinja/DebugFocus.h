#ifndef DEBUG_FOCUS_H
#define DEBUG_FOCUS_H
#pragma once

#include "FocusState.h"

void HandleSwitchDebug();
void OnSwitchDebug();
void UpdateDebug();
void RenderDebug();
inline const FocusState* FOCUS_DEBUG = new FocusState(OnSwitchDebug, UpdateDebug, RenderDebug, HandleSwitchDebug);

#endif // !DEBUG_FOCUS_H