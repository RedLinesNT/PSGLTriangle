#pragma once

#include <sysutil/sysutil_common.h>

class CELLCallbacks {
public:
	CELLCallbacks() = delete;

	//-----------------------------------------------------------------------------
	// Bind "HandleCallbacks(uint64_t, uint64_t, void*)" as the method 
	// who'll receive the system callbacks.
	//-----------------------------------------------------------------------------
	static void BindCallbacks();
	//-----------------------------------------------------------------------------
	// Unbind "HandleCallbacks(uint64_t, uint64_t, void*)" from
	// receiving system callbacks.
	//-----------------------------------------------------------------------------
	static void UnbindCallbacks();
	//-----------------------------------------------------------------------------
	// Check for incoming system callbacks.
	//-----------------------------------------------------------------------------
	static void Update();

	//-----------------------------------------------------------------------------
	// Whether the application should be running.
	// Returns: 
	//      True if the application should exit.
	//-----------------------------------------------------------------------------
	inline static bool HasReceivedCloseCallback() { return hasReceivedCloseCallback; }
	//-----------------------------------------------------------------------------
	// Whether the XrossMediaBar is current being displayed.
	// Returns: 
	//      True if open.
	//-----------------------------------------------------------------------------
	inline static bool IsTheXMBOpen() { return isTheXMBOpen; }

private:
	//-----------------------------------------------------------------------------
	// Handle every supported system callbacks.
	//-----------------------------------------------------------------------------
	static void HandleCallbacks(uint64_t status, uint64_t param, void* userdata);

	static bool hasReceivedCloseCallback; //Has received the "CELL_SYSUTIL_REQUEST_EXITGAME" callback?
	static bool isTheXMBOpen; //Has received the "CELL_SYSUTIL_SYSTEM_MENU_*" callbacks?
};