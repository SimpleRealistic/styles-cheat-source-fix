#pragma once

#include "SDK.h"
#include "InterfaceStruct.h"

class IMoveHelper : public Interface
{
public:
	void SetHost(IClientEntity* pEnt)
	{
		typedef void(__thiscall* SetHostFn)(void*, IClientEntity*);
		return VFunc<SetHostFn>(1)(this, pEnt);
	}
};

// if you think this is real styles you're fucking retarded and brain dead