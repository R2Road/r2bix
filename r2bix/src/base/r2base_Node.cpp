#include "pch.h"
#include "r2base_Node.h"

#include "component/r2component_TransformComponent.h"

namespace r2base
{
	Node::Node( Director& director ) :
		mDirector( director )
		, mComponentContainer()
		, mChildContainer()

		, mTransformComponent( nullptr )
	{}

	bool Node::Init()
	{
		//
		// Transform
		//
		auto component = r2component::TransformComponent::Create( *this );
		mTransformComponent = component.get();
		AddComponent( std::move( component ) );

		return true;
	}

	void Node::Update()
	{
		for( auto& c : mChildContainer )
		{
			c->Update();
		}
	}

	void Node::Render( const r2render::Camera* const camera, r2render::iRenderTarget* const render_target, r2::PointInt offset )
	{
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

	void Node::AddComponent( r2base::ComponentUp component )
	{
		mComponentContainer.push_back( std::move( component ) );
	}

	void Node::AddChild( r2base::NodeUp child_node )
	{
		mChildContainer.push_back( std::move( child_node ) );
	}
}