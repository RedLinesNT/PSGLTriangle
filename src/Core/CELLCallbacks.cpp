#include "CELLCallbacks.h"
#include "Core.h"

bool CELLCallbacks::hasReceivedCloseCallback = false;
bool CELLCallbacks::isTheXMBOpen = false;

void CELLCallbacks::BindCallbacks() {
	cellSysutilRegisterCallback(0, HandleCallbacks, nullptr);
}

void CELLCallbacks::UnbindCallbacks() {
	cellSysutilUnregisterCallback(0);
}

void CELLCallbacks::Update() {
	cellSysutilCheckCallback();
}

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