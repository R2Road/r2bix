#pragma once

namespace r2render
{
	class Camera;
	class iRenderTarget;

	class iRenderable
	{
	public:
		virtual void Render( const r2render::Camera* const camera, iRenderTarget* const render_target ) = 0;
	};
}