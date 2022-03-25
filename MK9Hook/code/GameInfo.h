#pragma once

class MKScript {
public:
	int GetFunctionID(char* name);
};

MKScript* GetScript(const char* name);