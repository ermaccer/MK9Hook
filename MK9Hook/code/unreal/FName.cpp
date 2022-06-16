#include "FName.h"

FName::FName(const char* Name, EFindName FindType, int formal)
{
	((void(__thiscall*)(FName*, const char*, EFindName, int))0x600980)(this, Name, FindType, formal);
}

int FName::GetIndex()
{
	return Index;
}
