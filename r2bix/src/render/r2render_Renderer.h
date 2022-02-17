#pragma once

#include <list>

namespace r2render
{
	class Camera;
	class iRenderable;

	class Renderer
	{
	public:
		using ContainerT = std::list<iRenderable*>;

		Renderer();

		void SetCamera( Camera* const camera )
		{
			mCamera = camera;
		}

		void Clear();
		void Add( iRenderable* const renderable );

		void Draw();

	private:
		Camera* mCamera;
		ContainerT mContainer;
	};
}