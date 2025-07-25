#pragma once

#include "cell/pad/pad_codes.h"

//-----------------------------------------------------------------------------
// Each button of a PlayStation3 SIXAXIS/DualShock3 controller.
//-----------------------------------------------------------------------------
enum E_PAD_BUTTONS {
	SELECT = 0,
	L3 = 1,
	R3 = 2,
	START = 3,

	DPAD_UP = 4,
	DPAD_RIGHT = 5,
	DPAD_DOWN = 6,
	DPAD_LEFT = 7,

	L2 = 8,
	R2 = 9,
	L1 = 10,
	R1 = 11,

	TRIANGLE = 12,
	CIRCLE = 13,
	CROSS = 14,
	SQUARE = 15,

	PAD_BUTTONS_MAX,
};

typedef void (*InputCallbackFunc)();

//-----------------------------------------------------------------------------
// Simple and primitive implementation to get input data
// from a PlayStation3 controller.
// Notes:
//      There's no support for "pressure-sensitive" buttons such as
//      the joysticks and triggers.
//-----------------------------------------------------------------------------
class Pad {
	friend class PadUtility;

public:
	Pad(uint8_t portID);
	~Pad();

	//-----------------------------------------------------------------------------
	// Bind a "void" method that'll be invoked when a specific button has been 
	// pressed on this pad.
	//-----------------------------------------------------------------------------
	void SetPressedFunc(E_PAD_BUTTONS button, InputCallbackFunc func);
	//-----------------------------------------------------------------------------
	// Unbind a "void" method from being invoked when a specific button has been 
	// pressed on this pad.
	//-----------------------------------------------------------------------------
	void RemovePressedFunc(E_PAD_BUTTONS button, InputCallbackFunc func);

	inline bool IsPadConnected() const { return isPadConnected; }

private:
	void Update(const CellPadData& data, const CellPadInfo2& info);
	bool ClearPadBuffer() const;

private:
	const uint8_t portID;
	InputCallbackFunc pressedCallbacks[PAD_BUTTONS_MAX];

	bool isPadConnected;
};