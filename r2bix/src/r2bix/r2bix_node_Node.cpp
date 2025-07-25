#include "r2bix_node_Node.h"

namespace r2bix_node
{
	Node::Node( r2bix::Director& director ) :
		  mName()

		, mDirector( director )

		, mbVisible( true )
		, mSignal4VisibleFlagChange()

		, mComponentContainer()

		, mParentNode( nullptr )
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

	void Node::Enter()
	{
		for( auto& c : mComponentContainer )
		{
			c->Enter();
		}
	}
	void Node::Exit()
	{
		for( auto& c : mComponentContainer )
		{
			c->Exit();
		}
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

	void Node::Render( const r2bix::Camera* const camera, r2bix_render::iRenderTarget* const render_target, r2::PointInt offset )
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

	void Node::Terminate()
	{
		for( auto& c : mComponentContainer )
		{
			c->Terminate();
		}

		ClearAllChild();
	}



	Node* Node::GetChildByName( const std::string_view name ) const
	{
		for( auto& c : mChildContainer )
		{
			if( name == c->GetName() )
			{
				return c.get();
			}
		}

		Node* ret = nullptr;

		for( auto& c : mChildContainer )
		{
			ret = c->GetChildByName( name );
			if( ret )
			{
				break;
			}
		}

		return ret;
	}



	void Node::ClearAllChild()
	{
		for( auto& c : mChildContainer )
		{
			c->Terminate();
		}

		mChildContainer.clear();
	}
}