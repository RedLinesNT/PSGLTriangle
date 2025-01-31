#include "PSGLContext.h"

#include <cstdio>
#include <sysutil/sysutil_sysparam.h>

bool PSGLContext::Initialize(const unsigned int* resolutions, unsigned int numResolutions) {
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
    if (!IsVideoOutputReady()) { std::printf("[PSGLContext::Initialize] The system's video output is currently not ready. Waiting...\n"); }
    while (!IsVideoOutputReady()) {} //Wait for the video output to be ready
    std::printf("[PSGLContext::Initialize] System's video output is ready!\n");

    PSGLinitOptions glInitOptions;
    glInitOptions.enable = PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS;
    glInitOptions.maxSPUs = 1; //Raw SPU initialized in "Entry.cpp" (?)
    glInitOptions.initializeSPUs = false; //Already previously initialized in "Entry.cpp"
    glInitOptions.persistentMemorySize = 0;
    glInitOptions.transientMemorySize = 0;
    glInitOptions.errorConsole = 1;
    glInitOptions.fifoSize = 0;
    
    //From what I understand, this is the memory that I allow
    //PSGL to use. In my case I allocate half of the PlayStation3
    //retail memory available.
    //Retail consoles have 256MB of memory and REFERENCE STATIONS
    //have 512MB (I think, and might be the same case with some DEVKITS).
    glInitOptions.hostMemorySize = 128 * 1024*1024; //128MB

    psglInit(&glInitOptions); //Initialize PSGL

    //Find the best resolution available resolution from what we have...
    unsigned int bestResolutionID = PSGLContext::GetBestVideoMode(resolutions, numResolutions);
    if (bestResolutionID == 0) {
        std::printf("[PSGLContext::Initialize] Unable to initialize with the '%u' resolution modes given!\n", numResolutions);
        return false;
    }

    //The target rendering resolution
    unsigned int targetWidth = 0;
    unsigned int targetHeight = 0;
    PSGLContext::GetResolutionFromResolutionID(bestResolutionID, targetWidth, targetHeight);
    std::printf("[PSGLContext::Initialize] Requested resolution '%ux%u' is available and will be used...\n", targetWidth, targetHeight);

    //Create the PSGLDevice initialization parameters
    PSGLdeviceParameters params;
    params.enable = PSGL_DEVICE_PARAMETERS_COLOR_FORMAT | PSGL_DEVICE_PARAMETERS_DEPTH_FORMAT |
                    PSGL_DEVICE_PARAMETERS_MULTISAMPLING_MODE | PSGL_DEVICE_PARAMETERS_WIDTH_HEIGHT;
    params.width = targetWidth;
    params.height = targetHeight;
    params.colorFormat = GL_ARGB_SCE;
    params.depthFormat = GL_DEPTH_COMPONENT24;
    params.multisamplingMode = GL_MULTISAMPLING_NONE_SCE;

    glDevice = psglCreateDeviceExtended(&params);
    glContext = psglCreateContext();

    psglMakeCurrent(glContext, glDevice);
    psglResetCurrentContext();

    //Everything is created, now we'll set up the rest of PSGL stuff
    CreateViewport();
    CreateDefaultOrthographicEnvironment();

    //The PSGL doesn't clear up the screen after being initialized,
    //we'll do it now. Why? First off because the documentation told me so,
    //and also because there's a chance the 'PreRender' and 'PostRender'
    //methods won't be called directly after this one (to load content for example).
    //So we'll ensure everything has been cleared.
    //(I forgot if it's the case with OpenGL)
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //Should output grey
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    psglSwap();
    
    return true; //Everything is finally ready to be used!
}

void PSGLContext::Dispose() const {
    psglDestroyContext(glContext);
    psglDestroyDevice(glDevice);
    psglExit();
    
    std::printf("[PSGLContext::Dispose] PSGL has been disposed!\n");
}

void PSGLContext::PreRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void PSGLContext::PostRender() {
    glFlush();
    psglSwap();
}

void PSGLContext::CreateViewport() const {
    //Retrieve the target buffer's dimensions (rendering dimensions)
    unsigned int viewportWidth;
    unsigned int viewportHeight;
    psglGetRenderBufferDimensions(glDevice, &viewportWidth, &viewportHeight);

    //Set the viewport
    glViewport(0, 0, viewportWidth, viewportHeight); //(Explicit conversion between uint to int)
}

void PSGLContext::CreateDefaultOrthographicEnvironment() const {
    //Get the appropriate aspect ratio (width/height) and
    //set the correct projection for the Orthographic view
    //
    //This process (like many others) are quite the same as
    //simply using OpenGL with bindings (like with GLFW iirc).

    GLfloat aspectRatio = psglGetDeviceAspectRatio(glDevice);
    float left = aspectRatio;
    float right = -left;
    float top = 1;
    float bottom = -1;

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrthof(left, right, bottom, top, 0, 1);

    glDisable(GL_CULL_FACE);
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
