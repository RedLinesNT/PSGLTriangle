#include "Renderer.h"
#include "Core/Core.h"

GraphicsContext* Renderer::context = nullptr;

bool Renderer::Initialize(const unsigned int* cellResolutionIDs, unsigned int count) {
	if (context != nullptr) {
		DEBUG_PRINT("[Renderer] The renderer is already initialized!")
		return true;
	}

	context = new GraphicsContext();
	if (!context->Initialize(cellResolutionIDs, count)) {
		DEBUG_PRINT("[Renderer] Failed to set up the context!")
		return false;
	}

	DEBUG_PRINT("[Renderer] Initialized")
	return true;
}

void Renderer::Shutdown() {
	context->Dispose();
	delete context;

	DEBUG_PRINT("[Renderer] Shutdown")
}

void Renderer::PreRender() {
	context->PreRender();
}

void Renderer::Render(float deltaTime, Camera* camera) {
	if (camera == nullptr) return;

}

void Renderer::PostRender() {
	context->PostRender();
}