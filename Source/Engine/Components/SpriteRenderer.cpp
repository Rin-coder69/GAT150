#include "RendererComponents.h"
#include "Render/Renderer.h"
#include "SpriteRenderer.h"

namespace gaia {
	void SpriteRenderer::Draw(Renderer& renderer) {
		auto texture = Resources().Get<Texture>(textureName, renderer);
	
			owner->transform.position.x,
			owner->transform.position.y, 
			owner->transform.rotation,
			owner->transform.scale;
	}

	void SpriteRenderer::Update(float dt)
	{
	}
}