#include "Offsets.h"

void Offsets::Initialise()
{
	// Modules
	Modules::Client = U::Memory::WaitOnModuleHandle("client_panorama.dll");
	Modules::Engine = U::Memory::WaitOnModuleHandle("engine.dll");
	Modules::VGUI2 = U::Memory::WaitOnModuleHandle("vgui2.dll");
	Modules::VGUISurface = U::Memory::WaitOnModuleHandle("vguimatsurface.dll");
	Modules::Material = U::Memory::WaitOnModuleHandle("materialsystem.dll");
	Modules::VPhysics = U::Memory::WaitOnModuleHandle("vphysics.dll");
	Modules::Stdlib = U::Memory::WaitOnModuleHandle("vstdlib.dll");

	//------------------------------------------------------------------------
	// VTables
#pragma region VTables
	VMT::CHL_GetAllClasses = 8;

	VMT::Engine_GetScreenSize = 5;
	VMT::Engine_GetPlayerInfo = 8;
	VMT::Engine_GetLocalPlayer = 12;
	VMT::Engine_Time = 14;
	VMT::Engine_GetViewAngles = 18;
	VMT::Engine_SetViewAngles = 19;
	VMT::Engine_GetMaxClients = 20;
	VMT::Engine_IsConnected = 27;
	VMT::Engine_IsInGame = 26;
	VMT::Engine_WorldToScreenMatrix = 37;
	VMT::Engine_ClientCmd_Unrestricted = 114;

	VMT::Panel_GetName = 36;
	VMT::Panel_PaintTraverse = 41;

	VMT::Surface_DrawSetColorA = 14;
	VMT::Surface_DrawSetColorB = 15;
	VMT::Surface_DrawFilledRect = 16;
	VMT::Surface_DrawOutlinedRect = 18;
	VMT::Surface_DrawLine = 19;
	VMT::Surface_DrawSetTextFont = 23;
	VMT::Surface_DrawSetTextColorA = 24;
	VMT::Surface_DrawSetTextColorB = 25;
	VMT::Surface_DrawSetTextPos = 26;
	VMT::Surface_DrawPrintText = 28;
	VMT::Surface_DrawSetTextureRGBA = 37;
	VMT::Surface_DrawSetTexture = 38;
	VMT::Surface_CreateNewTextureID = 43;
	VMT::Surface_FontCreate = 71;
	VMT::Surface_SetFontGlyphSet = 72;
	VMT::Surface_GetTextSize = 79;
	VMT::Surface_DrawOutlinedCircle = 103;
	VMT::Surface_SurfaceGetCursorPos = 66;
	VMT::Surface_DrawTexturedPolygon = 106;

	VMT::Material_GetName = 0;
	VMT::Material_SetMaterialVarFlag = 30;
	VMT::Material_GetMaterialVarFlag = 31;
	VMT::Material_AlphaModulate = 28;
	VMT::Material_ColorModulate = 29;
	VMT::Material_IncrementReferenceCount = 14;

	VMT::MaterialSystem_FindMaterial = 84;
	VMT::MaterialSystem_CreateMaterial = 83;

	VMT::ModelRender_ForcedMaterialOverride = 1;
	VMT::ModelRender_DrawModelExecute = 21;

	VMT::ModelInfo_GetModelName = 3;
	VMT::ModelInfo_GetStudiomodel = 30;

	VMT::RenderView_SetBlend = 4;
	VMT::RenderView_SetColorModulation = 6;

#pragma endregion Contains the VTable Indexs

	// An update changed the VTable offset for GetSpread.
	// Just incase ;)
	DWORD VMT_SpreadAddress = (DWORD)U::Memory::FindPattern("client_panorama.dll", (PBYTE)"\x8B\x80\x00\x00\x00\x00\xFF\xD0\x51\xD9\x1C\x24\x0F\xB6\xC3\x8B\x5C\x24\x30", "xx????xxxxxxxxxxxxx");
	if (VMT_SpreadAddress)
	{
		VMT::Weapon_GetSpread = *(DWORD*)(VMT_SpreadAddress + 2);
		VMT::Weapon_GetSpread = (VMT::Weapon_GetSpread / 4);
	}

	// I cbf trying to get the KeyValues part of the SDK working solo, so we'll just
	// Do some dirty shit
	Functions::KeyValues_KeyValues = U::Memory::FindPattern("client_panorama.dll", (PBYTE)"\x68\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x89\x45\xFC\xEB\x07\xC7\x45\x00\x00\x00\x00\x00\x8B\x03\x56", "x????xxx????xxxxxxx?????xxx");
	Functions::KeyValues_KeyValues += 7;
	Functions::KeyValues_KeyValues = Functions::KeyValues_KeyValues + *reinterpret_cast< PDWORD_PTR >(Functions::KeyValues_KeyValues + 1) + 5;

	Functions::KeyValues_LoadFromBuffer = U::Memory::FindPatternVersion2("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");

	Functions::dwCalcPlayerView = U::Memory::FindPattern("client_panorama.dll", (PBYTE)"\x84\xC0\x75\x08\x57\x8B\xCE\xE8\x00\x00\x00\x00\x8B\x06", "xxxxxxxx????xx");

	U::Log("Offsets/Indexes Up to Date");
}

