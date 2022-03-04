#include "pch.h"
#include "r2base_Node.h"

namespace r2base
{
	Node::Node( Director& director ) :
		mDirector( director )
		, mComponentContainer()
		, mChildContainer()
	{}

	void Node::Update()
	{
		for( auto& c : mChildContainer )
		{
			c->Update();
		}
	}

	void Node::Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target )
	{
		for( auto& c : mComponentContainer )
		{
			c->Render( camera, render_target );
		}

		for( auto& c : mChildContainer )
		{
			c->Render( camera, render_target );
		}
	}

	void Node::AddComponent( r2base::ComponentUp component )
	{
		mComponentContainer.push_back( std::move( component ) );
	}

	void Node::AddChild( r2base::NodeUp child_node )
	{
		mChildContainer.push_back( std::move( child_node ) );
	}
}