#include "pch.h"
#include "r2node_SceneNode.h"

#include "base/r2base_Director.h"
#include "component/r2component_TransformComponent.h"

namespace r2node
{
	SceneNode::SceneNode( r2base::Director& director ) : r2base::Node( director )
		, mKeyboardInputCollector()
		, mCamera( { director.GetScreenBufferSize().GetWidth() / 2, director.GetScreenBufferSize().GetHeight() / 2 }, director.GetScreenBufferSize() )
		, mRenderTarget( director.GetScreenBufferSize().GetWidth(), director.GetScreenBufferSize().GetHeight(), '@' )
	{}

	void SceneNode::Update( const float delta_time )
	{
		mKeyboardInputCollector.Collect();

		r2base::Node::Update( delta_time );
	}

	void SceneNode::Render()
	{
		mRenderTarget.FillAll( ' ' );

		r2base::Node::Render( &mCamera, &mRenderTarget, mTransformComponent->GetPosition() );

		mDirector.Write2BackBuffer( &mRenderTarget );
	}

	void SceneNode::AddInputListener( r2input::KeyboardInputListener* const keyboard_input_listener )
	{
		mKeyboardInputCollector.AddListener( keyboard_input_listener );
	}
}