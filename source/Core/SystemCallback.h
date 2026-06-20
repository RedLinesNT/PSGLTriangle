#pragma once

#include <sysutil/sysutil_common.h>

class SystemCallback {
	public:
		SystemCallback() = delete;

		static void Subscribe();
		static void Unsubscribe();
		static void Poll();

		// - Summary -----------------------------------------------------------------
		// Returns whether we've been asked to shutdown the application by the system.
		// ---------------------------------------------------------------------------
		inline static bool HasReceivedCloseCallback() { return hasReceivedCloseCallback; }
		// - Summary -----------------------------------------------------------------
		// Returns whether the XrossMenuBar is currently being displayed.
		// ---------------------------------------------------------------------------
		inline static bool IsXMBOpen() { return isXMBOpen; }

	private:
		// - Summary -----------------------------------------------------------------
		// Handle the "CELL_SYSUTIL_REQUEST_EXITGAME" callback.
		// ---------------------------------------------------------------------------
		static void HandleRequestExitGameCallback(uint64_t status, uint64_t param, void* data);
		// - Summary -----------------------------------------------------------------
		// Handle the "CELL_SYSUTIL_SYSTEM_MENU_OPEN"/"CELL_SYSUTIL_SYSTEM_MENU_CLOSE" 
		// callbacks.
		// ---------------------------------------------------------------------------
		static void HandleXMBCallback(uint64_t status, uint64_t param, void* data);

		static bool hasReceivedCloseCallback;
		static bool isXMBOpen;
};