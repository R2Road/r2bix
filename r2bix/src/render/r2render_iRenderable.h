#pragma once

namespace r2render
{
	class Camera;

	class iRenderable
	{
	public:
		virtual void Render( const r2render::Camera* const camera ) = 0;
	};
}