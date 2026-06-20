#include "SystemCallback.h"
#include "Core.h"

enum class E_SYSTEM_CALLBACK_SLOT : int {
	REQUEST_EXIT_GAME = 0,
	XMB_STATUS = 1,
};

bool SystemCallback::hasReceivedCloseCallback = false;
bool SystemCallback::isXMBOpen = false;

void SystemCallback::Subscribe() {
	cellSysutilRegisterCallback((int)E_SYSTEM_CALLBACK_SLOT::REQUEST_EXIT_GAME, HandleRequestExitGameCallback, nullptr);
	cellSysutilRegisterCallback((int)E_SYSTEM_CALLBACK_SLOT::XMB_STATUS, HandleXMBCallback, nullptr);
}

void SystemCallback::Unsubscribe() {
	cellSysutilUnregisterCallback((int)E_SYSTEM_CALLBACK_SLOT::REQUEST_EXIT_GAME);
	cellSysutilUnregisterCallback((int)E_SYSTEM_CALLBACK_SLOT::XMB_STATUS);
}

void SystemCallback::Poll() {
	cellSysutilCheckCallback();
}

void SystemCallback::HandleRequestExitGameCallback(uint64_t status, uint64_t param, void* data) {
	(void)param;
	(void)data;

	if (status == CELL_SYSUTIL_REQUEST_EXITGAME) {
		hasReceivedCloseCallback = true;
		PRINT("SystemCallback - Received CELL_SYSUTIL_REQUEST_EXITGAME event!\n")
	}
}

void SystemCallback::HandleXMBCallback(uint64_t status, uint64_t param, void* data) {
	(void)param;
	(void)data;

	if (status == CELL_SYSUTIL_SYSTEM_MENU_OPEN) {
		isXMBOpen = true;
		PRINT("SystemCallback - Received CELL_SYSUTIL_SYSTEM_MENU_OPEN event!\n")
	} else if (status == CELL_SYSUTIL_SYSTEM_MENU_CLOSE) {
		isXMBOpen = false;
		PRINT("SystemCallback - Received CELL_SYSUTIL_SYSTEM_MENU_CLOSE event!\n")
	}
}