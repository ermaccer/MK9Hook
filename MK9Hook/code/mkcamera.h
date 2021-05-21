#pragma once
#include "mk9.h"
// generic layer for other plugins too
class MKCamera {
public:
	void SetPosition(FVector* pos);
	void SetRotation(FRotator* rot);
	void SetFOV(float FOV, int unk);

	void HookedSetPosition(FVector* pos);
	void HookedSetRotation(FRotator* rot);
	void HookedSetFOV(float FOV, int unk);
};