namespace Offsets
{
	// Addresses of loaded game modules
	namespace Modules
	{
		DWORD Client;
		DWORD Engine;
		DWORD VGUI2;
		DWORD VGUISurface;
		DWORD Material;
		DWORD VPhysics;
		DWORD Stdlib;
	};

	// Virtual Method Table Indexes
	namespace VMT
	{
		//CHL Client
		DWORD CHL_GetAllClasses;

		//Engine Client
		DWORD Engine_GetScreenSize;
		DWORD Engine_GetPlayerInfo;
		DWORD Engine_GetLocalPlayer;
		DWORD Engine_Time;
		DWORD Engine_GetViewAngles;
		DWORD Engine_SetViewAngles;
		DWORD Engine_GetMaxClients;
		DWORD Engine_IsConnected;
		DWORD Engine_IsInGame;
		DWORD Engine_WorldToScreenMatrix;
		DWORD Engine_ClientCmd_Unrestricted;

		// Panels
		DWORD Panel_GetName;
		DWORD Panel_PaintTraverse;

		// Surface
		DWORD Surface_DrawSetColorA;
		DWORD Surface_DrawSetColorB;
		DWORD Surface_DrawFilledRect;
		DWORD Surface_DrawOutlinedRect;
		DWORD Surface_DrawLine;
		DWORD Surface_DrawSetTextFont;
		DWORD Surface_DrawSetTextColorA;
		DWORD Surface_DrawSetTextColorB;
		DWORD Surface_DrawSetTextPos;
		DWORD Surface_DrawPrintText;
		DWORD Surface_DrawSetTextureRGBA;
		DWORD Surface_DrawSetTexture;
		DWORD Surface_CreateNewTextureID;
		DWORD Surface_FontCreate;
		DWORD Surface_SetFontGlyphSet;
		DWORD Surface_GetTextSize;
		DWORD Surface_DrawOutlinedCircle;
		DWORD Surface_SurfaceGetCursorPos;
		DWORD Surface_DrawTexturedPolygon;

		DWORD Material_GetName;
		DWORD Material_SetMaterialVarFlag;
		DWORD Material_GetMaterialVarFlag;
		DWORD Material_AlphaModulate;
		DWORD Material_ColorModulate;
		DWORD Material_IncrementReferenceCount;

		DWORD MaterialSystem_FindMaterial;
		DWORD MaterialSystem_CreateMaterial;

		DWORD ModelRender_ForcedMaterialOverride;
		DWORD ModelRender_DrawModelExecute;

		DWORD ModelInfo_GetModelName;
		DWORD ModelInfo_GetStudiomodel;

		DWORD RenderView_SetBlend;
		DWORD RenderView_SetColorModulation;

		// Weapon entities
		DWORD Weapon_GetSpread;
	};

	// Addresses of engine functions to call
	namespace Functions
	{
		DWORD KeyValues_KeyValues;
		DWORD KeyValues_LoadFromBuffer;
		DWORD dwCalcPlayerView;
	};

};