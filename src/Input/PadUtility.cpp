#include "PadUtility.h"
#include "cell/pad/libpad.h"
#include "sys/return_code.h"
#include "Core/Core.h"

std::list<Pad*> PadUtility::pads;

void PadUtility::Initialize(uint8_t maxPads) {
	if (cellPadInit(maxPads) != CELL_OK) {
		DEBUG_PRINT("[PadUtility] Failed to initialize!\n")
		return;
	}

	for (int i = 0; i < maxPads; i++) {
		Pad* pad = new Pad((uint8_t)i);
		pads.push_back(pad);
	}

	DEBUG_PRINT("[PadUtility] Initialized %i pads\n", (maxPads+1))
}

void PadUtility::Dispose() {
	for (Pad* pad : pads) {
		//ClearPadBuffers() is called for each pad when deleting them
		delete pad;
	}

	cellPadEnd();
	DEBUG_PRINT("[PadUtility] Disposed!\n")
}

void PadUtility::Update() {
	CellPadData padData;
	CellPadInfo2 padsInfo;
	cellPadGetInfo2(&padsInfo);

	for (Pad* pad : pads) {
		cellPadGetData(pad->portID, &padData);
		pad->Update(padData, padsInfo);
	}
}

void PadUtility::ClearPadBuffers() {
	for (Pad* pad : pads) {
		if (!pad->ClearPadBuffer()) {
			DEBUG_PRINT("[PadUtility] 'cellPadClearBuf' failed on controller %u!\n", pad->portID)
		}
	}
}

Pad& PadUtility::GetPad(uint8_t portID) {
	for (Pad* pad : pads) {
		if (pad->portID == portID) return *pad;
	}

	return *pads.front();
}

bool PadUtility::IsPadConnected(uint8_t portID) {
	for (Pad* pad : pads) {
		if (pad->portID == portID) return pad->IsPadConnected();
	}

	return false;
}