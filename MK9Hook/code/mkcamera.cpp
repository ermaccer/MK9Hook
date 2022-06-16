#include "mkcamera.h"
#include "mk9menu.h"
#include <iostream>
#include "helper/eMath.h"

MKCamera* TheCamera;

void MKCamera::SetPosition(FVector * pos)
{
	TheCamera = this;
	((void(__thiscall*)(MKCamera*, FVector*))0x45E1C0)(this, pos);
}

void MKCamera::SetRotation(FRotator * rot)
{
	TheCamera = this;
	((void(__thiscall*)(MKCamera*, FRotator*))0x45DB30)(this, rot);
}

void MKCamera::SetFOV(float FOV, int unk)
{
	TheCamera = this;
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
			FVector eyePos[2];
			FVector middle;
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

			case CAMERA_HEAD_TRACKING:
				USkeletalMeshComponent* skeleton;
				if (TheMenu->m_bUsePlayerTwoAsTracker)
					skeleton = GetSkeleton(PLAYER2);
				else
					skeleton = GetSkeleton(PLAYER1);

				skeleton->GetBoneLocation(&eyePos[0], "F_Eye_L");
				skeleton->GetBoneLocation(&eyePos[1], "F_Eye_R");
				middle = (eyePos[0] + eyePos[1]) / 2.0;


				pos->X = middle.X + TheMenu->m_fAdjustCustomHeadCameraX;
				pos->Y = middle.Y + TheMenu->m_fAdjustCustomHeadCameraY2;
				pos->Z = middle.Z + TheMenu->m_fAdjustCustomHeadCameraZ;


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
			FRotator headRot;
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
			case CAMERA_HEAD_TRACKING:
				USkeletalMeshComponent* skeleton;
				if (TheMenu->m_bUsePlayerTwoAsTracker)
					skeleton = GetSkeleton(PLAYER2);
				else
					skeleton = GetSkeleton(PLAYER1);
				skeleton->GetBoneRotation(&headRot, "Head");

				rot->Pitch = headRot.Yaw / 10 + TheMenu->m_fAdjustCustomHeadCameraY;
				if (TheMenu->m_bStaticHead)
					rot->Yaw = 16000 + headRot.Pitch / 1000;
				else rot->Yaw = headRot.Pitch + 1000;
				rot->Roll = abs(headRot.Roll / 100);
				TheMenu->camRot = *rot;

				if (GetObj(PLAYER1))
					GetCharacterPosition(PLAYER1 ,&p1);
				if (GetObj(PLAYER2))
					GetCharacterPosition(PLAYER2, &p2);

				if (p2.Y < p1.Y && !TheMenu->m_bDontFlipCamera)
				{
					rot->Yaw *= -1;
				}
				else if (eMath::areVecsEqual(p1, p2) && !TheMenu->m_bDontAdjust) // sometimes happens in mk9
				{
					rot->Yaw *= -1;
				}
				else if (fabs(p1.Y - p2.Y) < 0.1f && !TheMenu->m_bDontAdjust)
				{
					rot->Yaw *= -1;
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

FMatrix MKCamera::GetMatrix()
{
	FRotator rot = *(FRotator*)(this + 280);
	FMatrix mat(&rot);
	return mat;
}
