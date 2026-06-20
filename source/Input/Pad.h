#pragma once

#include <cell\pad\pad_codes.h>
#include <list>

// - Summary -----------------------------------------------------------------
// Enumeration of the different buttons available on genuine 
// DualShock3/SIXAXIS controllers.
// ---------------------------------------------------------------------------
enum class E_PAD_BUTTON : int {
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

typedef void(*InputFunc)();

// - Remarks -----------------------------------------------------------------
// There is no implementation for "pressure-sensitive" buttons!
// ---------------------------------------------------------------------------
class Pad {
	friend class PadUtility;

	public:
		Pad(uint8_t portid);
		~Pad() = default;

		// - Summary -----------------------------------------------------------------
		// Invoke "func" when "target" is pressed.
		// ---------------------------------------------------------------------------
		void SubscribePressedFunc(E_PAD_BUTTON target, InputFunc func);
		// - Summary -----------------------------------------------------------------
		// Remove "func" from being invoked when "target" is pressed.
		// ---------------------------------------------------------------------------
		void UnsubscribePressedFunc(E_PAD_BUTTON target, InputFunc func);

	private:
		void Poll(const CellPadData& data) const;
		bool ClearBuffer() const;

		const uint8_t portid;
		InputFunc subscribers[(int)E_PAD_BUTTON::PAD_BUTTONS_MAX];
};