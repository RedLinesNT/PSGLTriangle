#include "PSGLContext.h"

#include <cstdio>
#include <sysutil/sysutil_sysparam.h>

bool PSGLContext::Initialize() {
    //Based on Sony's documentation, the system's video output MUST
    //be ready and available before fully initializing PSGL (which is fair).
    //
    //The documentation and examples recommend doing/starting background
    //tasks during this process because if the system is using
    //HDMI the video output might take some time to be fully ready.
    //Composite (non-HDMI) should skip these lines being always
    //available.
    //
    //For this project, waiting for the video output to be ready won't ever
    //be an issue, but in the case of a game, we should start some tasks in
    //background to boot a bit faster our "game".
    if (!IsVideoOutputReady()) { std::printf("[PSGLContext::Initialize()] The system's video output is currently not ready. Waiting...\n"); }
    while (!IsVideoOutputReady()) {} //Wait for the video output to be ready

    std::printf("[PSGLContext::Initialize()] System's video output is ready!\n");

    return true;
}

bool PSGLContext::IsVideoOutputReady() {
    //Retrieve the current video state
    CellVideoOutState currVideoState;
    cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &currVideoState);

    return currVideoState.state == CELL_VIDEO_OUT_OUTPUT_STATE_ENABLED;
}

int PSGLContext::GetResolutionFromResolutionID(unsigned int resolutionID, unsigned int& width, unsigned int& height) {
    switch (resolutionID) {
        //Standard resolution modes
        case CELL_VIDEO_OUT_RESOLUTION_480: width=720; height=480; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_576: width=720; height=576; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_720: width=1280; height=720; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_1080: width=1920; height=1080; return 1;

        //Lower rendering resolution, buffer (hardware) upscaled to 1080p
        case CELL_VIDEO_OUT_RESOLUTION_1600x1080: width=1600; height=1080; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_1440x1080: width=1440; height=1080; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_1280x1080: width=1280; height=1080; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_960x1080: width=960;  height=1080; return 1;
        
        default: break;
    }

    //Invalid modes
    //I don't think there's a human way of actually falling here
    //outside purposefully inputting wrong values (?). But we never know,
    //the documentation think it's better to do that way (and I do too).
    std::printf("[PSGLContext::GetResolutionFromResolutionID] ResolutionID '%u' isn't valid or "
                "unsupported!\n'", resolutionID);
    return 0;
}

unsigned int PSGLContext::GetBestVideoMode(const unsigned int* resolutions, unsigned int numResolutions) {
    for (unsigned int i=0; i<numResolutions; i++) {
        if (cellVideoOutGetResolutionAvailability(CELL_VIDEO_OUT_PRIMARY, resolutions[i], CELL_VIDEO_OUT_ASPECT_AUTO, 0)) {
            return resolutions[i]; //Yay! a wanted resolution is available!
        }
    }

    return 0; //Nothing is available :(
}
