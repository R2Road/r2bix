#pragma once

#include <memory>

#include "r2/r2_PointInt.h"

namespace r2bix_render
{
	class Camera;
	class iRenderTarget;
}

namespace r2bix_node
{
	class Node;
}

namespace r2bix_component
{
	using ComponentUp = std::unique_ptr<class iComponent>;
	class iComponent
	{
	protected:
		iComponent( r2bix_node::Node& owner_node ) : mOwnerNode( owner_node )
		{}

	public:
		virtual ~iComponent()
		{}

	public:
		r2bix_node::Node& GetOwnerNode() const
		{
			return mOwnerNode;
		}

		virtual int GetStaticID() const = 0;

		virtual bool Init()
		{
			return true;
		}
		virtual void Update( const float /*delta_time*/ )
		{}
		virtual void Render( const r2bix_render::Camera* const /*camera*/, r2bix_render::iRenderTarget* const /*render_target*/, r2::PointInt /*offset*/ )
		{}

	protected:
		r2bix_node::Node& mOwnerNode;
	};
}