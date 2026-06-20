#include "PadUtility.h"
#include "..\Core\Core.h"

std::list<Pad*> PadUtility::pads; //Initialized in "Setup"

void PadUtility::Setup(uint8_t num) {
	int32_t initResult = cellPadInit(num);
	if (initResult != CELL_OK) {
		PRINT("PadUtility - Failed to initialize! 'cellPadInit' returned '%u'.\n", initResult)
		return;
	}

	for (int i = 0; i < num; i++) {
		Pad* pad = new Pad((uint8_t)i);
		pads.push_back(pad);
	}

	PRINT("PadUtility - Initialized %i pads.\n", num+1)
}

void PadUtility::Dispose() {
	cellPadEnd();

	for (Pad* pad : pads) {
		delete pad;
	}
}

void PadUtility::Poll() {
	CellPadData data;

	for (Pad* pad : pads) {
		cellPadGetData(pad->portid, &data);
		pad->Poll(data);
	}
}

void PadUtility::ClearPadBuffers() {
	for (Pad* pad : pads) {
		if (!pad->ClearBuffer()) {
			PRINT("PadUtility - Failed to clear the buffer of pad %u.\n", pad->portid)
		}
	}
}

Pad& PadUtility::GetPad(uint8_t index) {
	for (Pad* pad : pads) {
		if (pad->portid == index) return *pad;
	}

	return *pads.front();
}