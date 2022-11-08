#pragma once

#include "r2bix_node_Node.h"

#include "r2bix_render_Camera.h"
#include "r2bix_render_Texture.h"

namespace r2bix
{
	class Director;
}

namespace r2bix_node
{
	using SceneNodeUp = std::unique_ptr<class SceneNode>;

	class SceneNode : public r2bix_node::Node
	{
	public:
		SceneNode( r2bix::Director& director );

		static SceneNodeUp Create( r2bix::Director& director );

		//
		// Override
		//
	private:
		void Render( const r2bix_render::Camera* const /*camera*/, r2bix_render::iRenderTarget* const /*render_target*/, r2::PointInt /*offset*/ ) override {}

		//
		//
		//
	public:
		void Render();

	protected:
		r2bix_render::Camera mCamera;
		r2bix_render::Texture mRenderTarget;
	};
}