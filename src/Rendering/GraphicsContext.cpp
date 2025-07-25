#include "GraphicsContext.h"
#include "Core/Core.h"

GraphicsContext::GraphicsContext() {
	psglContext = nullptr;
	psglDevice = nullptr;
	viewportWidth = 0;
	viewportHeight = 0;
	aspectRatio = 0;
	isVSyncEnabled = false;
}

GraphicsContext::~GraphicsContext() = default;

bool GraphicsContext::Initialize(const unsigned int* cellResolutionIDs, unsigned int count) {
	if (!IsVideoOutputReady()) {
		DEBUG_PRINT("[GraphicsContext] Waiting for the system's video output...\n")
	}

	//Currently, this freeze the whole application.
	//It would be a great idea to keep up with some background tasks while doing so.
	//That may be achieved by using multiple threads and leaving this one stuck while
	//the video output isn't ready
	while (!IsVideoOutputReady()) {} //Wait


	PSGLinitOptions glInitOptions;
	glInitOptions.enable = PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS; //Bitfield of the options we'd like to tweak
	glInitOptions.maxSPUs = 1; //1 Raw SPU for large operation with the RSX (Recommended)
	glInitOptions.initializeSPUs = false; //Already initialized at startup
#if _DEBUG
	glInitOptions.enable |= PSGL_INIT_ERROR_CONSOLE;
	glInitOptions.errorConsole = true;
#endif
	//HostMemorySize is the size of host memory allocated for the RSX. 
	//Host memory is used for system memory textures and buffer objects (vertex/pixel buffer objects).
	//The default value is "160MB"
	//glInitOptions.hostMemorySize = 128 * 1024 * 1024;

	psglInit(&glInitOptions);


	unsigned int bestResolutionID = GetBestVideoOutputID(cellResolutionIDs, count);
	if (bestResolutionID == 0) {
		DEBUG_PRINT("[GraphicsContext] Failed to find any video mode available amongst the '%u' modes given!\n", count);
		return false;
	}

	unsigned int targetResolutionWidth = 0;
	unsigned int targetResolutionHeight = 0;
	GetResolutionFromCELLResolutionID(bestResolutionID, targetResolutionWidth, targetResolutionHeight);
	DEBUG_PRINT("[GraphicsContext] Target resolution '%ux%u'\n", targetResolutionWidth, targetResolutionHeight);


	PSGLdeviceParameters devParams;
	devParams.enable = PSGL_DEVICE_PARAMETERS_COLOR_FORMAT | PSGL_DEVICE_PARAMETERS_DEPTH_FORMAT |
		PSGL_DEVICE_PARAMETERS_MULTISAMPLING_MODE | PSGL_DEVICE_PARAMETERS_WIDTH_HEIGHT; //Bitfield of the options we'd like to tweak
	devParams.width = targetResolutionWidth;
	devParams.height = targetResolutionHeight;
	devParams.colorFormat = GL_ARGB_SCE;
	devParams.depthFormat = GL_DEPTH_COMPONENT24;
	devParams.multisamplingMode = GL_MULTISAMPLING_4X_SQUARE_CENTERED_SCE;

	psglDevice = psglCreateDeviceExtended(&devParams);
	psglContext = psglCreateContext();
	aspectRatio = psglGetDeviceAspectRatio(psglDevice);

	psglMakeCurrent(psglContext, psglDevice);
	psglResetCurrentContext();

	CreateViewport(); //Setup the viewport

	//PSGL doesn't clear up the screen after being initialized, do it now...
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	psglSwap();

	return true;
}

void GraphicsContext::Dispose() const {
	psglDestroyContext(psglContext);
	psglDestroyDevice(psglDevice);
	psglExit();
}

void GraphicsContext::PreRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (isVSyncEnabled) glEnable(GL_VSYNC_SCE);
	else glDisable(GL_VSYNC_SCE);
}

void GraphicsContext::PostRender() {
	psglSwap();
}

void GraphicsContext::CreateViewport() {
	psglGetRenderBufferDimensions(psglDevice, &viewportWidth, &viewportHeight);

	//Set the viewport
	glViewport(0, 0, (GLsizei)viewportWidth, (GLsizei)viewportHeight);
	glScissor(0, 0, (GLsizei)viewportWidth, (GLsizei)viewportHeight);
}

bool GraphicsContext::IsVideoOutputReady() {
	CellVideoOutState currVideoState;
	cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &currVideoState);

	return currVideoState.state == CELL_VIDEO_OUT_OUTPUT_STATE_ENABLED;
}

int GraphicsContext::GetResolutionFromCELLResolutionID(unsigned int cellResolutionID, unsigned int& width, unsigned int& height){
	switch (cellResolutionID) {
		//Standard resolution modes
		case CELL_VIDEO_OUT_RESOLUTION_480: width = 720; height = 480; return 1;
		case CELL_VIDEO_OUT_RESOLUTION_576: width = 720; height = 576; return 1;
		case CELL_VIDEO_OUT_RESOLUTION_720: width = 1280; height = 720; return 1;
		case CELL_VIDEO_OUT_RESOLUTION_1080: width = 1920; height = 1080; return 1;

		//Lower rendering resolution, buffer (hardware) upscaled to 1080p
		case CELL_VIDEO_OUT_RESOLUTION_1600x1080: width = 1600; height = 1080; return 1;
		case CELL_VIDEO_OUT_RESOLUTION_1440x1080: width = 1440; height = 1080; return 1;
		case CELL_VIDEO_OUT_RESOLUTION_1280x1080: width = 1280; height = 1080; return 1;
		case CELL_VIDEO_OUT_RESOLUTION_960x1080: width = 960;  height = 1080; return 1;

		default: break;
	}

	DEBUG_PRINT("[GraphicsContext] CellVideoOutResolutionId '%u' is invalid or unsupported!\n'", cellResolutionID)
	return 0;
}

unsigned int GraphicsContext::GetBestVideoOutputID(const unsigned int* wantedCellResolutionIDs, const unsigned int count) {
	for (unsigned int i = 0; i<count; i++) {
		if (cellVideoOutGetResolutionAvailability(CELL_VIDEO_OUT_PRIMARY, wantedCellResolutionIDs[i], CELL_VIDEO_OUT_ASPECT_AUTO, 0)) {
			return wantedCellResolutionIDs[i]; //Yay! a wanted resolution is available!
		}
	}

	return 0; //Nothing is available :(
}