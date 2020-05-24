// lc_in_npr.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "npapi.h"
#include "npfunctions.h"

static NP_InitializeFunc True_NP_Initialize = NULL;
static NP_GetEntryPointsFunc True_NP_GetEntryPoints = NULL;
static NP_ShutdownFunc True_NP_Shutdown = NULL;

static HMODULE thisModule = NULL;

// https://stackoverflow.com/a/41910450
#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)

NPError APIENTRY NP_Initialize(NPNetscapeFuncs *pFuncs) {
#pragma EXPORT
	MessageBox(NULL, L"NP_Initialize called", L"Log", 0);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(thisModule, path, MAX_PATH);
	path[wcslen(path) - 1] = '0';
	HMODULE destModule = LoadLibraryW(path);
	NP_InitializeFunc realInit = (NP_InitializeFunc)GetProcAddress(destModule, "NP_Initialize");
	return realInit(pFuncs);
}

NPError APIENTRY NP_GetEntryPoints(NPPluginFuncs *pFuncs) {
#pragma EXPORT
	MessageBox(NULL, L"NP_GetEntryPoints called", L"Log", 0);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(thisModule, path, MAX_PATH);
	path[wcslen(path) - 1] = '0';
	HMODULE destModule = LoadLibraryW(path);
	NP_GetEntryPointsFunc realGetEntryPoints = (NP_GetEntryPointsFunc)GetProcAddress(destModule, "NP_GetEntryPoints");
	return realGetEntryPoints(pFuncs);
}

NPError APIENTRY NP_Shutdown() {
#pragma EXPORT
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