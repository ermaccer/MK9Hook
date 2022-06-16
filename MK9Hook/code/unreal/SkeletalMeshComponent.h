#pragma once
#include "FName.h"
#include "FVector.h"
#include "FQuat.h"
#include "FRotator.h"
#include "FMatrix.h"
class USkeletalMeshComponent {
public:
	void GetBoneLocation(FVector* loc, const char* name);
	void GetBoneQuaternion(FQuat* rot, const char* name);
	void GetBoneMatrix(FMatrix* mat, int id, int space);



	void GetBoneRotation(FRotator* rot, const char* name);
};