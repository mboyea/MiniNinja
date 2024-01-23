#ifndef FOCUS_STATE_H
#define FOCUS_STATE_H
#pragma once

struct FocusState {
	void (*OnSwitch)();
	void (*Update)();
	void (*Render)();
	void (*HandleSwitch)();

	FocusState(void (*OnSwitchFunction)(), void (*UpdateFunction)(), void (*RenderFunction)(), void (*HandleSwitchFunction)())
		: OnSwitch(OnSwitchFunction), Update(UpdateFunction), Render(RenderFunction), HandleSwitch(HandleSwitchFunction) {}
};

void SetFocus(const FocusState* focus);
const FocusState* GetFocus();
void UpdateFocus();
void RenderFocus();
void HandleFocusSwitching();

#endif // !FOCUS_STATE_H