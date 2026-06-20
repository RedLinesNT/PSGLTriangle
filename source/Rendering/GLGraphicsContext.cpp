#include "GLGraphicsContext.h"
#include "..\Core\Core.h"

GLGraphicsContext::GLGraphicsContext() {
	context = nullptr;
	device = nullptr;
	viewportWidth = 0;
	viewportHeight = 0;
	viewportAspectRatio = 0;
	isVSyncEnabled = false;
}

GLGraphicsContext::~GLGraphicsContext() = default;

bool GLGraphicsContext::Initialize(const unsigned int* resolutionIDs, unsigned int num) {
	//First you need to wait for the PlayStation(R)3 to be ready to draw anything.
	//Based on Sony's documentation, when using an HDMI connection, the video output is ready on the spot. But it'll be better to actually
	//run some tests to see if they "lied". :)
	//During that phase, we shouldn't lock up the entire thread waiting for the system but rather start background tasks that doesn't rely
	//on rendering stuff. (FileSystem, Audio, ...)
	if (!IsDeviceVideoOutputReady()) { PRINT("GLGraphicsContext - Waiting for the PlayStation(R)3's output to be ready...\n") }
	while (!IsDeviceVideoOutputReady()) {}

	PSGLinitOptions glInitOptions;
	glInitOptions.enable = PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS | PSGL_INIT_HOST_MEMORY_SIZE; //Options that we will be defining ourselves
	//Max amount of Raw SPU Used by PSGL | Whether PSGL should automatically initialize the CELL's SPUs | Memory size for PSGL
	glInitOptions.maxSPUs = 1;
	glInitOptions.initializeSPUs = false;
#if _DEBUG	
	glInitOptions.enable |= PSGL_INIT_ERROR_CONSOLE;
	glInitOptions.errorConsole = 1;
#endif
	//Retail PlayStation(R)3 systems have 256MB of VRAM for the RSX.
	//IIRC unlike the Xbox360, the memory isn't shared between the CPU and GPU. The CELL has another 256MB of memory for itself.
	//By default, PSGL seem to only define "128MB" to use. 
	//It is unclear (atleast for me) what goes and what doesn't go under that memory PSGL is taking for himself.
	//I should be reading more documentation...
	glInitOptions.hostMemorySize = 128 * 1024*1024; //128MB

	psglInit(&glInitOptions);

	//Find the best resolution available from what has been given
	unsigned int bestResolutionIndex = GetBestVideoOutputMode(resolutionIDs, num);
	if (bestResolutionIndex == 0) {
		PRINT("GLGraphicsContext - Failed to find any video mode available amongst the '%u' modes given!\n", num)
		return false;
	}

	unsigned int targetWidth = 0;
	unsigned int targetHeight = 0;
	GetResolutionFromCellResolutionID(bestResolutionIndex, targetWidth, targetHeight);
	PRINT("GLGraphicsContext - Output resolution taken: '%ux%u'.\n", targetWidth, targetHeight)

	PSGLdeviceParameters params;
	params.enable = PSGL_DEVICE_PARAMETERS_COLOR_FORMAT | PSGL_DEVICE_PARAMETERS_DEPTH_FORMAT | PSGL_DEVICE_PARAMETERS_MULTISAMPLING_MODE | PSGL_DEVICE_PARAMETERS_WIDTH_HEIGHT; //Options that we will be defining ourselves
	params.width = targetWidth;
	params.height = targetHeight;
	//params.renderWidth = PLACEHOLDER;
	//params.renderHeight = PLACEHOLDER;
	params.colorFormat = GL_ARGB_SCE;
	params.depthFormat = GL_DEPTH_COMPONENT24;
	params.multisamplingMode = GL_MULTISAMPLING_4X_SQUARE_CENTERED_SCE;

	device = psglCreateDeviceExtended(&params);
	context = psglCreateContext();
	viewportAspectRatio = psglGetDeviceAspectRatio(device);

	psglMakeCurrent(context, device);
	psglResetCurrentContext();

	CreateViewport();

	//Note: PSGL doesn't clear up the screen after being initialized
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	psglSwap();

	return true;
}

void GLGraphicsContext::Dispose() const {
	psglDestroyContext(context);
	psglDestroyDevice(device);
	psglExit();
}

void GLGraphicsContext::PreRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (isVSyncEnabled) glEnable(GL_VSYNC_SCE);
	else glDisable(GL_VSYNC_SCE);
}

void GLGraphicsContext::PostRender() {
	psglSwap();
}

void GLGraphicsContext::CreateViewport() {
	psglGetRenderBufferDimensions(device, &viewportWidth, &viewportHeight);

	glViewport(0, 0, (GLsizei)viewportWidth, (GLsizei)viewportHeight);
	glScissor(0, 0, (GLsizei)viewportWidth, (GLsizei)viewportHeight);
}

bool GLGraphicsContext::IsDeviceVideoOutputReady() {
	CellVideoOutState currVideoState;
	cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &currVideoState);

	return currVideoState.state == CELL_VIDEO_OUT_OUTPUT_STATE_ENABLED;
}

int GLGraphicsContext::GetResolutionFromCellResolutionID(unsigned int resolutionID, unsigned int& width, unsigned int& height){
	switch (resolutionID) {
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

	PRINT("GLGraphicsContext - CellVideoOutResolutionId '%u' is invalid or unsupported!\n'", resolutionID)
		return 0;
}

unsigned int GLGraphicsContext::GetBestVideoOutputMode(const unsigned int* resolutionIDs, const unsigned int num) {
	for (unsigned int i = 0; i<num; i++) {
		if (cellVideoOutGetResolutionAvailability(CELL_VIDEO_OUT_PRIMARY, resolutionIDs[i], CELL_VIDEO_OUT_ASPECT_AUTO, 0)) {
			return resolutionIDs[i];
		}
	}

	return 0; //:(
}