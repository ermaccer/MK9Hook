#include "SkeletalMeshComponent.h"
#include "../helper/eMath.h"
#include "FMatrix.h"
#include <iostream>

void USkeletalMeshComponent::GetBoneLocation(FVector* loc, const char* name)
{
	FName bone(name, FNAME_Add, 1);
	// 4 - alt fname?
	// 5 - space
	((void(__thiscall*)(USkeletalMeshComponent*, FVector*, int, int, int))0x77C3B0)(this, loc, bone.GetIndex(), 0, 0);
}

void USkeletalMeshComponent::GetBoneQuaternion(FQuat* rot, const char* name)
{
	FName bone(name, FNAME_Add, 1);
	((void(__thiscall*)(USkeletalMeshComponent*, FQuat*, int, int, int))0x77C2B0)(this, rot, bone.GetIndex(), 0, 1);
}

void USkeletalMeshComponent::GetBoneMatrix(FMatrix* mat, int id, int space)
{
	((void(__thiscall*)(USkeletalMeshComponent*, FMatrix*, int, int))0x76E250)(this, mat, id, space);
}

void USkeletalMeshComponent::GetBoneRotation(FRotator* rot, const char* name)
{
	FQuat qrot;
	GetBoneQuaternion(&qrot, name);

	FName bone(name, FNAME_Add, 1);
	int skeleton = *(int*)((int)this + 640);
	int boneID = 0;
	FMatrix mat;

	int IDs[2] = {};
	IDs[0] = bone.GetIndex();

	boneID = ((int(__thiscall*)(int, int*))0x779270)(skeleton,IDs);

	GetBoneMatrix(&mat, boneID, 1);
	mat.Rotator(rot);
}
void USkeletalMeshComponent::Dismember(int partID)
{
	((void(__thiscall*)(USkeletalMeshComponent*))0x77BD70)(this);
	((void(__thiscall*)(USkeletalMeshComponent*, int))0x766920)(this, partID);

}
//((FMatrix*(__thiscall*)(FMatrix*, FQuat*, FVector*))0x5ED0E0)(&tmp, &qrot, &origin);