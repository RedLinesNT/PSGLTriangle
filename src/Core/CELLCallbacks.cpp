#include "CELLCallbacks.h"
#include "Core.cpp"

bool CELLCallbacks::hasReceivedCloseCallback = false;
bool CELLCallbacks::isTheXMBOpen = false;


//-----------------------------------------------------------------------------
// Description: Bind "HandleCallbacks(uint64_t, uint64_t, void*)" as the
//				method who'll receive the system callbacks.
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void CELLCallbacks::BindCallbacks() {
	cellSysutilRegisterCallback(0, HandleCallbacks, nullptr);
}

//-----------------------------------------------------------------------------
// Description: Unbind "HandleCallbacks(uint64_t, uint64_t, void*)" from
//				receiving system callbacks.
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void CELLCallbacks::UnbindCallbacks() {
	cellSysutilUnregisterCallback(0);
}

//-----------------------------------------------------------------------------
// Description: Check for incoming system callbacks.
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void CELLCallbacks::Update() {
	cellSysutilCheckCallback();
}

//-----------------------------------------------------------------------------
// Description: Handle every supported system callbacks.
// Parameters:
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void CELLCallbacks::HandleCallbacks(uint64_t status, uint64_t param, void* userdata) {
	(void)param;
	(void)userdata;

	switch (status) {
		case CELL_SYSUTIL_REQUEST_EXITGAME: {
			DEBUG_PRINT("CELL_SYSUTIL_REQUEST_EXITGAME\n")
			hasReceivedCloseCallback = true;
			break;
		}
		case CELL_SYSUTIL_SYSTEM_MENU_OPEN: {
			DEBUG_PRINT("CELL_SYSUTIL_SYSTEM_MENU_OPEN\n")
			isTheXMBOpen = true;
			break;
		}
		case CELL_SYSUTIL_SYSTEM_MENU_CLOSE: {
			DEBUG_PRINT("CELL_SYSUTIL_SYSTEM_MENU_CLOSE\n")
			isTheXMBOpen = false;
			break;
		}

		default: //Unsupported
			break;
	}
}