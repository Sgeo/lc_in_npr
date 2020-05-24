// lc_in_npr.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "npapi.h"
#include "npfunctions.h"

static NP_InitializeFunc True_NP_Initialize = NULL;
static NP_GetEntryPointsFunc True_NP_GetEntryPoints = NULL;
static NP_ShutdownFunc True_NP_Shutdown = NULL;

static HMODULE thisModule = NULL;

__declspec(dllexport) NPError APIENTRY NP_Initialize(NPNetscapeFuncs *pFuncs) {
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(thisModule, path, MAX_PATH);
	path[wcslen(path) - 1] = '0';
	HMODULE destModule = LoadLibraryW(path);
	NP_InitializeFunc realInit = (NP_InitializeFunc)GetProcAddress(destModule, "NP_Initialize");
	return realInit(pFuncs);
}

__declspec(dllexport) NPError APIENTRY NP_GetEntryPoints(NPPluginFuncs *pFuncs) {
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(thisModule, path, MAX_PATH);
	path[wcslen(path) - 1] = '0';
	HMODULE destModule = LoadLibraryW(path);
	NP_GetEntryPointsFunc realGetEntryPoints = (NP_GetEntryPointsFunc)GetProcAddress(destModule, "NP_GetEntryPoints");
	return realGetEntryPoints(pFuncs);
}

__declspec(dllexport) NPError APIENTRY NP_Shutdown() {
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(thisModule, path, MAX_PATH);
	path[wcslen(path) - 1] = '0';
	HMODULE destModule = LoadLibraryW(path);
	NP_ShutdownFunc realShutdown = (NP_ShutdownFunc)GetProcAddress(destModule, "NP_Shutdown");
	return realShutdown();
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	thisModule = hModule;
	return TRUE;
}