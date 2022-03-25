#include "GameInfo.h"

int MKScript::GetFunctionID(char* name)
{
    return ((int(__thiscall*)(MKScript*, char*, int))0x458680)(this, name, 0);
}

MKScript* GetScript(const char* packageName, const char* name)
{
	int package = ((int(__cdecl*)(int, const char*))0x611E80)(0, packageName);
	if (package)
	{
		MKScript* script = ((MKScript * (__cdecl*)(int, const char*, int))0x48F850)(package, name, 1);
		return script;

	}
	return nullptr;
}
