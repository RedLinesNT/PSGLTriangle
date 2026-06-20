#include "Pad.h"
#include <cell\pad\libpad.h>
#include <sys\return_code.h>

Pad::Pad(uint8_t portid) : portid(portid), subscribers{} {}

void Pad::SubscribePressedFunc(E_PAD_BUTTON target, InputFunc func) {
	subscribers[(int)target] = func;
}

void Pad::UnsubscribePressedFunc(E_PAD_BUTTON target, InputFunc func) {
	if (subscribers[(int)target] != func) return;
	subscribers[(int)target] = nullptr;
}

void Pad::Poll(const CellPadData& data) const {
	if (data.len <= 0) return; //Nothing to do :)

	//Layout:
	//  data.button[2] -> Digital buttons
	//  data.button[3] -> More digital buttons
	//  data.button[4] -> Right JoyStick X
	//  data.button[5] -> Right JoyStick Y
	//  data.button[6] -> Left JoyStick X
	//  data.button[7] -> Left JoyStick Y
	//  data.button[8 <-> 19] -> "Pressure-Sensitive" buttons (Require "cellPadSetPortSetting" to handle)
	//  data.button[20 <-> 13] -> SIXAXIS (X,Y,Z) values (Require "cellPadSetPortSetting" to handle)

	if (data.button[2]) {
		for (int i = 0; i<(int)E_PAD_BUTTON::PAD_BUTTONS_MAX / 2; i++) {
			if (data.button[2] & (1 << i)) {
				if (subscribers[i]) subscribers[i](); //Got something to invoke
			}
		}
	}

	if (data.button[3]) {
		for (int i = 0; i<(int)E_PAD_BUTTON::PAD_BUTTONS_MAX / 2; i++) {
			if (data.button[3] & (1 << i)) {
				if (subscribers[(int)E_PAD_BUTTON::PAD_BUTTONS_MAX / 2 + i]) subscribers[(int)E_PAD_BUTTON::PAD_BUTTONS_MAX / 2 + i](); //Got something to invoke
			}
		}
	}
}

bool Pad::ClearBuffer() const {
	return cellPadClearBuf(portid) == CELL_OK;
}