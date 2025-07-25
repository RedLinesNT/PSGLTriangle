#include "Pad.h"
#include "cell/pad/libpad.h"
#include "sys/return_code.h"

Pad::Pad(uint8_t portID) : portID(portID), pressedCallbacks{}, isPadConnected(false) {}

Pad::~Pad() {
	ClearPadBuffer();
}

void Pad::SetPressedFunc(E_PAD_BUTTONS button, InputCallbackFunc func) {
	pressedCallbacks[button] = func;
}

void Pad::RemovePressedFunc(E_PAD_BUTTONS button, InputCallbackFunc func) {
	if (pressedCallbacks[button] != func) return;
	pressedCallbacks[button] = nullptr;
}

void Pad::Update(const CellPadData& data, const CellPadInfo2& info) {
	if (data.len <= 0) return;

	//Layout of a PS3 Pad:
	//   data.button[2] -> Digital buttons
	//   data.button[3] -> More digital buttons
	//   data.button[4] -> Right JoyStick X
	//   data.button[5] -> Right JoyStick Y
	//   data.button[6] -> Left JoyStick X
	//   data.button[7] -> Left JoyStick Y
	//   data.button[8 <-> 19] -> "Pressure-sensitive" buttons (Require "cellPadSetPortSetting" to handle) 
	//   data.button[20 <-> 23] -> SIXAXIS (X, Y, Z) values (Requires "cellPadSetPortSetting" to handle)

	if (data.button[2]) {
		for (int i = 0; i < PAD_BUTTONS_MAX / 2; i++) {
			if (data.button[2] & (1 << i)) {
				if (pressedCallbacks[i]) pressedCallbacks[i](); //We got something, invoke!
			}
		}
	}

	if (data.button[3]) {
		for (int i = 0; i < PAD_BUTTONS_MAX / 2; i++) {
			if (data.button[3] & (1 << i)) {
				if (pressedCallbacks[PAD_BUTTONS_MAX / 2 + i]) pressedCallbacks[PAD_BUTTONS_MAX / 2 + i](); //We got something, invoke!
			}
		}
	}

	if (info.port_status[portID] == CELL_PAD_STATUS_CONNECTED) {
		isPadConnected = true;
	} else if (info.port_status[portID] == CELL_PAD_STATUS_DISCONNECTED) {
		isPadConnected = false;
	}
}

bool Pad::ClearPadBuffer() const {
	return cellPadClearBuf(portID) == CELL_OK;
}