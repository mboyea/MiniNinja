#ifndef PAUSE_FOCUS_H
#define PAUSE_FOCUS_H
#pragma once

#include "FocusState.h"

void HandleSwitchPause();
void UpdatePause();
void RenderPause();
inline const FocusState* FOCUS_PAUSE = new FocusState(UpdatePause, RenderPause, HandleSwitchPause);

#endif // !PAUSE_FOCUS_H