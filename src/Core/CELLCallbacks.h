#pragma once

#include <sysutil/sysutil_common.h>

class CELLCallbacks {
public:
	CELLCallbacks() = delete;

	static void BindCallbacks();
	static void UnbindCallbacks();
	static void Update();

	//-----------------------------------------------------------------------------
	// Description: Whether the application should be running.
	// Parameters:
	// Returns: True if the application should exit.
	// Notes:
	//-----------------------------------------------------------------------------
	inline static bool HasReceivedCloseCallback() { return hasReceivedCloseCallback; }
	//-----------------------------------------------------------------------------
	// Description: Whether the XrossMediaBar is current being displayed.
	// Parameters:
	// Returns: True if open.
	// Notes:
	//-----------------------------------------------------------------------------
	inline static bool IsTheXMBOpen() { return isTheXMBOpen; }

private:
	static void HandleCallbacks(uint64_t status, uint64_t param, void* userdata);

	static bool hasReceivedCloseCallback; //Has received the "CELL_SYSUTIL_REQUEST_EXITGAME" callback?
	static bool isTheXMBOpen; //Has received the "CELL_SYSUTIL_SYSTEM_MENU_*" callbacks?
};