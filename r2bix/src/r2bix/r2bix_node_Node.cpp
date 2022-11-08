#include "r2bix_node_Node.h"

namespace r2bix_node
{
	Node::Node( r2bix::Director& director ) :
		mDirector( director )
		, mbVisible( true )
		, mComponentContainer()
		, mChildContainer()

		, mTransformComponent( nullptr )
	{}

	std::unique_ptr<Node> Node::Create( r2bix::Director& director )
	{
		std::unique_ptr<Node> ret( new ( std::nothrow ) Node( director ) );
		if( !ret || !ret->Init() )
		{
			ret.reset();
		}

		return ret;
	}

	bool Node::Init()
	{
		//
		// Transform
		//
		mTransformComponent = AddComponent<r2bix_component::TransformComponent>();

		return true;
	}

	void Node::Update( const float delta_time )
	{
		for( auto& c : mComponentContainer )
		{
			c->Update( delta_time );
		}

		for( auto& c : mChildContainer )
		{
			c->Update( delta_time );
		}
	}

	void Node::Render( const r2bix_render::Camera* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt offset )
	{
		if( !mbVisible )
		{
			return;
		}

		for( auto& c : mComponentContainer )
		{
			c->Render( camera, render_target, offset );
		}

		offset += mTransformComponent->GetPosition();
		for( auto& c : mChildContainer )
		{
			c->Render( camera, render_target, offset );
		}
	}
}