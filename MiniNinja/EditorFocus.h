#ifndef EDITOR_FOCUS_H
#define EDITOR_FOCUS_H

#include "FocusState.h"

void HandleSwitchEditor();
void UpdateEditor();
void RenderEditor();
inline const FocusState* FOCUS_EDITOR = new FocusState(UpdateEditor, RenderEditor, HandleSwitchEditor);

#endif // !EDITOR_FOCUS_H