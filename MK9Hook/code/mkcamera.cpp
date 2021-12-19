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
	float oneTime = 0.0f;
	float oneTimeX = 0.0f;
	if (!TheMenu->m_bYObtained)
	{
		oneTime = pos->Y;
		oneTimeX = pos->X;
		TheMenu->m_bYObtained = true;
	}
	if (TheMenu->m_bCustomCameras)
	{
		if (GetObj(PLAYER1) && GetObj(PLAYER2))
		{
			FVector plrPos;
			FVector p2;
			GetCharacterPosition(PLAYER1, &plrPos);
			GetCharacterPosition(PLAYER2, &p2);
			switch (TheMenu->m_nCurrentCustomCamera)
			{
			case CAMERA_3RDPERSON:
				pos->X = (oneTimeX / 5.0f) - 10.0f;
				pos->Y = oneTime - 330.0f;
				pos->Y += plrPos.Y * 0.85f;
				pos->Z = 210.0f + plrPos.Z;

				if (p2.Y < plrPos.Y)
				{
					pos->Y += 600.0f;
					pos->Z = 210.0f;

				}


				TheMenu->camPos = *pos;
				break;
			}
		}
		SetPosition(pos);
	}
	else
	{
		if (!TheMenu->m_bCustomCameraPos)
		{
			TheMenu->camPos = *pos;
			SetPosition(pos);
		}
		else
			SetPosition(&TheMenu->camPos);
	}
}

void MKCamera::HookedSetRotation(FRotator * rot)
{
	if (TheMenu->m_bCustomCameras)
	{
		if (GetObj(PLAYER1) && GetObj(PLAYER2))
		{
			FVector p1, p2;
			switch (TheMenu->m_nCurrentCustomCamera)
			{
			case CAMERA_3RDPERSON:
				rot->Pitch = -900;
				rot->Yaw = 16000;
				rot->Roll = 0;
				TheMenu->camRot = *rot;
				GetCharacterPosition(PLAYER1, &p1);
				GetCharacterPosition(PLAYER2, &p2);

				if (p2.Y < p1.Y)
				{
					rot->Yaw = -16000;
					rot->Pitch = -900;
				}

				TheMenu->camRot = *rot;
				break;
			}
		}

		SetRotation(rot);
	}
	else
	{
		if (!TheMenu->m_bCustomCameraRot)
		{
			TheMenu->camRot = *rot;
			SetRotation(rot);
		}
		else
			SetRotation(&TheMenu->camRot);
	}
}

void MKCamera::HookedSetFOV(float FOV, int unk)
{
	if (!TheMenu->m_bCustomCameraFOV)
	{
		TheMenu->camFov = FOV;
		SetFOV(FOV, unk);
	}
	else
		SetFOV(TheMenu->camFov, unk);
}
