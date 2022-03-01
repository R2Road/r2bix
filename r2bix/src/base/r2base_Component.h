#pragma once

#include <memory>

namespace r2render
{
	class Camera;
	class iRenderTarget;
}

namespace r2base
{
	class Node;

	using ComponentUp = std::unique_ptr<class Component>;
	class Component
	{
	protected:
		Component( Node& owner_node ) : mOwnerNode( owner_node ) {}
	public:
		virtual ~Component() {}

	public:
		virtual bool Init() { return true; }
		virtual void Update() {}
		virtual void Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target ) {}

	protected:
		Node& mOwnerNode;
	};
}