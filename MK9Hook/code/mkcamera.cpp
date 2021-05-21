#include "mkcamera.h"
#include "mk9menu.h"
#include <iostream>

void MKCamera::SetPosition(FVector * pos)
{
	((void(__thiscall*)(MKCamera*, FVector*))0x45E1C0)(this, pos);
}

void MKCamera::SetRotation(FRotator * rot)
{
	((void(__thiscall*)(MKCamera*, FRotator*))0x45DB30)(this, rot);
}

void MKCamera::SetFOV(float FOV, int unk)
{
	((void(__thiscall*)(MKCamera*, float, int))0x45DAE0)(this, FOV, unk);
}

void MKCamera::HookedSetPosition(FVector * pos)
{
	if (!TheMenu->bCustomCamera)
	{
		TheMenu->camPos = *pos;
		SetPosition(pos);
	}
	else
		SetPosition(&TheMenu->camPos);
}

void MKCamera::HookedSetRotation(FRotator * rot)
{
	if (!TheMenu->bCustomCameraRot)
	{
		TheMenu->camRot = *rot;
		SetRotation(rot);
	}
	else
		SetRotation(&TheMenu->camRot);
}

void MKCamera::HookedSetFOV(float FOV, int unk)
{
	if (!TheMenu->bCustomFOV)
	{
		TheMenu->camFov = FOV;
		SetFOV(FOV, unk);
	}
	else
		SetFOV(TheMenu->camFov, unk);
}
