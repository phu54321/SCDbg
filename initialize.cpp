#include <Windows.h>
#include "Plugin.h"

BOOL WINAPI Plugin::InitializePlugin(IMPQDraftServer *lpMPQDraftServer) {
	//StarCraft.exe version check
	char exePath[300];
	const DWORD pathLen = GetModuleFileName(NULL, exePath, sizeof(exePath));
	if (pathLen == sizeof(exePath)) {
		MessageBox(NULL, "Error: Cannot check version of StarCraft.exe. The file path is too long.", NULL, MB_OK);
		return FALSE;
	}
	if (!checkStarCraftExeVersion(exePath))
		return FALSE;



	// Inject hooks & several injections.

	// Nothing here

	return TRUE;
}

